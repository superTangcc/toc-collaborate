#!/bin/bash

N=$1
T=$2

pc_stat="3dfd_test_${N}_${T}_pc.stat"
pbl_stat="3dfd_test_${N}_${T}_pbl.stat"

set -x
perf stat -e instructions -e cache-references -e cache-misses -e branches -e branch-misses -e bus-cycles ./3dfd_test_pc $N $N $N $T >& ${pc_stat}

perf stat -e instructions -e cache-references -e cache-misses -e branches -e branch-misses -e bus-cycles ./3dfd_test_pbl $N $N $N $T >& ${pbl_stat}
set +x
