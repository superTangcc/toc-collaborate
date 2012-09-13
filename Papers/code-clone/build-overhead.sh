#!/bin/sh

cp $1 build-cost.tmp

for f in `ls mit-data/*.diff`; do
    out=`echo $f | sed -e "s/txt/out/"`
    prefix=`echo $f | sed -e "s/mit\-data\/\(.*\)\-.*/\1/"`
    prefix="MIT$prefix"
    cat $f | ./overhead-replace.pl build-cost.tmp $prefix > build-cost.tmp~
    mv build-cost.tmp~ build-cost.tmp
done;

for f in `ls tps-data/*.diff`; do
    out=`echo $f | sed -e "s/txt/out/"`
    prefix=`echo $f | sed -e "s/tps\-data\/\(.*\)\-.*/\1/"`
    prefix="TPS$prefix"
    cat $f | ./overhead-replace.pl build-cost.tmp $prefix > build-cost.tmp~
    mv build-cost.tmp~ build-cost.tmp
done;

cat build-cost.tmp
rm build-cost.tmp
