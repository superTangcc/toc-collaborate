#!/usr/bin/perl -w

# For naive algorithm, no block sizes needed
# This script is for loop unrolling

# Parameter list
#    0.  The platform name
#    1.  The compiler name
#    2.  The transformation (either "fs", "fa", "fv", "ma", or "mv")
#    3.  The number of iterations
#    4.  Least-contiguous dimension of the grid
#    5.  Middle-contiguous dimension of the grid
#    6.  Contiguous dimension of the grid

$platform = $ARGV[0];
$compiler = $ARGV[1];
$transformation = $ARGV[2];
$num_iter = $ARGV[3];
$i_grid_dim = $ARGV[4];
$j_grid_dim = $ARGV[5];
$k_grid_dim = $ARGV[6];

$out_file = ("" . $platform . "_" . $compiler . "_" . $transformation . "_" . $i_grid_dim . "_" . $j_grid_dim . "_" . $k_grid_dim . "_" . $num_iter . "iter.sh");
open(OUT, ">$out_file") || die ("Couldn't create $out_file.\n");

header_code();
print OUT ("num_iter=$num_iter\n");
print OUT ("i_grid_dim=" . $i_grid_dim . "\n");
print OUT ("j_grid_dim=" . $j_grid_dim . "\n");
print OUT ("k_grid_dim=" . $k_grid_dim . "\n\n");
print OUT ("EXE_FILE=../src/naive_" . $transformation . "_" . $compiler . "_c\n\n");
print OUT ("OUT_FILE=../results/${platform}_${compiler}_naive_${transformation}_\${i_grid_dim}_\${j_grid_dim}_\${k_grid_dim}_\${num_iter}iter_c.out\n");
print OUT ("rm \$OUT_FILE\n\n");
print OUT ("\$EXE_FILE \$num_iter \$i_grid_dim \$j_grid_dim \$k_grid_dim \$i_grid_dim \$j_grid_dim \$k_grid_dim >> \$OUT_FILE\n");

sub header_code {
    if ($platform eq "citris") {
	print OUT ("#!/bin/bash\n");
	print OUT ("#PBS -l walltime=00:59:00\n");
	print OUT ("#PBS -l nodes=1\n");
	print OUT ("#PBS -j oe\n\n");
	print OUT ("set echo\n");
	print OUT ("cd \$PBS_O_WORKDIR\n");
    }
    elsif ($platform eq "bassi") {
	print OUT ("#!/bin/bash\n");
	print OUT ("#@ job_type = serial\n");
	print OUT ("#@ class = interactive\n");
#	print OUT ("#@ class = regular\n");
	print OUT ("#@ wall_clock_limit = 00:29:00\n");
	print OUT ("#@ environment = COPY_ALL\n");
	print OUT ("#@ node_usage = not_shared\n");
	print OUT ("#\n");
	print OUT ("#@ queue\n");
    }
    elsif ($platform eq "davinci") {
	print OUT ("#!/bin/bash\n");
	print OUT ("#PBS -l mem=6gb,ncpus=1,walltime=0:29:00\n");
	print OUT ("#PBS -q batch\n\n");
	print OUT ("cd \$PBS_O_WORKDIR\n");
    }
    elsif ($platform eq "jacquard") {
	print OUT ("#!/bin/bash\n");
	print OUT ("#PBS -l walltime=00:29:00\n");
	print OUT ("#PBS -l nodes=1\n");
	print OUT ("#PBS -j oe\n\n");
	print OUT ("set echo\n");
	print OUT ("cd \$PBS_O_WORKDIR\n\n");
    }
}
