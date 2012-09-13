#!/usr/bin/perl -w

# THIS CODE PERFORMS COMMON SUBEXPRESSION ELIMINATION IN THE DIRECTION
# OF THE LONGEST REGISTER BLOCK DIMENSION FOR THE 3D 27-POINT STENCIL

### THESE PARAMETERS SPECIFY WHAT CODE IS GENERATED AND COMPILED ###

# choose "float" or "double" calculations
$precision = "double";

# read from "array" or "variable"
@read_from_types = ("array", "variable");

# "fixed" or "moving" pointers
@pointer_types = ("fixed", "moving");

# single ptr per "register_block", "plane", or "pencil"
@neighbor_index_types = ("register_block", "plane", "pencil");

# register block sizes (starts at 1)
@rb_sizes = ([1,1,1], [1,1,2], [1,2,1], [2,1,1], [1,2,2], [2,1,2], [2,2,1], [1,1,4], [1,4,1], [4,1,1], [1,1,8], [1,1,16]);

# prefetch options- "none", one for the "register_block", leading "plane"s, or leading "pencil"s
@prefetch_index_types = ("none", "register_block", "plane", "pencil");

# prefetch distances
@prefetch_distances = (0, 32, 64, 128, 256, 512);

# no clean up code (0) or clean up code (1)
$clean_up_code = 0;

### BELOW IS THE PERL SCRIPT'S "MAIN" SUBROUTINE ###

# @center and @neighbors can only contain non-negative integers

# @center is used to indicate the write point
@center = ([1,1,1]);

# @neighbors is used to indicate the read points that constitute the stencil
# each subarray in @neighbors indicates a different stencil weight
@neighbors = ([[1,1,1]],
	      [[0,1,1], [1,0,1], [1,1,0], [1,1,2], [1,2,1], [2,1,1]],
	      [[0,0,1], [0,1,0], [0,1,2], [0,2,1], [1,0,0], [1,0,2], [1,2,0], [1,2,2], [2,0,1], [2,1,0], [2,1,2], [2,2,1]],
	      [[0,0,0], [0,0,2], [0,2,0], [0,2,2], [2,0,0], [2,0,2], [2,2,0], [2,2,2]]);

%read_from_types_hash = ("array", 0, "variable", 1);
%pointer_types_hash = ("fixed", 0, "moving", 1);
%neighbor_index_types_hash = ("register_block", 0, "plane", 1, "pencil", 2);
%prefetch_index_types_hash = ("none", 0, "register_block", 1, "plane", 2, "pencil", 3);

$function_headers_file = ("function_headers.h");
open(OUT, ">$function_headers_file") || die ("Couldn't create $function_headers_file.\n");
generate_all_stencil_functions("function_headers");
close(OUT) || die;

$function_table_file = ("function_table.c");
open(OUT, ">$function_table_file") || die ("Couldn't create $function_table_file.\n");
generate_all_stencil_functions("function_table");
close(OUT) || die;

$variables_file = ("variables.c");
open(OUT, ">$variables_file") || die ("Couldn't create $variables_file.\n");
generate_global_vars();
close(OUT) || die;

$functions_file = ("functions.c");
open(OUT, ">$functions_file") || die ("Couldn't create $functions_file.\n");
generate_all_stencil_functions("generate");
close(OUT) || die;

$code_variant_header_file = ("code_variant.h");
open(OUT, ">$code_variant_header_file") || die ("Couldn't create $code_variant_header_file.\n");
generate_code_variant_header_file();
close(OUT) || die;

$code_variant_file = ("code_variant_mpi.c");
open(OUT, ">$code_variant_file") || die ("Couldn't create $code_variant_file.\n");
generate_code_variant_file();
close(OUT) || die;

$main_headers_file = ("stencil_pthreads.h");
open(OUT, ">$main_headers_file") || die ("Couldn't create $main_headers_file.\n");
generate_per_thread_function_name();
close(OUT) || die;

$specified_mpi_3D_27pt_cse_data_script = ("specified_mpi_3D_27pt_cse_data_generator.pl");
open(OUT, ">$specified_mpi_3D_27pt_cse_data_script") || die ("Couldn't create $specified_mpi_3D_27pt_cse_data_script.\n");
generate_specified_mpi_3D_27pt_cse_data_script();
close(OUT) || die;

$main_file = ("stencil_pthreads.c");
open(OUT, ">$main_file") || die ("Couldn't create $main_file.\n");
generate_directives();
generate_per_thread_function();
generate_main_function();
close(OUT) || die;

### BELOW ARE THE HELPER SUBROUTINES ###

# Converts signed integers to strings (in a specific way)
sub i2s {
    my($my_num) = @_;

    if ($my_num == 0) {
	$str = "";
    }
    elsif ($my_num > 0) {
	$str = "+" . $my_num;
    }
    else {
	$str = $my_num;
    }
    return $str;
}

# Removes the front plus from a string
sub remove_front_plus {
    my($my_str) = @_;

    if (index($my_str, "+") == 0) {
	substr($my_str, 0, 1) = "";
    }

    return $my_str;
}

sub zero_string_if_blank {
    my($my_str) = @_;

    if ($my_str eq "") {
	$my_str = "0";
    }
    
    return $my_str;
}

# compares two points based on x, then y, then z
# returns -1 if the first point is greater, 0 if they're the same, and 1 if the second point is greater
sub compare_points {
    my(@my_two_points) = @_;

    my @pt0 = @{$my_two_points[0]};
    my @pt1 = @{$my_two_points[1]};

    my $return_value = 0;
    for (my $dim=0; $dim < 3; $dim++) {
	if ($return_value == 0) {
	    if ($pt0[$dim] > $pt1[$dim]) {
		$return_value = -1;
	    }
	    elsif ($pt0[$dim] < $pt1[$dim]) {
		$return_value = 1;
	    }
	}
    }
    return $return_value;
}

# adds the two input points
sub add_points {
    my(@my_two_points) = @_;

    my @pt0 = @{$my_two_points[0]};
    my @pt1 = @{$my_two_points[1]};

    my @result = (0, 0, 0);

    for (my $dim=0; $dim < 3; $dim++) {
	$result[$dim] = $pt0[$dim] + $pt1[$dim];
    }

    return @result;
}

# subtracts the second input point from the first
sub subtract_points {
    my(@my_two_points) = @_;

    my @pt0 = @{$my_two_points[0]};
    my @pt1 = @{$my_two_points[1]};

    my @result = (0, 0, 0);

    for (my $dim=0; $dim < 3; $dim++) {
	$result[$dim] = $pt0[$dim] - $pt1[$dim];
    }

    return @result;
}

# find longest dimension of register block (if there's a tie, go with the most nearly unit-stride)
# this is used because we perform CSE in the longest register block dimension
# subroutine returns the number of the longest dimension, starting with 0 (least unit-stride)
sub find_longest_rb_dim {
    my(@my_rb_size) = @_;

    if ($my_rb_size[2] >= $my_rb_size[0]) {
	if ($my_rb_size[2] >= $my_rb_size[1]) {
	    return 2;
	}
	else {
	    return 1;
	}
    }
    elsif ($my_rb_size[1] >= $my_rb_size[0]) {
	return 1;
    }
    else {
	return 0;
    }
}

# checks a specified portion of the "neighbors" array to see which ones are zero in a specified dimension
# returns the indices of the points, NOT the points themselves
sub find_zero_indices {
    my($neighbor_type, $dim) = @_;

    my @zero_indices = ();

    for (my $neighbor_idx=0; $neighbor_idx < @{$neighbors[$neighbor_type]}; $neighbor_idx++) {
	if ($neighbors[$neighbor_type][$neighbor_idx][$dim] == 0) {
	    @zero_indices = (@zero_indices, $neighbor_idx);
	}
    }
    return @zero_indices;
}

sub convert_point_to_string {
    my($separator, @my_point) = @_;
    
    my $str = "";

    for (my $dim=0; $dim<2; $dim++) {
	$str = ($str . $my_point[$dim] . $separator);
    }
    $str = ($str . $my_point[2]);

    return $str;
}

# Converts points to a flattened 1D distance
# @my_idx is the point to be converted
sub convert_point_to_1D_string {
    my(@my_point) = @_;

    my $str = "";

    for (my $dim=0; $dim<3; $dim++) {
	if ($dim == 0) {
	    $dim_str = "plane_size";
	}
	elsif ($dim == 1) {
	    $dim_str = "nz";
	}

	if ($dim < 2) {
	    if ($my_point[$dim] < -1) {
		$str = ($str . $my_point[$dim] . "*" . $dim_str);
	    }
	    elsif ($my_point[$dim] == -1) {
		$str = ($str . "-" . $dim_str);
	    }
	    elsif ($my_point[$dim] == 1) {
		$str = ($str . "+" . $dim_str);
	    }
	    elsif ($my_point[$dim] > 1) {
		$str = ($str . "+" . $my_point[$dim] . "*" . $dim_str);
	    }
	}
	else {
	    if ($my_point[$dim] < 0) {
		$str = ($str . $my_point[$dim]);
	    }
	    elsif ($my_point[$dim] > 0) {
		$str = ($str . "+" . $my_point[$dim]);
	    }
	}
    }

    return $str;
}

