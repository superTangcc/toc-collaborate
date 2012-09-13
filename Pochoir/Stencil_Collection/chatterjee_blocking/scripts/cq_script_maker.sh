#!/bin/bash

# For circular queue algorithm, only the y-dimension varies

# Parameter list
#    1.  The platform name
#    2.  Boundary conditions: "ghost_layer" or "ghost_zone"
#    3.  One dimension of the cubic grid

if [ $3 -le 256 ]; then
    headerFile=$1_header_shortTime.txt
else
    headerFile=$1_header_longTime.txt
fi

scriptName=$1_cq_block_search_$2_$3cubed_z$3.sh

cp $headerFile $scriptName

echo 'block_dim_min=4' >> $scriptName
echo 'num_iterations=4' >> $scriptName
echo "grid_dim=$3" >> $scriptName
echo '' >> $scriptName
echo 'i_block_dim=$grid_dim' >> $scriptName
echo 'k_block_dim=$grid_dim' >> $scriptName
echo 'iteration_ctr=1' >> $scriptName
echo '' >> $scriptName
echo "EXE_FILE=../src/stencil_cq_$2_optimized" >> $scriptName
echo '' >> $scriptName
echo "OUT_FILE=../results/block_search/$2/$1_cq_\${grid_dim}cubed_z\${grid_dim}.out" >> $scriptName
echo 'rm $OUT_FILE' >> $scriptName
echo '' >> $scriptName
echo 'while [ $iteration_ctr -le $num_iterations ]' >> $scriptName
echo 'do' >> $scriptName
echo '  j_block_dim=$block_dim_min' >> $scriptName
echo '  while [ $j_block_dim -le $grid_dim ]' >> $scriptName
echo '    do' >> $scriptName
echo '    $EXE_FILE $iteration_ctr $grid_dim $grid_dim $grid_dim $i_block_dim $j_block_dim $k_block_dim >> $OUT_FILE' >> $scriptName
echo '    j_block_dim=$((j_block_dim*2))' >> $scriptName
echo '  done' >> $scriptName
echo '  iteration_ctr=$((iteration_ctr+1))' >> $scriptName
echo 'done' >> $scriptName

chmod 744 $scriptName
