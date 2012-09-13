#!/bin/bash

# For time skewing algorithm, both the x and y-dimensions vary

# Parameter list
#    1.  The platform name
#    2.  One dimension of the cubic grid

if [ $2 -le 128 ]; then
    headerFile=$1_header_shortTime.txt
else
    headerFile=$1_header_longTime.txt
fi

scriptName=$1_ts_$2cubed.sh

cp $headerFile $scriptName

echo '# NOTE: block_dim_min should be greater than or equal to num_iterations' >> $scriptName
echo 'block_dim_min=4' >> $scriptName
echo 'num_iterations=4' >> $scriptName
echo "grid_dim=$2" >> $scriptName
echo 'k_block_dim=$grid_dim' >> $scriptName
echo '' >> $scriptName
echo "EXE_FILE=../src/ts_nonperiodic_c" >> $scriptName
echo '' >> $scriptName
echo "OUT_FILE=../results/$1_ts_\${grid_dim}cubed_c.out" >> $scriptName
echo 'rm $OUT_FILE' >> $scriptName
echo '' >> $scriptName
echo 'iteration_ctr=1' >> $scriptName
echo '' >> $scriptName
echo 'while [ $iteration_ctr -le $num_iterations ]' >> $scriptName
echo 'do' >> $scriptName
echo '  i_block_dim=$block_dim_min' >> $scriptName
echo '  while [ $i_block_dim -le $grid_dim ]' >> $scriptName
echo '    do' >> $scriptName
echo '    j_block_dim=$block_dim_min' >> $scriptName
echo '    while [ $j_block_dim -le $grid_dim ]' >> $scriptName
echo '      do' >> $scriptName
echo '      $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim $i_block_dim $j_block_dim $k_block_dim >> $OUT_FILE' >> $scriptName
echo '      j_block_dim=$((j_block_dim*2))' >> $scriptName
echo '    done' >> $scriptName
echo '    i_block_dim=$((i_block_dim*2))' >> $scriptName
echo '  done' >> $scriptName
echo '  iteration_ctr=$((iteration_ctr+1))' >> $scriptName
echo 'done' >> $scriptName
echo '' >> $scriptName

echo 'block_dim_min=4' >> $scriptName
echo 'num_iterations=4' >> $scriptName
echo "grid_dim=$2" >> $scriptName
echo 'i_block_dim=$grid_dim' >> $scriptName
echo '' >> $scriptName
echo "EXE_FILE=../src/ts_dynamic_F" >> $scriptName
echo '' >> $scriptName
echo "OUT_FILE=../results/$1_ts_\${grid_dim}cubed_F.out" >> $scriptName
echo 'rm $OUT_FILE' >> $scriptName
echo '' >> $scriptName
echo 'iteration_ctr=1' >> $scriptName
echo '' >> $scriptName
echo 'while [ $iteration_ctr -le $num_iterations ]' >> $scriptName
echo 'do' >> $scriptName
echo '  k_block_dim=$block_dim_min' >> $scriptName
echo '  while [ $k_block_dim -le $grid_dim ]' >> $scriptName
echo '    do' >> $scriptName
echo '    j_block_dim=$block_dim_min' >> $scriptName
echo '    while [ $j_block_dim -le $grid_dim ]' >> $scriptName
echo '      do' >> $scriptName
echo '      echo "$iteration_ctr $grid_dim $grid_dim $grid_dim $i_block_dim $j_block_dim $k_block_dim" > ./param.in' >> $scriptName
echo '      $EXE_FILE < ./param.in >> $OUT_FILE' >> $scriptName
echo '      j_block_dim=$((j_block_dim*2))' >> $scriptName
echo '    done' >> $scriptName
echo '    k_block_dim=$((k_block_dim*2))' >> $scriptName
echo '  done' >> $scriptName
echo '  iteration_ctr=$((iteration_ctr+1))' >> $scriptName
echo 'done' >> $scriptName
echo 'rm ./param.in' >> $scriptName

chmod 744 $scriptName
