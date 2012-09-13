#!/usr/bin/perl -w

### BELOW ARE THE TUNABLE PARAMETERS ###

$platform = $ARGV[0];

# "complete" or "individual" statements
@statement_types = ("complete", "individual");

# read from "array" or "variable"
@read_from_types = ("array", "variable");

# "fixed" or "moving" pointers
@pointer_types = ("fixed", "moving");

# single ptr per "register_block", "plane", or "pencil"
@neighbor_index_types = ("register_block", "plane", "pencil");

# "noFMA" or "FMA"-like
@fma_ins_types = ("noFMA", "FMA");

# register block sizes (starts at 1)
@rb_sizes = ([1,1,1], [2,2,2]);

# no clean up code (0) or clean up code (1)
$clean_up_code = 0;

### BELOW IS THE PERL SCRIPT'S "MAIN" SUBROUTINE ###

# "center" and "neighbors" can only contain non-negative integers
@center = ([1,1,1]);
# the order of the "neighbors" array is the order shown in the code
@neighbors = ([0,1,1], [1,0,1], [1,1,0], [1,1,2], [1,2,1], [2,1,1]);
$num_neighbors = @neighbors;

$function_headers_file = ("function_headers.h");
open(OUT, ">$function_headers_file") || die ("Couldn't create $function_headers_file.\n");
generate_all_stencil_functions("function_headers");
close(OUT) || die;

$function_table_file = ("function_table.c");
open(OUT, ">$function_table_file") || die ("Couldn't create $function_table_file.\n");
generate_all_stencil_functions("function_table");
close(OUT) || die;

$functions_file = ("functions.c");
open(OUT, ">$functions_file") || die ("Couldn't create $functions_file.\n");
generate_all_stencil_functions("generate");
close(OUT) || die;

$main_file = ("serial_code.c");
open(OUT, ">$main_file") || die ("Couldn't create $main_file.\n");
generate_include_directives();
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

# adds the two input points (must be passed in the specific manner shown in the code)
sub add_points {
    my(@my_pts) = @_;

    @my_pt1 = ($my_pts[0][0], $my_pts[0][1], $my_pts[0][2]);
    @my_pt2 = ($my_pts[1], $my_pts[2], $my_pts[3]);
    @sum = (0, 0, 0);

    for ($dim=0; $dim < 3; $dim++) {
	$sum[$dim] = $my_pt1[$dim] + $my_pt2[$dim];
    }

    return @sum;
}

# Converts 3D points to a flattened 1D distance
# @my_idx is the point to be converted
sub convert_idx_to_str {
    my(@my_idx) = @_;

    $str = "";

    for ($dim=0; $dim<3; $dim++) {
	if ($dim == 0) {
	    $dim_str = "plane_size";
	}
	elsif ($dim == 1) {
	    $dim_str = "nz";
	}

	if ($dim < 2) {
	    if ($my_idx[$dim] < -1) {
		$str = ($str . $my_idx[$dim] . "*" . $dim_str);
	    }
	    elsif ($my_idx[$dim] == -1) {
		$str = ($str . "-" . $dim_str);
	    }
	    elsif ($my_idx[$dim] == 1) {
		$str = ($str . "+" . $dim_str);
	    }
	    elsif ($my_idx[$dim] > 1) {
		$str = ($str . "+" . $my_idx[$dim] . "*" . $dim_str);
	    }
	}
	else {
	    if ($my_idx[$dim] < 0) {
		$str = ($str . $my_idx[$dim]);
	    }
	    elsif ($my_idx[$dim] > 0) {
		$str = ($str . "+" . $my_idx[$dim]);
	    }
	}
    }

    return $str;
}

# Returns the function name as a string
sub function_name_str {
    return ("stencil_" . substr($statement_type, 0, 2) . "_" . substr($read_from_type, 0, 2) . "_" . substr($pointer_type, 0, 2) . "_" . substr($neighbor_index_type, 0, 2) . "_" . $fma_ins_type . "_" . $rb_size[0] . "x" . $rb_size[1] . "x" . $rb_size[2] . "RB");
}

sub function_table_name_str {
    return ("stencil[i1][i2][i3][i4][i5][i6]");
}

# Generates a reference name (either a variable or array reference)
# $my_read_from equals either "array" or "variable"
# $my_read_or_write equals either "read" or "write"
# @my_rb_size is a 3D coordinate
sub reference_name {
    my($my_read_from, $my_read_or_write, @my_rb_size) = @_;

    if (($my_read_from eq "array") && ($pointer_type eq "fixed")) {
	@fixed_ptr_idx = ();
	
	for ($idx=0; $idx < $fixed_ptr_indices_length; $idx++) {
	    if ($my_rb_size[0] > $fixed_ptr_indices[$idx][0]) {
		@fixed_ptr_idx = ($fixed_ptr_indices[$idx][0], $fixed_ptr_indices[$idx][1], $fixed_ptr_indices[$idx][2]);
	    }
	    elsif ($my_rb_size[0] == $fixed_ptr_indices[$idx][0]) {
		if ($my_rb_size[1] >= $fixed_ptr_indices[$idx][1]) {
		    @fixed_ptr_idx = ($fixed_ptr_indices[$idx][0], $fixed_ptr_indices[$idx][1], $fixed_ptr_indices[$idx][2]);
		}
	    }
	}
	@diff_pt = ($my_rb_size[0]-$fixed_ptr_idx[0], $my_rb_size[1]-$fixed_ptr_idx[1], $my_rb_size[2]-$fixed_ptr_idx[2]);
	$idx_str = ("[i_" . $fixed_ptr_idx[0] . "_" . $fixed_ptr_idx[1] . "_" . $fixed_ptr_idx[2] . convert_idx_to_str(@diff_pt) . "]");
	if ($my_read_or_write eq "read") {
	    return ("Read_start" . $idx_str);
	}
	elsif ($my_read_or_write eq "write") {
	    return ("Write_start" . $idx_str);
	}
    }
    else {
	$idx_str = ($my_rb_size[0] . "_" . $my_rb_size[1] . "_" . $my_rb_size[2]);
	if ($my_read_from eq "variable") {
	    if ($my_read_or_write eq "read") {
		return ("read_rb_" . $idx_str);
	    }
	    elsif ($my_read_or_write eq "write") {
		return ("write_rb_" . $idx_str);
	    }
	}
	elsif ($pointer_type eq "moving") {
	    if ($my_read_or_write eq "read") {
		return ("Read_rb_" . $idx_str);
	    }
	    elsif ($my_read_or_write eq "write") {
		return ("Write_rb_" . $idx_str);
	    }
	}
    }
}

