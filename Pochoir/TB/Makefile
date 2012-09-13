#/bin/bash
CC = icpc
ICC = icpc
OPT_FLAGS = -O3 -DNDEBUG -Wall -Werror -unroll-aggressive -funroll-loops -ipo -xHOST -fno-alias -fno-fnalias -fp-model precise -std=c++0x
DEBUG_FLAGS = -O0 -g3 -Wall -Werror -DDEBUG -std=c++0x -I${INTEL_CILK_HEADER} -include cilk_stub.h
cfor_2D_P : tb_cilk_for_2D_periodic.cpp
#   Phase-II compilation
	${CC} -o tb_cfor ${OPT_FLAGS} tb_cilk_for_2D_periodic.cpp
#	Phase-I compilation with debugging aid
#	${CC} -o tb_cfor_gdb ${POCHOIR_DEBUG_FLAGS} tb_cilk_for_2D_periodic.cpp
proxy : proxy.cpp
	icpc -o proxy -O0 -g -std=c++0x proxy.cpp
move : tb_move.cpp
	icpc -o move -O0 -g -std=c++0x tb_move.cpp
lca : tb_lca.cpp
	g++ -o lca -O3 -std=c++0x tb_lca.cpp
rbo_1d1b : tb_rbo_1d_1bit.cpp
#   Phase-II compilation
	icpc -o rbo_1d1b ${OPT_FLAGS} tb_rbo_1d_1bit.cpp
#   Phase-I compilation with debugging aid
#	icpc -o rbo_1d1b ${DEBUG_FLAGS} tb_rbo_1d_1bit.cpp
rbo_3D : tb_rbo_3D.cpp
#   Phase-II compilation
#	icpc -o rbo_3D ${OPT_FLAGS} tb_rbo_3D.cpp
#   Phase-I compilation with debugging aid
	icpc -o rbo_3D ${DEBUG_FLAGS} tb_rbo_3D.cpp
rbo_2D : tb_rbo_2D.cpp
#   Phase-II compilation
#	icpc -o rbo_2D ${OPT_FLAGS} tb_rbo_2D.cpp
#   Phase-I compilation with debugging aid
	icpc -o rbo_2D ${DEBUG_FLAGS} tb_rbo_2D.cpp
rbo : tb_rbo.cpp
#   Phase-II compilation
	icpc -o rbo ${OPT_FLAGS} tb_rbo.cpp
#   Phase-I compilation with debugging aid
#	icpc -o rbo ${DEBUG_FLAGS} tb_rbo.cpp
rmq_1d_1bit : tb_rmq_1d_1bit.c
	icc -o rmq_1d_1bit -O0 -g -c99 tb_rmq_1d_1bit.c
log2 : tb_log2.c
	icc -o log2 -O3 -c99 tb_log2.c
meta : tb_meta.cpp
	icpc -o meta -O0 -g -std=c++0x tb_meta.cpp
fib : tb_fib.cpp
	g++ -o fib -O0 -g -std=c++0x tb_fib.cpp
btype : tb_boost_type_traits.cpp
	icpc -o btype -O0 -g -std=c++0x tb_boost_type_traits.cpp
clean: 
	rm -f *.o *.i *_pochoir *_pochoir.cpp *.out