sub per_thread_function_name_str {
    return ("void *pthreads_each(void *thread_num_ptr)");
}

# Returns the function name as a string
sub function_name_str {
    return ("stencil_per_thread_" . substr($read_from_type, 0, 2) . "_" . substr($pointer_type, 0, 2) . "_" . substr($index_type, 0, 2) . "_" . substr($prefetch_index_type, 0, 2) . "_" . $prefetch_distance . "_" . convert_point_to_string("x", @rb_size) . "RB");
}

sub function_parameters_str {
    return ("\(int32_t rank\)");
}

sub function_table_name_str {
    return ("stencil_per_thread[read_from_type][pointer_type][neighbor_index_type][prefetch_index_type][prefetch_distance][rb_size]");
}

# Generates a reference name (either a variable or array reference)
# $my_read_from_type equals either "array" or "variable"
# $my_read_or_write equals either "read" or "write"
# @my_rb_size is a 3D coordinate
sub reference_name {
    my($my_read_from_type, $my_read_or_write, @my_rb_size) = @_;

    my $ptr_found = 0;
    
    if ($my_read_or_write eq "read") {
	my $i = @neighbor_read_indices-1;
	while (($i >= 0) && ($ptr_found == 0)) {
	    my $compare_value = compare_points([@{$neighbor_read_indices[$i]}], [@my_rb_size]);
	    if (($compare_value == 0) || ($compare_value == 1)) {
		@ptr = @{$neighbor_read_indices[$i]};
		$ptr_found = 1;
	    }
	    else {
		$i--;
	    }
	}
    }
    elsif ($my_read_or_write eq "write") {
	if ($pointer_type eq "fixed") {
	    @index_array = @neighbor_read_indices;
	}
	elsif ($pointer_type eq "moving") {
	    @index_array = @neighbor_write_indices;
	}
	my $i = @index_array-1;
	while (($i >= 0) && ($ptr_found == 0)) {
	    my $compare_value = compare_points([@{$index_array[$i]}], [@my_rb_size]);
	    if (($compare_value == 0) || ($compare_value == 1)) {
		@ptr = @{$index_array[$i]};
		$ptr_found = 1;
	    }
	    else {
		$i--;
	    }
	}
    }
    
    my @offset = subtract_points([@my_rb_size], [@ptr]);

    if ($my_read_from_type eq "array") {
	if ($pointer_type eq "fixed") {
	    $idx_str = ("[i_" . convert_point_to_string("_", @ptr) . convert_point_to_1D_string(@offset) . "]");
	    if ($my_read_or_write eq "read") {
		return ("Read_start_restrict" . $idx_str);
	    }
	    elsif ($my_read_or_write eq "write") {
		return ("Write_start_restrict" . $idx_str);
	    }
	}
	elsif ($pointer_type eq "moving") {
	    $idx_str = (convert_point_to_string("_", @ptr) . "[" . zero_string_if_blank(remove_front_plus(convert_point_to_1D_string(@offset))) . "]");
	    if ($my_read_or_write eq "read") {
		return ("Read_rb_" . $idx_str);
	    }
	    elsif ($my_read_or_write eq "write") {
		return ("Write_rb_" . $idx_str);
	    }
	}
    }
    elsif ($my_read_from_type eq "variable") {
	if ($my_read_or_write eq "read") {
	    return ("read_rb_" . convert_point_to_string("_", @my_rb_size));
	}
	elsif ($my_read_or_write eq "write") {
	    return ("write_rb_" . convert_point_to_string("_", @my_rb_size));
	}
    }
}

### BELOW ARE THE BUILDING BLOCK SUBROUTINES ###

# creates an array containing non-redundant stencil read points in increasing order
sub make_increasing_read_points_array {
    my(@my_rb_size) = @_;

    @increasing_read_points = ();
    
    for (my $i=0; $i < $my_rb_size[0]; $i++) {
	for (my $j=0; $j < $my_rb_size[1]; $j++) {
	    for (my $k=0; $k < $my_rb_size[2]; $k++) {
		my @rb_pt = ($i, $j, $k);
		for ($neighbor_type=0; $neighbor_type < @neighbors; $neighbor_type++) {
#		    print OUT ("neighbor_type = $neighbor_type, number of this type of neighbor = " . @{$neighbors[$neighbor_type]} . "\n");
		    for ($neighbor_idx=0; $neighbor_idx < @{$neighbors[$neighbor_type]}; $neighbor_idx++) {
			my @new_pt = add_points([@{$neighbors[$neighbor_type][$neighbor_idx]}], [@rb_pt]);
			@increasing_read_points = (@increasing_read_points, [ @new_pt ]);
			my $new_idx = @increasing_read_points-1;
			my $new_is_less_than_previous = 1;
			while (($new_idx >= 1) && ($new_is_less_than_previous==1)) {
			    my @previous_pt = @{$increasing_read_points[$new_idx-1]};
			    if (compare_points([@{$increasing_read_points[$new_idx-1]}], [@{$increasing_read_points[$new_idx]}]) == 0) {
				$new_is_less_than_previous = 0;

				# delete duplicate point
				if ($new_idx < (@increasing_read_points-1)) {
				    @increasing_read_points = @increasing_read_points[0..($new_idx-1), ($new_idx+1)..(@increasing_read_points-1)];
				}
				else {
				    @increasing_read_points = @increasing_read_points[0..($new_idx-1)];
				}
			    }
			    elsif (compare_points([@{$increasing_read_points[$new_idx-1]}], [@{$increasing_read_points[$new_idx]}]) == 1) {
				$new_is_less_than_previous = 0;
			    }
			    else {
				($increasing_read_points[$new_idx-1], $increasing_read_points[$new_idx]) = ($increasing_read_points[$new_idx], $increasing_read_points[$new_idx-1]);
				$new_idx--;
			    }
			}
		    }
		}
	    }
	}
    }
}

# creates an array containing non-redundant stencil write points in increasing order
sub make_increasing_write_points_array {
    my(@my_rb_size) = @_;

    @increasing_write_points = ();
    
    for (my $i=0; $i < $my_rb_size[0]; $i++) {
	for (my $j=0; $j < $my_rb_size[1]; $j++) {
	    for (my $k=0; $k < $my_rb_size[2]; $k++) {
		my @new_pt = add_points([@{$center[0]}], [($i, $j, $k)]);
		@increasing_write_points = (@increasing_write_points, [ @new_pt ]);
	    }
	}
    }
#    for ($i=0; $i < @increasing_write_points; $i++) {
#	print OUT ("increasing_write_points i = " . $i . ", (" . $increasing_write_points[$i][0] . ", ".  $increasing_write_points[$i][1] . ", " . $increasing_write_points[$i][2] . ")\n");
#    }
}

# Finds the neighbor (low) read indices (for each register block, plane, or pencil)
sub find_neighbor_read_indices {
    @neighbor_read_indices = ();

    @neighbor_read_indices = (@neighbor_read_indices, [@{$increasing_read_points[0]}]);
    for (my $i=1; $i < @increasing_read_points; $i++) {
	my @previous_point = @{$increasing_read_points[$i-1]};
	my @current_point = @{$increasing_read_points[$i]};
	
	if ($index_type eq "plane") {
	    if ($previous_point[0] < $current_point[0]) {
		@neighbor_read_indices = (@neighbor_read_indices, [@current_point]);
	    }
	}
	
	if ($index_type eq "pencil") {
	    if (($previous_point[0] < $current_point[0]) || ($previous_point[1] < $current_point[1])) {
		@neighbor_read_indices = (@neighbor_read_indices, [@current_point]);
	    }
	}
    }
}

# Finds the neighbor (low) write indices (for each register block, plane, or pencil)
sub find_neighbor_write_indices {
    @neighbor_write_indices = ();

    @neighbor_write_indices = (@neighbor_write_indices, [@{$increasing_write_points[0]}]);
    for (my $i=1; $i < @increasing_write_points; $i++) {
	my @previous_point = @{$increasing_write_points[$i-1]};
	my @current_point = @{$increasing_write_points[$i]};
	
	if ($index_type eq "plane") {
	    if ($previous_point[0] < $current_point[0]) {
		@neighbor_write_indices = (@neighbor_write_indices, [@current_point]);
	    }
	}
	
	if ($index_type eq "pencil") {
	    if (($previous_point[0] < $current_point[0]) || ($previous_point[1] < $current_point[1])) {
		@neighbor_write_indices = (@neighbor_write_indices, [@current_point]);
	    }
	}
    }
}

# Finds the prefetch (high) read indices (for each register block, plane, or pencil)
sub find_prefetch_read_indices {
    @prefetch_read_indices = ();

    for ($i=0; $i < (@increasing_read_points-1); $i++) {
	my @current_point = @{$increasing_read_points[$i]};
	my @next_point = @{$increasing_read_points[$i+1]};

	if ($prefetch_index_type eq "plane") {
	    if ($current_point[0] < $next_point[0]) {
		@prefetch_read_indices = (@prefetch_read_indices, [@current_point]);
	    }
	}

	if ($prefetch_index_type eq "pencil") {
	    if (($current_point[0] < $next_point[0]) || ($current_point[1] < $next_point[1])) {
		@prefetch_read_indices = (@prefetch_read_indices, [@current_point]);
	    }
	}
    }
    @prefetch_read_indices = (@prefetch_read_indices, [@{$increasing_read_points[@increasing_read_points-1]}]);
}

