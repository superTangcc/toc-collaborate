#!/bin/bash

# Parameter list
# 1.  Platform name
# 2.  Log2 of min stanza length (usually 11)
# 3.  Log2 of max stanza length (usually 19)
# 4.  Log2 of num iterations for min stanza length (usually 17)

headerFile=$1_header_shortTime.txt
scriptName=$1_cache_hit_time_benchmark.sh

cp $headerFile $scriptName

echo 'EXE_FILE=../src/cache_hit_time_benchmark' >> $scriptName
echo "OUT_FILE=../results/benchmarks/$1_cache_hit_time.out" >> $scriptName
echo '' >> $scriptName
echo 'rm $OUT_FILE' >> $scriptName
echo '' >> $scriptName
echo "log2_min_stanza_length=$2" >> $scriptName
echo "log2_max_stanza_length=$3" >> $scriptName
echo "log2_num_iterations=$4" >> $scriptName
echo '' >> $scriptName
echo 'log2_stanza_length=${log2_min_stanza_length}' >> $scriptName
echo 'while [ $log2_stanza_length -le $log2_max_stanza_length ]' >> $scriptName
echo '  do' >> $scriptName
echo '  $EXE_FILE $log2_stanza_length $log2_num_iterations >> $OUT_FILE' >> $scriptName
echo '  log2_stanza_length=$((log2_stanza_length+1))' >> $scriptName
echo '  log2_num_iterations=$((log2_num_iterations-1))' >> $scriptName
echo 'done' >> $scriptName
