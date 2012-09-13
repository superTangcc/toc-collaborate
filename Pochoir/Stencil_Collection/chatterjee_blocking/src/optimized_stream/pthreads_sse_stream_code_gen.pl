#!/usr/bin/perl -w

### THESE PARAMETERS SPECIFY WHAT CODE IS GENERATED AND COMPILED ###

# number of read arrays and write arrays
@read_array_counts = (0..7);
@write_array_counts = (0..7);

# write types - choose "store" or "stream" writes (or both)
@write_types = ("store", "stream");

# load types - choose "implicit" or "explicit" loads (or both)
@load_types = ("implicit", "explicit");

# number of loop unrolls ("1" means unit-stride traversal)
@loop_unrolls = (1..10);

# prefetch distances ("-1" means no prefetching)
@prefetch_distances = (-1, 0, 32, 64, 128, 256, 512);

### BELOW IS THE PERL SCRIPT'S "MAIN" SUBROUTINE ###
%write_types_hash = ("store", 0, "stream", 1);
%load_types_hash = ("implicit", 0, "explicit", 1);

$function_headers_file = ("function_headers.h");
open(OUT, ">$function_headers_file") || die ("Couldn't create $function_headers_file.\n");
generate_all_stream_functions("function_headers");
close(OUT) || die;

$function_table_file = ("function_table.c");
open(OUT, ">$function_table_file") || die ("Couldn't create $function_table_file.\n");
generate_all_stream_functions("function_table");
close(OUT) || die;

$variables_file = ("variables.c");
open(OUT, ">$variables_file") || die ("Couldn't create $variables_file.\n");
generate_global_vars();
close(OUT) || die;

$functions_file = ("functions.c");
open(OUT, ">$functions_file") || die ("Couldn't create $functions_file.\n");
generate_all_stream_functions("generate");
close(OUT) || die;

$code_variant_header_file = ("code_variant.h");
open(OUT, ">$code_variant_header_file") || die ("Couldn't create $code_variant_header_file.\n");
generate_code_variant_header_file();
close(OUT) || die;

$code_variant_file = ("code_variant.c");
open(OUT, ">$code_variant_file") || die ("Couldn't create $code_variant_file.\n");
generate_code_variant_file();
close(OUT) || die;

$main_headers_file = ("stream_pthreads.h");
open(OUT, ">$main_headers_file") || die ("Couldn't create $main_headers_file.\n");
generate_per_thread_function_name();
close(OUT) || die;

$main_file = ("stream_pthreads.c");
open(OUT, ">$main_file") || die ("Couldn't create $main_file.\n");
generate_directives();
generate_per_thread_function();
generate_main_function();
close(OUT) || die;

$specified_data_script = ("specified_sse_data_generator.pl");
open(OUT, ">$specified_data_script") || die ("Couldn't create $specified_data_script.\n");
generate_specified_data_script();
system ("chmod 755 $specified_data_script");
close(OUT) || die;

$greedy_data_script = ("greedy_sse_data_generator.pl");
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

sub per_thread_function_name_str {
    return ("void *pthreads_each(void *rank_ptr)");
}

# Returns the function name as a string
sub function_name_str {
    if ($prefetch_distance != -1) {
	return ("stream_per_thread_" . $read_array_count . "R_" . $write_array_count . "W_" . $write_type . "_" . $load_type . "_" . $loop_unroll . "LU_" . $prefetch_distance . "PD");
    }
    else {
	return ("stream_per_thread_" . $read_array_count . "R_" . $write_array_count . "W_" . $write_type . "_" . $load_type . "_" . $loop_unroll . "LU_noPrefetch");
    }
}

sub function_parameters_str {
    return ("\(uint32_t rank\)");
}

sub function_table_name_str {
    return ("stream_per_thread[read_arrays_case][write_arrays_case][write_type_case][load_type_case][loop_unroll_case][prefetch_distance_case]");
}

### BELOW ARE THE BUILDING BLOCK SUBROUTINES ###

sub prefetch_code {
    if ($prefetch_distance != -1) {
	for (my $rac=0; $rac < $read_array_count; $rac++) {
	    print OUT ("    PREFETCH_FOR_ONE_READ(&ReadArray" . $rac . "_local[i]" . i2s($prefetch_distance) . "\)\;\n");
	}
	for (my $wac=0; $wac < $write_array_count; $wac++) {
	    print OUT ("    PREFETCH_FOR_ONE_WRITE(&WriteArray" . $wac . "_local[i]" . i2s($prefetch_distance) . "\)\;\n");
	}
	print OUT ("\n");
    }
}

### BELOW ARE THE SUBROUTINES THAT MAKE THE NESTED LOOPS ###

