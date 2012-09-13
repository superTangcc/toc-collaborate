#!/usr/bin/perl -w

### THESE PARAMETERS SPECIFY WHAT CODE IS GENERATED AND COMPILED ###

# register block sizes (starts at 1)- ALL DIMENSIONS MUST BE EVEN FOR GSRB TO BE PROPERLY PERFORMED
@rb_sizes = ([2,2,2], [2,2,4], [2,2,8], [2,4,2], [2,4,4], [4,2,2], [4,2,4], [4,4,2], [4,4,4]);

# prefetch options- "none", one for the "register_block", leading "plane"s, or leading "pencil"s
@prefetch_index_types = ("none", "register_block", "plane", "pencil");

# prefetch distances
@prefetch_distances = (0, 32, 64, 128, 256, 512);

### BELOW IS THE PERL SCRIPT'S "MAIN" SUBROUTINE ###

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

$code_variant_file = ("code_variant.c");
open(OUT, ">$code_variant_file") || die ("Couldn't create $code_variant_file.\n");
generate_code_variant_file();
close(OUT) || die;

$main_headers_file = ("helmholtz_pthreads.h");
open(OUT, ">$main_headers_file") || die ("Couldn't create $main_headers_file.\n");
generate_per_thread_function_name();
close(OUT) || die;

$main_file = ("helmholtz_pthreads.c");
open(OUT, ">$main_file") || die ("Couldn't create $main_file.\n");
generate_directives();
generate_per_thread_function();
generate_main_function();
close(OUT) || die;

$specified_data_script = ("specified_3D_data_generator.pl");
open(OUT, ">$specified_data_script") || die ("Couldn't create $specified_data_script.\n");
generate_specified_data_script();
system ("chmod 755 $specified_data_script");
close(OUT) || die;

$greedy_data_script = ("greedy_3D_data_generator.pl");
open(OUT, ">$greedy_data_script") || die ("Couldn't create $specified_data_script.\n");
generate_greedy_data_script();
system ("chmod 755 $greedy_data_script");
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

sub convert_point_to_string {
    my($separator, @my_point) = @_;
    
    my $str = "";

    for (my $dim=0; $dim < 3; $dim++) {
	$num = $my_point[$dim];
	if ($num < 0) {
	    $num = "m" . ((-1) * $num);
	}

	if ($dim < 2) {
	    $str = ($str . $num . $separator);
	}
	else {
	    $str = ($str . $num);
	}
    }

    return $str;
}

sub per_thread_function_name_str {
    return ("void *pthreads_each(void *rank_ptr)");
}

# Returns the function name as a string
sub function_name_str {
    return ("helmholtz_per_thread_" . substr($prefetch_index_type, 0, 2) . "_" . $prefetch_distance . "_" . convert_point_to_string("x", @rb_size) . "RB");
}

sub function_parameters_str {
    return ("\(uint32_t rank, double dx, double alpha, double beta, uint32_t redBlack\)");
}

sub function_table_name_str {
    return ("helmholtz_per_thread[prefetch_index_type][prefetch_distance][rb_size]");
}

# Generates a reference name
# @my_rb_size is a 3D coordinate
sub reference_name {
    my(@my_rb_size) = @_;

    return ("(i" . i2s($my_rb_size[0]) . ",j" . i2s($my_rb_size[1]) . ",k" . i2s($my_rb_size[2]) . ")");
}

### BELOW ARE THE BUILDING BLOCK SUBROUTINES ###

