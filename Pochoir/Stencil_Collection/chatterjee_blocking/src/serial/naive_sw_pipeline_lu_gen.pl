#!/usr/bin/perl -w

$out_file = "naive_swp.c";
open(OUT, ">$out_file") || die ("Couldn't create $out_file.\n");

### TUNABLE PARAMETERS HERE! ###

$platform = $ARGV[0];

# number of maximum loop unrolls in the y-dimension
$max_rb_y = 4;

# specify if code should use FMA's, not use FMA's, or both
# (no FMA's = 0, FMA's = 1)
$min_fma_ins = 0;
$max_fma_ins = 1;

### "MAIN" METHOD HERE! ###

file_include_code();
generate_or_call_all_methods("generate");
generate_main_method();
close(OUT) || die;

### OTHER METHODS HERE! ###

# this method converts signed integers to strings
sub i2s {
    $num = $_[0];

    if ($num == 0) {
	$str = "";
    }
    elsif ($num > 0) {
	$str = "+" . $num;
    }
    else {
	$str = $num;
    }

    return $str;
}

sub method_name_code {
    if ($fma_ins) {
	$fma_ins_string = "FMA";
    }
    else {
	$fma_ins_string = "noFMA";
    }

    print OUT ("naive_SP_" . $nlu_y . "RB_" . $fma_ins_string . "()");
}

sub file_include_code {
    print OUT "\#include <stdio.h>\n";
    print OUT "\#include <stdlib.h>\n";
    print OUT "\#include <stdint.h>\n";
    print OUT "#include \"globals.h\"\n";
    print OUT "#include \"grid.h\"\n";
    print OUT "#include \"flush_cache.h\"\n";
    print OUT "\#ifndef DEBUG\n";
    print OUT "\#ifdef PAPI_ENABLED\n";
    print OUT "\#include \"../papi/papi_util.h\"\n";
    print OUT "\#else\n";
    print OUT "#include \"cycle_time.h\"\n";
    print OUT "#include \"cycle_time.c\"\n";
    print OUT "\#endif\n";
    print OUT "\#endif\n\n";
}

sub prolog_code {
    my($my_rb_y);
    $my_rb_y = $_[0];

    print OUT ("        k = realMin_z;\n\n");

    $num_lines_final_step = 6;
    $num_lines_this_step = 1;

    while ($num_lines_this_step <= $num_lines_final_step) {
	$unchecked_lines_ctr = $num_lines_final_step;
	$k_idx_ctr = 0;

	if ($unchecked_lines_ctr <= $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr .  " += S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr-1) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_c = S0 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s ($k_idx_ctr) . ")];\n");
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n *= S1;\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}
	$unchecked_lines_ctr--;

	if ($unchecked_lines_ctr <= $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr .  " += S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr+1) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n += Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr-1) . ")];\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}
	$unchecked_lines_ctr--;

	if ($unchecked_lines_ctr <= $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr .  " += S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr-1) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n += Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr+1) . ")];\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}
	$unchecked_lines_ctr--;

	if ($unchecked_lines_ctr <= $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr .  " += S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr+1) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n += Read[Index3D(i,j" . i2s($my_rb_y_ctr-1) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}
	$unchecked_lines_ctr--;

	if ($unchecked_lines_ctr <= $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr .  " += S1 * Read[Index3D(i-1,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n += Read[Index3D(i,j" . i2s($my_rb_y_ctr+1) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}
	$unchecked_lines_ctr--;

	if ($unchecked_lines_ctr <= $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr .  " = S1 * Read[Index3D(i+1,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr .  "_n = Read[Index3D(i+1,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr) . ")] + Read[Index3D(i-1,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}
	$unchecked_lines_ctr--;

	$num_lines_this_step++;
	print OUT ("\n");
    }
}