# Finds the prefetch (high) write indices (for each register block, plane, or pencil)
sub find_prefetch_write_indices {
    @prefetch_write_indices = ();

    for ($i=0; $i < (@increasing_write_points-1); $i++) {
	my @current_point = @{$increasing_write_points[$i]};
	my @next_point = @{$increasing_write_points[$i+1]};

	if ($prefetch_index_type eq "plane") {
	    if ($current_point[0] < $next_point[0]) {
		@prefetch_write_indices = (@prefetch_write_indices, [@current_point]);
	    }
	}

	if ($prefetch_index_type eq "pencil") {
	    if (($current_point[0] < $next_point[0]) || ($current_point[1] < $next_point[1])) {
		@prefetch_write_indices = (@prefetch_write_indices, [@current_point]);
	    }
	}
    }
    @prefetch_write_indices = (@prefetch_write_indices, [@{$increasing_write_points[@increasing_write_points-1]}]);
}

# declares the register block read variables
sub declare_rb_read_vars {
    print OUT ("  CALC_DATA_TYPE ");

    for (my $i=0; $i < @increasing_read_points; $i++) {
	print OUT ("read_rb_" . convert_point_to_string("_", @{$increasing_read_points[$i]}));
	if ($i < (@increasing_read_points-1)) {
	    print OUT (", ");
	}
	else {
	    print OUT (";\n");
	}
    }
}

# initializes the register block read variables
sub init_rb_read_vars {
    for (my $i=0; $i < @increasing_read_points; $i++) {
	print OUT ("                  read_rb_" . convert_point_to_string("_", @{$increasing_read_points[$i]}) . " = " . reference_name("array", "read", @{$increasing_read_points[$i]}) . ";\n");
    }
    print OUT ("\n");
}

# @my_rb_size is a 3D coordinate
sub init_fixed_ptrs {
    my(@my_rb_size) = @_;

    for (my $i=0; $i < @neighbor_read_indices; $i++) {
	print OUT ("                int32_t i_" . convert_point_to_string("_", @{$neighbor_read_indices[$i]}) . " = Index3D(i", i2s($neighbor_read_indices[$i][0]-1), ",j", i2s($neighbor_read_indices[$i][1]-1), ",coreBlockMin_z", i2s($neighbor_read_indices[$i][2]-1), ");\n");
    }
    
    print OUT ("\n");
}

# @my_rb_size is a 3D coordinate
sub declare_moving_ptrs {
    print OUT ("  CALC_DATA_TYPE ");
    for (my $i=0; $i < @neighbor_read_indices; $i++) {
	print OUT ("* __restrict__ Read_rb_" . convert_point_to_string("_", @{$neighbor_read_indices[$i]}));
	if ($i < (@neighbor_read_indices-1)) {
	    print OUT (", ");
	}
	else {
	    print OUT (";\n");
	}
    }
    
    print OUT ("  CALC_DATA_TYPE ");
    for (my $i=0; $i < @neighbor_write_indices; $i++) {
	print OUT ("* __restrict__ Write_rb_" . convert_point_to_string("_", @{$neighbor_write_indices[$i]}));
	if ($i < (@neighbor_write_indices-1)) {
	    print OUT (", ");
	}
	else {
	    print OUT (";\n");
	}
    }
}

# @my_rb_size is a 3D coordinate
sub init_moving_ptrs {
    my(@my_rb_size) = @_;

    my @offset_from_center = subtract_points([@{$neighbor_read_indices[0]}], [@{$center[0]}]);
    print OUT ("                Read_rb_" . convert_point_to_string("_", @{$neighbor_read_indices[0]}) . " = Read_start_unrestrict + Index3D(i" . i2s($offset_from_center[0]) . ",j" . i2s($offset_from_center[1]) . ",coreBlockMin_z". i2s($offset_from_center[2]) . ");\n");

    for (my $i=1; $i < @neighbor_read_indices; $i++) {
	my @offset_from_first = subtract_points([@{$neighbor_read_indices[$i]}], [@{$neighbor_read_indices[0]}]);
	print OUT ("                Read_rb_" . convert_point_to_string("_", @{$neighbor_read_indices[$i]}) . " = Read_rb_" . convert_point_to_string("_", @{$neighbor_read_indices[0]}) . convert_point_to_1D_string(@offset_from_first) . ";\n");
    }

    @offset_from_center = subtract_points([@{$neighbor_write_indices[0]}], [@{$center[0]}]);
    print OUT ("                Write_rb_" . convert_point_to_string("_", @{$neighbor_write_indices[0]}) . " = Write_start_unrestrict + Index3D(i" . i2s($offset_from_center[0]) . ",j" . i2s($offset_from_center[1]) . ",coreBlockMin_z". i2s($offset_from_center[2]) . ");\n");

    for (my $i=1; $i < @neighbor_write_indices; $i++) {
	my @offset_from_first = subtract_points([@{$neighbor_write_indices[$i]}], [@{$neighbor_write_indices[0]}]);
	print OUT ("                Write_rb_" . convert_point_to_string("_", @{$neighbor_write_indices[$i]}) . " = Write_rb_" . convert_point_to_string("_", @{$neighbor_write_indices[0]}) . convert_point_to_1D_string(@offset_from_first) . ";\n");
    }

    print OUT ("\n");
}

# @my_rb_size is a 3D coordinate
sub advance_fixed_ptrs {
    my(@my_rb_size) = @_;

    for (my $i=0; $i < @neighbor_read_indices; $i++) {
	if ($my_rb_size[2] == 1) {
	    print OUT ("                  i_" . convert_point_to_string("_", @{$neighbor_read_indices[$i]}) . "++;\n");
	}
	else {
	    print OUT ("                  i_" . convert_point_to_string("_", @{$neighbor_read_indices[$i]}) . " += " . $my_rb_size[2] . ";\n");
	}
    }
}

# @my_rb_size is a 3D coordinate
sub advance_moving_ptrs {
    my(@my_rb_size) = @_;

    for (my $i=0; $i < @neighbor_read_indices; $i++) {
	if ($my_rb_size[2] == 1) {
	    print OUT ("                  Read_rb_" . convert_point_to_string("_", @{$neighbor_read_indices[$i]}) . "++;\n");
	}
	else {
	    print OUT ("                  Read_rb_" . convert_point_to_string("_", @{$neighbor_read_indices[$i]}) . " += " . $my_rb_size[2] . ";\n");
	}
    }

    for (my $i=0; $i < @neighbor_write_indices; $i++) {
	if ($my_rb_size[2] == 1) {
	    print OUT ("                  Write_rb_" . convert_point_to_string("_", @{$neighbor_write_indices[$i]}) . "++;\n");
	}
	else {
	    print OUT ("                  Write_rb_" . convert_point_to_string("_", @{$neighbor_write_indices[$i]}) . " += " . $my_rb_size[2] . ";\n");
	}
    }
}

sub prefetch_code {
    my(@my_rb_size) = @_;

    find_prefetch_read_indices();
    find_prefetch_write_indices();

    for (my $i=0; $i < @prefetch_read_indices; $i++) {
	@prefetch_pt = @{$prefetch_read_indices[$i]};
	$leading_pt_str = reference_name("array", "read", @prefetch_pt);
	print OUT ("                  PREFETCH_FOR_REUSE\(&" . $leading_pt_str . "+$prefetch_distance\)\;\n");
    }
    
    for (my $i=0; $i < @prefetch_write_indices; $i++) {
	@prefetch_pt = @{$prefetch_write_indices[$i]};
	$leading_pt_str = reference_name("array", "write", @prefetch_pt);
	print OUT ("                  PREFETCH_FOR_ONE_WRITE\(&" . $leading_pt_str . "+$prefetch_distance\)\;\n");
    }

    print OUT ("\n");
}


### BELOW ARE THE SUBROUTINES THAT MAKE THE NESTED LOOPS ###

# generates statements for the sums of the edges and corners of 3x3 square planes
sub sum_edges_and_corners_statements {
    my($longest_dim, @my_rb_pt) = @_;

    for ($neighbors_idx = 2; $neighbors_idx <= 3; $neighbors_idx++) {
	my @zero_indices = find_zero_indices($neighbors_idx, $longest_dim);

	if ($neighbors_idx == 2) {
	    $neighbors_str = "edges";
	}
	elsif ($neighbors_idx == 3) {
	    $neighbors_str = "corners";
	}

	print OUT ("                  ");
	print OUT ("sum_" . $neighbors_str . "_" . convert_point_to_string("_", @my_rb_pt) . " = ");
	for ($zero_idx=0; $zero_idx < @zero_indices; $zero_idx++) {
	    print OUT (reference_name($read_from_type, "read", add_points([@{$neighbors[$neighbors_idx][$zero_indices[$zero_idx]]}], [@my_rb_pt])));
	    if ($zero_idx < (@zero_indices-1)) {
		print OUT (" + ");
	    }
	    else {
		print OUT (";\n");
	    }
	}
    }
}

