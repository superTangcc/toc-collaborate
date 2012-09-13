#!/bin/bash

# Parameter list
# 1.  Platform name
# 2.  Log2 of array size in doubles (usually 20)

headerFile=$1_header_shortTime.txt
scriptName=$1_striad.sh

cp $headerFile $scriptName

echo 'EXE_FILE=../src/stanza_c' >> $scriptName
echo "OUT_FILE=../results/$1_stanza_c.out" >> $scriptName
echo 'rm $OUT_FILE' >> $scriptName
echo "\$EXE_FILE $2 >> \$OUT_FILE" >> $scriptName
echo '' >> $scriptName

echo 'EXE_FILE=../src/striad_c' >> $scriptName
echo "OUT_FILE=../results/$1_striad_c.out" >> $scriptName
echo 'rm $OUT_FILE' >> $scriptName
echo "\$EXE_FILE $2 >> \$OUT_FILE" >> $scriptName
echo '' >> $scriptName

echo "echo \"$2\" > param.in" >> $scriptName
echo '' >> $scriptName

echo 'EXE_FILE=../src/stanza_F' >> $scriptName
echo "OUT_FILE=../results/$1_stanza_F.out" >> $scriptName
echo 'rm $OUT_FILE' >> $scriptName
echo '$EXE_FILE < param.in >> $OUT_FILE' >> $scriptName
echo '' >> $scriptName

echo 'EXE_FILE=../src/striad_F' >> $scriptName
echo "OUT_FILE=../results/$1_striad_F.out" >> $scriptName
echo 'rm $OUT_FILE' >> $scriptName
echo '$EXE_FILE < param.in >> $OUT_FILE' >> $scriptName
echo '' >> $scriptName

echo 'rm ./param.in' >> $scriptName

chmod 744 $scriptName