# Generates the code for the triply nested loops
sub singly_nested_loop_code {
    print OUT ("  maxLoopUnrolledLength = threadArrayLength - " . (2*$loop_unroll-1) . ";\n");
    print OUT ("  for (i=0; i < maxLoopUnrolledLength; i+=" . (2*$loop_unroll) . ") {\n");
    prefetch_code();

    if ($load_type eq "explicit") {
	for ($rac=0; $rac < $read_array_count; $rac++) {
	    for (my $lu=0; $lu < $loop_unroll; $lu++) {
		print OUT ("    read_" . $rac . "_" . $lu . " = _mm_load_pd(&(ReadArray" . $rac . "_local[i" . i2s(2*$lu) . "]));\n");
	    }
	}
	print OUT ("\n");
    }

    for (my $lu=0; $lu < $loop_unroll; $lu++) {
	if ($write_array_count == 0) {
	    for ($rac=0; $rac < $read_array_count; $rac++) {
		print OUT ("    result" . $lu . " = _mm_mul_pd(result" . $lu);
		if ($load_type eq "implicit") {
		    print OUT (", *(__m128d *)(&(ReadArray" . $rac . "_local[i" . i2s(2*$lu) . "])));\n");
		}
		elsif ($load_type eq "explicit") {
		    print OUT (", read_" . $rac . "_" . $lu . ");\n");
		}
	    }
	}
	else {
	    if ($read_array_count == 1) {
		if ($load_type eq "implicit") {
		    print OUT ("    result" . $lu . " = *(__m128d *)(&(ReadArray0_local[i" . i2s(2*$lu) . "]));\n");
		}
		elsif ($load_type eq "explicit") {
		    print OUT ("    result" . $lu . " = read_0_" . $lu . ";\n");
		}
	    }
	    elsif ($read_array_count > 1) {
		for ($rac=1; $rac < $read_array_count; $rac++) {
		    print OUT ("    result" . $lu . " = _mm_mul_pd(");
		    if ($rac == 1) {
			if ($load_type eq "implicit") {
			    print OUT ("*(__m128d *)(&(ReadArray0_local[i" . i2s(2*$lu) . "]))");
			}
			elsif ($load_type eq "explicit") {
			    print OUT ("read_0_" . $lu);
			}
		    }
		    else {
			print OUT ("result" . $lu);
		    }
		    if ($load_type eq "implicit") {
			print OUT (", *(__m128d *)(&(ReadArray" . $rac . "_local[i" . i2s(2*$lu) . "])));\n");
		    }
		    elsif ($load_type eq "explicit") {
			print OUT (", read_" . $rac . "_" . $lu . ");\n");
		    }
		}
	    }
	}
    }
    print OUT ("\n");

    for (my $lu=0; $lu < $loop_unroll; $lu++) {
	for ($wac=0; $wac < $write_array_count; $wac++) {
	    print OUT ("    _mm_" . $write_type . "_pd(&WriteArray" . $wac . "_local[i" . i2s(2*$lu) . "], result" . $lu . ");\n");
	}
    }
    print OUT ("  }\n");

    if ($read_array_count > 0) {
	print OUT ("\n  for (; i < threadArrayLength; i++) {\n");
	for ($wac=0; $wac < $write_array_count; $wac++) {
	    print OUT ("    WriteArray" . $wac . "_local[i] = ");
	    for ($rac=0; $rac < $read_array_count; $rac++) {
		print OUT ("ReadArray" . $rac . "_local[i]");
		if ($rac < ($read_array_count-1)) {
		    print OUT (" * ");
		}
	    }
	    print OUT (";\n");
	}
	print OUT ("  }\n");
    }

    if (($read_array_count > 0) && ($write_array_count == 0)) {
	for (my $lu=0; $lu < $loop_unroll; $lu++) {
	    print OUT ("  _mm_" . $write_type . "_pd(&ReadArray0_local[" . (2*$lu) . "], result" . $lu . ");\n");
	}
    }

    print OUT ("  barrier_wait(&my_barrier, rank);\n");
}

### BELOW ARE THE SUBROUTINES THAT GENERATE FULL FUNCTIONS ###