### BELOW ARE THE BUILDING BLOCK SUBROUTINES ###

# Declares or initializes the register block read variables
# $code_type can equal either "declaration" or "initialization"
# @my_rb_size is a 3D coordinate
sub rb_read_vars {
    my($code_type, @my_rb_size) = @_;

    if ($code_type eq "declaration") {
	print OUT ("  double ");
	$is_first_var = 1;
    }

    @rb_pt = (0, 0, 0);

    for ($rb_pt[0]=0; $rb_pt[0] <= ($my_rb_size[0]+1); $rb_pt[0]++) {
	for ($rb_pt[1]=0; $rb_pt[1] <= ($my_rb_size[1]+1); $rb_pt[1]++) {
	    for ($rb_pt[2]=0; $rb_pt[2] <= ($my_rb_size[2]+1); $rb_pt[2]++) {
		$count = 0;
		for ($dim=0; $dim < 3; $dim++) {
		    if (($rb_pt[$dim] == 0) || ($rb_pt[$dim] == ($my_rb_size[$dim]+1))) {
			$count++;
		    }
		}
		if ($count < 2) {
		    if ($code_type eq "declaration") {
			if ($is_first_var) {
			    $is_first_var = 0;
			}
			else {
			    print OUT (", ");
			}
			print OUT reference_name("variable", "read", @rb_pt);
		    }
		    elsif ($code_type eq "initialization") {
			if ($pointer_type eq "fixed") {
			    print OUT ("          " . reference_name("variable", "read", @rb_pt) . " = " . reference_name("array", "read", @rb_pt) . ";\n");
			}
			elsif ($pointer_type eq "moving") {
			    @pointer = ($rb_pt[0]-1, $rb_pt[1]-1, $rb_pt[2]-1);
			    @offset = (1, 1, 1);

			    for ($dim=0; $dim < 3; $dim++) {
				if ($rb_pt[$dim] == 0) {
				    $pointer[$dim]++;
				    $offset[$dim]--;
				}
				elsif ($rb_pt[$dim] == ($my_rb_size[$dim]+1)) {
				    $pointer[$dim]--;
				    $offset[$dim]++;
				}
			    }

			    @offset_array = ([$offset[0], $offset[1], $offset[2]]);
			    print OUT ("          " . reference_name("variable", "read", @rb_pt) . " = " . reference_name("array", "read", @pointer) . moving_pointer_idx($offset_array[0]) . ";\n");
			}
		    }
		}
	    }
	}
    }
    if ($code_type eq "declaration") {
	print OUT (";\n");
    }
    elsif ($code_type eq "initialization") {
	print OUT ("\n");
    }
}

# Declares or initializes the register block write variables
# @my_rb_size is a 3D coordinate
sub rb_write_vars {
    my(@my_rb_size) = @_;

    print OUT ("  double ");

    @rb_pt = (1, 1, 1);

    for ($rb_pt[0]=1; $rb_pt[0] <= $my_rb_size[0]; $rb_pt[0]++) {
	for ($rb_pt[1]=1; $rb_pt[1] <= $my_rb_size[1]; $rb_pt[1]++) {
	    for ($rb_pt[2]=1; $rb_pt[2] <= $my_rb_size[2]; $rb_pt[2]++) {
		print OUT reference_name("variable", "write", @rb_pt);
		if (($rb_pt[0] == $my_rb_size[0]) && ($rb_pt[1] == $my_rb_size[1]) && ($rb_pt[2] == $my_rb_size[2])) {
		    print OUT (";\n");
		}
		else {
		    print OUT (", ");
		}
	    }
	}
    }
}

