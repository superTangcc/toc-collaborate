#!/usr/bin/perl -w

$platform=$ARGV[0];
$compiler=$ARGV[1];

my $exec_file = "./stencil_pthreads_${compiler}_c";
@numIter_values = (1);
@log2_nreals_x_values = (8);
@log2_nreals_y_values = (8);
@log2_nreals_z_values = (8);
@log2_numThreads_values = (0..3);
@padding_values = (0..31);
@log2_numCoreBlockCells_x_values = (2..8);
@log2_numCoreBlockCells_y_values = (2..8);
@log2_numCoreBlockCells_z_values = (3..8);
@statement_type_values = (0..0);
@read_from_type_values = (0..0);
@pointer_type_values = (0..0);
@neighbor_index_type_values = (0..0);
@fma_ins_type_values = (0..0);
@prefetch_index_type_values = (0..0);
@prefetch_distance_values = (0..0);
@rb_size_values = (0..1);

foreach $numIter (@numIter_values) {
	foreach $log2_nreals_x (@log2_nreals_x_values) {
		my $nreals_x = 2**($log2_nreals_x);
		foreach $log2_nreals_y (@log2_nreals_y_values) {
			my $nreals_y = 2**($log2_nreals_y);
			foreach $log2_nreals_z (@log2_nreals_z_values) {
				my $nreals_z = 2**($log2_nreals_z);
				foreach $log2_numThreads (@log2_numThreads_values) {
					my $numThreads = 2**($log2_numThreads); # 1 to 8 in powers of 2
					my $output_file = ("./" . $platform . "_" . $compiler . "_specified_3D_" . $nreals_x . "_" . $nreals_y . "_" . $nreals_z . "_" . $numIter . "i_" . $numThreads . "t.txt");
					foreach $padding (@padding_values) {
						foreach $log2_numCoreBlockCells_x (@log2_numCoreBlockCells_x_values) {
							my $numCoreBlockCells_x = 2**($log2_numCoreBlockCells_x); # 2 to $nreals_x in powers of 2
							foreach $log2_numCoreBlockCells_y (@log2_numCoreBlockCells_y_values) {
								my $numCoreBlockCells_y = 2**($log2_numCoreBlockCells_y); # 2 to $nreals_y in powers of 2
								foreach $log2_numCoreBlockCells_z (@log2_numCoreBlockCells_z_values) {
									my $numCoreBlockCells_z = 2**($log2_numCoreBlockCells_z); # 8 to $nreals_z in powers of 2
									@log2_numCoreBlocksPerChunk_values = (0..(($log2_nreals_x + $log2_nreals_y + $log2_nreals_z) - ($log2_numCoreBlockCells_x + $log2_numCoreBlockCells_y + $log2_numCoreBlockCells_z + $log2_numThreads)));
									foreach $log2_numCoreBlocksPerChunk (@log2_numCoreBlocksPerChunk_values) {
										my $numCoreBlocksPerChunk = 2**($log2_numCoreBlocksPerChunk);
										foreach $statement_type (@statement_type_values) {
											foreach $read_from_type (@read_from_type_values) {
												foreach $pointer_type (@pointer_type_values) {
													foreach $neighbor_index_type (@neighbor_index_type_values) {
														foreach $fma_ins_type (@fma_ins_type_values) {
															foreach $prefetch_index_type (@prefetch_index_type_values) {
																foreach $prefetch_distance (@prefetch_distance_values) {
																	foreach $rb_size (@rb_size_values) {
#																		system ("echo \"Start Time:\" >> $output_file");
#																		system ("date >> $output_file");
																		system ("$exec_file $numIter $nreals_x $nreals_y $nreals_z $numThreads $padding $numCoreBlockCells_x $numCoreBlockCells_y $numCoreBlockCells_z $numCoreBlocksPerChunk 0 0 $statement_type $read_from_type $pointer_type $neighbor_index_type $fma_ins_type $prefetch_index_type $prefetch_distance $rb_size >> $output_file");
#																		system ("echo \"End Time:\" >> $output_file");
#																		system ("date >> $output_file");
#																		system ("echo \"***************************************\" >> $output_file");
#																		system ("echo >> $output_file");
#																		system ("echo >> $output_file");
#																		system ("sleep 5");
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
		}
	}
}
