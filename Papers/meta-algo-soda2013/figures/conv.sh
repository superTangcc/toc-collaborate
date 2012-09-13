#!/bin/bash

set -x

png="`ls *.png`"

for f in ${png} 
do
    echo $f
    # name without extension
    name=${f%%.*}
    convert "${name}.png" "${name}.eps"
done

set +x