sub find_fixed_ptr_indices {
    my(@my_rb_size) = @_;

    @rb_pt = (0, 0, 0);
    $candidate_fixed_ptr_indices_length = 0;
    @candidate_fixed_ptr_indices = ();

    # find all the stencil indices for this register block
    for ($rb_pt[0]=0; $rb_pt[0] < $my_rb_size[0]; $rb_pt[0]++) {
	for ($rb_pt[1]=0; $rb_pt[1] < $my_rb_size[1]; $rb_pt[1]++) {
	    for ($rb_pt[2]=0; $rb_pt[2] < $my_rb_size[2]; $rb_pt[2]++) {
		foreach $neighbors_idx (@neighbors_indices) {
		    @neighbor_pt = ($neighbors[$neighbors_idx][0], $neighbors[$neighbors_idx][1], $neighbors[$neighbors_idx][2]);
		    @candidate_fixed_ptr_indices = (@candidate_fixed_ptr_indices, [$neighbor_pt[0] + $rb_pt[0], $neighbor_pt[1] + $rb_pt[1], $neighbor_pt[2] + $rb_pt[2]]);
		    $candidate_fixed_ptr_indices_length++;
		}
	    }
	}
    }

    @fixed_ptr_indices = ();
    $fixed_ptr_indices_length = 0;
    @low_pt = (0,0,0);

    # find the fixed ptr indices for a REGISTER BLOCK
    if ($neighbor_index_type eq "register_block") {
	$idx_found = 0;
	for ($idx=0; $idx < $candidate_fixed_ptr_indices_length; $idx++) {
	    @candidate_fixed_ptr_idx = ($candidate_fixed_ptr_indices[$idx][0], $candidate_fixed_ptr_indices[$idx][1], $candidate_fixed_ptr_indices[$idx][2]);
	    if ($candidate_fixed_ptr_idx[0] == $low_pt[0]) {
		if ($idx_found == 0) {
		    @fixed_ptr_idx = @candidate_fixed_ptr_idx;
		    $idx_found = 1;
		}
		elsif ($candidate_fixed_ptr_idx[1] < $fixed_ptr_idx[1]) {
		    @fixed_ptr_idx = @candidate_fixed_ptr_idx;
		}
		elsif ($candidate_fixed_ptr_idx[1] == $fixed_ptr_idx[1]) {
		    if ($candidate_fixed_ptr_idx[2] < $fixed_ptr_idx[2]) {
			@fixed_ptr_idx = @candidate_fixed_ptr_idx;
		    }
		}
	    }
	}
	if ($idx_found == 1) {
	    @fixed_ptr_indices = (@fixed_ptr_indices, [$fixed_ptr_idx[0], $fixed_ptr_idx[1], $fixed_ptr_idx[2]]);
	    $fixed_ptr_indices_length++;
	}
    }
    
    # find the fixed ptr indices for a PLANE
    if ($neighbor_index_type eq "plane") {
	for ($low_pt[0]=0; $low_pt[0] < ($my_rb_size[0]+5); $low_pt[0]++) {
	    $idx_found = 0;
	    for ($idx=0; $idx < $candidate_fixed_ptr_indices_length; $idx++) {
		@candidate_fixed_ptr_idx = ($candidate_fixed_ptr_indices[$idx][0], $candidate_fixed_ptr_indices[$idx][1], $candidate_fixed_ptr_indices[$idx][2]);
		if ($candidate_fixed_ptr_idx[0] == $low_pt[0]) {
		    if ($idx_found == 0) {
			@fixed_ptr_idx = @candidate_fixed_ptr_idx;
			$idx_found = 1;
		    }
		    elsif ($candidate_fixed_ptr_idx[1] < $fixed_ptr_idx[1]) {
			@fixed_ptr_idx = @candidate_fixed_ptr_idx;
		    }
		    elsif ($candidate_fixed_ptr_idx[1] == $fixed_ptr_idx[1]) {
			if ($candidate_fixed_ptr_idx[2] < $fixed_ptr_idx[2]) {
			    @fixed_ptr_idx = @candidate_fixed_ptr_idx;
			}
		    }
		}
	    }
	    if ($idx_found == 1) {
		@fixed_ptr_indices = (@fixed_ptr_indices, [$fixed_ptr_idx[0], $fixed_ptr_idx[1], $fixed_ptr_idx[2]]);
		$fixed_ptr_indices_length++;
	    }
	}
    }

    # find the fixed ptr indices for a PENCIL
    if ($neighbor_index_type eq "pencil") {
	for ($low_pt[0]=0; $low_pt[0] < ($my_rb_size[0]+5); $low_pt[0]++) {
	    for ($low_pt[1]=0; $low_pt[1] < ($my_rb_size[1]+5); $low_pt[1]++) {
		$idx_found = 0;
		for ($idx=0; $idx < $candidate_fixed_ptr_indices_length; $idx++) {
		    @candidate_fixed_ptr_idx = ($candidate_fixed_ptr_indices[$idx][0], $candidate_fixed_ptr_indices[$idx][1], $candidate_fixed_ptr_indices[$idx][2]);
		    if ($candidate_fixed_ptr_idx[0] == $low_pt[0]) {
			if ($candidate_fixed_ptr_idx[1] == $low_pt[1]) {
			    if ($idx_found == 0) {
				@fixed_ptr_idx = @candidate_fixed_ptr_idx;
				$idx_found = 1;
			    }
			    elsif ($candidate_fixed_ptr_idx[2] < $fixed_ptr_idx[2]) {
				@fixed_ptr_idx = @candidate_fixed_ptr_idx;
			    }
			}
		    }
		}
		if ($idx_found == 1) {
		    @fixed_ptr_indices = (@fixed_ptr_indices, [$fixed_ptr_idx[0], $fixed_ptr_idx[1], $fixed_ptr_idx[2]]);
		    $fixed_ptr_indices_length++;
		}
	    }
	}
    }
}

# @my_rb_size is a 3D coordinate
sub init_fixed_ptr_indices {
    my(@my_rb_size) = @_;

    for ($idx=0; $idx < $fixed_ptr_indices_length; $idx++) {
	print OUT ("        uint32_t i_", $fixed_ptr_indices[$idx][0], "_", $fixed_ptr_indices[$idx][1], "_", $fixed_ptr_indices[$idx][2], " = Index3D(i", i2s($fixed_ptr_indices[$idx][0]-1), ",j", i2s($fixed_ptr_indices[$idx][1]-1), ",realMin_z", i2s($fixed_ptr_indices[$idx][2]-1), ");\n");
    }
    
    print OUT ("\n");
}

sub init_fixed_ptrs {
    print OUT ("  double * __restrict__ Read_start = A;\n");
    print OUT ("  double * __restrict__ Write_start = B;\n\n");
}

# initializes the indices for moving pointers (which are constant)
sub init_moving_ptr_indices {
    foreach $neighbors_idx (@neighbors_indices) {
	@neighbor_pt = ($neighbors[$neighbors_idx][0], $neighbors[$neighbors_idx][1], $neighbors[$neighbors_idx][2]);
	print OUT ("  const uint32_t i_" . $neighbor_pt[0] . "_" . $neighbor_pt[1] . "_" . $neighbor_pt[2] . " = " . remove_front_plus(convert_idx_to_str(@neighbor_pt)) . ";\n");
    }
    print OUT ("\n");
}

