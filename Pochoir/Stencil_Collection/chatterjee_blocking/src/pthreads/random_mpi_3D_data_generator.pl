#!/usr/bin/perl -w

$platform=$ARGV[0];
$compiler=$ARGV[1];

my $exec_file = "./stencil_pthreads_${compiler}_c";
my $num_data_points = 1000;
my @config_list = ();
$numIter = 1;

$log2_nreals_x = 8;
$nreals_x = 2**($log2_nreals_x);

$log2_nreals_y = 8;
$nreals_y = 2**($log2_nreals_y);

$log2_nreals_z = 8;
$nreals_z = 2**($log2_nreals_z);

my $output_file = ("./" . $platform . "_" . $compiler . "_random_mpi_3D_" . $nreals_x . "_" . $nreals_y . "_" . $nreals_z . "_" . $numIter . "i.txt");
for (my $i=0; $i < $num_data_points; $i++) {
  my $config_pt_in_config_list = 1;
  while ($config_pt_in_config_list == 1) {
    $log2_numThreads = int(rand(4));
    $numThreads = 2**($log2_numThreads); # 1 to 8 in powers of 2

    $padding = int(rand(32));

    $log2_numCoreBlockCells_x = int(rand($log2_nreals_x))+1;
    $numCoreBlockCells_x = 2**($log2_numCoreBlockCells_x); # 2 to $nreals_x in powers of 2

    $log2_numCoreBlockCells_y = int(rand($log2_nreals_y))+1;
    $numCoreBlockCells_y = 2**($log2_numCoreBlockCells_y); # 2 to $nreals_y in powers of 2

    $log2_numCoreBlockCells_z = int(rand($log2_nreals_z-2))+3;
    $numCoreBlockCells_z = 2**($log2_numCoreBlockCells_z); # 8 to $nreals_z in powers of 2

    $log2_maxCoreBlocksPerChunk = ($log2_nreals_x + $log2_nreals_y + $log2_nreals_z) - ($log2_numCoreBlockCells_x + $log2_numCoreBlockCells_y + $log2_numCoreBlockCells_z + $log2_numThreads);
    if ($log2_maxCoreBlocksPerChunk <= 0) {
      $numCoreBlocksPerChunk = 1;
    }
    else {
      $numCoreBlocksPerChunk = 2**(int(rand($log2_maxCoreBlocksPerChunk)));
    }

    $statement_type = int(rand(2));
    $read_from_type = int(rand(2));
    $pointer_type = int(rand(2));
    $neighbor_index_type = int(rand(3));
    $fma_ins_type = int(rand(2));
    $prefetch_index_type = int(rand(2));
    $prefetch_distance = int(rand(2));
    $rb_size = int(rand(2));

    @config_pt = ($numThreads, $padding, $numCoreBlockCells_x, $numCoreBlockCells_y, $numCoreBlockCells_z, $numCoreBlocksPerChunk, $statement_type, $read_from_type, $pointer_type, $neighbor_index_type, $fma_ins_type, $prefetch_index_type, $prefetch_distance, $rb_size);
    $config_pt_in_config_list = 0;
    for (my $j=0; $j < @config_list; $j++) {
      if (compare_points([@{$config_list[$j]}], [ @config_pt ]) == 0) {
        $config_pt_in_config_list = 1;
      }
    }
  }
  @config_list = (@config_list, [ @config_pt ]);
#  system ("echo \"Start Time:\" >> $output_file");
#  system ("date >> $output_file");
  system ("$exec_file $numIter $nreals_x $nreals_y $nreals_z $numThreads $padding $numCoreBlockCells_x $numCoreBlockCells_y $numCoreBlockCells_z $numCoreBlocksPerChunk 0 0 $statement_type $read_from_type $pointer_type $neighbor_index_type $fma_ins_type $prefetch_index_type $prefetch_distance $rb_size >> $output_file");
#  system ("echo \"End Time:\" >> $output_file");
#  system ("date >> $output_file");
#  system ("echo \"***************************************\" >> $output_file");
#  system ("echo >> $output_file");
#  system ("echo >> $output_file");
#  system ("sleep 5");
}

# compares two points based on x, then y, then z
# returns -1 if the first point is greater, 0 if they're the same, and 1 if the second point is greater
sub compare_points {
  my(@my_two_points) = @_;

  my @pt0 = @{$my_two_points[0]};
  my @pt1 = @{$my_two_points[1]};

  my $return_value = 0;
  for (my $dim=0; $dim < 14; $dim++) {
    if ($return_value == 0) {
      if ($pt0[$dim] > $pt1[$dim]) {
        $return_value = -1;
      }
      elsif ($pt0[$dim] < $pt1[$dim]) {
        $return_value = 1;
      }
    }
  }
  return $return_value;
}
