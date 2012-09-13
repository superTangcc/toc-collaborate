#!/bin/bash
#PBS -l mem=6gb,ncpus=1,walltime=5:59:00
#PBS -q batch

cd $PBS_O_WORKDIR

grid_dim=256
num_iterations=4

iteration_ctr=1

EXE_FILE=../src/stencil_c_naive_dynamic_aliased
OUT_FILE=../results/davinci_c_naive_dynamic_aliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

iteration_ctr=1

EXE_FILE=../src/stencil_c_naive_dynamic_unaliased
OUT_FILE=../results/davinci_c_naive_dynamic_unaliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

iteration_ctr=1

EXE_FILE=../src/stencil_c_naive_dynamic_unaliased
OUT_FILE=../results/davinci_c_naive_dynamic_unaliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

iteration_ctr=1

EXE_FILE=../src/stencil_c_naive_static_aliased
OUT_FILE=../results/davinci_c_naive_static_aliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done

iteration_ctr=1

EXE_FILE=../src/stencil_c_naive_static_unaliased
OUT_FILE=../results/davinci_c_naive_static_unaliased_${grid_dim}cubed_z${grid_dim}.out
rm $OUT_FILE

while [ $iteration_ctr -le $num_iterations ]
do
  $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim >> $OUT_FILE
  iteration_ctr=$((iteration_ctr+1))
done