# @my_rb_size is a 3D coordinate
sub init_moving_ptrs {
    my(@my_rb_size) = @_;

    @rb_pt = (0, 0, 0);

    print OUT ("        " . reference_name("array", "read", @rb_pt) . " = Read_start + Index3D(i-" . $center[0][0] . ",j-" . $center[0][1] . ",realMin_z-" . $center[0][2] . ");\n");
    print OUT ("        " . reference_name("array", "write", @rb_pt) . " = Write_start + Index3D(i-" . $center[0][0] . ",j-" . $center[0][1] . ",realMin_z-" . $center[0][2] . ");\n");

    for ($rb_pt[0]=0; $rb_pt[0] < $my_rb_size[0]; $rb_pt[0]++) {
	for ($rb_pt[1]=0; $rb_pt[1] < $my_rb_size[1]; $rb_pt[1]++) {
	    for ($rb_pt[2]=0; $rb_pt[2] < $my_rb_size[2]; $rb_pt[2]++) {
		if (($rb_pt[0] != 0) || ($rb_pt[1] != 0) || ($rb_pt[2] != 0)) {
		    print OUT ("        " . reference_name("array", "read", @rb_pt) . " = " . reference_name("array", "read", (0, 0, 0)) . convert_idx_to_str(@rb_pt) . ";\n");
		    print OUT ("        " . reference_name("array", "write", @rb_pt) . " = " . reference_name("array", "write", (0, 0, 0)) . convert_idx_to_str(@rb_pt) . ";\n");
		}
	    }
	}
    }
    print OUT ("\n");
}

# @my_pt is the point we'd like to convert to an index for moving pointers
sub moving_pointer_idx {
    my(@my_pt) = @_;

    @my_neighbor = ($my_pt[0][0], $my_pt[0][1], $my_pt[0][2]);

    $closest_neighbor_found = 0;
    foreach $neighbors_idx (reverse @neighbors_indices) {
	@candidate_neighbor = ($neighbors[$neighbors_idx][0], $neighbors[$neighbors_idx][1], $neighbors[$neighbors_idx][2]);
	if (!$closest_neighbor_found) {
	    if ($candidate_neighbor[0] < $my_neighbor[0]) {
		$closest_neighbor_found = 1;
	    }
	    elsif ($candidate_neighbor[0] == $my_neighbor[0]) {
		if ($candidate_neighbor[1] < $my_neighbor[1]) {
		    $closest_neighbor_found = 1;
		}
		elsif ($candidate_neighbor[1] == $my_neighbor[1]) {
		    if ($candidate_neighbor[2] <= $my_neighbor[2]) {
			$closest_neighbor_found = 1;
		    }
		}
	    }
	    if ($closest_neighbor_found) {
		@closest_neighbor = @candidate_neighbor;
	    }
	}
    }

    $idx_str = "i";
    @offset = (0, 0, 0);
    for ($dim=0; $dim<3; $dim++) {
	$idx_str = ($idx_str . "_" . $closest_neighbor[$dim]);
	$offset[$dim] = $my_neighbor[$dim] - $closest_neighbor[$dim];
    }

    return ("[" . $idx_str . convert_idx_to_str(@offset) . "]");
}

# @my_rb_size is a 3D coordinate
sub advance_fixed_ptrs {
    my(@my_rb_size) = @_;

    for ($idx=0; $idx < $fixed_ptr_indices_length; $idx++) {
	if ($my_rb_size[2] == 1) {
	    print OUT ("          i_" . $fixed_ptr_indices[$idx][0] . "_" . $fixed_ptr_indices[$idx][1] . "_" . $fixed_ptr_indices[$idx][2] . "++;\n");
	}
	else {
	    print OUT ("          i_" . $fixed_ptr_indices[$idx][0] . "_" . $fixed_ptr_indices[$idx][1] . "_" . $fixed_ptr_indices[$idx][2] . " += " . $my_rb_size[2] . ";\n");
	}
    }
}

# @my_rb_size is a 3D coordinate
sub advance_moving_ptrs {
    my(@my_rb_size) = @_;

    @rb_pt = (0, 0, 0);

    for ($rb_pt[0]=0; $rb_pt[0] < $my_rb_size[0]; $rb_pt[0]++) {
	for ($rb_pt[1]=0; $rb_pt[1] < $my_rb_size[1]; $rb_pt[1]++) {
	    for ($rb_pt[2]=0; $rb_pt[2] < $my_rb_size[2]; $rb_pt[2]++) {
		if ($my_rb_size[2] == 1) {
		    print OUT ("          " . reference_name("array", "read", @rb_pt) . "++;\n");
		    print OUT ("          " . reference_name("array", "write", @rb_pt) . "++;\n");
		}
		else {
		    print OUT ("          " . reference_name("array", "read", @rb_pt) . " += " . $my_rb_size[2] . ";\n");
		    print OUT ("          " . reference_name("array", "write", @rb_pt) . " += " . $my_rb_size[2] . ";\n");
		}
	    }
	}
    }
}

### BELOW ARE THE SUBROUTINES THAT MAKE THE NESTED LOOPS ###

