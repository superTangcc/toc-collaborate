#!/usr/bin/perl -w

$platform=$ARGV[0];
$compiler=$ARGV[1];

my $exec_file = "./helmholtz_pthreads_${compiler}_c";

@total_mem_footprints_in_GB = (0.5, 1, 2, 4);
@numIter_values = (1);
@log2_nreals_x_values = (8);
@log2_nreals_y_values = (8);
@log2_nreals_z_values = (8);
@log2_numThreads_values = (0..3);
@padding_values = (0..7);
@log2_numCoreBlockCells_x_values = (2..8);
@log2_numCoreBlockCells_y_values = (2..8);
@log2_numCoreBlockCells_z_values = (3..8);
@prefetch_index_type_values = (0..3);
@prefetch_distance_values = (0..5);
@rb_size_values = (0..8);

foreach $total_mem_footprint_in_GB (@total_mem_footprints_in_GB) {
	foreach $numIter (@numIter_values) {
		foreach $log2_nreals_x (@log2_nreals_x_values) {
			my $nreals_x = 2**($log2_nreals_x);
			foreach $log2_nreals_y (@log2_nreals_y_values) {
				my $nreals_y = 2**($log2_nreals_y);
				foreach $log2_nreals_z (@log2_nreals_z_values) {
					my $nreals_z = 2**($log2_nreals_z);
					my $numGrids = int(($total_mem_footprint_in_GB * 2**30) / (8 * ((($nreals_x + 2) * ($nreals_y + 2) * ($nreals_z + 2)) + (($nreals_x + 2) * $nreals_y * $nreals_z) + ($nreals_x * ($nreals_y + 2) * $nreals_z) + ($nreals_x * $nreals_y * ($nreals_z + 2)) + 3 * ($nreals_x * $nreals_y * $nreals_z))));
					foreach $log2_numThreads (@log2_numThreads_values) {
						my $numThreads = 2**($log2_numThreads); # 1 to 8 in powers of 2
						@log2_numThreadsPerGrid_values = (0..$log2_numThreads);
						foreach $log2_numThreadsPerGrid (@log2_numThreadsPerGrid_values) {
							my $numThreadsPerGrid = 2**($log2_numThreadsPerGrid);
							my $output_file = ("./" . $platform . "_" . $compiler . "_specified_3D_" . $nreals_x . "x" . $nreals_y . "x" . $nreals_z . "_" . $numIter . "i_" . $numThreads . "t_" . $numThreadsPerGrid . "tpg_" . $total_mem_footprint_in_GB . "GB.txt");
							foreach $padding (@padding_values) {
								foreach $log2_numCoreBlockCells_x (@log2_numCoreBlockCells_x_values) {
									my $numCoreBlockCells_x = 2**($log2_numCoreBlockCells_x); # 2 to $nreals_x in powers of 2
									foreach $log2_numCoreBlockCells_y (@log2_numCoreBlockCells_y_values) {
										my $numCoreBlockCells_y = 2**($log2_numCoreBlockCells_y); # 2 to $nreals_y in powers of 2
										foreach $log2_numCoreBlockCells_z (@log2_numCoreBlockCells_z_values) {
											my $numCoreBlockCells_z = 2**($log2_numCoreBlockCells_z); # 8 to $nreals_z in powers of 2
											if ($numThreadsPerGrid == 1) {
												@log2_numCoreBlocksPerChunk_values = (0);
											}
											else {
												@log2_numCoreBlocksPerChunk_values = (0..(($log2_nreals_x + $log2_nreals_y + $log2_nreals_z) - ($log2_numCoreBlockCells_x + $log2_numCoreBlockCells_y + $log2_numCoreBlockCells_z + $log2_numThreadsPerGrid)));
											}
											foreach $log2_numCoreBlocksPerChunk (@log2_numCoreBlocksPerChunk_values) {
												my $numCoreBlocksPerChunk = 2**($log2_numCoreBlocksPerChunk);
												foreach $prefetch_index_type (@prefetch_index_type_values) {
													foreach $prefetch_distance (@prefetch_distance_values) {
														foreach $rb_size (@rb_size_values) {
															system ("$exec_file $numGrids $numIter $nreals_x $nreals_y $nreals_z $numThreads $numThreadsPerGrid $padding $numCoreBlockCells_x $numCoreBlockCells_y $numCoreBlockCells_z $numCoreBlocksPerChunk $prefetch_index_type $prefetch_distance $rb_size >> $output_file");
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