# Generates a single stream function
sub generate_single_stream_function {
    print OUT ("void " . function_name_str() . function_parameters_str() . " {\n");

    if ($read_array_count > 0) {
	print OUT ("  double ");
    }
    for ($rac=0; $rac < $read_array_count; $rac++) {
	print OUT ("*ReadArray" . $rac . "_local");
	if ($rac < ($read_array_count-1)) {
	    print OUT (", ");
	}
    }
    if ($read_array_count > 0) {
	print OUT (";\n");
    }

    if ($write_array_count > 0) {
	print OUT ("  double ");
    }
    for ($wac=0; $wac < $write_array_count; $wac++) {
	print OUT ("*WriteArray" . $wac . "_local");
	if ($wac < ($write_array_count-1)) {
	    print OUT (", ");
	}
    }
    if ($write_array_count > 0) {
	print OUT (";\n");
    }

    if ($load_type eq "explicit") {
	for ($rac=0; $rac < $read_array_count; $rac++) {
	    print OUT ("  __m128d ");
	    for (my $lu=0; $lu < $loop_unroll; $lu++) {
		print OUT ("read_" . $rac . "_" . $lu);
		if ($lu < ($loop_unroll-1)) {
		    print OUT (", ");
		}
		else {
		    print OUT (";\n");
		}
	    }
	}
    }

    print OUT ("  uint32_t i, maxLoopUnrolledLength\;\n");

    if (($read_array_count > 0) || ($write_array_count > 0)) {
	print OUT ("  __m128d ");
	for (my $lu=0; $lu < $loop_unroll; $lu++) {
	    print OUT ("result" . $lu);
	    if ($lu < ($loop_unroll-1)) {
		print OUT (", ");
	    }
	}
	print OUT (";\n\n");
	
	for (my $lu=0; $lu < $loop_unroll; $lu++) {
	    print OUT ("  result" . $lu . " = _mm_set1_pd(1.0);\n");
	}
	print OUT ("\n");
    }

    for ($rac=0; $rac < $read_array_count; $rac++) {
	print OUT ("  ReadArray" . $rac . "_local = (double *) Arrays[" . $rac . "][rank];\n");
    }
    print OUT ("\n");

    for ($wac=0; $wac < $write_array_count; $wac++) {
	print OUT ("  WriteArray" . $wac . "_local = (double *) Arrays[" . ($read_array_count + $wac) . "][rank];\n");
    }
    print OUT ("\n");

    singly_nested_loop_code();

    print OUT ("}\n\n");
}