# Generates individual statements within the z-dimensional (smallest) loop
sub inner_loop_statement {
    my($my_current_write_point_str, $my_ins_ctr, @my_rb_pt) = @_;
    
    if ($fma_ins_type eq "noFMA") {
	if ($my_ins_ctr < ($num_neighbors-1)) {
	    if (($pointer_type eq "moving") && ($read_from_type eq "array")) {
		$current_read_point_str = (reference_name($read_from_type, "read", @my_rb_pt) . moving_pointer_idx($neighbors[$my_ins_ctr]));
		$next_point_str = (reference_name($read_from_type, "read", @my_rb_pt) . moving_pointer_idx($neighbors[$my_ins_ctr+1]));
	    }
	    else {
		$current_read_point_str = reference_name($read_from_type, "read", add_points($neighbors[$my_ins_ctr], @my_rb_pt));
		$next_point_str = reference_name($read_from_type, "read", add_points($neighbors[$my_ins_ctr+1], @my_rb_pt));
	    }
	}
	elsif ($my_ins_ctr == $num_neighbors) {
	    if (($pointer_type eq "moving") && ($read_from_type eq "array")) {
		$current_read_point_str = (reference_name($read_from_type, "read", @my_rb_pt) . moving_pointer_idx($center[0]));
	    }
	    else {
		$current_read_point_str = reference_name($read_from_type, "read", add_points($center[0], @my_rb_pt));
	    }
	}
	
	if ($my_ins_ctr == 0) {
	    if ($statement_type eq "complete") {
		print OUT ("S1 * (" . $current_read_point_str . " + " . $next_point_str);
	    }
	    elsif ($statement_type eq "individual") {
		print OUT ($my_current_write_point_str . " = " . $current_read_point_str . " + " . $next_point_str . ";\n");
	    }
	}
	elsif ($my_ins_ctr < ($num_neighbors-1)) {
	    if ($statement_type eq "complete") {
		print OUT (" + " . $next_point_str);
	    }
	    elsif ($statement_type eq "individual") {
		print OUT ($my_current_write_point_str . " += " . $next_point_str . ";\n");
	    }
	}
	elsif ($my_ins_ctr == ($num_neighbors-1)) {
	    if ($statement_type eq "individual") {
		print OUT ($my_current_write_point_str . " *= S1;\n");
	    }
	}
	elsif ($my_ins_ctr == $num_neighbors) {
	    if ($statement_type eq "complete") {
		print OUT (") + S0 * " . $current_read_point_str . ";\n");
	    }
	    elsif ($statement_type eq "individual") {
		print OUT ($my_current_write_point_str . " += S0 * " . $current_read_point_str . ";\n");
	    }
	}
	elsif ($my_ins_ctr == ($num_neighbors+1)) {
	    if ($statement_type eq "individual") {
		if ($pointer_type eq "fixed") {
		    print OUT (reference_name("array", "write", add_points($center[0], @my_rb_pt)) . " = " . $my_current_write_point_str . ";\n");
		}
		elsif ($pointer_type eq "moving") {
		    print OUT (reference_name("array", "write", @my_rb_pt) . moving_pointer_idx($center[0]) . " = " . $my_current_write_point_str . ";\n");
		}
	    }
	}
    }
    elsif ($fma_ins_type eq "FMA") {
	if ($my_ins_ctr < $num_neighbors) {
	    if (($pointer_type eq "moving") && ($read_from_type eq "array")) {
		$current_read_point_str = (reference_name($read_from_type, "read", @my_rb_pt) . moving_pointer_idx($neighbors[$my_ins_ctr]));
	    }
	    else {
		$current_read_point_str = reference_name($read_from_type, "read", add_points($neighbors[$my_ins_ctr], @my_rb_pt));
	    }
	}
	elsif ($my_ins_ctr == $num_neighbors) {
	    if (($pointer_type eq "moving") && ($read_from_type eq "array")) {
		$current_read_point_str = (reference_name($read_from_type, "read", @my_rb_pt) . moving_pointer_idx($center[0]));
	    }
	    else {
		$current_read_point_str = reference_name($read_from_type, "read", add_points($center[0], @my_rb_pt));
	    }
	}

	if ($my_ins_ctr == 0) {
	    if ($statement_type eq "complete") {
		print OUT (" S1 * " . $current_read_point_str);
	    }
	    elsif ($statement_type eq "individual") {
		print OUT ($my_current_write_point_str . " = S1 * " . $current_read_point_str . ";\n");
	    }
	}
	elsif ($my_ins_ctr < $num_neighbors) {
	    if ($statement_type eq "complete") {
		print OUT (" + S1 * " . $current_read_point_str);
	    }
	    elsif ($statement_type eq "individual") {
		print OUT ($my_current_write_point_str . " += S1 * " . $current_read_point_str . ";\n");
	    }
	}
	elsif ($my_ins_ctr == $num_neighbors) {
	    if ($statement_type eq "complete") {
		print OUT (" + S0 * " . $current_read_point_str . ";\n");
	    }
	    elsif ($statement_type eq "individual") {
		print OUT ($my_current_write_point_str . " += S0 * " . $current_read_point_str . ";\n");
	    }
	}
	elsif ($my_ins_ctr == ($num_neighbors+1)) {
	    if ($statement_type eq "individual") {
		if ($pointer_type eq "fixed") {
		    print OUT (reference_name("array", "write", add_points($center[0], @my_rb_pt)) . " = " . $my_current_write_point_str . ";\n");
		}
		elsif ($pointer_type eq "moving") {
		    print OUT (reference_name("array", "write", @my_rb_pt) . moving_pointer_idx($center[0]) . " = " . $my_current_write_point_str . ";\n");
		}
	    }
	}
    }
}

