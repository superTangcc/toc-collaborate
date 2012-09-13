#!/bin/bash

set -x

out="`ls *.out`"

for f in ${out} 
do
    echo $f
    # name without extension
    name=${f%%.*}
    ./pochoir "${name}.out" 
done

set +x
