#!/usr/bin/perl -w

$platform=$ARGV[0];
$compiler=$ARGV[1];

my $exec_file = "./stream_pthreads_${compiler}_c";

$mem_footprint_in_GB = 2.0;
@numThreads_values = (1,2,4,8);
@read_array_count_values = (0..6);
@write_array_count_values = (0..6);
@threadPaddingLength_values = (0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
@write_type_values = (0..1);
@load_type_values = (0..1);
@loop_unroll_values = (0..9);
@prefetch_distance_values = (0..6);

sub find_best_load_type {
	my($my_file_name, $my_best_timing_line_number) = @_;

	open (TXT, "$my_file_name");
	$load_type_line_number = $my_best_timing_line_number - 16;

	while (<TXT>) {
		if ($. == $load_type_line_number) {
			@best_load_type = split(/,/, $_);
		}
	}

	$output_file_line_length = $.;
	close(TXT);
}

sub find_best_padding {
	my($my_file_name, $my_best_timing_line_number) = @_;

	open (TXT, "$my_file_name");
	$padding_line_number = $my_best_timing_line_number - 18;

	while (<TXT>) {
		if ($. == $padding_line_number) {
			@best_padding = split(/,/, $_);
		}
	}

	$output_file_line_length = $.;
	close(TXT);
}

sub find_best_loop_unroll {
	my($my_file_name, $my_best_timing_line_number) = @_;

	open (TXT, "$my_file_name");
	$loop_unroll_and_case_line_number = $my_best_timing_line_number - 12;

	while (<TXT>) {
		if ($. == $loop_unroll_and_case_line_number) {
			@best_loop_unroll_and_case = split(/,/, $_);
			@best_loop_unroll = $best_loop_unroll_and_case[0];
			@best_loop_unroll_case = $best_loop_unroll_and_case[2];
		}
	}
	$output_file_line_length = $.;
	close(TXT);
}

sub find_best_prefetching {
	my($my_file_name, $my_best_timing_line_number) = @_;

	open(TXT, "$my_file_name");
	$prefetch_distance_and_case_line_number = $my_best_timing_line_number - 10;
	while (<TXT>) {
		if ($. == $prefetch_distance_and_case_line_number) {
			@best_prefetch_distance_and_case = split(/,/, $_);
			@best_prefetch_distance = $best_prefetch_distance_and_case[0];
			@best_prefetch_distance_case = $best_prefetch_distance_and_case[2];
		}
	}

	$output_file_line_length = $.;
	close(TXT);
}

sub find_best_time_for_opt {
	my($my_file_name, $my_opt_start_line_number) = @_;

	open (TXT, "$my_file_name");

	%median_bandwidths = ();
	while (<TXT>) {
		if ($. > $my_opt_start_line_number) {
			if (/Median Bandwidth: /) {
				@median_bandwidth = split(/Median Bandwidth: /, $_);
				$median_bandwidths{$.} = $median_bandwidth[1];
			}
		}
	}

	close (TXT);

	# reverse sort %median_bandwidths by bandwidth, then find the line number of the best timing
	$my_best_timing_line_number = -1;

	$i = 0;
	foreach $timing_line_number (sort {$median_bandwidths{$b} <=> $median_bandwidths{$a}} keys %median_bandwidths) {
		if ($i == 0) {
			$my_best_timing_line_number = $timing_line_number;
			# print "$timing_line_number $median_bandwidths{$timing_line_number}\n";
		}
		# print "$timing_line_number $median_bandwidths{$timing_line_number}\n";
		$i++;
	}
	return $my_best_timing_line_number;
}

### BELOW IS THE PERL SCRIPT'S "MAIN" SUBROUTINE ###

$memory_footprint_in_B = int($mem_footprint_in_GB * 2**30);
foreach $numThreads (@numThreads_values) {
	foreach $read_array_count_value (@read_array_count_values) {
		foreach $write_array_count_value (@write_array_count_values) {
			foreach $write_type_value (@write_type_values) {
				if ($write_type_value == 0) {
					$write_str = "store";
				}
				elsif ($write_type_value == 1) {
					$write_str = "stream";
				}
				my $output_file = ("./" . $platform . "_" . $compiler . "_greedy_sse_" . $read_array_count_value . "r_" . $write_array_count_value . "w_" . $write_str . "_" . $mem_footprint_in_GB . "GB_" . $numThreads . "t.txt");
				$output_file_line_length = 0;

				# initialize "best" arrays
				@best_load_type = ();
				@best_padding = ();
				@best_loop_unroll = ();
				@best_prefetch_distance = ();

				# set initial values
				my $init_threadPaddingLength = $threadPaddingLength_values[0];
				my $init_loop_unroll_value = $loop_unroll_values[0];
				my $init_prefetch_distance_value = $prefetch_distance_values[0];

				# LOAD TYPE
				foreach $load_type_value (@load_type_values) {
					system ("$exec_file $numThreads $read_array_count_value $write_array_count_value $memory_footprint_in_B $init_threadPaddingLength $write_type_value $load_type_value $init_loop_unroll_value $init_prefetch_distance_value >> $output_file");
				}
				$best_timing_line_number = find_best_time_for_opt($output_file, $output_file_line_length);
				find_best_load_type($output_file, $best_timing_line_number);
				system ("echo \"BEST LOAD TYPE:\" >> $output_file");
				system ("echo \"Load type (0 = implicit, 1 = explicit): $best_load_type[0]\" >> $output_file");
				system ("echo \"Bandwidth: $median_bandwidths{$my_best_timing_line_number}\" >> $output_file");

				# PADDING
				foreach $threadPaddingLength (@threadPaddingLength_values) {
					system ("$exec_file $numThreads $read_array_count_value $write_array_count_value $memory_footprint_in_B $threadPaddingLength $write_type_value $best_load_type[0] $init_loop_unroll_value $init_prefetch_distance_value >> $output_file");
				}
				$best_timing_line_number = find_best_time_for_opt($output_file, $output_file_line_length);
				find_best_padding($output_file, $best_timing_line_number);
				system ("echo \"BEST PADDING:\" >> $output_file");
				system ("echo \"Padding: $best_padding[0]\" >> $output_file");
				system ("echo \"Bandwidth: $median_bandwidths{$my_best_timing_line_number}\" >> $output_file");

				# LOOP UNROLLS
				foreach $loop_unroll_value (@loop_unroll_values) {
					system ("$exec_file $numThreads $read_array_count_value $write_array_count_value $memory_footprint_in_B $best_padding[0] $write_type_value $best_load_type[0] $loop_unroll_value $init_prefetch_distance_value >> $output_file");
				}
				$best_timing_line_number = find_best_time_for_opt($output_file, $output_file_line_length);
				find_best_loop_unroll($output_file, $best_timing_line_number);
				system("echo \"BEST LOOP UNROLL:\" >> $output_file");
				system("echo \"Loop unrolling: $best_loop_unroll[0], case = $best_loop_unroll_case[0]\" >> $output_file");
				system("echo \"Bandwidth: $median_bandwidths{$my_best_timing_line_number}\" >> $output_file");

				# PREFETCHING DISTANCE
				foreach $prefetch_distance (@prefetch_distance_values) {
					system ("$exec_file $numThreads $read_array_count_value $write_array_count_value $memory_footprint_in_B $best_padding[0] $write_type_value $best_load_type[0] $best_loop_unroll_case[0] $prefetch_distance >> $output_file");
				}
				$best_timing_line_number = find_best_time_for_opt($output_file, $output_file_line_length);
				find_best_prefetching($output_file, $best_timing_line_number);
				system("echo \"BEST PREFETCHING:\" >> $output_file");
				system("echo \"Prefetch distance: $best_prefetch_distance[0], case = $best_prefetch_distance_case[0]\" >> $output_file");
				system("echo \"Bandwidth: $median_bandwidths{$my_best_timing_line_number}\" >> $output_file");
			}
		}
	}
}
