#!/usr/bin/perl -w

$platform=$ARGV[0];
$compiler=$ARGV[1];

my $exec_file = "./stream_pthreads_${compiler}_c";

$mem_footprint_in_GB = 2.0;
@numThreads_values = (1,2,4,8);
@read_array_count_values = (0..6);
@write_array_count_values = (0..6);
@threadPaddingLength_values = (0..31);
@loop_unroll_values = (0..9);
@prefetch_distance_values = (0..6);

$memory_footprint_in_B = int($mem_footprint_in_GB * 2**30);
foreach $numThreads (@numThreads_values) {
	foreach $read_array_count_value (@read_array_count_values) {
		foreach $write_array_count_value (@write_array_count_values) {
			my $output_file = ("./" . $platform . "_" . $compiler . "_specified_" . $read_array_count_value . "r_" . $write_array_count_value . "w_" . $mem_footprint_in_GB . "GB_" . $numThreads . "t.txt");
			foreach $threadPaddingLength (@threadPaddingLength_values) {
				foreach $loop_unroll_value (@loop_unroll_values) {
					foreach $prefetch_distance (@prefetch_distance_values) {
						system ("$exec_file $numThreads $read_array_count_value $write_array_count_value $memory_footprint_in_B $threadPaddingLength $loop_unroll_value $prefetch_distance >> $output_file");
					}
				}
			}
		}
	}
}
