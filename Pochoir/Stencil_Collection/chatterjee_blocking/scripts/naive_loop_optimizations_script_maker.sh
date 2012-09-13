#!/bin/bash

# Parameter list
#    1.  The platform name
#    2.  Boundary conditions: "ghost_layer" or "ghost_zone"
#    3.  Number of iterations
#    4.  The x-dimension of the grid
#    5.  The y-dimension of the grid
#    6.  The z-dimension of the grid

headerFile=$1_header_shortTime.txt
scriptName=$1_naive_loop_optimizations_$2_$3iter_$4_$5_$6.sh

cp $headerFile $scriptName

echo "OUT_FILE=../results/loop_optimizations/$2/$1_naive_$3iter_$4_$5_$6.out" >> $scriptName
echo 'rm $OUT_FILE' >> $scriptName
echo '' >> $scriptName

echo "../src/stencil_naive_$2_noLU $3 $4 $5 $6 $4 $5 $6 >> \$OUT_FILE" >> $scriptName
echo "../src/stencil_naive_$2_noLU_RC $3 $4 $5 $6 $4 $5 $6 >> \$OUT_FILE" >> $scriptName
echo "../src/stencil_naive_$2_yLU $3 $4 $5 $6 $4 $5 $6 >> \$OUT_FILE" >> $scriptName
echo "../src/stencil_naive_$2_yLU_RC $3 $4 $5 $6 $4 $5 $6 >> \$OUT_FILE" >> $scriptName
echo "../src/stencil_naive_$2_zLU $3 $4 $5 $6 $4 $5 $6 >> \$OUT_FILE" >> $scriptName
echo "../src/stencil_naive_$2_zLU_RC $3 $4 $5 $6 $4 $5 $6 >> \$OUT_FILE" >> $scriptName

chmod 744 $scriptName
