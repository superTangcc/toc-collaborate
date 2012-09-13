#!/bin/bash

# Parameter list
#    1.  The platform name
#    2.  Boundary conditions: "ghost_layer" or "ghost_zone"
#    3.  One dimension of the cubic grid

if [ $3 -le 256 ]; then
    headerFile=$1_header_shortTime.txt
else
    headerFile=$1_header_longTime.txt
fi

scriptName=$1_naive_block_search_$2_$3cubed_z$3.sh

cp $headerFile $scriptName

echo "OUT_FILE=../results/block_search/$2/$1_naive_$3cubed_z$3.out" >> $scriptName
echo 'rm $OUT_FILE' >> $scriptName
echo '' >> $scriptName
echo 'num_iterations=4' >> $scriptName
echo 'iteration_ctr=1' >> $scriptName
echo '' >> $scriptName
echo 'while [ $iteration_ctr -le $num_iterations ]' >> $scriptName
echo 'do' >> $scriptName
echo "  ../src/stencil_naive_$2_noLU \$iteration_ctr $3 $3 $3 $3 $3 $3 >> \$OUT_FILE" >> $scriptName
echo '  iteration_ctr=$((iteration_ctr+1))' >> $scriptName
echo 'done' >> $scriptName

chmod 744 $scriptName
