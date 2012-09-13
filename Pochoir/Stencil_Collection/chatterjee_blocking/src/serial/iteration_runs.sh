#!/bin/bash

# Parameter list
# 1.  Platform name
# 2.  Compiler name
# 3.  Cubic grid dimension
# 4.  Algorithm (ts, cq, or serial)
# 5.  Max iterations
# 6.  X-dim of cache block
# 7.  Y-dim of cache block
# 8.  Z-dim of cache block

platform=$1
compiler=$2
grid_dim=$3
alg=$4
max_iter=$5
cache_block_dim_x=$6
cache_block_dim_y=$7
cache_block_dim_z=$8

EXE_FILE=./${alg}_${compiler}_c
OUT_FILE=${platform}_${alg}_iteration_run_${grid_dim}.out

rm $OUT_FILE

num_iter=1
while [ $num_iter -le $max_iter ]
  do
  $EXE_FILE $num_iter $grid_dim $grid_dim $grid_dim $cache_block_dim_x $cache_block_dim_y $cache_block_dim_z >> $OUT_FILE
  num_iter=$((num_iter+1))
done
