#!/bin/bash
#@ job_type = serial
#@ class = regular
#@ wall_clock_limit = 00:29:00
#@ environment = COPY_ALL
#@ node_usage = not_shared
#
#@ queue

grid_dim=256
num_iterations=4

iteration_ctr=1

EXE_FILE=../src/stencil_c_naive_dynamic_aliased
OUT_FILE=../results/bassi_c_naive_dynamic_aliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

iteration_ctr=1

EXE_FILE=../src/stencil_c_naive_dynamic_unaliased
OUT_FILE=../results/bassi_c_naive_dynamic_unaliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

iteration_ctr=1

EXE_FILE=../src/stencil_c_naive_dynamic_unaliased
OUT_FILE=../results/bassi_c_naive_dynamic_unaliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

iteration_ctr=1

EXE_FILE=../src/stencil_c_naive_static_aliased
OUT_FILE=../results/bassi_c_naive_static_aliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

iteration_ctr=1

EXE_FILE=../src/stencil_c_naive_static_unaliased
OUT_FILE=../results/bassi_c_naive_static_unaliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done
