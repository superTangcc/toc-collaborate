#!/usr/bin/perl -w

$platform=$ARGV[0];
$compiler=$ARGV[1];
$opt_sweep_number=$ARGV[2]; # if greater than 1

my $exec_file = "./stencil_pthreads_${compiler}_c";
@numIter_values = (1);
@log2_nreals_x_values = (8);
@log2_nreals_y_values = (8);
@log2_nreals_z_values = (8);
@log2_numThreads_values = (0..3);
$numOffAlignment_z = 0;
@write_type_values = (0..0);
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
					if ($log2_numThreads == 0) {
						$log2_numCoreBlockCells_x = 8;
						$log2_numCoreBlockCells_y = 8;
						$log2_numCoreBlockCells_z = 8;
						$log2_numCoreBlocksPerChunk = 0;
					}
					if ($log2_numThreads == 1) {
						$log2_numCoreBlockCells_x = 8;
						$log2_numCoreBlockCells_y = 8;
						$log2_numCoreBlockCells_z = 8;
						$log2_numCoreBlocksPerChunk = 0;
					}
					if ($log2_numThreads == 2) {
						$log2_numCoreBlockCells_x = 8;
						$log2_numCoreBlockCells_y = 8;
						$log2_numCoreBlockCells_z = 8;
						$log2_numCoreBlocksPerChunk = 0;
					}
					if ($log2_numThreads == 3) {
						$log2_numCoreBlockCells_x = 8;
						$log2_numCoreBlockCells_y = 8;
						$log2_numCoreBlockCells_z = 8;
						$log2_numCoreBlocksPerChunk = 0;
					}
					my $numCoreBlockCells_x = 2**($log2_numCoreBlockCells_x);
					my $numCoreBlockCells_y = 2**($log2_numCoreBlockCells_y);
					my $numCoreBlockCells_z = 2**($log2_numCoreBlockCells_z);
					my $numCoreBlocksPerChunk = 2**($log2_numCoreBlocksPerChunk);
					foreach $write_type (@write_type_values) {
						if ($write_type == 0) {
							$write_str = "store";
						}
						elsif ($write_type == 1) {
							$write_str = "stream";
						}
						my $output_file = ("./" . $platform . "_" . $compiler . "_specified${opt_sweep_number}_3D_sse_" . $write_str . "_" . $nreals_x . "_" . $nreals_y . "_" . $nreals_z . "_" . $numIter . "i_" . $numThreads . "t.txt");
						foreach $prefetch_index_type (@prefetch_index_type_values) {
							foreach $prefetch_distance (@prefetch_distance_values) {
								foreach $rb_size (@rb_size_values) {
#									system ("echo \"Start Time:\" >> $output_file");
#									system ("date >> $output_file");
									system ("$exec_file $numIter $nreals_x $nreals_y $nreals_z $numThreads $numOffAlignment_z $numCoreBlockCells_x $numCoreBlockCells_y $numCoreBlockCells_z $numCoreBlocksPerChunk $write_type $prefetch_index_type $prefetch_distance $rb_size >> $output_file");
#									system ("echo \"End Time:\" >> $output_file");
#									system ("date >> $output_file");
#									system ("echo \"***************************************\" >> $output_file");
#									system ("echo >> $output_file");
#									system ("echo >> $output_file");
#									system ("sleep 5");
								}
							}
						}
					}
				}
			}
		}
	}
}
