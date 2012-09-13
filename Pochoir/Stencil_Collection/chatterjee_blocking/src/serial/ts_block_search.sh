#!/bin/bash

# Parameter list
# 1.  Platform name
# 2.  Compiler name
# 3.  Cubic grid dimension
# 4.  Num iterations

platform=$1
compiler=$2
grid_dim=$3
num_iter=$4

EXE_FILE=./ts_${compiler}_c
OUT_FILE=${platform}_ts_block_search_${grid_dim}.out

rm $OUT_FILE

min_cache_block_dim_x=1
min_cache_block_dim_y=1
# min_cache_block_dim_z=1
# if we don't cut in the unit-stride dimension, allow the following:
min_cache_block_dim_z=$grid_dim

cache_block_dim_x=$grid_dim
while [ $cache_block_dim_x -ge $min_cache_block_dim_x ]
  do
  cache_block_dim_y=$grid_dim
  while [ $cache_block_dim_y -ge $min_cache_block_dim_y ]
    do
    cache_block_dim_z=$grid_dim
    while [ $cache_block_dim_z -ge $min_cache_block_dim_z ]
      do
      $EXE_FILE $num_iter $grid_dim $grid_dim $grid_dim $cache_block_dim_x $cache_block_dim_y $cache_block_dim_z >> $OUT_FILE
      cache_block_dim_z=$((cache_block_dim_z/2))
    done
    cache_block_dim_y=$((cache_block_dim_y/2))
  done
  cache_block_dim_x=$((cache_block_dim_x/2))
done
