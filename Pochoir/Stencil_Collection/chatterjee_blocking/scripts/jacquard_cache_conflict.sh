#!/bin/bash
#PBS -l walltime=02:00:00
#PBS -l nodes=1
#PBS -j oe

set echo
cd $PBS_O_WORKDIR

num_iterations=1
grid_dim_x=126
grid_dim_y=126
grid_dim_z=48
max_grid_dim_z=298

EXE_FILE=../src/naive_c
OUT_FILE=./jacquard_cache_conflict.out
rm $OUT_FILE

while [ $grid_dim_z -le $max_grid_dim_z ]
do
  $EXE_FILE $num_iterations $grid_dim_x $grid_dim_y $grid_dim_z $grid_dim_x $grid_dim_y $grid_dim_z >> $OUT_FILE
  grid_dim_z=$((grid_dim_z+1))
done
