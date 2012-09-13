#!/bin/bash
#PBS -l mem=6gb,ncpus=1,walltime=01:00:00
#PBS -q batch

cd $PBS_O_WORKDIR

# NOTE: The arguments that are passed are as follows (in order):
#    1.  log2 of the stanza length
#    2.  jump length

EXE_FILE=../src/cache_benchmark
OUT_FILE=../results/davinci_cache_benchmark.out
rm $OUT_FILE

log2_stanza_length=16
num_iterations=200
offset=0

$EXE_FILE $log2_stanza_length $num_iterations $offset >> $OUT_FILE

num_iterations=300

$EXE_FILE $log2_stanza_length $num_iterations $offset >> $OUT_FILE

offset=256
num_iterations=200

$EXE_FILE $log2_stanza_length $num_iterations $offset >> $OUT_FILE

num_iterations=300

$EXE_FILE $log2_stanza_length $num_iterations $offset >> $OUT_FILE