# Generates all the stream functions, or all the function headers, or the function table
sub generate_all_stream_functions {
    my($code_type) = @_;

    if ($code_type eq "function_table") {
	print OUT ("#define READ_ARRAY_COUNTS " . @read_array_counts . "\t// the number of read arrays\n");
	print OUT ("#define WRITE_ARRAY_COUNTS " . @write_array_counts . "\t// the number of write arrays\n");
	print OUT ("#define WRITE_TYPES " . @write_types . "\t// regular stores or streaming stores\n");
	print OUT ("#define LOAD_TYPES " . @load_types . "\t// implicit or explicit loads\n");
	print OUT ("#define LOOP_UNROLLS " . @loop_unrolls . "\t\t// the number of loop unrolls\n");
	print OUT ("#define PREFETCH_DISTANCES " . @prefetch_distances . "\t// the distances ahead being prefetched\n\n");
	print OUT ("void (*stream_per_thread[READ_ARRAY_COUNTS][WRITE_ARRAY_COUNTS][WRITE_TYPES][LOAD_TYPES][LOOP_UNROLLS][PREFETCH_DISTANCES])() =\n{");
    }

    foreach $read_array_count (@read_array_counts) {
	if ($code_type eq "function_table") {
	    print OUT ("{");
	}
	foreach $write_array_count (@write_array_counts) {
	    if ($code_type eq "function_table") {
		print OUT ("{");
	    }
	    foreach $write_type (@write_types) {
		if ($code_type eq "function_table") {
		    print OUT ("{");
		}
		foreach $load_type (@load_types) {
		    if ($code_type eq "function_table") {
			print OUT ("{");
		    }
		    foreach $loop_unroll (@loop_unrolls) {
			if ($code_type eq "function_table") {
			    print OUT ("{");
			}
			foreach $prefetch_distance (@prefetch_distances) {
			    if ($code_type eq "generate") {
				generate_single_stream_function();
			    }
			    elsif ($code_type eq "function_headers") {
				print OUT ("void " . function_name_str() . function_parameters_str() . ";\n");
			    }
			    elsif ($code_type eq "function_table") {
				print OUT ("\t&" . function_name_str());
				if ($prefetch_distance != $prefetch_distances[@prefetch_distances-1]) {
				    print OUT (", ");
				}
			    }
			}
			if ($code_type eq "function_table") {
			    if ($loop_unroll != $loop_unrolls[@loop_unrolls-1]) {
				print OUT ("},\n");
			    }
			    else {
				print OUT ("}\n");
			    }
			}
		    }
		    if ($code_type eq "function_table") {
			if ($load_type eq $load_types[@load_types-1]) {
			    print OUT ("}\n");
			}
			else {
			    print OUT ("},\n");
			}
		    }
		}
		if ($code_type eq "function_table") {
		    if ($write_type eq $write_types[@write_types-1]) {
			print OUT ("}\n");
		    }
		    else {
			print OUT ("},\n");
		    }
		}
	    }
	    if ($code_type eq "function_table") {
		if ($write_array_count != $write_array_counts[@write_array_counts-1]) {
		    print OUT ("},\n");
		}
		else {
		    print OUT ("}\n");
		}
	    }
	}
	if ($code_type eq "function_table") {
	    if ($read_array_count != $read_array_counts[@read_array_counts-1]) {
		print OUT ("},\n");
	    }
	    else {
		print OUT ("}\n");
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
    print OUT "uint32_t read_arrays_case, write_arrays_case, write_type_case, load_type_case, loop_unroll_case, prefetch_distance_case\;\n\n";
    print OUT "void select_code_variant\(char *argv\[\]\)\;\n";
    print OUT "void print_code_variant_parameters\(void\)\;\n";
}

sub generate_code_variant_file {
    print OUT ("void select_code_variant\(char *argv\[\]\) {\n");
    print OUT ("  read_arrays_case = numReadArraysPerThread - " . $read_array_counts[0] . ";\n");
    print OUT ("  write_arrays_case = numWriteArraysPerThread - " . $write_array_counts[0] . ";\n");
    print OUT ("  write_type_case = atoi\(argv\[6\]\)\;\n");
    print OUT ("  load_type_case = atoi\(argv\[7\]\)\;\n");
    print OUT ("  loop_unroll_case = atoi\(argv\[8\]\)\;\n");
    print OUT ("  prefetch_distance_case = atoi\(argv\[9\]\)\;\n");
    print OUT ("}\n\n");
    print OUT ("void print_code_variant_parameters\(\) {\n");
    print OUT ("  switch (write_type_case) {\n");
    $case_count = 0;
    foreach $type (@write_types) {
	print OUT ("    case $case_count: printf\(\"write type (store=0, stream=1) = \\n$write_types_hash{$type},\\n\"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("  switch (load_type_case) {\n");
    $case_count = 0;
    foreach $type (@load_types) {
	print OUT ("    case $case_count: printf\(\"load type (implicit=0, explicit=1) = \\n$load_types_hash{$type},\\n\"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("  switch (loop_unroll_case) {\n");
    $case_count = 0;
    foreach $loop_unroll (@loop_unrolls) {
	print OUT ("    case $case_count: printf\(\"loop_unroll = \\n$loop_unroll, case number, $case_count,\\n\"\)\; break\;\n");
	$case_count++;
    }
    print OUT ("  }\n");
    print OUT ("  switch (prefetch_distance_case) {\n");
    $case_count = 0;
    foreach $distance (@prefetch_distances) {
	print OUT ("    case $case_count: printf\(\"prefetch distance = \\n$distance, case number, $case_count,\\n\"\)\; break\;\n");
	$case_count++;
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
    print OUT "#include \"array.h\"\n";
    print OUT "#include \"code_variant.h\"\n";
    print OUT ("#include \"" . $function_headers_file . "\"\n");
    print OUT ("#include \"" . $main_headers_file . "\"\n");
    print OUT "#if defined(GETTIMEOFDAY)\n";
    print OUT "#include \"../../timers/gettimeofday.h\"\n";
    print OUT "#endif\n";
    print OUT "#if defined(CLOCK_GETTIME)\n";
    print OUT "#include \"../../timers/clock_gettime.h\"\n";
    print OUT "#endif\n";
    print OUT "#include \"../../timers/time_pthreads_stream.h\"\n";
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
    print OUT "#include \"array.c\"\n";
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
    print OUT ("#if !defined(DEBUG)\n");
    print OUT ("  uint32_t bytes_transferred\;\n");
    print OUT ("#endif\n");
    print OUT ("\n#if defined(PAPI_ENABLED) && !defined(DEBUG)\n");
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
    print OUT ("  init_arrays\(rank\)\;\n");
    print OUT ("  barrier_wait\(&my_barrier, rank\)\;\n");
    print OUT ("  " . function_table_name_str() . "\(rank\)\;\n");
    print OUT ("  barrier_wait\(&my_barrier, rank\)\;\n");
    print OUT ("  if \(rank == 0\) {\n");
    print OUT ("    print_arrays\(\)\;\n");
    print OUT ("  }\n");
    print OUT ("#else\n");
    print OUT ("  TIMER_MAKE_MEASUREMENTS(" . function_table_name_str() . "(rank), results, rank, NUM_TRIALS);\n");
    print OUT ("  if \(rank == 0\) {\n");
    print OUT ("    printf\(\"TIME (IN SECONDS)\\n\"\)\;\n");
    print OUT ("    print_max_timer_measurements\(results, numThreads, NUM_TRIALS, median_counts_per_sec\)\;\n");
    print OUT ("    printf\(\"\\nBANDWIDTH (IN GB/S, WHERE 1 GB/S = 10^9 B/S)\\n\"\)\;\n");
    print OUT ("    bytes_transferred = 0\;\n");
    print OUT ("    if (write_type_case == 0) {\n");
    print OUT ("      bytes_transferred = (numReadArraysPerThread + 2*numWriteArraysPerThread) * (numThreads * threadArrayLength * NUM_BYTES_PER_DOUBLE)\;\n");
    print OUT ("    }\n");
    print OUT ("    else if (write_type_case == 1) {\n");
    print OUT ("      bytes_transferred = (numReadArraysPerThread + numWriteArraysPerThread) * (numThreads * threadArrayLength * NUM_BYTES_PER_DOUBLE)\;\n");
    print OUT ("    }\n");
    print OUT ("    print_bandwidth_measurements\(results, bytes_transferred, numThreads, NUM_TRIALS, median_counts_per_sec\)\;\n");
    print OUT ("    printf\(\"\\n\\n\"\)\;\n");
    print OUT ("  }\n");
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
    print OUT "  uint32_t t\;\n\n";
    print OUT "  printf\(\"Optimized Stream benchmark (using SSE intrinsics)\\n\"\)\;\n\n";
    print OUT "  init_flush_cache_array\(\)\;\n";
    print OUT "  malloc_arrays\(argv\)\;\n";
    print OUT "  print_array_parameters\(\)\;\n";
    print OUT "  select_code_variant\(argv\)\;\n";
    print OUT "  print_code_variant_parameters\(\)\;\n\n";
    print OUT "  threads = \(pthread_t *\) malloc\(numThreads * sizeof\(pthread_t\)\)\;\n";
    print OUT "  ranks = \(uint32_t **\) malloc\(numThreads * sizeof\(uint32_t *\)\);\n\n";
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
    print OUT "  // run stream tests\n";
    print OUT "  for \(t=0\; t < numThreads\; t++\) {\n";
    print OUT "    ranks[t] = \(uint32_t *\) malloc\(sizeof\(uint32_t\)\);\n";
    print OUT "    *ranks[t] = t\;\n";
    print OUT "  }\n\n";
    print OUT "  for \(t=1\; t < numThreads\; t++\) {\n";
    print OUT "#if defined\(DEBUG\)\n";
    print OUT "    printf\(\"Creating thread %u\\n\", t);\n";
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
    print OUT "#if defined\(PAPI_ENABLED\) && !defined\(DEBUG\)\n";
    print OUT "  papi_cleanup\(event_sets, num_sets\)\;\n";
    print OUT "#endif\n";
    print OUT ("  pthread_attr_destroy\(&attr\);\n");
    print OUT ("  pthread_exit\(NULL\)\;\n");
    print OUT ("  barrier_destroy\(&my_barrier\)\;\n");
    print OUT ("  free_arrays\(\);\n\n");
    print OUT ("  return EXIT_SUCCESS;\n");
    print OUT ("}\n");
}

sub generate_specified_data_script {
    print OUT ("#!/usr/bin/perl -w\n\n");
    print OUT ("\$platform=\$ARGV[0]\;\n");
    print OUT ("\$compiler=\$ARGV[1]\;\n\n");
    print OUT ("my \$exec_file = \"./stream_pthreads_\${compiler}_c\"\;\n\n");
    print OUT ("\$mem_footprint_in_GB = 2.0\;\n");
    print OUT ("\@numThreads_values = (1,2,4,8)\;\n");
    print OUT ("\@read_array_count_values = (" . $read_array_counts[0] . ".." . $read_array_counts[@read_array_counts-1] . ")\;\n");
    print OUT ("\@write_array_count_values = (" . $write_array_counts[0] . ".." . $write_array_counts[@write_array_counts-1] . ")\;\n");
    print OUT ("\@threadPaddingLength_values = (0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30)\;\n");
    print OUT ("\@write_type_values = (0.." . (@write_types-1) . ")\;\n");
    print OUT ("\@load_type_values = (0.." . (@load_types-1) . ")\;\n");
    print OUT ("\@loop_unroll_values = (0.." . (@loop_unrolls-1) . ")\;\n");
    print OUT ("\@prefetch_distance_values = (0.." . (@prefetch_distances-1) . ")\;\n\n");
    print OUT ("\$memory_footprint_in_B = int(\$mem_footprint_in_GB * 2**30)\;\n");
    print OUT ("foreach \$numThreads (\@numThreads_values) {\n");
    print OUT ("\tforeach \$read_array_count_value (\@read_array_count_values) {\n");
    print OUT ("\t\tforeach \$write_array_count_value (\@write_array_count_values) {\n");
    print OUT ("\t\t\tforeach \$write_type_value (\@write_type_values) {\n");
    print OUT ("\t\t\t\tif (\$write_type_value == 0) {\n");
    print OUT ("\t\t\t\t\t\$write_str = \"store\"\;\n");
    print OUT ("\t\t\t\t}\n");
    print OUT ("\t\t\t\telsif (\$write_type_value == 1) {\n");
    print OUT ("\t\t\t\t\t\$write_str = \"stream\"\;\n");
    print OUT ("\t\t\t\t}\n");
    print OUT ("\t\t\t\tmy \$output_file = (\"./\" . \$platform . \"_\" . \$compiler . \"_specified_sse_\" . \$read_array_count_value . \"r_\" . \$write_array_count_value . \"w_\" . \$mem_footprint_in_GB . \"GB_\" . \$write_str . \"_\" . \$numThreads . \"t.txt\");\n");
    print OUT ("\t\t\t\tforeach \$threadPaddingLength (\@threadPaddingLength_values) {\n");
    print OUT ("\t\t\t\t\tforeach \$load_type_value (\@load_type_values) {\n");
    print OUT ("\t\t\t\t\t\tforeach \$loop_unroll_value (\@loop_unroll_values) {\n");
    print OUT ("\t\t\t\t\t\t\tforeach \$prefetch_distance (\@prefetch_distance_values) {\n");
    print OUT ("\t\t\t\t\t\t\t\tsystem (\"\$exec_file \$numThreads \$read_array_count_value \$write_array_count_value \$memory_footprint_in_B \$threadPaddingLength \$write_type_value \$load_type_value \$loop_unroll_value \$prefetch_distance >> \$output_file\")\;\n");
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
    print OUT ("\$compiler=\$ARGV[1]\;\n\n");
    print OUT ("my \$exec_file = \"./stream_pthreads_\${compiler}_c\"\;\n\n");
    print OUT ("\$mem_footprint_in_GB = 2.0\;\n");
    print OUT ("\@numThreads_values = (1,2,4,8)\;\n");
    print OUT ("\@read_array_count_values = (" . $read_array_counts[0] . ".." . $read_array_counts[@read_array_counts-1] . ")\;\n");
    print OUT ("\@write_array_count_values = (" . $write_array_counts[0] . ".." . $write_array_counts[@write_array_counts-1] . ")\;\n");
    print OUT ("\@threadPaddingLength_values = (0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30)\;\n");
    print OUT ("\@write_type_values = (0.." . (@write_types-1) . ")\;\n");
    print OUT ("\@load_type_values = (0.." . (@load_types-1) . ")\;\n");
    print OUT ("\@loop_unroll_values = (0.." . (@loop_unrolls-1) . ")\;\n");
    print OUT ("\@prefetch_distance_values = (0.." . (@prefetch_distances-1) . ")\;\n\n");
    print OUT ("sub find_best_load_type {\n");
    print OUT ("\tmy(\$my_file_name, \$my_best_timing_line_number) = \@_\;\n\n");
    print OUT ("\topen (TXT, \"\$my_file_name\")\;\n");
    print OUT ("\t\$load_type_line_number = \$my_best_timing_line_number - 16\;\n\n");
    print OUT ("\twhile (<TXT>) {\n");
    print OUT ("\t\tif (\$. == \$load_type_line_number) {\n");
    print OUT ("\t\t\t\@best_load_type = split(/,/, \$_)\;\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n\n");
    print OUT ("\t\$output_file_line_length = \$.\;\n");
    print OUT ("\tclose(TXT)\;\n");
    print OUT ("}\n\n");
    print OUT ("sub find_best_padding {\n");
    print OUT ("\tmy(\$my_file_name, \$my_best_timing_line_number) = \@_\;\n\n");
    print OUT ("\topen (TXT, \"\$my_file_name\")\;\n");
    print OUT ("\t\$padding_line_number = \$my_best_timing_line_number - 18\;\n\n");
    print OUT ("\twhile (<TXT>) {\n");
    print OUT ("\t\tif (\$. == \$padding_line_number) {\n");
    print OUT ("\t\t\t\@best_padding = split(/,/, \$_)\;\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n\n");
    print OUT ("\t\$output_file_line_length = \$.\;\n");
    print OUT ("\tclose(TXT)\;\n");
    print OUT ("}\n\n");
    print OUT ("sub find_best_loop_unroll {\n");
    print OUT ("\tmy(\$my_file_name, \$my_best_timing_line_number) = \@_;\n\n");
    print OUT ("\topen (TXT, \"\$my_file_name\");\n");
    print OUT ("\t\$loop_unroll_and_case_line_number = \$my_best_timing_line_number - 12;\n\n");
    print OUT ("\twhile (<TXT>) {\n");
    print OUT ("\t\tif (\$. == \$loop_unroll_and_case_line_number) {\n");
    print OUT ("\t\t\t\@best_loop_unroll_and_case = split(/,/, \$_);\n");
    print OUT ("\t\t\t\@best_loop_unroll = \$best_loop_unroll_and_case[0];\n");
    print OUT ("\t\t\t\@best_loop_unroll_case = \$best_loop_unroll_and_case[2];\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n");
    print OUT ("\t\$output_file_line_length = \$.;\n");
    print OUT ("\tclose(TXT);\n");
    print OUT ("}\n\n");
    print OUT ("sub find_best_prefetching {\n");
    print OUT ("\tmy(\$my_file_name, \$my_best_timing_line_number) = \@_;\n\n");
    print OUT ("\topen(TXT, \"\$my_file_name\");\n");
    print OUT ("\t\$prefetch_distance_and_case_line_number = \$my_best_timing_line_number - 10;\n");
    print OUT ("\twhile (<TXT>) {\n");
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
    print OUT ("\t\%median_bandwidths = ();\n");
    print OUT ("\twhile (<TXT>) {\n");
    print OUT ("\t\tif (\$. > \$my_opt_start_line_number) {\n");
    print OUT ("\t\t\tif (/Median Bandwidth: /) {\n");
    print OUT ("\t\t\t\t\@median_bandwidth = split(/Median Bandwidth: /, \$_);\n");
    print OUT ("\t\t\t\t\$median_bandwidths{\$.} = \$median_bandwidth[1];\n");
    print OUT ("\t\t\t}\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n\n");
    print OUT ("\tclose (TXT);\n\n");
    print OUT ("\t# reverse sort \%median_bandwidths by bandwidth, then find the line number of the best timing\n");
    print OUT ("\t\$my_best_timing_line_number = -1;\n\n");
    print OUT ("\t\$i = 0;\n");
    print OUT ("\tforeach \$timing_line_number (sort {\$median_bandwidths{\$b} <=> \$median_bandwidths{\$a}} keys \%median_bandwidths) {\n");
    print OUT ("\t\tif (\$i == 0) {\n");
    print OUT ("\t\t\t\$my_best_timing_line_number = \$timing_line_number;\n");
    print OUT ("\t\t\t\# print \"\$timing_line_number \$median_bandwidths{\$timing_line_number}\\n\";\n");
    print OUT ("\t\t}\n");
    print OUT ("\t\t\# print \"\$timing_line_number \$median_bandwidths{\$timing_line_number}\\n\";\n");
    print OUT ("\t\t\$i++;\n");
    print OUT ("\t}\n");
    print OUT ("\treturn \$my_best_timing_line_number;\n");
    print OUT ("}\n\n");
    print OUT ("\#\#\# BELOW IS THE PERL SCRIPT'S \"MAIN\" SUBROUTINE \#\#\#\n\n");
    print OUT ("\$memory_footprint_in_B = int(\$mem_footprint_in_GB * 2**30)\;\n");
    print OUT ("foreach \$numThreads (\@numThreads_values) {\n");
    print OUT ("\tforeach \$read_array_count_value (\@read_array_count_values) {\n");
    print OUT ("\t\tforeach \$write_array_count_value (\@write_array_count_values) {\n");
    print OUT ("\t\t\tforeach \$write_type_value (\@write_type_values) {\n");
    print OUT ("\t\t\t\tif (\$write_type_value == 0) {\n");
    print OUT ("\t\t\t\t\t\$write_str = \"store\"\;\n");
    print OUT ("\t\t\t\t}\n");
    print OUT ("\t\t\t\telsif (\$write_type_value == 1) {\n");
    print OUT ("\t\t\t\t\t\$write_str = \"stream\"\;\n");
    print OUT ("\t\t\t\t}\n");
    print OUT ("\t\t\t\tmy \$output_file = (\"./\" . \$platform . \"_\" . \$compiler . \"_greedy_sse_\" . \$read_array_count_value . \"r_\" . \$write_array_count_value . \"w_\" . \$write_str . \"_\" . \$mem_footprint_in_GB . \"GB_\" . \$numThreads . \"t.txt\");\n");
    print OUT ("\t\t\t\t\$output_file_line_length = 0;\n\n");
    print OUT ("\t\t\t\t\# initialize \"best\" arrays\n");    
    print OUT ("\t\t\t\t\@best_load_type = ();\n");
    print OUT ("\t\t\t\t\@best_padding = ();\n");
    print OUT ("\t\t\t\t\@best_loop_unroll = ();\n");
    print OUT ("\t\t\t\t\@best_prefetch_distance = ();\n\n");
    print OUT ("\t\t\t\t\# set initial values\n");
    print OUT ("\t\t\t\tmy \$init_threadPaddingLength = \$threadPaddingLength_values[0];\n");
    print OUT ("\t\t\t\tmy \$init_loop_unroll_value = \$loop_unroll_values[0];\n");
    print OUT ("\t\t\t\tmy \$init_prefetch_distance_value = \$prefetch_distance_values[0];\n\n");
    print OUT ("\t\t\t\t\# LOAD TYPE\n");
    print OUT ("\t\t\t\tforeach \$load_type_value (\@load_type_values) {\n");
    print OUT ("\t\t\t\t\tsystem (\"\$exec_file \$numThreads \$read_array_count_value \$write_array_count_value \$memory_footprint_in_B \$init_threadPaddingLength \$write_type_value \$load_type_value \$init_loop_unroll_value \$init_prefetch_distance_value >> \$output_file\")\;\n");
    print OUT ("\t\t\t\t}\n");    
    print OUT ("\t\t\t\t\$best_timing_line_number = find_best_time_for_opt(\$output_file, \$output_file_line_length);\n");
    print OUT ("\t\t\t\tfind_best_load_type(\$output_file, \$best_timing_line_number);\n");
    print OUT ("\t\t\t\tsystem (\"echo \\\"BEST LOAD TYPE:\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\tsystem (\"echo \\\"Load type (0 = implicit, 1 = explicit): \$best_load_type[0]\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\tsystem (\"echo \\\"Bandwidth: \$median_bandwidths{\$my_best_timing_line_number}\\\" >> \$output_file\");\n\n");
    print OUT ("\t\t\t\t\# PADDING\n");
    print OUT ("\t\t\t\tforeach \$threadPaddingLength (\@threadPaddingLength_values) {\n");
    print OUT ("\t\t\t\t\tsystem (\"\$exec_file \$numThreads \$read_array_count_value \$write_array_count_value \$memory_footprint_in_B \$threadPaddingLength \$write_type_value \$best_load_type[0] \$init_loop_unroll_value \$init_prefetch_distance_value >> \$output_file\")\;\n");
    print OUT ("\t\t\t\t}\n");
    print OUT ("\t\t\t\t\$best_timing_line_number = find_best_time_for_opt(\$output_file, \$output_file_line_length);\n");
    print OUT ("\t\t\t\tfind_best_padding(\$output_file, \$best_timing_line_number);\n");
    print OUT ("\t\t\t\tsystem (\"echo \\\"BEST PADDING:\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\tsystem (\"echo \\\"Padding: \$best_padding[0]\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\tsystem (\"echo \\\"Bandwidth: \$median_bandwidths{\$my_best_timing_line_number}\\\" >> \$output_file\");\n\n");
    print OUT ("\t\t\t\t\# LOOP UNROLLS\n");
    print OUT ("\t\t\t\tforeach \$loop_unroll_value (\@loop_unroll_values) {\n");
    print OUT ("\t\t\t\t\tsystem (\"\$exec_file \$numThreads \$read_array_count_value \$write_array_count_value \$memory_footprint_in_B \$best_padding[0] \$write_type_value \$best_load_type[0] \$loop_unroll_value \$init_prefetch_distance_value >> \$output_file\")\;\n");
    print OUT ("\t\t\t\t}\n");
    print OUT ("\t\t\t\t\$best_timing_line_number = find_best_time_for_opt(\$output_file, \$output_file_line_length);\n");
    print OUT ("\t\t\t\tfind_best_loop_unroll(\$output_file, \$best_timing_line_number);\n");
    print OUT ("\t\t\t\tsystem(\"echo \\\"BEST LOOP UNROLL:\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\tsystem(\"echo \\\"Loop unrolling: \$best_loop_unroll[0], case = \$best_loop_unroll_case[0]\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\tsystem(\"echo \\\"Bandwidth: \$median_bandwidths{\$my_best_timing_line_number}\\\" >> \$output_file\");\n\n");
    print OUT ("\t\t\t\t\# PREFETCHING DISTANCE\n");
    print OUT ("\t\t\t\tforeach \$prefetch_distance (\@prefetch_distance_values) {\n");
    print OUT ("\t\t\t\t\tsystem (\"\$exec_file \$numThreads \$read_array_count_value \$write_array_count_value \$memory_footprint_in_B \$best_padding[0] \$write_type_value \$best_load_type[0] \$best_loop_unroll_case[0] \$prefetch_distance >> \$output_file\")\;\n");
    print OUT ("\t\t\t\t}\n");
    print OUT ("\t\t\t\t\$best_timing_line_number = find_best_time_for_opt(\$output_file, \$output_file_line_length);\n");
    print OUT ("\t\t\t\tfind_best_prefetching(\$output_file, \$best_timing_line_number);\n");
    print OUT ("\t\t\t\tsystem(\"echo \\\"BEST PREFETCHING:\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\tsystem(\"echo \\\"Prefetch distance: \$best_prefetch_distance[0], case = \$best_prefetch_distance_case[0]\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t\tsystem(\"echo \\\"Bandwidth: \$median_bandwidths{\$my_best_timing_line_number}\\\" >> \$output_file\");\n");
    print OUT ("\t\t\t}\n");
    print OUT ("\t\t}\n");
    print OUT ("\t}\n");
    print OUT ("}\n");
}
