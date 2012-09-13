#!/bin/bash
#@ job_type = serial
#@ class = interactive
#@ wall_clock_limit = 00:29:00
#@ environment = COPY_ALL
#@ node_usage = not_shared
#
#@ queue

# NOTE: The arguments that are passed to the executable are (in order):
#    1.  The number of relaxes being performed
#    2.  The x-dimension of the grid
#    3.  The y-dimension of the grid
#    4.  The z-dimension of the grid
#    5.  The x-dimension of the cache block (must be a divisor of the x-dimension of the grid)
#    6.  The y-dimension of the cache block (must be a divisor of the y-dimension of the grid)
#    7.  The z-dimension of the cache block (must be a divisor of the z-dimension of the grid)

# This script performs 1-8 iterations of a 7-point stencil code over a 128^3 grid while
# using a cache block size of 8x8x128 (the size with the best performance).  It then runs
# the same problem with no cache blocking for comparison.
# Both runs use the baseline code (no modifications).

# NOTE: the minimum block_dim should be greater than or equal to num_iterations
x_grid_dim=256
y_grid_dim=256
z_grid_dim=256
x_block_dim=8
y_block_dim=8
z_block_dim=$z_grid_dim
num_iterations=8

OUT_FILE=../results/single_block/bassi_${x_grid_dim}_${y_grid_dim}_${z_grid_dim}_compilerOptimizations.out
rm $OUT_FILE

EXE_FILE=../src/stencil_O3_qhot_qarch_qtune

iteration_ctr=1

# run with fused inner loops and best size block
while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $x_grid_dim $y_grid_dim $z_grid_dim $x_block_dim $y_block_dim $z_block_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

EXE_FILE=../src/stencil_O4

iteration_ctr=1

# run with loop unrolling once and best size block
while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $x_grid_dim $y_grid_dim $z_grid_dim $x_block_dim $y_block_dim $z_block_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

EXE_FILE=../src/stencil_O5_qnohot

iteration_ctr=1

# run with loop unrolling once and best size block
while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $x_grid_dim $y_grid_dim $z_grid_dim $x_block_dim $y_block_dim $z_block_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

EXE_FILE=../src/stencil_O5

iteration_ctr=1

# run with loop unrolling once and best size block
while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $x_grid_dim $y_grid_dim $z_grid_dim $x_block_dim $y_block_dim $z_block_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done
