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

PARAM_FILE=./param.in
rm $PARAM_FILE

iteration_ctr=1

EXE_FILE=../src/stencil_f77_naive_static_aliased
OUT_FILE=../results/bassi_f77_naive_static_aliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  echo "$iteration_ctr" > $PARAM_FILE
  $EXE_FILE < $PARAM_FILE >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

iteration_ctr=1

EXE_FILE=../src/stencil_f77_naive_static_unaliased
OUT_FILE=../results/bassi_f77_naive_static_unaliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  echo "$iteration_ctr" > $PARAM_FILE
  $EXE_FILE < $PARAM_FILE >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

rm $PARAM_FILE