sub prefetch_code {
    my(@my_rb_size) = @_;

    my @my_double_rb_size = (2 * ($my_rb_size[0]-1), 2 * ($my_rb_size[1]-1), 2 * ($my_rb_size[2]-1));

    my @my_phi_rb_offset = add_points([@{[1,0,0]}], [@my_double_rb_size]);
    my @my_rhs_rb_offset = @my_double_rb_size;
    my @my_aCoef_rb_offset = @my_double_rb_size;
    my @my_bCoef0_rb_offset = add_points([@{[1,0,0]}], [@my_double_rb_size]);
    my @my_bCoef1_rb_offset = add_points([@{[0,1,0]}], [@my_double_rb_size]);
    my @my_bCoef2_rb_offset = add_points([@{[0,0,1]}], [@my_double_rb_size]);
    my @my_lambda_rb_offset = @my_double_rb_size;

    my @my_phi_plane_offset1 = add_points([@{[-1,0,0]}], [@my_double_rb_size]);
    my @my_phi_plane_offset2 = @my_double_rb_size;
    my @my_bCoef0_plane_offset = @my_double_rb_size;
    my @my_bCoef1_plane_offset = @my_double_rb_size;
    my @my_bCoef2_plane_offset = @my_double_rb_size;

    my @my_phi_pencil_offset1 = add_points([@{[0,-1,0]}], [@my_double_rb_size]);
    my @my_phi_pencil_offset2 = add_points([@{[0,1,0]}], [@my_double_rb_size]);

    if (($prefetch_index_type eq "register_block") || ($prefetch_index_type eq "plane") || ($prefetch_index_type eq "pencil")) {
	print OUT ("                    PREFETCH_FOR_REUSE\(&phi[Iphi" . reference_name(@my_phi_rb_offset) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&rhs[Irhs" . reference_name(@my_rhs_rb_offset) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&aCoef[IaCoef" . reference_name(@my_aCoef_rb_offset) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&bCoef0[IbCoef0" . reference_name(@my_bCoef0_rb_offset) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&bCoef1[IbCoef1" . reference_name(@my_bCoef1_rb_offset) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&bCoef2[IbCoef2" . reference_name(@my_bCoef2_rb_offset) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&lambda[Ilambda" . reference_name(@my_lambda_rb_offset) . "]+$prefetch_distance\)\;\n");
    }
    if (($prefetch_index_type eq "plane") || ($prefetch_index_type eq "pencil")) {
	print OUT ("                    PREFETCH_FOR_REUSE\(&phi[Iphi" . reference_name(@my_phi_plane_offset1) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&phi[Iphi" . reference_name(@my_phi_plane_offset2) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&bCoef0[IbCoef0" . reference_name(@my_bCoef0_plane_offset) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&bCoef1[IbCoef1" . reference_name(@my_bCoef1_plane_offset) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&bCoef2[IbCoef2" . reference_name(@my_bCoef2_plane_offset) . "]+$prefetch_distance\)\;\n");
    }
    if ($prefetch_index_type eq "pencil") {
	print OUT ("                    PREFETCH_FOR_REUSE\(&phi[Iphi" . reference_name(@my_phi_pencil_offset1) . "]+$prefetch_distance\)\;\n");
	print OUT ("                    PREFETCH_FOR_REUSE\(&phi[Iphi" . reference_name(@my_phi_pencil_offset2) . "]+$prefetch_distance\)\;\n");
    }
    print OUT ("\n");
}


### BELOW ARE THE SUBROUTINES THAT MAKE THE NESTED LOOPS ###

# generates all necessary statements for a single write point
sub inner_loop_first_statement {
    my(@my_rb_pt) = @_;

    print OUT ("                      lofphi" . $my_rb_pt[0] . $my_rb_pt[1] . $my_rb_pt[2] . " = \n");
    print OUT ("                        alpha * aCoef[IaCoef" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "] * phi[Iphi" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "]\n");
    print OUT ("                        - beta *\n");
    print OUT ("                        (\n");
    print OUT ("                         bCoef0[IbCoef0" . reference_name(add_points([@{[1,0,0]}], [@my_rb_pt])) . "]\n");
    print OUT ("                         * (phi[Iphi" . reference_name(add_points([@{[1,0,0]}], [@my_rb_pt])) . "] - phi[Iphi" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "])\n");
    print OUT ("                         - bCoef0[IbCoef0" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "]\n");
    print OUT ("                         * (phi[Iphi" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "] - phi[Iphi" . reference_name(add_points([@{[-1,0,0]}], [@my_rb_pt])) . "])\n");
    print OUT ("                         + bCoef1[IbCoef1" . reference_name(add_points([@{[0,1,0]}], [@my_rb_pt])) . "]\n");
    print OUT ("                         * (phi[Iphi" . reference_name(add_points([@{[0,1,0]}], [@my_rb_pt])) . "] - phi[Iphi" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "])\n");
    print OUT ("                         - bCoef1[IbCoef1" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "]\n");
    print OUT ("                         * (phi[Iphi" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "] - phi[Iphi" . reference_name(add_points([@{[0,-1,0]}], [@my_rb_pt])) . "])\n");
    print OUT ("                         + bCoef2[IbCoef2" . reference_name(add_points([@{[0,0,1]}], [@my_rb_pt])) . "]\n");
    print OUT ("                         * (phi[Iphi" . reference_name(add_points([@{[0,0,1]}], [@my_rb_pt])) . "] - phi[Iphi" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "])\n");
    print OUT ("                         - bCoef2[IbCoef2" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "]\n");
    print OUT ("                         * (phi[Iphi" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "] - phi[Iphi" . reference_name(add_points([@{[0,0,-1]}], [@my_rb_pt])) . "])\n");
    print OUT ("                        ) * dxinv\;\n");
    print OUT ("\n");
}

sub inner_loop_second_statement {
    my(@my_rb_pt) = @_;

    print OUT ("                      phi[Iphi" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "] -=\n");
    print OUT ("                        lambda[Ilambda" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "] * (lofphi" . $my_rb_pt[0] . $my_rb_pt[1] . $my_rb_pt[2] . " - rhs[Irhs" . reference_name(add_points([@{[0,0,0]}], [@my_rb_pt])) . "])\;\n");
    print OUT ("\n");
}

# @my_rb_size is a 3D coordinate
sub inner_loop {
    my(@my_rb_size) = @_;

    prefetch_code(@my_rb_size);

    print OUT ("                    if (offset) {\n");
    for (my $i = 0; $i < $my_rb_size[0]; $i++) {
	for (my $j = 0; $j < $my_rb_size[1]; $j++) {
	    for (my $k = 0; $k < $my_rb_size[2]; $k++) {
		my @rb_pt = ($i, $j, $k);
		if ((($i+$j+$k)%2) == 1) {
		    inner_loop_first_statement(@rb_pt);
		}
	    }
	}
    }
    for (my $i = 0; $i < $my_rb_size[0]; $i++) {
	for (my $j = 0; $j < $my_rb_size[1]; $j++) {
	    for (my $k = 0; $k < $my_rb_size[2]; $k++) {
		my @rb_pt = ($i, $j, $k);
		if ((($i+$j+$k)%2) == 1) {
		    inner_loop_second_statement(@rb_pt);
		}
	    }
	}
    }
    print OUT ("                    }\n");
    print OUT ("                    else {\n");
    for (my $i = 0; $i < $my_rb_size[0]; $i++) {
	for (my $j = 0; $j < $my_rb_size[1]; $j++) {
	    for (my $k = 0; $k < $my_rb_size[2]; $k++) {
		my @rb_pt = ($i, $j, $k);
		if ((($i+$j+$k)%2) == 0) {
		    inner_loop_first_statement(@rb_pt);
		}
	    }
	}
    }
    for (my $i = 0; $i < $my_rb_size[0]; $i++) {
	for (my $j = 0; $j < $my_rb_size[1]; $j++) {
	    for (my $k = 0; $k < $my_rb_size[2]; $k++) {
		my @rb_pt = ($i, $j, $k);
		if ((($i+$j+$k)%2) == 0) {
		    inner_loop_second_statement(@rb_pt);
		}
	    }
	}
    }
    print OUT ("                    }\n");
}

# Generates the code for the z-dimensional loop
# @my_rb_size is a 3D coordinate
sub singly_nested_loop_code {
    my(@my_rb_size) = @_;

    print OUT ("                  indtot = i + j + coreBlockMin_z\;\n");
    print OUT ("                  offset = abs((indtot+redBlack) % 2)\;\n");
    print OUT ("                  for (k=coreBlockMin_z; k < coreBlockMax_z; k+=" . $my_rb_size[2] . ") {\n");

    inner_loop(@my_rb_size);
    print OUT ("                  }\n");
}

# Generates the code for the nested y- and z-dimensional loops
# @my_rb_size is a 3D coordinate
sub doubly_nested_loop_code {
    my(@my_rb_size) = @_;

    if ($my_rb_size[1] == 1) {
	print OUT ("                for (j=coreBlockMin_y; j < coreBlockMax_y; j++) {\n");
    }
    else {
	print OUT ("                for (j=coreBlockMin_y; j < coreBlockMax_y; j+=" . $my_rb_size[1] . ") {\n");
    }

    singly_nested_loop_code(@my_rb_size);
    print OUT ("                }\n");
}

# Generates the code for the triply nested loops
sub triply_nested_loop_code {
    if ($rb_size[0] == 1) {
	print OUT ("              for (i=coreBlockMin_x; i < coreBlockMax_x; i++) {\n");
    }
    else {
	print OUT ("              for (i=coreBlockMin_x; i < coreBlockMax_x; i+=" . $rb_size[0] . ") {\n");
    }

    doubly_nested_loop_code(@rb_size);
    print OUT ("              }\n");
}

sub outer_nested_loop_code {
    print OUT ("  for (g=(rank/numThreadsPerGrid); g < numGrids; g+=(numThreads/numThreadsPerGrid)) {\n");
    print OUT ("    phi = (double *) phi_grids[g]\;\n");
    print OUT ("    rhs = (double *) rhs_grids[g]\;\n");
    print OUT ("    aCoef = (double *) aCoef_grids[g]\;\n");
    print OUT ("    bCoef0 = (double *) bCoef0_grids[g]\;\n");
    print OUT ("    bCoef1 = (double *) bCoef1_grids[g]\;\n");
    print OUT ("    bCoef2 = (double *) bCoef2_grids[g]\;\n");
    print OUT ("    lambda = (double *) lambda_grids[g]\;\n\n");
    print OUT ("    for (n=0; n < niter; n++) {\n");
    print OUT ("      cb_n = 0;\n");
    print OUT ("      for (cb_i=0; cb_i < numCoreBlocks_x; cb_i++) {\n");
    print OUT ("        for (cb_j=0; cb_j < numCoreBlocks_y; cb_j++) {\n");
    print OUT ("          for (cb_k=0; cb_k < numCoreBlocks_z; cb_k++) {\n");
    print OUT ("            if (((cb_n/numCoreBlocksPerChunk) % numThreadsPerGrid) == (rank % numThreadsPerGrid)) {\n");
    print OUT ("              coreBlockMin_x = 1 + cb_i * numCoreBlockCells_x\;\n");
    print OUT ("              coreBlockMax_x = coreBlockMin_x + numCoreBlockCells_x\;\n");
    print OUT ("              coreBlockMin_y = 1 + cb_j * numCoreBlockCells_y\;\n");
    print OUT ("              coreBlockMax_y = coreBlockMin_y + numCoreBlockCells_y\;\n");
    print OUT ("              coreBlockMin_z = 1 + cb_k * numCoreBlockCells_z\;\n");
    print OUT ("              coreBlockMax_z = coreBlockMin_z + numCoreBlockCells_z\;\n");
    triply_nested_loop_code();
    print OUT ("            }\n");
    print OUT ("            cb_n++\;\n");
    print OUT ("          }\n");
    print OUT ("        }\n");
    print OUT ("      }\n");
    print OUT ("      // the following sync will possibly allow the final (load unbalanced) grids to get the wrong answer\n");
    print OUT ("      if ((numThreadsPerGrid > 1) && (n < (niter - 1)) && (g < numGridsForPerfectLoadBalance)) {\n");
    print OUT ("        barrier_wait(&my_barrier, rank);\n");
    print OUT ("      }\n");
    print OUT ("      redBlack = 1-redBlack\;\n");
    print OUT ("    }\n");
    print OUT ("  }\n");
    print OUT ("  // sync before time readings\n");
    print OUT ("  barrier_wait(&my_barrier, rank);\n");
}

### BELOW ARE THE SUBROUTINES THAT GENERATE FULL FUNCTIONS ###

# Generates a single stencil function
sub generate_single_stencil_function {
    print OUT ("void " . function_name_str() . function_parameters_str() . " {\n");
    print OUT ("  double dxinv");
    for (my $i = 0; $i < $rb_size[0]; $i++) {
	for (my $j = 0; $j < $rb_size[1]; $j++) {
	    for (my $k = 0; $k < $rb_size[2]; $k++) {
		print OUT (", ");
		print OUT ("lofphi" . $i . $j . $k);
	    }
	}
    }
    print OUT ("\;\n");

    print OUT ("  double *phi, *rhs, *aCoef, *bCoef0, *bCoef1, *bCoef2, *lambda\;\n");
    print OUT ("  uint32_t coreBlockMin_x, coreBlockMin_y, coreBlockMin_z, coreBlockMax_x, coreBlockMax_y, coreBlockMax_z\;\n");
    print OUT ("  uint32_t cb_n, cb_i, cb_j, cb_k\;\n");
    print OUT ("  uint32_t numGridsForPerfectLoadBalance\;\n");
    print OUT ("  uint32_t indtot, offset\;\n");
    print OUT ("  uint32_t g, n, i, j, k\;\n\n");

    print OUT ("  dxinv = 1.0/(dx*dx);\n");
    print OUT ("  numGridsForPerfectLoadBalance = numGrids - (numGrids % (numThreads/numThreadsPerGrid))\;\n\n");

    outer_nested_loop_code();

    print OUT ("}\n\n");
}

# Generates all the stencil functions, or all the function headers, or the function table
sub generate_all_stencil_functions {
    my($code_type) = @_;

    if ($code_type eq "function_table") {
	print OUT ("#define PREFETCH_INDEX_TYPES " . @prefetch_index_types . "\t// no prefetch, or prefetch for register block, leading planes, or leading pencils\n");
	print OUT ("#define PREFETCH_DISTANCES " . @prefetch_distances . "\t// the distances ahead being prefetched\n");
	print OUT ("#define RB_SIZES " . @rb_sizes . "\t\t// the number of register block sizes\n\n");
	print OUT ("void (*helmholtz_per_thread[PREFETCH_INDEX_TYPES][PREFETCH_DISTANCES][RB_SIZES])() =\n{");
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
    print OUT "uint32_t prefetch_index_type, prefetch_distance, rb_size\;\n\n";
    print OUT "void select_code_variant\(char *argv\[\]\)\;\n";
    print OUT "void print_code_variant_parameters\(void\)\;\n";
}

sub generate_code_variant_file {
    print OUT ("void select_code_variant\(char *argv\[\]\) {\n");
    print OUT ("  prefetch_index_type = atoi\(argv\[13\]\)\;\n");
    print OUT ("  prefetch_distance = atoi\(argv\[14\]\)\;\n");
    print OUT ("  rb_size = atoi\(argv\[15\]\)\;\n");
    print OUT ("}\n\n");
    print OUT ("void print_code_variant_parameters\(\) {\n");
    print OUT ("  switch (prefetch_index_type) {\n");
    $case_count = 0;
    foreach $type (@prefetch_index_types) {
	print OUT ("    case $case_count: printf\(\"prefetch index type (none=0, single prefetch per register block=1, per plane=2, per pencil=3) = \\n$prefetch_index_types_hash{$type},\\n\"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("  switch (prefetch_distance) {\n");
    $case_count = 0;
    foreach $distance (@prefetch_distances) {
	print OUT ("    case $case_count: printf\(\"prefetch distance = \\n$distance, case number, $case_count,\\n\"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("  switch (rb_size) {\n");
    for ($rb_idx=0; $rb_idx < @rb_sizes; $rb_idx++) {
	print OUT ("    case $rb_idx: printf\(\"register block size = \\n$rb_sizes[$rb_idx][0], $rb_sizes[$rb_idx][1], $rb_sizes[$rb_idx][2], case number, $rb_idx,\\n\"\)\; break\;\n");
    }
    print OUT ("  }\n");
    print OUT ("  printf\(\"\\n\"\);\n");
    print OUT ("}\n");
}

# generates the include directives
sub generate_directives {
    print OUT "#include <stdio.h>\n";
    print OUT "#include <stdlib.h>\n";
    print OUT "#include <stdint.h>\n";
    print OUT "#include <pthread.h>\n";
    print OUT "#include <unistd.h>\n";
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
    print OUT "#include \"code_variant.h\"\n";
    print OUT ("#include \"" . $function_headers_file . "\"\n");
    print OUT ("#include \"" . $main_headers_file . "\"\n");
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
    print OUT "#include \"../common/helper_functions.c\"\n";
    print OUT "#include \"../common/flush_cache.c\"\n";
    print OUT "#include \"grid.c\"\n";
    print OUT ("#include \"" . $function_table_file . "\"\n");
    print OUT "#include \"code_variant.c\"\n";
    print OUT ("#include \"" . $variables_file . "\"\n");
    print OUT ("#include \"" . $functions_file . "\"\n\n");
}

sub generate_per_thread_function_name {
    print OUT (per_thread_function_name_str() . ";\n");
}

sub generate_per_thread_function {
    print OUT (per_thread_function_name_str() . " {\n");
    print OUT ("  uint32_t rank\;\n");
    print OUT ("#if defined(DEBUG)\n");
    print OUT ("  uint32_t g\;\n");
    print OUT ("#endif\n\n");
    print OUT ("#if defined(PAPI_ENABLED) && !defined(DEBUG)\n");
    print OUT ("  int num_sets\;\n");
    print OUT ("  PAPI_event_set_wrapper_t* event_sets\;\n\n");
    print OUT ("  papi_filter_events\(desired_events, num_desired, &event_sets, &num_sets\)\;\n");
    print OUT ("#endif\n\n");
    print OUT ("  rank = *\(\(uint32_t *\) rank_ptr\)\;\n\n");
    print OUT ("#if defined\(AFFINITY_ENABLED\)\n");
    print OUT ("  Affinity_Bind_Thread\(rank\)\;\n");
    print OUT ("  Affinity_Bind_Memory\(rank\)\;\n");
    print OUT ("#endif\n\n");
    print OUT ("#if defined(DEBUG)\n");
    print OUT ("  init_grids\(rank\)\;\n");
    print OUT ("  barrier_wait\(&my_barrier, rank\)\;\n");
    print OUT ("  if \(rank == 0\) {\n");
    print OUT ("    for \(g=0; g < numGrids; g++) {\n");
    print OUT ("      printf\(\"\\nGRID phi_grids[%u] BEFORE:\", g\)\;\n");
    print OUT ("      print_grid\(phi_grids[g], nx_rhs+2, ny_rhs+2, nz_rhs+2\)\;\n");
    print OUT ("      printf\(\"\\nGRID rhs_grids[%u] BEFORE:\", g\)\;\n");
    print OUT ("      print_grid\(rhs_grids[g], nx_rhs, ny_rhs, nz_rhs\)\;\n");
    print OUT ("      printf\(\"\\nGRID aCoef_grids[%u] BEFORE:\", g\)\;\n");
    print OUT ("      print_grid\(aCoef_grids[g], nx_rhs, ny_rhs, nz_rhs\)\;\n");
    print OUT ("      printf\(\"\\nGRID bCoef0_grids[%u] BEFORE:\", g\)\;\n");
    print OUT ("      print_grid\(bCoef0_grids[g], nx_rhs+1, ny_rhs, nz_rhs\)\;\n");
    print OUT ("      printf\(\"\\nGRID bCoef1_grids[%u] BEFORE:\", g\)\;\n");
    print OUT ("      print_grid\(bCoef1_grids[g], nx_rhs, ny_rhs+1, nz_rhs\)\;\n");
    print OUT ("      printf\(\"\\nGRID bCoef2_grids[%u] BEFORE:\", g\)\;\n");
    print OUT ("      print_grid\(bCoef2_grids[g], nx_rhs, ny_rhs, nz_rhs+1\)\;\n");
    print OUT ("      printf\(\"\\nGRID lambda_grids[%u] BEFORE:\", g\)\;\n");
    print OUT ("      print_grid\(lambda_grids[g], nx_rhs, ny_rhs, nz_rhs\)\;\n");
    print OUT ("    }\n");
    print OUT ("    printf\(\"\\n\\n\"\)\;\n");
    print OUT ("  }\n");
    print OUT ("  barrier_wait\(&my_barrier, rank\)\;\n");
    print OUT ("  " . function_table_name_str() . "\(rank, 2.5, 5.0, 10.0, 0\)\;\n");
    print OUT ("  if \(rank == 0\) {\n");
    print OUT ("    for \(g=0; g < numGrids; g++) {\n");
    print OUT ("      printf\(\"\\nGRID phi_grids[%u] AFTER:\", g\)\;\n");
    print OUT ("      print_grid\(phi_grids[g], nx_rhs+2, ny_rhs+2, nz_rhs+2\)\;\n");
    print OUT ("      printf\(\"\\nGRID rhs_grids[%u] AFTER:\", g\)\;\n");
    print OUT ("      print_grid\(rhs_grids[g], nx_rhs, ny_rhs, nz_rhs\)\;\n");
    print OUT ("      printf\(\"\\nGRID aCoef_grids[%u] AFTER:\", g\)\;\n");
    print OUT ("      print_grid\(aCoef_grids[g], nx_rhs, ny_rhs, nz_rhs\)\;\n");
    print OUT ("      printf\(\"\\nGRID bCoef0_grids[%u] AFTER:\", g\)\;\n");
    print OUT ("      print_grid\(bCoef0_grids[g], nx_rhs+1, ny_rhs, nz_rhs\)\;\n");
    print OUT ("      printf\(\"\\nGRID bCoef1_grids[%u] AFTER:\", g\)\;\n");
    print OUT ("      print_grid\(bCoef1_grids[g], nx_rhs, ny_rhs+1, nz_rhs\)\;\n");
    print OUT ("      printf\(\"\\nGRID bCoef2_grids[%u] AFTER:\", g\)\;\n");
    print OUT ("      print_grid\(bCoef2_grids[g], nx_rhs, ny_rhs, nz_rhs+1\)\;\n");
    print OUT ("      printf\(\"\\nGRID lambda_grids[%u] AFTER:\", g\)\;\n");
    print OUT ("      print_grid\(lambda_grids[g], nx_rhs, ny_rhs, nz_rhs\)\;\n");
    print OUT ("    }\n");
    print OUT ("    printf\(\"\\n\\n\"\)\;\n");
    print OUT ("  }\n");
    print OUT ("  barrier_wait\(&my_barrier, rank\)\;\n");
    print OUT ("#else\n");
    print OUT ("#if defined(PAPI_ENABLED)\n");
    print OUT ("  int papi_setnum\;\n\n");
    print OUT ("  for \(papi_setnum=0; papi_setnum < num_sets; papi_setnum++\) {\n");
    print OUT ("    PAPI_MAKE_MEASUREMENTS\(event_sets[papi_setnum].set, " . function_table_name_str() . "\(rank, 2.5, 5.0, 10.0, 0\), results, NUM_TRIALS*\(papi_setnum*numThreads+rank\), NUM_TRIALS\)\;\n");
    print OUT ("  }\n");
    print OUT ("  if (rank == 0) {\n");
    print OUT ("    print_papi_measurements\(event_sets, results, num_sets, numThreads, NUM_TRIALS\)\;\n");
    print OUT ("    printf\(\"\\n\\n\"\)\;\n");
    print OUT ("  }\n");
    print OUT ("#else\n");
    print OUT ("  TIMER_MAKE_MEASUREMENTS(" . function_table_name_str() . "(rank, 2.5, 5.0, 10.0, 0), results, rank, NUM_TRIALS);\n");
    print OUT ("  if \(rank == 0\) {\n");
    print OUT ("    printf\(\"TIME (IN SECONDS)\\n\"\)\;\n");
    print OUT ("#if defined(THREAD_PROFILING)\n");
    print OUT ("    uint32_t t\;\n");
    print OUT ("    for \(t=0\; t < numThreads\; t++\) {\n");
    print OUT ("      printf\(\"Thread %u:\\n\", t\)\;\n");
    print OUT ("      print_timer_measurements\(&results[t * NUM_TRIALS], NUM_TRIALS, median_counts_per_sec\)\;\n");
    print OUT ("    }\n");
    print OUT ("#endif\n");
    print OUT ("    print_max_timer_measurements\(results, numThreads, NUM_TRIALS, median_counts_per_sec\)\;\n");
    print OUT ("    printf\(\"\\n\\n\"\)\;\n");
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
    print OUT "  uint32_t **ranks\;\n";
    print OUT "  void *status\;\n\n";
    print OUT "#if defined(PAPI_ENABLED) && !defined(DEBUG)\n";
    print OUT "  int num_sets;\n";
    print OUT "  PAPI_event_set_wrapper_t* event_sets\;\n";
    print OUT "#endif\n";
    print OUT "  int rc\;\n";
    print OUT "  int32_t t\;\n\n";
    print OUT "  printf\(\"Variable coefficient Helmholtz GSRB solver\\n\"\)\;\n\n";
    print OUT "  init_flush_cache_array\(\)\;\n";
    print OUT "  malloc_grids\(argv\)\;\n";
    print OUT "  print_grid_parameters\(\)\;\n";
    print OUT "  select_code_variant\(argv\)\;\n";
    print OUT "  print_code_variant_parameters\(\)\;\n\n";
    print OUT "  threads = \(pthread_t *\) malloc\(numThreads * sizeof\(pthread_t\)\)\;\n";
    print OUT "  ranks = \(uint32_t **\) malloc\(numThreads * sizeof\(int32_t *\)\);\n\n";
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
    print OUT "    ranks[t] = \(uint32_t *\) malloc\(sizeof\(int32_t\)\);\n";
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

sub generate_specified_data_script {
    print OUT ("#!/usr/bin/perl -w\n\n");
    print OUT ("\$platform=\$ARGV[0]\;\n");
    print OUT ("\$compiler=\$ARGV[1]\;\n\n");
    print OUT ("my \$exec_file = \"./helmholtz_pthreads_\${compiler}_c\"\;\n\n");
    print OUT ("\@total_mem_footprints_in_GB = (0.5, 1, 2, 4)\;\n");
    print OUT ("\@numIter_values = (1)\;\n");
    print OUT ("\@log2_nreals_x_values = (8)\;\n");
    print OUT ("\@log2_nreals_y_values = (8)\;\n");
    print OUT ("\@log2_nreals_z_values = (8)\;\n");
    print OUT ("\@log2_numThreads_values = (0..3)\;\n");
    print OUT ("\@padding_values = (0..7)\;\n");
    print OUT ("\@log2_numCoreBlockCells_x_values = (2..8)\;\n");
    print OUT ("\@log2_numCoreBlockCells_y_values = (2..8)\;\n");
    print OUT ("\@log2_numCoreBlockCells_z_values = (3..8)\;\n");
    print OUT ("\@prefetch_index_type_values = (0.." . (@prefetch_index_types-1) . ")\;\n");
    print OUT ("\@prefetch_distance_values = (0.." . (@prefetch_distances-1) . ")\;\n");
    print OUT ("\@rb_size_values = (0.." . (@rb_sizes-1) . ")\;\n\n");
    print OUT ("foreach \$total_mem_footprint_in_GB (\@total_mem_footprints_in_GB) {\n");
    print OUT ("\tforeach \$numIter (\@numIter_values) {\n");
    print OUT ("\t\tforeach \$log2_nreals_x (\@log2_nreals_x_values) {\n");
    print OUT ("\t\t\tmy \$nreals_x = 2**(\$log2_nreals_x)\;\n");
    print OUT ("\t\t\tforeach \$log2_nreals_y (\@log2_nreals_y_values) {\n");
    print OUT ("\t\t\t\tmy \$nreals_y = 2**(\$log2_nreals_y)\;\n");
    print OUT ("\t\t\t\tforeach \$log2_nreals_z (\@log2_nreals_z_values) {\n");
    print OUT ("\t\t\t\t\tmy \$nreals_z = 2**(\$log2_nreals_z)\;\n");
    print OUT ("\t\t\t\t\tmy \$numGrids = int((\$total_mem_footprint_in_GB * 2**30) / (8 * (((\$nreals_x + 2) * (\$nreals_y + 2) * (\$nreals_z + 2)) + ((\$nreals_x + 2) * \$nreals_y * \$nreals_z) + (\$nreals_x * (\$nreals_y + 2) * \$nreals_z) + (\$nreals_x * \$nreals_y * (\$nreals_z + 2)) + 3 * (\$nreals_x * \$nreals_y * \$nreals_z))))\;\n");
    print OUT ("\t\t\t\t\tforeach \$log2_numThreads (\@log2_numThreads_values) {\n");
    print OUT ("\t\t\t\t\t\tmy \$numThreads = 2**(\$log2_numThreads)\; # 1 to 8 in powers of 2\n");
    print OUT ("\t\t\t\t\t\t\@log2_numThreadsPerGrid_values = (0..\$log2_numThreads)\;\n");
    print OUT ("\t\t\t\t\t\tforeach \$log2_numThreadsPerGrid (\@log2_numThreadsPerGrid_values) {\n");
    print OUT ("\t\t\t\t\t\t\tmy \$numThreadsPerGrid = 2**(\$log2_numThreadsPerGrid)\;\n");
    print OUT ("\t\t\t\t\t\t\tmy \$output_file = (\"./\" . \$platform . \"_\" . \$compiler . \"_specified_3D_\" . \$nreals_x . \"x\" . \$nreals_y . \"x\" . \$nreals_z . \"_\" . \$numIter . \"i_\" . \$numThreads . \"t_\" . \$numThreadsPerGrid . \"tpg_\" . \$total_mem_footprint_in_GB . \"GB.txt\");\n");
    print OUT ("\t\t\t\t\t\t\tforeach \$padding (\@padding_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\tforeach \$log2_numCoreBlockCells_x (\@log2_numCoreBlockCells_x_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\tmy \$numCoreBlockCells_x = 2**(\$log2_numCoreBlockCells_x); # 2 to \$nreals_x in powers of 2\n");
    print OUT ("\t\t\t\t\t\t\t\t\tforeach \$log2_numCoreBlockCells_y (\@log2_numCoreBlockCells_y_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\tmy \$numCoreBlockCells_y = 2**(\$log2_numCoreBlockCells_y); # 2 to \$nreals_y in powers of 2\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\tforeach \$log2_numCoreBlockCells_z (\@log2_numCoreBlockCells_z_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\tmy \$numCoreBlockCells_z = 2**(\$log2_numCoreBlockCells_z); # 8 to \$nreals_z in powers of 2\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\tif (\$numThreadsPerGrid == 1) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\@log2_numCoreBlocksPerChunk_values = (0)\;\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\telse {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\@log2_numCoreBlocksPerChunk_values = (0..((\$log2_nreals_x + \$log2_nreals_y + \$log2_nreals_z) - (\$log2_numCoreBlockCells_x + \$log2_numCoreBlockCells_y + \$log2_numCoreBlockCells_z + \$log2_numThreadsPerGrid)))\;\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\tforeach \$log2_numCoreBlocksPerChunk (\@log2_numCoreBlocksPerChunk_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\tmy \$numCoreBlocksPerChunk = 2**(\$log2_numCoreBlocksPerChunk)\;\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\tforeach \$prefetch_index_type (\@prefetch_index_type_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\tforeach \$prefetch_distance (\@prefetch_distance_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\t\tforeach \$rb_size (\@rb_size_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tsystem (\"\$exec_file \$numGrids \$numIter \$nreals_x \$nreals_y \$nreals_z \$numThreads \$numThreadsPerGrid \$padding \$numCoreBlockCells_x \$numCoreBlockCells_y \$numCoreBlockCells_z \$numCoreBlocksPerChunk \$prefetch_index_type \$prefetch_distance \$rb_size >> \$output_file\")\;\n");
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
}

sub generate_greedy_data_script {
    print OUT ("#!/usr/bin/perl -w\n\n");
    print OUT ("\$platform=\$ARGV[0]\;\n");
    print OUT ("\$compiler=\$ARGV[1]\;\n");
    print OUT ("my \$exec_file = \"./helmholtz_pthreads_\${compiler}_c\"\;\n");
    print OUT ("\@total_mem_footprints_in_GB = (0.5, 1, 2, 4)\;\n");
    print OUT ("\@numIter_values = (1);\n");
    print OUT ("\@log2_nreals_x_values = (8)\;\n");
    print OUT ("\@log2_nreals_y_values = (8)\;\n");
    print OUT ("\@log2_nreals_z_values = (8)\;\n");
    print OUT ("\@log2_numThreads_values = (0..3)\;\n");
    print OUT ("\@padding_values = (0..7)\;\n");
    print OUT ("\@log2_numCoreBlockCells_x_values = (2..8)\;\n");
    print OUT ("\@log2_numCoreBlockCells_y_values = (2..8)\;\n");
    print OUT ("\@log2_numCoreBlockCells_z_values = (3..8)\;\n");
    print OUT ("\@prefetch_index_type_values = (0.." . (@prefetch_index_types-1) . ")\;\n");
    print OUT ("\@prefetch_distance_values = (0.." . (@prefetch_distances-1) . ")\;\n");
    print OUT ("\@rb_size_values = (0.." . (@rb_sizes-1) . ")\;\n\n");
    print OUT ("sub find_best_padding {\n");
    print OUT ("\tmy(\$my_file_name, \$my_best_timing_line_number) = \@_\;\n\n");
    print OUT ("\topen (TXT, \"\$my_file_name\")\;\n");
    print OUT ("\t\$padding_line_number = \$my_best_timing_line_number - 15\;\n\n");
    print OUT ("\twhile (<TXT>) {\n");
    print OUT ("\t\tif (\$. == \$padding_line_number) {\n");
    print OUT ("\t\t\t\@best_padding_dims = split(/,/, \$_)\;\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n\n");
    print OUT ("\t\$output_file_line_length = \$.\;\n");
    print OUT ("\tclose(TXT)\;\n");
    print OUT ("}\n\n");
    print OUT ("sub find_best_core_block_and_chunk_size {\n");
    print OUT ("\tmy(\$my_file_name, \$my_best_timing_line_number) = \@_;\n\n");
    print OUT ("\topen (TXT, \"\$my_file_name\");\n");
    print OUT ("\t\$core_block_line_number = \$my_best_timing_line_number - 13;\n");
    print OUT ("\t\$chunk_size_line_number = \$core_block_line_number + 2;\n");
    print OUT ("\twhile (<TXT>) {\n");
    print OUT ("\t\tif (\$. == \$core_block_line_number) {\n");
    print OUT ("\t\t\t\@best_core_block_dims = split(/,/, \$_)\n");
    print OUT ("\t\t}\n\n");
    print OUT ("\t\tif (\$. == \$chunk_size_line_number) {\n");
    print OUT ("\t\t\t\@best_chunk_size = split(/,/, \$_);\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n\n");
    print OUT ("\t\$output_file_line_length = \$.;\n");
    print OUT ("\tclose(TXT);\n");
    print OUT ("}\n\n");
    print OUT ("sub find_best_inner_loop {\n");
    print OUT ("\tmy(\$my_file_name, \$my_best_timing_line_number) = \@_;\n\n");
    print OUT ("\topen (TXT, \"\$my_file_name\");\n");
    print OUT ("\t\$rb_size_and_case_line_number = \$my_best_timing_line_number - 5;\n\n");
    print OUT ("\twhile (<TXT>) {\n");
    print OUT ("\t\tif (\$. == \$rb_size_and_case_line_number) {\n");
    print OUT ("\t\t\t\@best_rb_size_and_case = split(/,/, \$_);\n");
    print OUT ("\t\t\t\@best_register_block_dims = \@best_rb_size_and_case[0,1,2];\n");
    print OUT ("\t\t\t\@best_rb_case = \$best_rb_size_and_case[4];\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n");
    print OUT ("\t\$output_file_line_length = \$.;\n");
    print OUT ("\tclose(TXT);\n");
    print OUT ("}\n\n");
    print OUT ("sub find_best_prefetching {\n");
    print OUT ("\tmy(\$my_file_name, \$my_best_timing_line_number) = \@_;\n\n");
    print OUT ("\topen(TXT, \"\$my_file_name\");\n");
    print OUT ("\t\$prefetch_index_type_line_number = \$my_best_timing_line_number - 9;\n");
    print OUT ("\t\$prefetch_distance_and_case_line_number = \$prefetch_index_type_line_number + 2;\n\n");
    print OUT ("\twhile (<TXT>) {\n");
    print OUT ("\t\tif (\$. == \$prefetch_index_type_line_number) {\n");
    print OUT ("\t\t\t\@best_prefetch_index_type = split(/,/, \$_);\n");
    print OUT ("\t\t}\n\n");
    print OUT ("\t\tif (\$. == \$prefetch_distance_and_case_line_number) {\n");
    print OUT ("\t\t\t\@best_prefetch_distance_and_case = split(/,/, \$_);\n");
    print OUT ("\t\t\t\@best_prefetch_distance = \$best_prefetch_distance_and_case[0];\n");
    print OUT ("\t\t\t\@best_prefetch_distance_case = \$best_prefetch_distance_and_case[2];\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n\n");
    print OUT ("\t\$output_file_line_length = \$.;\n");
    print OUT ("\tclose(TXT);\n");
    print OUT ("}\n\n");
    print OUT ("sub find_best_time_for_opt {\n");
    print OUT ("\tmy(\$my_file_name, \$my_opt_start_line_number) = \@_;\n\n");
    print OUT ("\topen \(TXT, \"\$my_file_name\")\;\n\n");
    print OUT ("\t\%median_times = ();\n");
    print OUT ("\twhile (<TXT>) {\n");
    print OUT ("\t\tif (\$. > \$my_opt_start_line_number) {\n");
    print OUT ("\t\t\tif (/Median Time: /) {\n");
    print OUT ("\t\t\t\t\@median_time = split(/Median Time: /, \$_);\n");
    print OUT ("\t\t\t\t\$median_times{\$.} = \$median_time[1];\n");
    print OUT ("\t\t\t}\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n\n");
    print OUT ("\tclose (TXT);\n\n");
    print OUT ("\t# sort \%median_times by time, then find the line number of the best timing\n");
    print OUT ("\t\$my_best_timing_line_number = -1;\n\n");
    print OUT ("\t\$i = 0;\n");
    print OUT ("\tforeach \$timing_line_number (sort {\$median_times{\$a} <=> \$median_times{\$b}} keys \%median_times) {\n");
    print OUT ("\t\tif (\$i == 0) {\n");
    print OUT ("\t\t\t\$my_best_timing_line_number = \$timing_line_number;\n");
    print OUT ("\t\t\t\# print \"\$timing_line_number \$median_times{\$timing_line_number}\\n\";\n");
    print OUT ("\t\t}\n");
    print OUT ("\t\t\# print \"\$timing_line_number \$median_times{\$timing_line_number}\\n\";\n");
    print OUT ("\t\t\$i++;\n");
    print OUT ("\t}\n");
    print OUT ("\treturn \$my_best_timing_line_number;\n");
    print OUT ("}\n\n");
    print OUT ("\#\#\# BELOW IS THE PERL SCRIPT'S \"MAIN\" SUBROUTINE \#\#\#\n\n");
    print OUT ("foreach \$total_mem_footprint_in_GB (\@total_mem_footprints_in_GB) {\n");
    print OUT ("\tforeach \$numIter (\@numIter_values) {\n");
    print OUT ("\t\tforeach \$log2_nreals_x (\@log2_nreals_x_values) {\n");
    print OUT ("\t\t\tmy \$nreals_x = 2**(\$log2_nreals_x);\n");
    print OUT ("\t\t\tforeach \$log2_nreals_y (\@log2_nreals_y_values) {\n");
    print OUT ("\t\t\t\tmy \$nreals_y = 2**(\$log2_nreals_y);\n");
    print OUT ("\t\t\t\tforeach \$log2_nreals_z (\@log2_nreals_z_values) {\n");
    print OUT ("\t\t\t\t\tmy \$nreals_z = 2**(\$log2_nreals_z);\n");
    print OUT ("\t\t\t\t\tmy \$numGrids = int((\$total_mem_footprint_in_GB * 2**30) / (8 * (((\$nreals_x + 2) * (\$nreals_y + 2) * (\$nreals_z + 2)) + ((\$nreals_x + 2) * \$nreals_y * \$nreals_z) + (\$nreals_x * (\$nreals_y + 2) * \$nreals_z) + (\$nreals_x * \$nreals_y * (\$nreals_z + 2)) + 3 * (\$nreals_x * \$nreals_y * \$nreals_z))))\;\n");
    print OUT ("\t\t\t\t\tforeach \$log2_numThreads (\@log2_numThreads_values) {\n");
    print OUT ("\t\t\t\t\t\tmy \$numThreads = 2**(\$log2_numThreads);\n\n");
    print OUT ("\t\t\t\t\t\t\@log2_numThreadsPerGrid_values = (0..\$log2_numThreads)\;\n");
    print OUT ("\t\t\t\t\t\tforeach \$log2_numThreadsPerGrid (\@log2_numThreadsPerGrid_values) {\n");
    print OUT ("\t\t\t\t\t\t\tmy \$numThreadsPerGrid = 2**(\$log2_numThreadsPerGrid)\;\n");
    print OUT ("\t\t\t\t\t\t\tmy \$output_file = (\"./\" . \$platform . \"_\" . \$compiler . \"_greedy_3D_\" . \$nreals_x . \"x\" . \$nreals_y . \"x\" . \$nreals_z . \"_\" . \$numIter . \"i_\" . \$numThreads . \"t_\" . \$numThreadsPerGrid . \"tpg_\" . \$total_mem_footprint_in_GB . \"GB.txt\");\n");
    print OUT ("\t\t\t\t\t\t\t\$output_file_line_length = 0;\n\n");
    print OUT ("\t\t\t\t\t\t\t\# initialize \"best\" arrays\n");
    print OUT ("\t\t\t\t\t\t\t\@best_padding_dims = ();\n");
    print OUT ("\t\t\t\t\t\t\t\@best_core_block_dims = ();\n");
    print OUT ("\t\t\t\t\t\t\t\@best_chunk_size = ();\n");
    print OUT ("\t\t\t\t\t\t\t\@best_register_block_dims = ();\n");
    print OUT ("\t\t\t\t\t\t\t\@best_prefetch_index_type = ();\n");
    print OUT ("\t\t\t\t\t\t\t\@best_prefetch_distance = ();\n\n");
    print OUT ("\t\t\t\t\t\t\t\# set initial values\n");
    print OUT ("\t\t\t\t\t\t\tmy \$init_numCoreBlockCells_x = (\$nreals_x/\$numThreadsPerGrid);\n");
    print OUT ("\t\t\t\t\t\t\tmy \$init_numCoreBlockCells_y = \$nreals_y;\n");
    print OUT ("\t\t\t\t\t\t\tmy \$init_numCoreBlockCells_z = \$nreals_z;\n");
    print OUT ("\t\t\t\t\t\t\tmy \$init_numCoreBlocksPerChunk = 1;\n");
    print OUT ("\t\t\t\t\t\t\tmy \$init_prefetch_index_type_value = \$prefetch_index_type_values[0];\n");
    print OUT ("\t\t\t\t\t\t\tmy \$init_prefetch_distance_value = \$prefetch_distance_values[0];\n");
    print OUT ("\t\t\t\t\t\t\tmy \$init_rb_size_value = \$rb_size_values[0];\n\n");
    print OUT ("\t\t\t\t\t\t\t\# PADDING\n");
    print OUT ("\t\t\t\t\t\t\tforeach \$padding (\@padding_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\tsystem (\"\$exec_file \$numGrids \$numIter \$nreals_x \$nreals_y \$nreals_z \$numThreads \$numThreadsPerGrid \$padding \$init_numCoreBlockCells_x \$init_numCoreBlockCells_y \$init_numCoreBlockCells_z \$init_numCoreBlocksPerChunk \$init_prefetch_index_type_value \$init_prefetch_distance_value \$init_rb_size_value >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\$best_timing_line_number = find_best_time_for_opt(\$output_file, \$output_file_line_length);\n");
    print OUT ("\t\t\t\t\t\t\tfind_best_padding(\$output_file, \$best_timing_line_number);\n");
    print OUT ("\t\t\t\t\t\t\tsystem (\"echo \\\"BEST PADDING:\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\tsystem (\"echo \\\"Padding: \@best_padding_dims[0,1,2]\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\tsystem (\"echo \\\"Time: \$median_times{\$my_best_timing_line_number}\\\" >> \$output_file\");\n\n");
    print OUT ("\t\t\t\t\t\t\t\# CORE BLOCK AND CHUNK SIZE\n");
    print OUT ("\t\t\t\t\t\t\tforeach \$log2_numCoreBlockCells_x (\@log2_numCoreBlockCells_x_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\$numCoreBlockCells_x = 2**(\$log2_numCoreBlockCells_x); \# 2 to \$nreals_x in powers of 2\n");
    print OUT ("\t\t\t\t\t\t\t\tforeach \$log2_numCoreBlockCells_y (\@log2_numCoreBlockCells_y_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\tmy \$numCoreBlockCells_y = 2**(\$log2_numCoreBlockCells_y); \# 2 to \$nreals_y in powers of 2\n");
    print OUT ("\t\t\t\t\t\t\t\t\tforeach \$log2_numCoreBlockCells_z (\@log2_numCoreBlockCells_z_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\tmy \$numCoreBlockCells_z = 2**(\$log2_numCoreBlockCells_z); \# 8 to \$nreals_z in powers of 2\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\tif (\$numThreadsPerGrid == 1) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\@log2_numCoreBlocksPerChunk_values = (0)\;\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\telse {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\t\@log2_numCoreBlocksPerChunk_values = (0..((\$log2_nreals_x + \$log2_nreals_y + \$log2_nreals_z) - (\$log2_numCoreBlockCells_x + \$log2_numCoreBlockCells_y + \$log2_numCoreBlockCells_z + \$log2_numThreadsPerGrid)))\;\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\tforeach \$log2_numCoreBlocksPerChunk (\@log2_numCoreBlocksPerChunk_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\tmy \$numCoreBlocksPerChunk = 2**(\$log2_numCoreBlocksPerChunk);\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t\tsystem (\"\$exec_file \$numGrids \$numIter \$nreals_x \$nreals_y \$nreals_z \$numThreads \$numThreadsPerGrid \$best_padding_dims[2] \$numCoreBlockCells_x \$numCoreBlockCells_y \$numCoreBlockCells_z \$numCoreBlocksPerChunk \$init_prefetch_index_type_value \$init_prefetch_distance_value \$init_rb_size_value >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t}\n\n");
    print OUT ("\t\t\t\t\t\t\t\$best_timing_line_number = find_best_time_for_opt(\$output_file, \$output_file_line_length);\n");
    print OUT ("\t\t\t\t\t\t\tfind_best_core_block_and_chunk_size(\$output_file, \$best_timing_line_number);\n");
    print OUT ("\t\t\t\t\t\t\tsystem (\"echo \\\"BEST CORE BLOCK AND CHUNK SIZE:\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\tsystem (\"echo \\\"Core block: \@best_core_block_dims[0,1,2]\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\tsystem (\"echo \\\"Chunk size: \$best_chunk_size[0]\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\tsystem (\"echo \\\"Time: \$median_times{\$my_best_timing_line_number}\\\" >> \$output_file\");\n\n");
    print OUT ("\t\t\t\t\t\t\t\# INNER LOOP\n");
    print OUT ("\t\t\t\t\t\t\tforeach \$rb_size (\@rb_size_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\tsystem (\"\$exec_file \$numGrids \$numIter \$nreals_x \$nreals_y \$nreals_z \$numThreads \$numThreadsPerGrid \$best_padding_dims[2] \$best_core_block_dims[0] \$best_core_block_dims[1] \$best_core_block_dims[2] \$best_chunk_size[0] \$init_prefetch_index_type_value \$init_prefetch_distance_value \$rb_size >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\$best_timing_line_number = find_best_time_for_opt(\$output_file, \$output_file_line_length);\n");
    print OUT ("\t\t\t\t\t\t\tfind_best_inner_loop(\$output_file, \$best_timing_line_number);\n");
    print OUT ("\t\t\t\t\t\t\tsystem(\"echo \\\"BEST INNER LOOP:\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\tsystem(\"echo \\\"Register block: \@best_register_block_dims[0,1,2], case = \$best_rb_case[0]\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\tsystem(\"echo \\\"Time: \$median_times{\$my_best_timing_line_number}\\\" >> \$output_file\");\n\n");
    print OUT ("\t\t\t\t\t\t\t\# PREFETCHING\n");
    print OUT ("\t\t\t\t\t\t\tforeach \$prefetch_index_type (\@prefetch_index_type_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\tforeach \$prefetch_distance (\@prefetch_distance_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\t\tsystem (\"\$exec_file \$numGrids \$numIter \$nreals_x \$nreals_y \$nreals_z \$numThreads \$numThreadsPerGrid \$best_padding_dims[2] \$best_core_block_dims[0] \$best_core_block_dims[1] \$best_core_block_dims[2] \$best_chunk_size[0] \$prefetch_index_type \$prefetch_distance \$best_rb_case[0] >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t\t\t\$best_timing_line_number = find_best_time_for_opt(\$output_file, \$output_file_line_length);\n");
    print OUT ("\t\t\t\t\t\t\tfind_best_prefetching(\$output_file, \$best_timing_line_number);\n");
    print OUT ("\t\t\t\t\t\t\tsystem(\"echo \\\"BEST PREFETCHING:\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\tsystem(\"echo \\\"Prefetch index type: \$best_prefetch_index_type[0]\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\tsystem(\"echo \\\"Prefetch distance: \$best_prefetch_distance[0], case = \$best_prefetch_distance_case[0]\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t\tsystem(\"echo \\\"Time: \$median_times{\$my_best_timing_line_number}\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t\t}\n");
    print OUT ("\t\t\t\t}\n");
    print OUT ("\t\t\t}\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n");
    print OUT ("}\n");
}
