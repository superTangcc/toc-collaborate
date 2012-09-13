#!/usr/bin/perl -w

$platform=$ARGV[0];
$compiler=$ARGV[1];
$opt_sweep_number=$ARGV[2]; # if greater than 1

my $exec_file = "./stencil_pthreads_${compiler}_c";
@numIter_values = (1);
@log2_nreals_x_values = (8);
@log2_nreals_y_values = (8);
@log2_nreals_z_values = (8);
@log2_numThreads_values = (2);
@log2_numCoreBlockCells_x_values = (6);
@log2_numCoreBlockCells_y_values = (8);
@log2_numCoreBlockCells_z_values = (8);
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
					my $numThreads = 2**($log2_numThreads);
					my $output_file = ("./" . $platform . "_" . $compiler . "_specified${opt_sweep_number}_3D_bgp_" . $nreals_x . "_" . $nreals_y . "_" . $nreals_z . "_" . $numIter . "i_" . $numThreads . "t.txt");
						foreach $log2_numCoreBlockCells_x (@log2_numCoreBlockCells_x_values) {
							my $numCoreBlockCells_x = 2**($log2_numCoreBlockCells_x); # 2 to $nreals_x in powers of 2
							foreach $log2_numCoreBlockCells_y (@log2_numCoreBlockCells_y_values) {
								my $numCoreBlockCells_y = 2**($log2_numCoreBlockCells_y); # 2 to $nreals_y in powers of 2
								foreach $log2_numCoreBlockCells_z (@log2_numCoreBlockCells_z_values) {
									my $numCoreBlockCells_z = 2**($log2_numCoreBlockCells_z); # 8 to $nreals_z in powers of 2
									@log2_numCoreBlocksPerChunk_values = (0);
									foreach $log2_numCoreBlocksPerChunk (@log2_numCoreBlocksPerChunk_values) {
										my $numCoreBlocksPerChunk = 2**($log2_numCoreBlocksPerChunk);
										foreach $prefetch_index_type (@prefetch_index_type_values) {
											foreach $prefetch_distance (@prefetch_distance_values) {
												foreach $rb_size (@rb_size_values) {
#												system ("echo \"Start Time:\" >> $output_file");
#												system ("date >> $output_file");
												system ("qsub -n 64 -t 19 -q prod-devel $exec_file $numIter $nreals_x $nreals_y $nreals_z $numThreads 0 $numCoreBlockCells_x $numCoreBlockCells_y $numCoreBlockCells_z $numCoreBlocksPerChunk $prefetch_index_type $prefetch_distance $rb_size >> $output_file");
#												system ("echo \"End Time:\" >> $output_file");
#												system ("date >> $output_file");
#												system ("echo \"***************************************\" >> $output_file");
#												system ("echo >> $output_file");
#												system ("echo >> $output_file");
#												system ("sleep 5");
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