sub inner_loop_code {
    my($my_rb_y);
    $my_rb_y = $_[0];

    print OUT ("        for (; k < (realMax_z-6); k++) {\n");
    
    $my_rb_y_ctr = 0;
    while ($my_rb_y_ctr <= $my_rb_y) {
	if ($fma_ins) {
	    print OUT ("          Write[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k)] = S0 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k)] + temp_" . $my_rb_y_ctr . "_0;\n");
	}
	else {
	    print OUT ("          Write[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k)] = temp_" . $my_rb_y_ctr . "_c + temp_" . $my_rb_y_ctr . "_0_n;\n");
	}
	$my_rb_y_ctr++;
    }

    $my_rb_y_ctr = 0;
    while ($my_rb_y_ctr <= $my_rb_y) {
	if ($fma_ins) {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_0 = S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k)] + temp_" . $my_rb_y_ctr . "_1;\n");
	}
	else {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_c = S0 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k+1)];\n");
	    print OUT ("          temp_" . $my_rb_y_ctr . "_0_n = S1 * temp_" . $my_rb_y_ctr . "_1_n;\n");
	}
	$my_rb_y_ctr++;
    }
	
    $my_rb_y_ctr = 0;
    while ($my_rb_y_ctr <= $my_rb_y) {
	if ($fma_ins) {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_1 = S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k+3)] + temp_" . $my_rb_y_ctr . "_2;\n");
	}
	else {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_1_n = Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k+1)] + temp_" . $my_rb_y_ctr . "_2_n;\n");
	}
	$my_rb_y_ctr++;
    }
	
    $my_rb_y_ctr = 0;
    while ($my_rb_y_ctr <= $my_rb_y) {
	if ($fma_ins) {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_2 = S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr-1) . ",k+3)] + temp_" . $my_rb_y_ctr . "_3;\n");
	}
	else {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_2_n = Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k+4)] + temp_" . $my_rb_y_ctr . "_3_n;\n");
	}
	$my_rb_y_ctr++;
    }
	
    $my_rb_y_ctr = 0;
    while ($my_rb_y_ctr <= $my_rb_y) {
	if ($fma_ins) {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_3 = S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr+1) . ",k+4)] + temp_" . $my_rb_y_ctr . "_4;\n");
	}
	else {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_3_n = Read[Index3D(i,j" . i2s($my_rb_y_ctr-1) . ",k+4)] + temp_" . $my_rb_y_ctr . "_4_n;\n");
	}
	$my_rb_y_ctr++;
    }

    $my_rb_y_ctr = 0;
    while ($my_rb_y_ctr <= $my_rb_y) {
	if ($fma_ins) {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_4 = S1 * Read[Index3D(i-1,j" . i2s($my_rb_y_ctr) . ",k+5)] + temp_" . $my_rb_y_ctr . "_5;\n");
	}
	else {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_4_n = Read[Index3D(i,j" . i2s($my_rb_y_ctr+1) . ",k+5)] + temp_" . $my_rb_y_ctr . "_5_n;\n");
	}
	$my_rb_y_ctr++;
    }

    $my_rb_y_ctr = 0;
    while ($my_rb_y_ctr <= $my_rb_y) {
	if ($fma_ins) {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_5 = S1 * Read[Index3D(i+1,j" . i2s($my_rb_y_ctr) . ",k+6)];\n");
	}
	else {
	    print OUT ("          temp_" . $my_rb_y_ctr . "_5_n = Read[Index3D(i+1,j" . i2s($my_rb_y_ctr) . ",k+6)] + Read[Index3D(i-1,j" . i2s($my_rb_y_ctr) . ",k+6)];\n");
	}
	$my_rb_y_ctr++;
    }

    print OUT ("        }\n\n");
}

