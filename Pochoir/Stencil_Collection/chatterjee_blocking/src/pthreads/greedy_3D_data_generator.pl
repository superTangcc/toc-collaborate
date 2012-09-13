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

sub find_best_padding {
	my($my_file_name, $my_best_timing_line_number) = @_;

	open (TXT, "$my_file_name");
	$padding_line_number = $my_best_timing_line_number - 25;

	while (<TXT>) {
		if ($. == $padding_line_number) {
			@best_padding_dims = split(/,/, $_);
		}
	}

	$output_file_line_length = $.;
	close(TXT);
}

sub find_best_core_block_and_chunk_size {
	my($my_file_name, $my_best_timing_line_number) = @_;

	open (TXT, "$my_file_name");
	$core_block_line_number = $my_best_timing_line_number - 23;
	$chunk_size_line_number = $core_block_line_number + 2;

	while (<TXT>) {
		if ($. == $core_block_line_number) {
			@best_core_block_dims = split(/,/, $_)
		}

		if ($. == $chunk_size_line_number) {
			@best_chunk_size = split(/,/, $_);
		}
	}

	$output_file_line_length = $.;
	close(TXT);
}

sub find_best_inner_loop {
	my($my_file_name, $my_best_timing_line_number) = @_;

	open (TXT, "$my_file_name");
	$statement_type_line_number = $my_best_timing_line_number - 19;
	$read_from_type_line_number = $statement_type_line_number + 2;
	$pointer_type_line_number = $read_from_type_line_number + 2;
	$neighbor_index_type_line_number = $pointer_type_line_number + 2;
	$fma_ins_type_line_number = $neighbor_index_type_line_number + 2;
	$rb_size_and_case_line_number = $fma_ins_type_line_number + 6;

	while (<TXT>) {
		if ($. == $statement_type_line_number) {
			@best_statement_type = split(/,/, $_);		}

		if ($. == $read_from_type_line_number) {
			@best_read_from_type = split(/,/, $_);
		}

		if ($. == $pointer_type_line_number) {
			@best_pointer_type = split(/,/, $_);
		}

		if ($. == $neighbor_index_type_line_number) {
			@best_neighbor_index_type = split(/,/, $_);
		}

		if ($. == $fma_ins_type_line_number) {
			@best_fma_ins_type = split(/,/, $_);
		}

		if ($. == $rb_size_and_case_line_number) {
			@best_rb_size_and_case = split(/,/, $_);
			@best_register_block_dims = @best_rb_size_and_case[0,1,2];
			@best_rb_case = $best_rb_size_and_case[4];
		}
	}
	$output_file_line_length = $.;
	close(TXT);
}