# generates statements for the sums of 3x3 square planes (the side planes of the cube)
sub side_plane_statements {
    my($longest_dim, @my_rb_pt) = @_;

    @offset_pt = (0, 0, 0);
    $offset_pt[$longest_dim] = $offset_pt[$longest_dim] - 1;

    print OUT ("                  ");
    print OUT ("side_plane_" . convert_point_to_string("_", @my_rb_pt) . " = c1 * " .
	       reference_name($read_from_type, "read", add_points([@{$neighbors[0][0]}], [add_points([@my_rb_pt], [@offset_pt])])) . " + c2 * " .
	       "sum_edges_" . convert_point_to_string("_", @my_rb_pt) . " + c3 * " .
	       "sum_corners_" . convert_point_to_string("_", @my_rb_pt) . ";\n");
}

# generates statements for the sums of 3x3 square planes (the center planes of the cube)
sub center_plane_statements {
    my($longest_dim, @my_rb_pt) = @_;

    @offset_pt = (0, 0, 0);
    $offset_pt[$longest_dim] = $offset_pt[$longest_dim] - 1;

    print OUT ("                  ");
    print OUT ("center_plane_" . convert_point_to_string("_", @my_rb_pt) . " = c0 * " .
	       reference_name($read_from_type, "read", add_points([@{$neighbors[0][0]}], [add_points([@my_rb_pt], [@offset_pt])])) . " + c1 * " .
	       "sum_edges_" . convert_point_to_string("_", @my_rb_pt) . " + c2 * " .
	       "sum_corners_". convert_point_to_string("_", @my_rb_pt) . ";\n");
}

# generates statements for the sums of 3x3 square planes (the center planes of the cube)
sub write_back_statements {
    my($longest_dim, @my_rb_pt) = @_;

    @one_after_pt = @my_rb_pt;
    $one_after_pt[$longest_dim] = $one_after_pt[$longest_dim]+1;
    @two_after_pt = @one_after_pt;
    $two_after_pt[$longest_dim] = $two_after_pt[$longest_dim]+1;

    print OUT ("                  ");
    print OUT (reference_name("array", "write", add_points([@{$neighbors[0][0]}], [@my_rb_pt])) . " = " .
	       "side_plane_" . convert_point_to_string("_", @my_rb_pt) . " + " .
	       "center_plane_" . convert_point_to_string("_", @one_after_pt) . " + " .
	       "side_plane_" . convert_point_to_string("_", @two_after_pt) . ";\n");
}

# @my_rb_size is a 3D coordinate
sub inner_loop {
    my(@my_rb_size) = @_;

    if ($prefetch_index_type ne "none") {
	prefetch_code(@my_rb_size);
    }

    if ($read_from_type eq "variable") {
	init_rb_read_vars();
    }

    my $longest_dim = find_longest_rb_dim(@my_rb_size);
    my @my_cse_rb_size = @my_rb_size;
    $my_cse_rb_size[$longest_dim] = $my_cse_rb_size[$longest_dim] + 2;

    for (my $i=0; $i < $my_cse_rb_size[0]; $i++) {
	for (my $j=0; $j < $my_cse_rb_size[1]; $j++) {
	    for (my $k=0; $k < $my_cse_rb_size[2]; $k++) {
		my @rb_pt = ($i, $j, $k);
		sum_edges_and_corners_statements($longest_dim, @rb_pt);
	    }
	    print OUT ("\n");
	}
    }

    if (($my_cse_rb_size[0] != 1) || ($my_cse_rb_size[1] != 1) || ($my_cse_rb_size[2] != 3)) {
	for ($i=0; $i < $my_cse_rb_size[0]; $i++) {
	    for ($j=0; $j < $my_cse_rb_size[1]; $j++) {
		for ($k=0; $k < $my_cse_rb_size[2]; $k++) {
		    @rb_pt = ($i, $j, $k);
		    side_plane_statements($longest_dim, @rb_pt);
		}
		print OUT ("\n");
	    }
	}
    }
    else {
	side_plane_statements($longest_dim, (0,0,0));
	side_plane_statements($longest_dim, (0,0,2));
	print OUT ("\n");
    }

    my @start_pt = (0, 0, 0);
    $start_pt[$longest_dim] = $start_pt[$longest_dim]+1;
    my @end_pt = @my_rb_size;
    $end_pt[$longest_dim] = $end_pt[$longest_dim]+1;

    for ($i=$start_pt[0]; $i < $end_pt[0]; $i++) {
	for ($j=$start_pt[1]; $j < $end_pt[1]; $j++) {
	    for ($k=$start_pt[2]; $k < $end_pt[2]; $k++) {
		@rb_pt = ($i, $j, $k);
		center_plane_statements($longest_dim, @rb_pt);
	    }
	    print OUT ("\n");
	}
    }

    for ($i=0; $i < $my_rb_size[0]; $i++) {
	for ($j=0; $j < $my_rb_size[1]; $j++) {
	    for ($k=0; $k < $my_rb_size[2]; $k++) {
		@rb_pt = ($i, $j, $k);
		write_back_statements($longest_dim, @rb_pt);
	    }
	    print OUT ("\n");
	}
    }

    if ($pointer_type eq "fixed") {
	advance_fixed_ptrs(@my_rb_size);
    }
    elsif ($pointer_type eq "moving") {
	advance_moving_ptrs(@my_rb_size);
    }
}

# Generates the code for the z-dimensional loop
# @my_rb_size is a 3D coordinate
sub singly_nested_loop_code {
    my(@my_rb_size) = @_;

    if ($my_rb_size[2] == 1) {
	print OUT ("                for (k=coreBlockMin_z; k < coreBlockMax_z; k++) {\n");
    }
    else {
	print OUT ("                for (k=coreBlockMin_z; k < (coreBlockMax_z-" . ($my_rb_size[2]-1) . "); k+=" . $my_rb_size[2] . ") {\n");
    }

    inner_loop(@my_rb_size);
    print OUT ("                }\n");

    if ($clean_up_code) {
	if ($my_rb_size[2] > 1) {
	    print OUT ("                for (; k < coreBlockMax_z; k++) {\n");
	    inner_loop(($my_rb_size[0], $my_rb_size[1], 1));
	    print OUT ("                }\n");
	}
    }
}

# Generates the code for the nested y- and z-dimensional loops
# @my_rb_size is a 3D coordinate
sub doubly_nested_loop_code {
    my(@my_rb_size) = @_;

    if ($my_rb_size[1] == 1) {
	print OUT ("              for (j=coreBlockMin_y; j < coreBlockMax_y; j++) {\n");
    }
    else {
	print OUT ("              for (j=coreBlockMin_y; j < (coreBlockMax_y-" . ($my_rb_size[1]-1) . "); j+=" . $my_rb_size[1] . ") {\n");
    }

    if ($pointer_type eq "fixed") {
	init_fixed_ptrs(@my_rb_size);
    }
    elsif ($pointer_type eq "moving") {
	find_neighbor_write_indices();
	init_moving_ptrs(@my_rb_size);
    }

    singly_nested_loop_code(@my_rb_size);
    print OUT ("              }\n");

    if ($clean_up_code) {
	if ($my_rb_size[1] > 1) {
	    print OUT ("              for (; j < coreBlockMax_y; j++) {\n");
	    
	    if ($pointer_type eq "fixed") {
		find_fixed_ptrs($my_rb_size[0], 1, $my_rb_size[2]);
		init_fixed_ptrs($my_rb_size[0], 1, $my_rb_size[2]);
	    }
	    elsif ($pointer_type eq "moving") {
		init_moving_ptrs($my_rb_size[0], 1, $my_rb_size[2]);
	    }

	    singly_nested_loop_code($my_rb_size[0], 1, $my_rb_size[2]);
	    print OUT ("              }\n");
	}
    }
}

# Generates the code for the triply nested loops
sub triply_nested_loop_code {
    if ($rb_size[0] == 1) {
	print OUT ("            for (i=coreBlockMin_x; i < coreBlockMax_x; i++) {\n");
    }
    else {
	print OUT ("            for (i=coreBlockMin_x; i < (coreBlockMax_x-" . ($rb_size[0]-1) . "); i+=" . $rb_size[0] . ") {\n");
    }

    doubly_nested_loop_code(@rb_size);
    print OUT ("            }\n");

    if ($clean_up_code) {
	if ($rb_size[0] > 1) {
	    print OUT ("            for (; i < coreBlockMax_x; i++) {\n");
	    doubly_nested_loop_code(1, $rb_size[1], $rb_size[2]);
	    print OUT ("            }\n");
	}
    }
}

