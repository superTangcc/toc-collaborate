#/bin/bash
CC = icpc
ICC = icpc
PAR_OPT_FLAGS = -O3 -DNDEBUG -Wall -Werror -unroll-aggressive -funroll-loops -std=c++0x
SER_OPT_FLAGS = -O3 -DNDEBUG -Wall -Werror -unroll-aggressive -funroll-loops -std=c++0x -I${INTEL_CILK_HEADER} -include cilk_stub.h
DEBUG_FLAGS = -O0 -g3 -Wall -Werror -DDEBUG -std=c++0x -I${INTEL_CILK_HEADER} -include cilk_stub.h
LIB = lib_common.hpp lib_init_1D.hpp lib_init_2D.hpp lib_meta_1D.hpp lib_meta_2D.hpp lib_init_3D.hpp lib_meta_3D.hpp
meta_3D : ${LIB} tb_meta_3D.cpp
#   Phase-II compilation with parallelization
#	${CC} -o meta_3D_1Star_par ${PAR_OPT_FLAGS} tb_meta_3D.cpp
#   Phase-II compilation without parallelization
	${CC} -o meta_3D_2Star_ser ${SER_OPT_FLAGS} tb_meta_3D.cpp
#   Phase-I compilation with debugging aid
#	${CC} -o meta_3D ${DEBUG_FLAGS} tb_meta_3D.cpp
meta_2D : ${LIB} tb_meta_2D.cpp
#   Phase-II compilation with parallelization
#	${CC} -o meta_2D_1Star_par ${PAR_OPT_FLAGS} tb_meta_2D.cpp
#   Phase-II compilation without parallelization
	${CC} -o meta_2D_1Star_ser ${SER_OPT_FLAGS} tb_meta_2D.cpp
#   Phase-I compilation with debugging aid
#	${CC} -o meta_2D ${DEBUG_FLAGS} tb_meta_2D.cpp
meta_1D : ${LIB} tb_meta_1D.cpp
#   Phase-II compilation with parallelization
#	${CC} -o meta_1D_NlogStarN_par ${PAR_OPT_FLAGS} tb_meta_1D.cpp
#   Phase-II compilation without parallelization
	${CC} -o meta_1D_2Star_ser ${SER_OPT_FLAGS} tb_meta_1D.cpp
#   Phase-I compilation with debugging aid
#	${CC} -o meta_1D ${DEBUG_FLAGS} tb_meta_1D.cpp
alpha : ${LIB} tb_alpha.cpp
#   Phase-II compilation
	${CC} -o alpha ${SER_OPT_FLAGS} tb_alpha.cpp
#   Phase-I compilation with debugging aid
#	${CC} -o alpha ${DEBUG_FLAGS} tb_alpha.cpp
clean: 
	rm -f *.o *.i *.out alpha meta_*