sub find_best_prefetching {
	my($my_file_name, $my_best_timing_line_number) = @_;

	open(TXT, "$my_file_name");
	$prefetch_index_type_line_number = $my_best_timing_line_number - 9;
	$prefetch_distance_and_case_line_number = $prefetch_index_type_line_number + 2;

	while (<TXT>) {
		if ($. == $prefetch_index_type_line_number) {
			@best_prefetch_index_type = split(/,/, $_);
		}

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

	%median_times = ();
	while (<TXT>) {
		if ($. > $my_opt_start_line_number) {
			if (/Median Time: /) {
				@median_time = split(/Median Time: /, $_);
				$median_times{$.} = $median_time[1];
			}
		}
	}

	close (TXT);

	# sort %median_times by time, then find the line number of the best timing
	$my_best_timing_line_number = -1;

	$i = 0;
	foreach $timing_line_number (sort {$median_times{$a} <=> $median_times{$b}} keys %median_times) {
		if ($i == 0) {
			$my_best_timing_line_number = $timing_line_number;
			# print "$timing_line_number $median_times{$timing_line_number}\n";
		}
		# print "$timing_line_number $median_times{$timing_line_number}\n";
		$i++;
	}
	return $my_best_timing_line_number;
}

### BELOW IS THE PERL SCRIPT'S "MAIN" SUBROUTINE ###

foreach $numIter (@numIter_values) {
	foreach $log2_nreals_x (@log2_nreals_x_values) {
		my $nreals_x = 2**($log2_nreals_x);
		foreach $log2_nreals_y (@log2_nreals_y_values) {
			my $nreals_y = 2**($log2_nreals_y);
			foreach $log2_nreals_z (@log2_nreals_z_values) {
				my $nreals_z = 2**($log2_nreals_z);
				foreach $log2_numThreads (@log2_numThreads_values) {
					my $numThreads = 2**($log2_numThreads);

					my $output_file = ("./" . $platform . "_" . $compiler . "_greedy${opt_sweep_number}_3D_" . $nreals_x . "_" . $nreals_y . "_" . $nreals_z . "_" . $numIter . "i_" . $numThreads . "t.txt");
					$output_file_line_length = 0;

					# initialize "best" arrays
					@best_padding_dims = ();
					@best_core_block_dims = ();
					@best_chunk_size = ();
					@best_statement_type = ();
					@best_read_from_type = ();
					@best_pointer_type = ();
					@best_neighbor_index_type = ();
					@best_fma_ins_type = ();
					@best_register_block_dims = ();
					@best_prefetch_index_type = ();
					@best_prefetch_distance = ();

					# set initial values
					my $init_numCoreBlockCells_x = ($nreals_x/$numThreads);
					my $init_numCoreBlockCells_y = $nreals_y;
					my $init_numCoreBlockCells_z = $nreals_z;
					my $init_numCoreBlocksPerChunk = 1;
					my $init_statement_type_value = $statement_type_values[0];
					my $init_read_from_type_value = $read_from_type_values[0];
					my $init_pointer_type_value = $pointer_type_values[0];
					my $init_neighbor_index_type_value = $neighbor_index_type_values[0];
					my $init_fma_ins_type_value = $fma_ins_type_values[0];
					my $init_prefetch_index_type_value = $prefetch_index_type_values[0];
					my $init_prefetch_distance_value = $prefetch_distance_values[0];
					my $init_rb_size_value = $rb_size_values[0];

					if ($log2_numThreads == 0) {
						$init_numCoreBlockCells_x = ($nreals_x/$numThreads);
						$init_numCoreBlockCells_y = $nreals_y;
						$init_numCoreBlockCells_z = $nreals_z;
						$init_numCoreBlocksPerChunk = 1;
						$init_statement_type_value = $statement_type_values[0];
						$init_read_from_type_value = $read_from_type_values[0];
						$init_pointer_type_value = $pointer_type_values[0];
						$init_neighbor_index_type_value = $neighbor_index_type_values[0];
						$init_fma_ins_type_value = $fma_ins_type_values[0];
						$init_prefetch_index_type_value = $prefetch_index_type_values[0];
						$init_prefetch_distance_value = $prefetch_distance_values[0];
						$init_rb_size_value = $rb_size_values[0];
					}

					if ($log2_numThreads == 1) {
						$init_numCoreBlockCells_x = ($nreals_x/$numThreads);
						$init_numCoreBlockCells_y = $nreals_y;
						$init_numCoreBlockCells_z = $nreals_z;
						$init_numCoreBlocksPerChunk = 1;
						$init_statement_type_value = $statement_type_values[0];
						$init_read_from_type_value = $read_from_type_values[0];
						$init_pointer_type_value = $pointer_type_values[0];
						$init_neighbor_index_type_value = $neighbor_index_type_values[0];
						$init_fma_ins_type_value = $fma_ins_type_values[0];
						$init_prefetch_index_type_value = $prefetch_index_type_values[0];
						$init_prefetch_distance_value = $prefetch_distance_values[0];
						$init_rb_size_value = $rb_size_values[0];
					}

					if ($log2_numThreads == 2) {
						$init_numCoreBlockCells_x = ($nreals_x/$numThreads);
						$init_numCoreBlockCells_y = $nreals_y;
						$init_numCoreBlockCells_z = $nreals_z;
						$init_numCoreBlocksPerChunk = 1;
						$init_statement_type_value = $statement_type_values[0];
						$init_read_from_type_value = $read_from_type_values[0];
						$init_pointer_type_value = $pointer_type_values[0];
						$init_neighbor_index_type_value = $neighbor_index_type_values[0];
						$init_fma_ins_type_value = $fma_ins_type_values[0];
						$init_prefetch_index_type_value = $prefetch_index_type_values[0];
						$init_prefetch_distance_value = $prefetch_distance_values[0];
						$init_rb_size_value = $rb_size_values[0];
					}

					if ($log2_numThreads == 3) {
						$init_numCoreBlockCells_x = ($nreals_x/$numThreads);
						$init_numCoreBlockCells_y = $nreals_y;
						$init_numCoreBlockCells_z = $nreals_z;
						$init_numCoreBlocksPerChunk = 1;
						$init_statement_type_value = $statement_type_values[0];
						$init_read_from_type_value = $read_from_type_values[0];
						$init_pointer_type_value = $pointer_type_values[0];
						$init_neighbor_index_type_value = $neighbor_index_type_values[0];
						$init_fma_ins_type_value = $fma_ins_type_values[0];
						$init_prefetch_index_type_value = $prefetch_index_type_values[0];
						$init_prefetch_distance_value = $prefetch_distance_values[0];
						$init_rb_size_value = $rb_size_values[0];
					}

					# PADDING
					foreach $padding (@padding_values) {
						system ("$exec_file $numIter $nreals_x $nreals_y $nreals_z $numThreads $padding $init_numCoreBlockCells_x $init_numCoreBlockCells_y $init_numCoreBlockCells_z $init_numCoreBlocksPerChunk 0 0 $init_statement_type_value $init_read_from_type_value $init_pointer_type_value $init_neighbor_index_type_value $init_fma_ins_type_value $init_prefetch_index_type_value $init_prefetch_distance_value $init_rb_size_value >> $output_file");
					}
					$best_timing_line_number = find_best_time_for_opt($output_file, $output_file_line_length);
					find_best_padding($output_file, $best_timing_line_number);
					system ("echo \"BEST PADDING:\" >> $output_file");
					system ("echo \"Padding: @best_padding_dims[0,1,2]\" >> $output_file");
					system ("echo \"Time: $median_times{$my_best_timing_line_number}\" >> $output_file");

					# CORE BLOCK AND CHUNK SIZE
					foreach $log2_numCoreBlockCells_x (@log2_numCoreBlockCells_x_values) {
						$numCoreBlockCells_x = 2**($log2_numCoreBlockCells_x); # 2 to $nreals_x in powers of 2
						foreach $log2_numCoreBlockCells_y (@log2_numCoreBlockCells_y_values) {
							my $numCoreBlockCells_y = 2**($log2_numCoreBlockCells_y); # 2 to $nreals_y in powers of 2
							foreach $log2_numCoreBlockCells_z (@log2_numCoreBlockCells_z_values) {
								my $numCoreBlockCells_z = 2**($log2_numCoreBlockCells_z); # 8 to $nreals_z in powers of 2
								@log2_numCoreBlocksPerChunk_values = (0..(($log2_nreals_x + $log2_nreals_y + $log2_nreals_z) - ($log2_numCoreBlockCells_x + $log2_numCoreBlockCells_y + $log2_numCoreBlockCells_z + $log2_numThreads)));
								foreach $log2_numCoreBlocksPerChunk (@log2_numCoreBlocksPerChunk_values) {
									my $numCoreBlocksPerChunk = 2**($log2_numCoreBlocksPerChunk);
									system ("$exec_file $numIter $nreals_x $nreals_y $nreals_z $numThreads $best_padding_dims[2] $numCoreBlockCells_x $numCoreBlockCells_y $numCoreBlockCells_z $numCoreBlocksPerChunk 0 0 $init_statement_type_value $init_read_from_type_value $init_pointer_type_value $init_neighbor_index_type_value $init_fma_ins_type_value $init_prefetch_index_type_value $init_prefetch_distance_value $init_rb_size_value >> $output_file");
								}
							}
						}
					}

					$best_timing_line_number = find_best_time_for_opt($output_file, $output_file_line_length);
					find_best_core_block_and_chunk_size($output_file, $best_timing_line_number);
					system ("echo \"BEST CORE BLOCK AND CHUNK SIZE:\" >> $output_file");
					system ("echo \"Core block: @best_core_block_dims[0,1,2]\" >> $output_file");
					system ("echo \"Chunk size: $best_chunk_size[0]\" >> $output_file");
					system ("echo \"Time: $median_times{$my_best_timing_line_number}\" >> $output_file");

					# INNER LOOP
					foreach $statement_type (@statement_type_values) {
						foreach $read_from_type (@read_from_type_values) {
							foreach $pointer_type (@pointer_type_values) {
								foreach $neighbor_index_type (@neighbor_index_type_values) {
									foreach $fma_ins_type (@fma_ins_type_values) {
										foreach $rb_size (@rb_size_values) {
											system ("$exec_file $numIter $nreals_x $nreals_y $nreals_z $numThreads $best_padding_dims[2] $best_core_block_dims[0] $best_core_block_dims[1] $best_core_block_dims[2] $best_chunk_size[0] 0 0 $statement_type $read_from_type $pointer_type $neighbor_index_type $fma_ins_type $init_prefetch_index_type_value $init_prefetch_distance_value $rb_size >> $output_file");
										}
									}
								}
							}
						}
					}
					$best_timing_line_number = find_best_time_for_opt($output_file, $output_file_line_length);
					find_best_inner_loop($output_file, $best_timing_line_number);
					system("echo \"BEST INNER LOOP:\" >> $output_file");
					system("echo \"Statement type: $best_statement_type[0]\" >> $output_file");
					system("echo \"Read from type: $best_read_from_type[0]\" >> $output_file");
					system("echo \"Pointer type: $best_pointer_type[0]\" >> $output_file");
					system("echo \"Neighbor index type: $best_neighbor_index_type[0]\" >> $output_file");
					system("echo \"FMA instruction type: $best_fma_ins_type[0]\" >> $output_file");
					system("echo \"Register block: @best_register_block_dims[0,1,2], case = $best_rb_case[0]\" >> $output_file");
					system("echo \"Time: $median_times{$my_best_timing_line_number}\" >> $output_file");

					# PREFETCHING
					foreach $prefetch_index_type (@prefetch_index_type_values) {
						foreach $prefetch_distance (@prefetch_distance_values) {
							system ("$exec_file $numIter $nreals_x $nreals_y $nreals_z $numThreads $best_padding_dims[2] $best_core_block_dims[0] $best_core_block_dims[1] $best_core_block_dims[2] $best_chunk_size[0] 0 0 $best_statement_type[0] $best_read_from_type[0] $best_pointer_type[0] $best_neighbor_index_type[0] $best_fma_ins_type[0] $prefetch_index_type $prefetch_distance $best_rb_case[0] >> $output_file");
						}
					}
					$best_timing_line_number = find_best_time_for_opt($output_file, $output_file_line_length);
					find_best_prefetching($output_file, $best_timing_line_number);
					system("echo \"BEST PREFETCHING:\" >> $output_file");
					system("echo \"Prefetch index type: $best_prefetch_index_type[0]\" >> $output_file");
					system("echo \"Prefetch distance: $best_prefetch_distance[0], case = $best_prefetch_distance_case[0]\" >> $output_file");
					system("echo \"Time: $median_times{$my_best_timing_line_number}\" >> $output_file");
				}
			}
		}
	}
}