sub outer_nested_loop_code {
    print OUT ("    cb_n = 0;\n\n");
    print OUT ("    for (cb_i=0; cb_i < numCoreBlocks_x; cb_i++) {\n");
    print OUT ("      for (cb_j=0; cb_j < numCoreBlocks_y; cb_j++) {\n");
    print OUT ("        for (cb_k=0; cb_k < numCoreBlocks_z; cb_k++) {\n");
    print OUT ("          if (((cb_n/numCoreBlocksPerChunk) % numThreads) == rank) {\n");
    print OUT ("            coreBlockMin_x = realMin_x + cb_i * numCoreBlockCells_x\;\n");
    print OUT ("            coreBlockMax_x = coreBlockMin_x + numCoreBlockCells_x\;\n");
    print OUT ("            coreBlockMin_y = realMin_y + cb_j * numCoreBlockCells_y\;\n");
    print OUT ("            coreBlockMax_y = coreBlockMin_y + numCoreBlockCells_y\;\n");
    print OUT ("            coreBlockMin_z = realMin_z + cb_k * numCoreBlockCells_z\;\n");
    print OUT ("            coreBlockMax_z = coreBlockMin_z + numCoreBlockCells_z\;\n");
    triply_nested_loop_code();
    print OUT ("          }\n");
    print OUT ("          cb_n++\;\n");
    print OUT ("        }\n");
    print OUT ("      }\n");
    print OUT ("    }\n");
    print OUT ("    temp_ptr = Read_start_unrestrict;\n");
    print OUT ("    Read_start_unrestrict = Write_start_unrestrict;\n");
    print OUT ("    Write_start_unrestrict = temp_ptr;\n\n");
    print OUT ("    // barrier after each iteration (except the last iteration)\n");
    print OUT ("    if \(t < \(numIter-1\)\) {\n");
    print OUT ("      barrier_wait(&my_barrier, rank);\n");
    print OUT ("    }\n");
}

### BELOW ARE THE SUBROUTINES THAT GENERATE FULL FUNCTIONS ###

# Generates a single stencil function
sub generate_single_stencil_function {
    print OUT ("void " . function_name_str() . function_parameters_str() . " {\n");
    print OUT ("  CALC_DATA_TYPE * __restrict__ temp_ptr;\n");

    my $longest_dim = find_longest_rb_dim(@rb_size);
    my @my_cse_rb_size = @rb_size;
    $my_cse_rb_size[$longest_dim] = $my_cse_rb_size[$longest_dim] + 2;

    print OUT ("\n");
    for (my $i=0; $i < $my_cse_rb_size[0]; $i++) {
	for (my $j=0; $j < $my_cse_rb_size[1]; $j++) {
	    print OUT ("  CALC_DATA_TYPE ");
	    for (my $k=0; $k < $my_cse_rb_size[2]; $k++) {
		print OUT ("sum_edges_" . $i . "_" . $j . "_" . $k);
		if ($k != ($my_cse_rb_size[2]-1)) {
		    print OUT (", ");
		}
		else {
		    print OUT (";\n");
		}
	    }
	}
    }
    print OUT ("\n");

    for ($i=0; $i < $my_cse_rb_size[0]; $i++) {
	for ($j=0; $j < $my_cse_rb_size[1]; $j++) {
	    print OUT ("  CALC_DATA_TYPE ");
	    for ($k=0; $k < $my_cse_rb_size[2]; $k++) {
		print OUT ("sum_corners_" . $i . "_" . $j . "_" . $k);
		if ($k != ($my_cse_rb_size[2]-1)) {
		    print OUT (", ");
		}
		else {
		    print OUT (";\n");
		}
	    }
	}
    }
    print OUT ("\n");

    if (($my_cse_rb_size[0] != 1) || ($my_cse_rb_size[1] != 1) || ($my_cse_rb_size[2] != 3)) {
	for ($i=0; $i < $my_cse_rb_size[0]; $i++) {
	    for ($j=0; $j < $my_cse_rb_size[1]; $j++) {
		print OUT ("  CALC_DATA_TYPE ");
		for ($k=0; $k < $my_cse_rb_size[2]; $k++) {
		    print OUT ("side_plane_" . $i . "_" . $j . "_" . $k);
		    if ($k != ($my_cse_rb_size[2]-1)) {
			print OUT (", ");
		    }
		    else {
			print OUT (";\n");
		    }
		}
	    }
	}
    }
    else {
	print OUT ("  CALC_DATA_TYPE side_plane_0_0_0, side_plane_0_0_2;\n");
    }
    print OUT ("\n");

    my @start_pt = (0, 0, 0);
    $start_pt[$longest_dim] = $start_pt[$longest_dim]+1;
    my @end_pt = @rb_size;
    $end_pt[$longest_dim] = $end_pt[$longest_dim]+1;

    for ($i=$start_pt[0]; $i < $end_pt[0]; $i++) {
	for ($j=$start_pt[1]; $j < $end_pt[1]; $j++) {
	    print OUT ("  CALC_DATA_TYPE ");
	    for ($k=$start_pt[2]; $k < $end_pt[2]; $k++) {
		print OUT ("center_plane_" . $i . "_" . $j . "_" . $k);
		if ($k != ($end_pt[2]-1)) {
		    print OUT (", ");
		}
		else {
		    print OUT (";\n");
		}
	    }
	}
    }
    print OUT ("\n");

    make_increasing_read_points_array(@rb_size);
    make_increasing_write_points_array(@rb_size);
    find_neighbor_read_indices();
    find_neighbor_write_indices();

    if ($pointer_type eq "moving") {
	declare_moving_ptrs();
    }
    if ($read_from_type eq "variable") {
	declare_rb_read_vars();
    }

    print OUT ("  int32_t coreBlockMin_x, coreBlockMin_y, coreBlockMin_z, coreBlockMax_x, coreBlockMax_y, coreBlockMax_z\;\n");
    print OUT ("  int32_t cb_n, cb_i, cb_j, cb_k\;\n");
    print OUT ("  int32_t i, j, k, t\;\n\n");

    for (my $neighbor_type=0; $neighbor_type < @neighbors; $neighbor_type++) {
	print OUT ("  const CALC_DATA_TYPE c" . $neighbor_type . " = C" . $neighbor_type . "\;\n");
    }

    print OUT ("\n  CALC_DATA_TYPE * Read_start_unrestrict = A;\n");
    print OUT ("  CALC_DATA_TYPE * Write_start_unrestrict = B;\n\n");

    if (($pointer_type eq "moving") || ($index_type eq "register_block")) {
	print OUT ("  const int32_t plane_size = ny * nz;\n\n");
    }

    print OUT ("  for (t=0; t < numIter; t++) {\n");
    if ($pointer_type eq "fixed") {
	print OUT ("    CALC_DATA_TYPE * __restrict__ Read_start_restrict = Read_start_unrestrict\;\n");
	print OUT ("    CALC_DATA_TYPE * __restrict__ Write_start_restrict = Write_start_unrestrict\;\n");
    }

    outer_nested_loop_code();

    print OUT ("  }\n");
    print OUT ("}\n\n");
}

# Generates all the stencil functions, or all the function headers, or the function table
sub generate_all_stencil_functions {
    my($code_type) = @_;

    if ($code_type eq "function_table") {
	print OUT ("#define READ_FROM_TYPES " . @read_from_types . "\t// read from array or variable\n");
	print OUT ("#define POINTER_TYPES " . @pointer_types . "\t\t// fixed or moving pointers\n");
	print OUT ("#define NEIGHBOR_INDEX_TYPES " . @neighbor_index_types . "\t// single ptr per register block, plane, or pencil\n");
	print OUT ("#define PREFETCH_INDEX_TYPES " . @prefetch_index_types . "\t// no prefetch, or prefetch for register block, leading planes, or leading pencils\n");
	print OUT ("#define PREFETCH_DISTANCES " . @prefetch_distances . "\t// the distances ahead being prefetched\n");
	print OUT ("#define RB_SIZES " . @rb_sizes . "\t\t// the number of register block sizes\n\n");
	print OUT ("void (*stencil_per_thread[READ_FROM_TYPES][POINTER_TYPES][NEIGHBOR_INDEX_TYPES][PREFETCH_INDEX_TYPES][PREFETCH_DISTANCES][RB_SIZES])() =\n{");
    }

    foreach $read_from_type (@read_from_types) {
	if ($code_type eq "function_table") {
	    print OUT ("{");
	}
	foreach $pointer_type (@pointer_types) {
	    if ($code_type eq "function_table") {
		print OUT ("{");
	    }
	    foreach $index_type (@neighbor_index_types) {
		if ($code_type eq "function_table") {
		    print OUT ("{");
		}
		foreach $prefetch_index_type (@prefetch_index_types) {
		    if ($code_type eq "function_table") {
			print OUT ("{");
		    }
		    foreach $prefetch_distance (@prefetch_distances) {
			if ($code_type eq "function_table") {
			    print OUT ("{");
			}
			for ($rb_idx=0; $rb_idx < @rb_sizes; $rb_idx++) {
			    @rb_size = ($rb_sizes[$rb_idx][0], $rb_sizes[$rb_idx][1], $rb_sizes[$rb_idx][2]);
			    if ($code_type eq "generate") {
				generate_single_stencil_function();
			    }
			    elsif ($code_type eq "function_headers") {
				print OUT ("void " . function_name_str() . function_parameters_str() . ";\n");
			    }
			    elsif ($code_type eq "function_table") {
				print OUT ("\t&" . function_name_str());
				if ($rb_idx != (@rb_sizes-1)) {
				    print OUT (", ");
				}
			    }
			}
			if ($code_type eq "function_table") {
			    if ($prefetch_distance eq $prefetch_distances[@prefetch_distances-1]) {
				print OUT ("}\n");
			    }
			    else {
				print OUT ("},\n");
			    }
			}
		    }
		    if ($code_type eq "function_table") {
			if ($prefetch_index_type eq $prefetch_index_types[@prefetch_index_types-1]) {
			    print OUT ("}\n");
			}
			else {
			    print OUT ("},\n");
			}
		    }
		}
		if ($code_type eq "function_table") {
		    if ($index_type eq $neighbor_index_types[@neighbor_index_types-1]) {
			print OUT ("}\n");
		    }
		    else {
			print OUT ("},\n");
		    }
		}
	    }
	    if ($code_type eq "function_table") {
		if ($pointer_type eq $pointer_types[@pointer_types-1]) {
		    print OUT ("}\n");
		}
		else {
		    print OUT ("},\n");
		}
	    }
	}
	if ($code_type eq "function_table") {
	    if ($read_from_type eq $read_from_types[@read_from_types-1]) {
		print OUT ("}\n");
	    }
	    else {
		print OUT ("},\n");
	    }
	}
    }
    if ($code_type eq "function_table") {
	print OUT ("};\n");
    }
}