# Generates the code within the z-dimensional (smallest) loop
# @my_rb_size is a 3D coordinate
sub inner_loop_code {
    my(@my_rb_size) = @_;

    $ins_ctr_max = $num_neighbors + 2;

    if ($read_from_type eq "variable") {
	rb_read_vars("initialization", @my_rb_size);
    }

    @rb_pt = (0, 0, 0);

    if ($statement_type eq "complete") {
	for ($rb_pt[0] = 0; $rb_pt[0] < $my_rb_size[0]; $rb_pt[0]++) {
	    for ($rb_pt[1] = 0; $rb_pt[1] < $my_rb_size[1]; $rb_pt[1]++) {
		for ($rb_pt[2] = 0; $rb_pt[2] < $my_rb_size[2]; $rb_pt[2]++) {
		    print OUT ("          ");
		    if ($pointer_type eq "fixed") {
			$current_write_point_str = reference_name("array", "write", add_points($center[0], @rb_pt));
		    }
		    elsif ($pointer_type eq "moving") {
			$current_write_point_str = (reference_name("array", "write", @rb_pt) . moving_pointer_idx($center[0]));
		    }
		    print OUT ($current_write_point_str . " = ");
		    for ($ins_ctr = 0; $ins_ctr < $ins_ctr_max; $ins_ctr++) {
			inner_loop_statement($current_write_point_str, $ins_ctr, @rb_pt);
		    }
		}
	    }
	}
    }
    elsif ($statement_type eq "individual") {
	for ($ins_ctr = 0; $ins_ctr < $ins_ctr_max; $ins_ctr++) {
	    for ($rb_pt[0] = 0; $rb_pt[0] < $my_rb_size[0]; $rb_pt[0]++) {
		for ($rb_pt[1] = 0; $rb_pt[1] < $my_rb_size[1]; $rb_pt[1]++) {
		    for ($rb_pt[2] = 0; $rb_pt[2] < $my_rb_size[2]; $rb_pt[2]++) {
			print OUT ("          ");
			if ($pointer_type eq "fixed") {
			    $current_write_point_str = reference_name("variable", "write", add_points($center[0], @rb_pt));
			}
			else {
			    $current_write_point_str = reference_name("variable", "write", add_points($center[0], @rb_pt));
			}
			inner_loop_statement($current_write_point_str, $ins_ctr, @rb_pt);
		    }
		}
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
	print OUT ("        for (k=realMin_z; k < realMax_z; k++) {\n");
    }
    else {
	print OUT ("        for (k=realMin_z; k < (realMax_z-" . ($my_rb_size[2]-1) . "); k+=" . $my_rb_size[2] . ") {\n");
    }

    inner_loop_code(@my_rb_size);
    print OUT ("        }\n");

    if ($clean_up_code) {
	if ($my_rb_size[2] > 1) {
	    print OUT ("        for (; k < realMax_z; k++) {\n");
	    inner_loop_code(($my_rb_size[0], $my_rb_size[1], 1));
	    print OUT ("        }\n");
	}
    }
}

# Generates the code for the nested y- and z-dimensional loops
# @my_rb_size is a 3D coordinate
sub doubly_nested_loop_code {
    my(@my_rb_size) = @_;

    if ($pointer_type eq "fixed") {
	find_fixed_ptr_indices(@my_rb_size);
    }

    if ($my_rb_size[1] == 1) {
	print OUT ("        for (j=cacheBlockMin_y; j < cacheBlockMax_y; j++) {\n");
    }
    else {
	print OUT ("        for (j=cacheBlockMin_y; j < (cacheBlockMax_y-" . ($my_rb_size[1]-1) . "); j+=" . $my_rb_size[1] . ") {\n");
    }

    if ($pointer_type eq "fixed") {
	init_fixed_ptr_indices(@my_rb_size);
    }
    elsif ($pointer_type eq "moving") {
	init_moving_ptrs(@my_rb_size);
    }

    singly_nested_loop_code(@my_rb_size);
    print OUT ("      }\n");

    if ($clean_up_code) {
	if ($my_rb_size[1] > 1) {
	    print OUT ("      for (; j < realMax_y; j++) {\n");
	    
	    if ($pointer_type eq "fixed") {
		find_fixed_ptr_indices($my_rb_size[0], 1, $my_rb_size[2]);
		init_fixed_ptr_indices($my_rb_size[0], 1, $my_rb_size[2]);
	    }
	    elsif ($pointer_type eq "moving") {
		init_moving_ptrs($my_rb_size[0], 1, $my_rb_size[2]);
	    }

	    singly_nested_loop_code($my_rb_size[0], 1, $my_rb_size[2]);
	    print OUT ("      }\n");
	}
    }
}

# Generates the code for the triply nested loops
sub triply_nested_loop_code {
    print OUT ("    for (cb_j=0; cb_j < numBlocks_y; cb_j++) {\n");
    print OUT ("      cacheBlockMin_y = realMin_y + cb_j * numBlockCells_y\;\n");
    print OUT ("      cacheBlockMax_y = cacheBlockMin_y + numBlockCells_y\;\n");

    if ($rb_size[0] == 1) {
	print OUT ("    for (i=realMin_x; i < realMax_x; i++) {\n");
    }
    else {
	print OUT ("    for (i=realMin_x; i < (realMax_x-" . ($rb_size[0]-1) . "); i+=" . $rb_size[0] . ") {\n");
    }

    doubly_nested_loop_code(@rb_size);
    print OUT ("    }\n");
    print OUT ("    }\n");

    # clean-up code
    if ($clean_up_code) {
	if ($rb_size[0] > 1) {
	    print OUT ("    for (; i < realMax_x; i++) {\n");
	    
	    doubly_nested_loop_code(1, $rb_size[1], $rb_size[2]);
	    print OUT ("    }\n");
	}
    }
    print OUT ("    temp_ptr = Read_start;\n");
    print OUT ("    Read_start = Write_start;\n");
    print OUT ("    Write_start = temp_ptr;\n");
}

### BELOW ARE THE SUBROUTINES THAT GENERATE FULL FUNCTIONS ###

# Generates a single stencil function
sub generate_single_stencil_function {
    print OUT ("void " . function_name_str() . "() {\n");
    print OUT ("  double * __restrict__ temp_ptr;\n");

    if ($pointer_type eq "moving") {
	print OUT ("  double ");
	@rb_pt = (0, 0, 0);
	for ($rb_pt[0]=0; $rb_pt[0] < $rb_size[0]; $rb_pt[0]++) {
	    for ($rb_pt[1]=0; $rb_pt[1] < $rb_size[1]; $rb_pt[1]++) {
		for ($rb_pt[2]=0; $rb_pt[2] < $rb_size[2]; $rb_pt[2]++) {
		    print OUT ("* __restrict__ " . reference_name("array", "read", @rb_pt) . ", * __restrict__ " . reference_name("array", "write", @rb_pt));
		    if (($rb_pt[0] == ($rb_size[0]-1)) && ($rb_pt[1] == ($rb_size[1]-1)) && ($rb_pt[2] == ($rb_size[2]-1))) {
			print OUT (";\n");
		    }
		    else {
			print OUT (", ");
		    }
		}
	    }
	}
    }

    if ($read_from_type eq "variable") {
	rb_read_vars("declaration", @rb_size);
    }
    if ($statement_type eq "individual") {
	rb_write_vars(@rb_size);
    }

    print OUT ("  int32_t cacheBlockMin_y, cacheBlockMax_y, cb_j\;\n");
    print OUT ("  uint32_t i, j, k, t;\n\n");

    if (($pointer_type eq "moving") || ($neighbor_index_type eq "register_block")) {
	print OUT ("  const uint32_t plane_size = ny * nz;\n");
    }

    if ($pointer_type eq "moving") {
	init_moving_ptr_indices();
    }
    init_fixed_ptrs();

    print OUT ("  for (t=0; t < numIter; t++) {\n");

    if ($platform eq "bassi") {
	print OUT ("\n#pragma disjoint(*Read_start, *Write_start)\n\n");
    }
    triply_nested_loop_code();

    print OUT ("  }\n");
    print OUT ("}\n\n");
}

# Generates all the stencil functions, or all the function headers, or the function table
sub generate_all_stencil_functions {
    my($code_type) = @_;

    if ($code_type eq "function_table") {
	print OUT ("#define STATEMENT_TYPES " . @statement_types . "\t// complete or individual statements\n");
	print OUT ("#define READ_FROM_TYPES " . @read_from_types . "\t// read from array or variable\n");
	print OUT ("#define POINTER_TYPES " . @pointer_types . "\t\t// fixed or moving pointers\n");
	print OUT ("#define NEIGHBOR_INDEX_TYPES " . @neighbor_index_types . "\t// single ptr per register block, plane, or pencil\n");
	print OUT ("#define FMA_INS_TYPES " . @fma_ins_types . "\t\t// non-FMA or FMA like instructions\n");
	print OUT ("#define RB_SIZES " . @rb_sizes . "\t\t// the number of register block sizes\n\n");
	print OUT ("void (*stencil[STATEMENT_TYPES][READ_FROM_TYPES][POINTER_TYPES][NEIGHBOR_INDEX_TYPES][FMA_INS_TYPES][RB_SIZES])() =\n{");
    }

    foreach $statement_type (@statement_types) {
	if ($code_type eq "function_table") {
	    print OUT ("{");
	}
	foreach $read_from_type (@read_from_types) {
	    if ($code_type eq "function_table") {
		print OUT ("{");
	    }
	    foreach $pointer_type (@pointer_types) {
		if ($code_type eq "function_table") {
		    print OUT ("{");
		}
		foreach $neighbor_index_type (@neighbor_index_types) {
		    if ($code_type eq "function_table") {
			print OUT ("{");
		    }

		    if ($neighbor_index_type eq "register_block") {
			@neighbors_indices = (0);
		    }
		    elsif ($neighbor_index_type eq "plane") {
			@neighbors_indices = (0, 1, 5);
		    }
		    elsif ($neighbor_index_type eq "pencil") {
			@neighbors_indices = (0, 1, 2, 4, 5);
		    }
		    foreach $fma_ins_type (@fma_ins_types) {
			if ($code_type eq "function_table") {
			    print OUT ("{");
			}
			for ($rb_idx=0; $rb_idx < @rb_sizes; $rb_idx++) {
			    @rb_size = ($rb_sizes[$rb_idx][0], $rb_sizes[$rb_idx][1], $rb_sizes[$rb_idx][2]);
			    if ($code_type eq "generate") {
				generate_single_stencil_function();
			    }
			    elsif ($code_type eq "function_headers") {
				print OUT ("void " . function_name_str() . "();\n");
			    }
			    elsif ($code_type eq "function_table") {
				print OUT ("\t&" . function_name_str());
				if ($rb_idx != (@rb_sizes-1)) {
				    print OUT (", ");
				}
			    }
			}
			if ($code_type eq "function_table") {
			    if ($fma_ins_type eq $fma_ins_types[@fma_ins_types-1]) {
				print OUT ("}\n");
			    }
			    else {
				print OUT ("},\n");
			    }
			}
		    }
		    if ($code_type eq "function_table") {
			if ($neighbor_index_type eq $neighbor_index_types[@neighbor_index_types-1]) {
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
	    if ($statement_type eq $statement_types[@statement_types-1]) {
		print OUT ("}\n");
	    }
	    else {
		print OUT ("},\n");
	    }
	}
    }
    if ($code_type eq "function_table") {
	print OUT ("};");
    }
}

# Generates the include directives
sub generate_include_directives {
    print OUT "#include <stdio.h>\n";
    print OUT "#include <stdlib.h>\n";
    print OUT "#include <stdint.h>\n";
    print OUT "#include \"globals.h\"\n";
    print OUT "#include \"../common/flush_cache.h\"\n";
    print OUT "#include \"../common/helper_functions.h\"\n";
    print OUT ("#include \"" . $function_headers_file . "\"\n");
    print OUT ("#include \"" . $function_table_file . "\"\n");
    print OUT "#if !defined(DEBUG)\n";
    print OUT "#if defined(PAPI_ENABLED)\n";
    print OUT "#include \"../../papi/papi_util.c\"\n";
    print OUT "#else\n";
    print OUT "#include <unistd.h>\n";
    print OUT "#include \"../../cycle_time/cycle_time.h\"\n";
    print OUT "#include \"../../cycle_time/cycle_time.c\"\n";
    print OUT "#endif\n";
    print OUT "#endif\n";
    print OUT "#include \"grid.c\"\n";
    print OUT "#include \"../common/flush_cache.c\"\n";
    print OUT "#include \"../common/helper_functions.c\"\n";
    print OUT ("#include \"" . $functions_file . "\"\n\n");
}

# Generates the main function
sub generate_main_function {
    print OUT "int main(int argc, char *argv[]) {\n";
    print OUT "  double results[NUM_TRIALS];\n";
    print OUT "#if !defined(DEBUG)\n";
    print OUT "#if defined(PAPI_ENABLED)\n";
    print OUT "  int papi_setnum, num_desired, num_sets;\n";
    print OUT "#else\n";
    print OUT "  double median_counts_per_sec;\n";
    print OUT "#endif\n";
    print OUT "#endif\n\n";
    print OUT "  printf\(\"7-point stencil, no add, naive C code with non-periodic boundary conditions\\n\"\);\n\n";
    print OUT "  // initialize arrays\n";
    print OUT "  init_flush_cache_array\(\);\n";
    print OUT "  malloc_grids\(argv\);\n\n";
    print OUT "\#if !defined(DEBUG)\n";
    print OUT "\#if defined(PAPI_ENABLED)\n";
    print OUT "  // initialize papi\n";
    print OUT "  int desired_events[] = {PAPI_TOT_CYC, PAPI_FP_INS, PAPI_L2_DCA, PAPI_L2_DCM, PAPI_L3_DCM, PAPI_TLB_DM, PAPI_LD_INS, PAPI_SR_INS};\n";
    print OUT "  num_desired = 9;\n";
    print OUT "  PAPI_event_set_wrapper_t* event_sets;\n";
    print OUT "  papi_init\(desired_events, num_desired, &event_sets, &num_sets\);\n";
    print OUT "#else\n";
    print OUT "  // calculate clock rate\n";
    print OUT "  GET_CLOCK_RATE\(results, NUM_TRIALS\);\n";
    print OUT "  median_counts_per_sec = find_median\(results, NUM_TRIALS\);\n";
    print OUT "  printf\(\"Median ticks per second = %e\\n\", median_counts_per_sec\);\n";
    print OUT "#endif\n";
    print OUT "#endif\n\n";
    print OUT "  printf\(\"\\n\"\);\n\n";
    print OUT ("  uint32_t i1, i2, i3, i4, i5, i6;\n\n");
    print OUT ("  for (i1=0; i1<=" . (@statement_types-1) . "; i1++\) {\n");
    print OUT ("    for (i2=0; i2<=" . (@read_from_types-1) . "; i2++\) {\n");
    print OUT ("      for (i3=0; i3<=" . (@pointer_types-1) . "; i3++\) {\n");
    print OUT ("        for (i4=0; i4<=" . (@neighbor_index_types-1) . "; i4++\) {\n");
    print OUT ("          for (i5=0; i5<=" . (@fma_ins_types-1) . "; i5++\) {\n");
    print OUT ("            for (i6=0; i6<=" . (@rb_sizes-1) . "; i6++\) {\n");
    print OUT ("              switch (i1) {\n");
    $case_count = 0;
    foreach $type (@statement_types) {
	print OUT ("                case $case_count: printf\(\"$type statements, \"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("              }\n");
    print OUT ("              switch (i2) {\n");
    $case_count = 0;
    foreach $type (@read_from_types) {
	print OUT ("                case $case_count: printf\(\"read from $type, \"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("              }\n");
    print OUT ("              switch (i3) {\n");
    $case_count = 0;
    foreach $type (@pointer_types) {
	print OUT ("                case $case_count: printf\(\"$type pointers, \"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("              }\n");
    print OUT ("              switch (i4) {\n");
    $case_count = 0;
    foreach $type (@neighbor_index_types) {
	print OUT ("                case $case_count: printf\(\"single pointer per $type, \"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("              }\n");
    print OUT ("              switch (i5) {\n");
    $case_count = 0;
    foreach $type (@fma_ins_types) {
	print OUT ("               case $case_count: printf\(\"$type, \"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("              }\n");
    print OUT ("              switch (i6) {\n");
    $case_count = 0;
    for ($rb_idx=0; $rb_idx < @rb_sizes; $rb_idx++) {
	print OUT ("                case $case_count: printf\(\"RB = \($rb_sizes[$rb_idx][0], $rb_sizes[$rb_idx][1], $rb_sizes[$rb_idx][2] \)\\n\\n\"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("              }\n");
    print OUT "#if defined(DEBUG)\n";
    print OUT ("              init_grids\(\);\n");
    print OUT ("              printf\(\"\\nGRID A BEFORE:\"\);\n");
    print OUT ("              print_grid\(A\);\n");
    print OUT ("              printf\(\"\\nGRID B BEFORE:\"\);\n");
    print OUT ("              print_grid\(B\);\n");
    print OUT ("              " . function_table_name_str() . "();\n");
    print OUT ("              printf\(\"\\nGRID A AFTER:\"\);\n");
    print OUT ("              print_grid\(A\);\n");
    print OUT ("              printf\(\"\\nGRID B AFTER:\"\);\n");
    print OUT ("              print_grid\(B\);\n");
    print OUT "#else\n";
    print OUT "#if defined(PAPI_ENABLED)\n";
    print OUT ("              for \(papi_setnum=0; papi_setnum < num_sets; papi_setnum++\) {\n");
    print OUT ("                PAPI_MAKE_MEASUREMENTS\(event_sets[papi_setnum].set, " . function_table_name_str() . "(), NUM_TRIALS, results\);\n");
    print OUT ("                print_papi_measurements\(&\(event_sets[papi_setnum]\), results, NUM_TRIALS\);\n");
    print OUT ("              }\n");
    print OUT "#else\n";
    print OUT ("              TIMER_MAKE_MEASUREMENTS\(" . function_table_name_str() . "(), results, NUM_TRIALS\);\n");
    print OUT ("              print_timer_measurements(results, NUM_TRIALS, median_counts_per_sec\);\n");
    print OUT "#endif\n";
    print OUT "#endif\n";
    print OUT ("              printf\(\"\\n\"\);\n");
    print OUT ("            }\n");
    print OUT ("          }\n");
    print OUT ("        }\n");
    print OUT ("      }\n");
    print OUT ("    }\n");
    print OUT ("  }\n");
    print OUT ("  printf\(\"\\n\"\);\n");
    print OUT ("  printf\(\"\\nFinal interior values: A[%d, %d, %d] = %4.2e, B[%d, %d, %d] = %4.2e\\n\", nx/2, ny/2, nz/2, A[Index3D\(nx/2, ny/2, nz/2\)], nx/2, ny/2, nz/2, B[Index3D\(nx/2, ny/2, nz/2\)]\);\n");
    print OUT ("  flush_cache_checksum\(\);\n\n");
    print OUT "#if defined\(PAPI_ENABLED\) && !defined\(DEBUG\)\n";
    print OUT ("  papi_cleanup\(event_sets, num_sets\);\n");
    print OUT "#endif\n";
    print OUT ("  free_grids\(\);\n");
    print OUT ("  return EXIT_SUCCESS;\n");
    print OUT ("}\n");
}