sub epilog_code {
    my($my_rb_y);
    $my_rb_y = $_[0];

    $num_lines_final_step = 1;
    $num_lines_this_step = 6;
    $min_k_idx_ctr = -1;

    while ($num_lines_this_step >= $num_lines_final_step) {
	$min_k_idx_ctr++;
	$k_idx_ctr = $min_k_idx_ctr;

	if (($k_idx_ctr-$min_k_idx_ctr) < $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        Write[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr) . ")] = S0 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr) . ")] + temp_". $my_rb_y_ctr . "_" . $k_idx_ctr . ";\n");
		}
		else {
		    print OUT ("        Write[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr) . ")] = temp_" . $my_rb_y_ctr . "_c + temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n;\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}

	if (($k_idx_ctr-$min_k_idx_ctr) < $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . " += S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr-1) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_c = S0 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s ($k_idx_ctr) . ")];\n");
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n *= S1;\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}

	if (($k_idx_ctr-$min_k_idx_ctr) < $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . " += S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr+1) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n += Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr-1) . ")];\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}

	if (($k_idx_ctr-$min_k_idx_ctr) < $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . " += S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr-1) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n += Read[Index3D(i,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr+1) . ")];\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}

	if (($k_idx_ctr-$min_k_idx_ctr) < $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . " += S1 * Read[Index3D(i,j" . i2s($my_rb_y_ctr+1) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n += Read[Index3D(i,j" . i2s($my_rb_y_ctr-1) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}

	if (($k_idx_ctr-$min_k_idx_ctr) < $num_lines_this_step) {
	    $my_rb_y_ctr = 0;
	    while ($my_rb_y_ctr <= $my_rb_y) {
		if ($fma_ins) {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . " += S1 * Read[Index3D(i-1,j" . i2s($my_rb_y_ctr) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		else {
		    print OUT ("        temp_" . $my_rb_y_ctr . "_" . $k_idx_ctr . "_n += Read[Index3D(i,j" . i2s($my_rb_y_ctr+1) . ",k" . i2s($k_idx_ctr) . ")];\n");
		}
		$my_rb_y_ctr++;
	    }
	    $k_idx_ctr++;
	}

	$num_lines_this_step--;
	print OUT ("\n");
    }
}

sub triply_nested_loop_code {
    print OUT ("    for (i=realMin_x; i < realMax_x; i++) {\n");
    if ($nlu_y == 0) {
	print OUT ("      for (j=realMin_y; j < realMax_y; j++) {\n");
    }
    else {
	print OUT ("      for (j=realMin_y; j < (realMax_y-" . $nlu_y . "); j+=" . ($nlu_y+1) . ") {\n");
    }

    prolog_code($nlu_y);
    inner_loop_code($nlu_y);
    epilog_code($nlu_y);

    print OUT ("      }\n");
    if ($nlu_y > 0) {
	print OUT ("\n      for (; j < realMax_y; j++) {\n");
	prolog_code(0);
	inner_loop_code(0);
	epilog_code(0);
	print OUT ("      }\n");
    }
    print OUT ("    }\n");
}

sub generate_stencil_method {
    print OUT ("void ");
    method_name_code();
    print OUT (" {\n");

    print OUT ("  double * __restrict__ temp_ptr;\n");

    # temp variable declarations
    $nlu_y_ctr = 0;
    while ($nlu_y_ctr <= $nlu_y) {
	if ($fma_ins) {
	    print OUT ("  double temp_" . $nlu_y_ctr . "_0, temp_" . $nlu_y_ctr . "_1, temp_" . $nlu_y_ctr . "_2, temp_" . $nlu_y_ctr . "_3, temp_" . $nlu_y_ctr . "_4, temp_" . $nlu_y_ctr . "_5;\n");
	}
	else {
	    print OUT ("  double temp_" . $nlu_y_ctr . "_c, temp_" . $nlu_y_ctr . "_0_n, temp_" . $nlu_y_ctr . "_1_n, temp_" . $nlu_y_ctr . "_2_n, temp_" . $nlu_y_ctr . "_3_n, temp_" . $nlu_y_ctr . "_4_n, temp_" . $nlu_y_ctr . "_5_n;\n");
	}
	$nlu_y_ctr++;
    }

    print OUT ("  uint_fast32_t i, j, k, t;\n\n");
    print OUT ("  double * __restrict__ Read = A;\n");
    print OUT ("  double * __restrict__ Write = B;\n\n");
    print OUT ("  for (t=0; t < numIter; t++) {\n");
    
    if ($platform eq "bassi") {
	print OUT ("\n#pragma disjoint(*C, *D)\n\n");
    }

    triply_nested_loop_code();

    print OUT ("    temp_ptr = Read;\n");
    print OUT ("    Read = Write;\n");
    print OUT ("    Write = temp_ptr;\n");
    print OUT ("  }\n");
    print OUT ("}\n\n");
}

sub generate_or_call_one_method {
    my($code_type);

    $code_type = $_[0];

    if ($fma_ins) {
	$method_desc_string = ("  printf\(\"$nlu_y LOOP UNROLL IN Y-DIM, SOFTWARE PIPELINING IN Z-DIM, FMAs USED:\\n\"\);\n");
    }
    else {
	$method_desc_string = ("  printf\(\"$nlu_y LOOP UNROLL IN Y-DIM, SOFTWARE PIPELINING IN Z-DIM, NO FMAs USED:\\n\"\);\n");
    }

    if ($code_type eq "generate") {
	generate_stencil_method();
    }
    elsif ($code_type eq "debug_call") {
	print OUT ("\n  init_grids\(\);\n");
	print OUT $method_desc_string;
	print OUT ("  printf\(\"\\nGRID A BEFORE:\"\);\n");
	print OUT ("  print_grid\(A\);\n");
	print OUT ("  printf\(\"\\nGRID B BEFORE:\"\);\n");
	print OUT ("  print_grid\(B\);\n\n  ");
	method_name_code();
	print OUT (";\n\n");
	print OUT ("  printf\(\"\\nGRID A AFTER:\"\);\n");
	print OUT ("  print_grid\(A\);\n");
	print OUT ("  printf\(\"\\nGRID B AFTER:\"\);\n");
	print OUT ("  print_grid\(B\);\n");
    }
    elsif ($code_type eq "papi_call") {
	print OUT $method_desc_string;
	print OUT ("  for \(papi_setnum=0; papi_setnum < num_sets; papi_setnum++\) {\n");
	print OUT ("    PAPI_MAKE_MEASUREMENTS\(event_sets[papi_setnum].set, ");
	method_name_code();
	print OUT (", NUM_TRIALS, results\);\n");
	print OUT ("    print_papi_measurements\(&\(event_sets[papi_setnum]\), results, NUM_TRIALS\);\n");
	print OUT ("  }\n");
	print OUT ("  printf\(\"\\n\"\);\n");
    }
    elsif ($code_type eq "timer_call") {
	print OUT $method_desc_string;
	print OUT ("  TIMER_MAKE_MEASUREMENTS\(");
	method_name_code();
	print OUT (", NUM_TRIALS, results\);\n");
	print OUT ("  printf\(\"CYCLES =\\n\"\);\n");
	print OUT ("  print_timer_measurements(results, NUM_TRIALS\);\n");
	print OUT ("  printf\(\"\\n\"\);\n");
    }
}

sub generate_or_call_all_methods {
    my($code_type);

    $code_type = $_[0];
    $fma_ins = $min_fma_ins;
    
    while ($fma_ins <= $max_fma_ins) {
	$nlu_y = 0;
	while ($nlu_y <= $max_rb_y) {
	    generate_or_call_one_method($code_type);
	    $nlu_y++;
	}
	$fma_ins++;
    }
}

sub generate_main_method {
    print OUT ("int main(int argc, char *argv[]) {\n");
    print OUT ("  double results[NUM_TRIALS];\n");
    print OUT ("\#ifdef PAPI_ENABLED\n");
    print OUT ("  int papi_setnum;\n");
    print OUT ("\#endif\n");
    print OUT ("  int i;\n\n");
    print OUT ("  printf\(\"7-point stencil, no add, naive C code with non-periodic boundary conditions\\n\"\);\n");
    print OUT ("\#ifndef DEBUG\n");
    print OUT ("  // calculate clock rate\n");
    print OUT ("  GET_CLOCK_RATE\(NUM_TRIALS, results\);\n");
    print OUT ("  printf\(\"Clock rate: \"\);\n");
    print OUT ("  for \(i=0; i < NUM_TRIALS; i++\) {\n");
    print OUT ("    printf\(\"%0.3f, \", results[i]\);\n");
    print OUT ("  }\n");
    print OUT ("  printf\(\" GHz\\n\"\);\n");
    print OUT ("#endif\n");
    print OUT ("\#ifdef PAPI_ENABLED\n");
    print OUT ("  // initialize papi\n");
    print OUT ("  int desired_events[] = {PAPI_TOT_CYC, PAPI_FP_INS, PAPI_L2_DCA, PAPI_L2_DCM, PAPI_L3_DCM, PAPI_TLB_DM, PAPI_LD_INS, PAPI_SR_INS};\n");
    print OUT ("  int num_desired = 9;\n");
    print OUT ("  PAPI_event_set_wrapper_t* event_sets;\n");
    print OUT ("  int num_sets;\n");
    print OUT ("  papi_init\(desired_events, num_desired, &event_sets, &num_sets\);\n");
    print OUT ("\#endif\n\n");
    print OUT ("  // initialize arrays\n");
    print OUT ("  init_flush_cache_array\(\);\n");
    print OUT ("  malloc_grids\(argv\);\n\n");
    print OUT ("  printf\(\"\\n\"\);\n");
    print OUT ("\#ifdef DEBUG\n");

    generate_or_call_all_methods("debug_call");

    print OUT ("\#else\n");
    print OUT ("\#ifdef PAPI_ENABLED\n");

    generate_or_call_all_methods("papi_call");

    print OUT ("  papi_cleanup\(event_sets, num_sets\);\n");
    print OUT ("\#else\n");
	
    generate_or_call_all_methods("timer_call");

    print OUT ("  printf\(\"\\n\"\);\n");
    print OUT ("\#endif\n");
    print OUT ("\#endif\n\n");
    print OUT ("  printf\(\"\\nFinal interior values: A[%d, %d, %d] = %4.2e, B[%d, %d, %d] = %4.2e\\n\", nx/2, ny/2, nz/2, A[Index3D\(nx/2, ny/2, nz/2\)], nx/2, ny/2, nz/2, B[Index3D\(nx/2, ny/2, nz/2\)]\);\n");
    print OUT ("  fc_checksum\(\);\n");
    print OUT ("  free\(A\);\n");
    print OUT ("  free\(B\);\n\n");
    print OUT ("  return EXIT_SUCCESS;\n");
    print OUT ("}\n");
}