sub generate_global_vars {
    print OUT "#if !defined\(DEBUG\)\n";
    print OUT "double *results\;\n";
    print OUT "#if defined(PAPI_ENABLED)\n";
    print OUT "int num_desired = 10;\n";
    print OUT "int desired_events[] = {PAPI_TOT_CYC, PAPI_TOT_INS, PAPI_FP_INS, PAPI_VEC_INS, PAPI_L1_DCM, PAPI_L2_DCM, PAPI_TLB_DM, PAPI_CA_SHR, PAPI_CA_CLN, PAPI_CA_ITV}\;\n";
    print OUT "#endif\n";
    print OUT "#endif\n\n";
    print OUT "barrier_t my_barrier\;\n";
    print OUT "double median_counts_per_sec\;\n\n";
}

sub generate_code_variant_header_file {
    print OUT "int32_t read_from_type, pointer_type, neighbor_index_type, prefetch_index_type, prefetch_distance, rb_size\;\n\n";
    print OUT "void select_code_variant\(char *argv\[\]\)\;\n";
    print OUT "void print_code_variant_parameters\(void\)\;\n";
}

sub generate_code_variant_file {
    print OUT ("void select_code_variant\(char *argv\[\]\) {\n");
    print OUT ("  int32_t read_from_type_param, pointer_type_param, neighbor_index_type_param, prefetch_index_type_param, prefetch_distance_param, rb_size_param\;\n");
    print OUT ("  int32_t parameters_set = 0\;\n");
    print OUT ("  int32_t job_num = 0\;\n\n");
    print OUT ("  for \(read_from_type_param=0\; read_from_type_param < " . @read_from_types . "\; read_from_type_param++\) {\n");
    print OUT ("    for \(pointer_type_param=0\; pointer_type_param < " . @pointer_types . "\; pointer_type_param++\) {\n");
    print OUT ("      for \(neighbor_index_type_param=0\; neighbor_index_type_param < " . @neighbor_index_types . "\; neighbor_index_type_param++\) {\n");
    print OUT ("        for \(prefetch_index_type_param=0\; prefetch_index_type_param < " . @prefetch_index_types . "\; prefetch_index_type_param++\) {\n");
    print OUT ("          for \(prefetch_distance_param=0\; prefetch_distance_param < " . @prefetch_distances . "\; prefetch_distance_param++\) {\n");
    print OUT ("            for \(rb_size_param=0\; rb_size_param < " . @rb_sizes . "\; rb_size_param++\) {\n");
    print OUT ("              if (my_proc_num == (job_num % num_procs)) {\n");
    print OUT ("                read_from_type = read_from_type_param\;\n");
    print OUT ("                pointer_type = pointer_type_param\;\n");
    print OUT ("                neighbor_index_type = neighbor_index_type_param\;\n");
    print OUT ("                prefetch_index_type = prefetch_index_type_param\;\n");
    print OUT ("                prefetch_distance = prefetch_distance_param\;\n");
    print OUT ("                rb_size = rb_size_param\;\n");
    print OUT ("                parameters_set = 1\;\n");
    print OUT ("              }\n");
    print OUT ("              job_num++\;\n");
    print OUT ("            }\n");
    print OUT ("          }\n");
    print OUT ("        }\n");
    print OUT ("      }\n");
    print OUT ("    }\n");
    print OUT ("  }\n");
    print OUT ("  if \(!parameters_set\) {\n");
    print OUT ("    exit(EXIT_SUCCESS)\;\n");
    print OUT ("  }\n");
    print OUT ("//  read_from_type = atoi\(argv\[14\]\)\;\n");
    print OUT ("//  pointer_type = atoi\(argv\[15\]\)\;\n");
    print OUT ("//  neighbor_index_type = atoi\(argv\[16\]\)\;\n");
    print OUT ("//  prefetch_index_type = atoi\(argv\[18\]\)\;\n");
    print OUT ("//  prefetch_distance = atoi\(argv\[19\]\)\;\n");
    print OUT ("//  rb_size = atoi\(argv\[20\]\)\;\n");
    print OUT ("}\n\n");
    print OUT ("void print_code_variant_parameters\(\) {\n");
    print OUT ("  switch (read_from_type) {\n");
    $case_count = 0;
    foreach $type (@read_from_types) {
	print OUT ("    case $case_count: strcat\(output_str, \"read from type (array=0, variable=1) = $read_from_types_hash{$type}\; \"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("  switch (pointer_type) {\n");
    $case_count = 0;
    foreach $type (@pointer_types) {
	print OUT ("    case $case_count: strcat\(output_str, \"pointer type (fixed=0, moving=1) = $pointer_types_hash{$type}\; \"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("  switch (neighbor_index_type) {\n");
    $case_count = 0;
    foreach $type (@neighbor_index_types) {
	print OUT ("    case $case_count: strcat\(output_str, \"neighbor index type (single ptr per register block=0, per plane=1, per pencil=2) = $neighbor_index_types_hash{$type}\; \"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("  switch (prefetch_index_type) {\n");
    $case_count = 0;
    foreach $type (@prefetch_index_types) {
	print OUT ("    case $case_count: strcat\(output_str, \"prefetch index type (none=0, single prefetch per register block=1, per plane=2, per pencil=3) = $prefetch_index_types_hash{$type}\; \"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("  switch (prefetch_distance) {\n");
    $case_count = 0;
    foreach $distance (@prefetch_distances) {
	print OUT ("    case $case_count: strcat\(output_str, \"prefetch distance = $distance, case number, $case_count\; \"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("  switch (rb_size) {\n");
    $case_count = 0;
    for ($rb_idx=0; $rb_idx < @rb_sizes; $rb_idx++) {
	print OUT ("    case $rb_idx: strcat\(output_str, \"register block size = $rb_sizes[$rb_idx][0], $rb_sizes[$rb_idx][1], $rb_sizes[$rb_idx][2], case number, $rb_idx\;\"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("}\n");
}

# generates the include directives
sub generate_directives {
    print OUT "#include <stdio.h>\n";
    print OUT "#include <stdlib.h>\n";
    print OUT "#include <stdint.h>\n";
    print OUT "#include <mpi.h>\n";
    print OUT "#include <pthread.h>\n";
    print OUT "#include <unistd.h>\n";
    print OUT "#define CALC_DATA_TYPE $precision\n";
    print OUT "#include \"globals.h\"\n";
    print OUT "#include \"../common/intrin.h\"\n";
    print OUT "#include \"../common/prefetch.h\"\n";
    print OUT "#if defined(AFFINITY_ENABLED)\n";
    print OUT "#if defined(__x86_64__)\n";
    print OUT "#include \"../common/affinity.sles.h\"\n";
    print OUT "#elif defined(__sparc) && defined(__GNUC__)\n";
    print OUT "#include \"../common/affinity.solaris.h\"\n";
    print OUT "#else\n";
    print OUT "#include \"../common/affinity.h\"\n";
    print OUT "#endif\n";
    print OUT "#endif\n";
    print OUT "#include \"../common/barrier.h\"\n";
    print OUT "#include \"../common/helper_functions.h\"\n";
    print OUT "#include \"../common/flush_cache.h\"\n";
    print OUT "#include \"grid.h\"\n";
    print OUT "int32_t num_procs, my_proc_num;\n";
    print OUT "char output_str[700];\n";
    print OUT "#include \"code_variant.h\"\n";
    print OUT ("#include \"" . $function_headers_file . "\"\n");
    print OUT ("#include \"" , $main_headers_file . "\"\n");
    print OUT "#if defined(GETTIMEOFDAY)\n";
    print OUT "#include \"../../timers/gettimeofday.h\"\n";
    print OUT "#endif\n";
    print OUT "#if defined(CLOCK_GETTIME)\n";
    print OUT "#include \"../../timers/clock_gettime.h\"\n";
    print OUT "#endif\n";
    print OUT "#include \"../../timers/time_pthreads.h\"\n";
    print OUT "#if defined(CYCLE_TIME)\n";
    print OUT "#include \"../../timers/cycle_time.c\"\n";
    print OUT "#endif\n";
    print OUT "#if defined(GETTIMEOFDAY)\n";
    print OUT "#include \"../../timers/gettimeofday.c\"\n";
    print OUT "#endif\n";
    print OUT "#if defined(CLOCK_GETTIME)\n";
    print OUT "#include \"../../timers/clock_gettime.c\"\n";
    print OUT "#endif\n";
    print OUT "#if (!defined(DEBUG) && defined(PAPI_ENABLED))\n";
    print OUT "#include \"../../papi/papi_util_pthreads.c\"\n";
    print OUT "#endif\n";
    print OUT "#if defined(AFFINITY_ENABLED)\n";
    print OUT "#if defined(__x86_64__)\n";
    print OUT "#include \"../common/affinity.sles.c\"\n";
    print OUT "#elif defined(__sparc) && defined(__GNUC__)\n";
    print OUT "#include \"../common/affinity.solaris.c\"\n";
    print OUT "#else\n";
    print OUT "#include \"../common/affinity.c\"\n";
    print OUT "#endif\n";
    print OUT "#endif\n";
    print OUT "#include \"../common/barrier.c\"\n";
    print OUT "#include \"../common/helper_functions_mpi.c\"\n";
    print OUT "#include \"../common/flush_cache.c\"\n";
    print OUT "#include \"grid_mpi.c\"\n";
    print OUT ("#include \"" . $function_table_file . "\"\n");
    print OUT "#include \"code_variant_mpi.c\"\n";
    print OUT ("#include \"" . $variables_file . "\"\n");
    print OUT ("#include \"" . $functions_file . "\"\n\n");
}

sub generate_per_thread_function_name {
    print OUT (per_thread_function_name_str() . ";\n");
}

sub generate_per_thread_function {
    print OUT (per_thread_function_name_str() . " {\n");
    print OUT ("  int32_t my_thread_num\;\n\n");
    print OUT ("#if defined(PAPI_ENABLED) && !defined(DEBUG)\n");
    print OUT ("  int num_sets\;\n");
    print OUT ("  PAPI_event_set_wrapper_t* event_sets\;\n\n");
    print OUT ("  papi_filter_events\(desired_events, num_desired, &event_sets, &num_sets\)\;\n");
    print OUT ("#endif\n\n");
    print OUT ("  my_thread_num = *\(\(int32_t *\) thread_num_ptr\)\;\n\n");
    print OUT ("#if defined\(AFFINITY_ENABLED\)\n");
    print OUT ("  Affinity_Bind_Thread\(my_thread_num\)\;\n");
    print OUT ("  Affinity_Bind_Memory\(my_thread_num\)\;\n");
    print OUT ("#endif\n\n");
    print OUT ("#if defined(DEBUG)\n");
    print OUT ("  init_grids\(my_thread_num\)\;\n");
    print OUT ("  barrier_wait\(&my_barrier, my_thread_num\)\;\n");
    print OUT ("  if \(my_thread_num == 0\) {\n");
    print OUT ("    printf\(\"\\nGRID A BEFORE:\"\)\;\n");
    print OUT ("    print_grid\(A\)\;\n");
    print OUT ("    printf\(\"\\nGRID B BEFORE:\"\)\;\n");
    print OUT ("    print_grid\(B\)\;\n");
    print OUT ("  }\n");
    print OUT ("  barrier_wait\(&my_barrier, my_thread_num\)\;\n");
    print OUT ("  " . function_table_name_str() . "\(my_thread_num\)\;\n");
    print OUT ("  barrier_wait\(&my_barrier, my_thread_num\)\;\n");
    print OUT ("  if \(my_thread_num == 0\) {\n");
    print OUT ("    printf\(\"\\nGRID A AFTER:\"\)\;\n");
    print OUT ("    print_grid\(A\)\;\n");
    print OUT ("    printf\(\"\\nGRID B AFTER:\"\)\;\n");
    print OUT ("    print_grid\(B\)\;\n");
    print OUT ("    printf\(\"\\n\\n\"\)\;\n");
    print OUT ("  }\n");
    print OUT ("  barrier_wait\(&my_barrier, my_thread_num\)\;\n");
    print OUT ("#else\n");
    print OUT ("#if defined(PAPI_ENABLED)\n");
    print OUT ("  int papi_setnum\;\n\n");
    print OUT ("  for \(papi_setnum=0; papi_setnum < num_sets; papi_setnum++\) {\n");
    print OUT ("    PAPI_MAKE_MEASUREMENTS\(event_sets[papi_setnum].set, " . function_table_name_str() . "\(my_thread_num\), results, NUM_TRIALS*\(papi_setnum*numThreads+my_thread_num\), NUM_TRIALS\)\;\n");
    print OUT ("  }\n");
    print OUT ("  barrier_wait(&my_barrier, my_thread_num)\;\n");
    print OUT ("  if (my_thread_num == 0) {\n");
    print OUT ("    print_papi_measurements\(event_sets, results, num_sets, numThreads, NUM_TRIALS\)\;\n");
    print OUT ("    printf\(\"\\n\\n\"\)\;\n");
    print OUT ("  }\n");
    print OUT ("#else\n");
    print OUT ("  TIMER_MAKE_MEASUREMENTS(" . function_table_name_str() . "(my_thread_num), results, my_thread_num, NUM_TRIALS);\n");
    print OUT ("  barrier_wait(&my_barrier, my_thread_num)\;\n");
    print OUT ("  if \(my_thread_num == 0\) {\n");
    print OUT ("    strcat\(output_str, \"TIME (IN SECONDS) \"\)\;\n");
    print OUT ("#if defined(THREAD_PROFILING)\n");
    print OUT ("    int32_t t\;\n");
    print OUT ("    for \(t=0\; t < numThreads\; t++\) {\n");
    print OUT ("      printf\(\"Thread %d:\\n\", t\)\;\n");
    print OUT ("      print_timer_measurements\(&results[t * NUM_TRIALS], NUM_TRIALS, median_counts_per_sec\)\;\n");
    print OUT ("    }\n");
    print OUT ("#endif\n");
    print OUT ("    print_max_timer_measurements\(results, numThreads, NUM_TRIALS, median_counts_per_sec\)\;\n");
    print OUT ("    printf\(\"%s\\n\\n\", output_str\);\n");
    print OUT ("  }\n");
    print OUT ("#endif\n");
    print OUT ("#endif\n");
    print OUT ("  pthread_exit\(\(void*\) 0\)\;\n");
    print OUT ("}\n\n");
}

# Generates the main function
sub generate_main_function {
    print OUT "int main(int argc, char *argv[]) {\n";
    print OUT "  pthread_t *threads\;\n";
    print OUT "  pthread_attr_t attr\;\n";
    print OUT "  int32_t **ranks\;\n";
    print OUT "  void *status\;\n\n";
    print OUT "  MPI_Init(&argc, &argv);\n";
    print OUT "  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);\n";
    print OUT "  MPI_Comm_rank(MPI_COMM_WORLD, &my_proc_num);\n\n";
    print OUT "#if defined(PAPI_ENABLED) && !defined(DEBUG)\n";
    print OUT "  int num_sets;\n";
    print OUT "  PAPI_event_set_wrapper_t* event_sets\;\n";
    print OUT "#endif\n";
    print OUT "  int rc\;\n";
    print OUT "  int32_t t\;\n\n";
    print OUT "  //printf\(\"7-point stencil, no add, naive C code with non-periodic boundary conditions\\n\"\)\;\n\n";
    print OUT "  init_flush_cache_array\(\)\;\n";
    print OUT "  malloc_grids\(argv\)\;\n";
    print OUT "  print_grid_parameters\(\)\;\n";
    print OUT "  select_code_variant\(argv\)\;\n";
    print OUT "  print_code_variant_parameters\(\)\;\n\n";
    print OUT "  threads = \(pthread_t *\) malloc\(numThreads * sizeof\(pthread_t\)\)\;\n";
    print OUT "  ranks = \(int32_t **\) malloc\(numThreads * sizeof\(int32_t *\)\);\n\n";
    print OUT "#if !defined\(DEBUG\)\n";
    print OUT "#if defined\(PAPI_ENABLED\)\n";
    print OUT "  papi_init\(desired_events, num_desired, &event_sets, &num_sets\)\;\n\n";
    print OUT "  // initialize threaded PAPI\n";
    print OUT "  if \(PAPI_thread_init\(\(unsigned long \(*\)\(void\)\) \(pthread_self\)\) != PAPI_OK\) {\n";
    print OUT "    printf\(\"Error with PAPI_thread_init\(\).\\n\"\)\;\n";
    print OUT "    exit\(EXIT_FAILURE\)\;\n";
    print OUT "  }\n\n";
    print OUT "  results = \(double *\) malloc\(num_sets * numThreads * NUM_TRIALS * sizeof\(double\)\)\;\n";
    print OUT "  if (results==NULL) {\n";
    print OUT "    printf\(\"Error on array results malloc.\\n\"\)\;\n";
    print OUT "    exit\(EXIT_FAILURE\)\;\n";
    print OUT "  }\n";
    print OUT "#else\n";
    print OUT "  results = \(double *\) malloc\(numThreads * NUM_TRIALS * sizeof\(double\)\)\;\n";
    print OUT "  if (results==NULL) {\n";
    print OUT "    printf\(\"Error on array results malloc.\\n\"\)\;\n";
    print OUT "    exit\(EXIT_FAILURE\)\;\n";
    print OUT "  }\n";
    print OUT "#if defined\(CYCLE_TIME\)\n";
    print OUT "  // calculate clock rate\n";
    print OUT "  GET_CLOCK_RATE\(results, NUM_TRIALS\)\;\n";
    print OUT "  median_counts_per_sec = find_median\(results, NUM_TRIALS\)\;\n";
    print OUT "  //printf\(\"Median ticks per second = %e\\n\", median_counts_per_sec\)\;\n\n";
    print OUT "#else\n";
    print OUT "  timer_init();\n";
    print OUT "  median_counts_per_sec = 1.0;\n";
    print OUT "#endif\n";
    print OUT "#endif\n";
    print OUT "#endif\n\n";
    print OUT "  pthread_attr_init\(&attr\)\;\n";
    print OUT "  pthread_attr_setdetachstate\(&attr, PTHREAD_CREATE_JOINABLE\)\;\n";
    print OUT "  barrier_init\(&my_barrier, numThreads\)\;\n";
    print OUT "#if defined\(AFFINITY_ENABLED\)\n";
    print OUT "  Affinity_Init\(\)\;\n";
    print OUT "#endif\n\n";
    print OUT "  // run stencil tests\n";
    print OUT "  for \(t=0\; t < numThreads\; t++\) {\n";
    print OUT "    ranks[t] = \(int32_t *\) malloc\(sizeof\(int32_t\)\);\n";
    print OUT "    *ranks[t] = t\;\n";
    print OUT "  }\n\n";
    print OUT "  for \(t=1\; t < numThreads\; t++\) {\n";
    print OUT "#if defined\(DEBUG\)\n";
    print OUT "    printf\(\"Creating thread %d\\n\", t);\n";
    print OUT "#endif\n";
    print OUT "    rc = pthread_create\(&threads[t], &attr, pthreads_each, \(void *\) ranks[t]\)\;\n";
    print OUT "    if \(rc\) \{\n";
    print OUT "      printf\(\"ERROR\; return code from pthread_create\(\) is %d\\n\", rc\)\;\n";
    print OUT "      exit\(EXIT_FAILURE\)\;\n";
    print OUT "    }\n";
    print OUT "  }\n";
    print OUT "  pthreads_each(\(void *\) ranks[0]\)\;\n\n";
    print OUT "  // join the other threads\n";
    print OUT "  for \(t=1\; t < numThreads\; t++\) {\n";
    print OUT "    pthread_join\(threads[t], &status\)\;\n";
    print OUT "  }\n\n";
    print OUT ("  //printf\(\"\\nFinal interior values: A[%d, %d, %d] = %4.2e, B[%d, %d, %d] = %4.2e\\n\\n\", nx/2, ny/2, nz/2, A[Index3D\(nx/2, ny/2, nz/2\)], nx/2, ny/2, nz/2, B[Index3D\(nx/2, ny/2, nz/2\)]\);\n\n");
    print OUT "#if defined\(PAPI_ENABLED\) && !defined\(DEBUG\)\n";
    print OUT "  papi_cleanup\(event_sets, num_sets\)\;\n";
    print OUT "#endif\n";
    print OUT ("  pthread_attr_destroy\(&attr\);\n");
    print OUT ("  pthread_exit\(NULL\)\;\n");
    print OUT ("  barrier_destroy\(&my_barrier\)\;\n");
    print OUT ("  free_grids\(\);\n\n");
    print OUT ("  return EXIT_SUCCESS;\n");
    print OUT ("}\n");
}

sub generate_specified_mpi_3D_27pt_cse_data_script {
    print OUT ("#!/usr/bin/perl -w\n\n");
    print OUT ("\$platform=\$ARGV[0]\;\n");
    print OUT ("\$compiler=\$ARGV[1]\;\n\n");
    print OUT ("my \$exec_file = \"./stencil_pthreads_\${compiler}_c\"\;\n");
    print OUT ("\@numIter_values = (1);\n");
    print OUT ("\@log2_nreals_x_values = (8)\;\n");
    print OUT ("\@log2_nreals_y_values = (8)\;\n");
    print OUT ("\@log2_nreals_z_values = (8)\;\n");
    print OUT ("\@log2_numThreads_values = (2)\;\n");
    print OUT ("\@padding_values = (0..31)\;\n");
    print OUT ("\@log2_numCoreBlockCells_x_values = (6)\;\n");
    print OUT ("\@log2_numCoreBlockCells_y_values = (8)\;\n");
    print OUT ("\@log2_numCoreBlockCells_z_values = (8)\;\n");
    print OUT ("\@read_from_type_values = (0.." . (@read_from_types-1) . ")\;\n");
    print OUT ("\@pointer_type_values = (0.." . (@pointer_types-1) . ")\;\n");
    print OUT ("\@neighbor_index_type_values = (0.." . (@neighbor_index_types-1) . ")\;\n");
    print OUT ("\@prefetch_index_type_values = (0.." . (@prefetch_index_types-1) . ")\;\n");
    print OUT ("\@prefetch_distance_values = (0.." . (@prefetch_distances-1) . ")\;\n");
    print OUT ("\@rb_size_values = (0.." . (@rb_sizes-1) . ")\;\n\n");
    print OUT ("foreach \$numIter (\@numIter_values) {\n");
    print OUT ("\tforeach \$log2_nreals_x (\@log2_nreals_x_values) {\n");
    print OUT ("\t\tmy \$nreals_x = 2**(\$log2_nreals_x)\;\n");
    print OUT ("\t\tforeach \$log2_nreals_y (\@log2_nreals_y_values) {\n");
    print OUT ("\t\t\tmy \$nreals_y = 2**(\$log2_nreals_y)\;\n");
    print OUT ("\t\t\tforeach \$log2_nreals_z (\@log2_nreals_z_values) {\n");
    print OUT ("\t\t\t\tmy \$nreals_z = 2**(\$log2_nreals_z)\;\n");
    print OUT ("\t\t\t\tforeach \$log2_numThreads (\@log2_numThreads_values) {\n");
    print OUT ("\t\t\t\t\tmy \$numThreads = 2**(\$log2_numThreads)\; # 1 to 8 in powers of 2\n");
    print OUT ("\t\t\t\t\tmy \$output_file = (\"./\" . \$platform . \"_\" . \$compiler . \"_specified_27pt_cse_\" . \$nreals_x . \"_\" . \$nreals_y . \"_\" . \$nreals_z . \"_\" . \$numIter . \"i_\" . \$numThreads . \"t.txt\");\n");
    print OUT ("\t\t\t\t\tforeach \$padding (\@padding_values) {\n");
    print OUT ("\t\t\t\t\t\tforeach \$log2_numCoreBlockCells_x (\@log2_numCoreBlockCells_x_values) {\n");
    print OUT ("\t\t\t\t\t\t\tmy \$numCoreBlockCells_x = 2**(\$log2_numCoreBlockCells_x); # 2 to \$nreals_x in powers of 2\n");
    print OUT ("\t\t\t\t\t\t\tforeach \$log2_numCoreBlockCells_y (\@log2_numCoreBlockCells_y_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\tmy \$numCoreBlockCells_y = 2**(\$log2_numCoreBlockCells_y); # 2 to \$nreals_y in powers of 2\n");
    print OUT ("\t\t\t\t\t\t\t\tforeach \$log2_numCoreBlockCells_z (\@log2_numCoreBlockCells_z_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\tmy \$numCoreBlockCells_z = 2**(\$log2_numCoreBlockCells_z); # 8 to \$nreals_z in powers of 2\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\@log2_numCoreBlocksPerChunk_values = (0)\;\n");
    print OUT ("\t\t\t\t\t\t\t\t\tforeach \$log2_numCoreBlocksPerChunk (\@log2_numCoreBlocksPerChunk_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\tmy \$numCoreBlocksPerChunk = 2**(\$log2_numCoreBlocksPerChunk)\;\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\tforeach \$read_from_type (\@read_from_type_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\tforeach \$pointer_type (\@pointer_type_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\tforeach \$neighbor_index_type (\@neighbor_index_type_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\tforeach \$prefetch_index_type (\@prefetch_index_type_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\t\tforeach \$prefetch_distance (\@prefetch_distance_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tforeach \$rb_size (\@rb_size_values) {\n");
    print OUT ("#\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tsystem (\"echo \\\"Start Time:\\\" >> \$output_file\")\;\n");
    print OUT ("#\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tsystem (\"date >> \$output_file\")\;\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tsystem (\"qsub -n 64 -t 19 -q prod-devel \$exec_file \$numIter \$nreals_x \$nreals_y \$nreals_z \$numThreads \$padding \$numCoreBlockCells_x \$numCoreBlockCells_y \$numCoreBlockCells_z \$numCoreBlocksPerChunk 0 0 0 \$read_from_type \$pointer_type \$neighbor_index_type 0 \$prefetch_index_type \$prefetch_distance \$rb_size >> \$output_file\")\;\n");
    print OUT ("#\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tsystem (\"echo \\\"End Time:\\\" >> \$output_file\")\;\n");
    print OUT ("#\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tsystem (\"date >> \$output_file\")\;\n");
    print OUT ("#\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tsystem (\"echo \\\"***************************************\\\" >> \$output_file\")\;\n");
    print OUT ("#\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tsystem (\"echo >> \$output_file\")\;\n");
    print OUT ("#\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tsystem (\"echo >> \$output_file\")\;\n");
    print OUT ("#\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tsystem (\"sleep 5\")\;\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t}\n");
    print OUT ("\t\t\t}\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n");
    print OUT ("}\n");
    system ("chmod 755 specified_mpi_3D_27pt_cse_data_generator.pl");
}
