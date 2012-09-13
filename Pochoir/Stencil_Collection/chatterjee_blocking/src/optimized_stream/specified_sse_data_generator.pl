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
				my $output_file = ("./" . $platform . "_" . $compiler . "_specified_sse_" . $read_array_count_value . "r_" . $write_array_count_value . "w_" . $mem_footprint_in_GB . "GB_" . $write_str . "_" . $numThreads . "t.txt");
				foreach $threadPaddingLength (@threadPaddingLength_values) {
					foreach $load_type_value (@load_type_values) {
						foreach $loop_unroll_value (@loop_unroll_values) {
							foreach $prefetch_distance (@prefetch_distance_values) {
								system ("$exec_file $numThreads $read_array_count_value $write_array_count_value $memory_footprint_in_B $threadPaddingLength $write_type_value $load_type_value $loop_unroll_value $prefetch_distance >> $output_file");
							}
						}
					}
				}
			}
		}
	}
}
