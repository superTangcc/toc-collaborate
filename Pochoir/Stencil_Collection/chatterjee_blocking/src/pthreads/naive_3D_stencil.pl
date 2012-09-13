#!/usr/bin/perl -w

$platform=$ARGV[0];
$compiler=$ARGV[1];
$code_type=$ARGV[2];  # either "3D" or "27pt_cse"

my $exec_file = "./stencil_pthreads_${compiler}_c";
@numIter_values = (1);
@log2_nreals_x_values = (8);
@log2_nreals_y_values = (8);
@log2_nreals_z_values = (8);
@log2_numThreads_values = (0..3);

foreach $numIter (@numIter_values) {
    foreach $log2_nreals_x (@log2_nreals_x_values) {
	my $nreals_x = 2**($log2_nreals_x);
	foreach $log2_nreals_y (@log2_nreals_y_values) {
	    my $nreals_y = 2**($log2_nreals_y);
	    foreach $log2_nreals_z (@log2_nreals_z_values) {
		my $nreals_z = 2**($log2_nreals_z);
		foreach $log2_numThreads (@log2_numThreads_values) {
		    my $numThreads = 2**($log2_numThreads);
		    
		    my $output_file = ("./" . $platform . "_" . $compiler . "_naive_" . $code_type . "_" . $nreals_x . "_" . $nreals_y . "_" . $nreals_z . "_" . $numIter . "i_" . $numThreads . "t.txt");
		    
		    my $numCoreBlockCells_x = ($nreals_x/$numThreads);
#		    system ("echo \"Start Time:\" >> $output_file");
#		    system ("date >> $output_file");
		    system ("$exec_file $numIter $nreals_x $nreals_y $nreals_z $numThreads 0 $numCoreBlockCells_x $nreals_y $nreals_z 1 0 0 0 0 0 0 0 0 0 0 >> $output_file");
#		    system ("echo \"End Time:\" >> $output_file");
#		    system ("date >> $output_file");
#		    system ("echo \"***************************************\" >> $output_file");
#		    system ("echo >> $output_file");
#		    system ("echo >> $output_file");
#		    system ("sleep 5");
		}
	    }
	}
    }
}
