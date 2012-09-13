#/bin/bash
CC = icpc
ICC = icpc
PAR_OPT_FLAGS = -O3 -DNDEBUG -Wall -Werror -unroll-aggressive -funroll-loops -std=c++0x
SER_OPT_FLAGS = -O3 -DNDEBUG -Wall -Werror -unroll-aggressive -funroll-loops -std=c++0x -I${INTEL_CILK_HEADER} -include cilk_stub.h
PAR_DEBUG_FLAGS = -O0 -g3 -Wall -Werror -DDEBUG -std=c++0x 
SER_DEBUG_FLAGS = -O0 -g3 -Wall -Werror -DDEBUG -std=c++0x -I${INTEL_CILK_HEADER} -include cilk_stub.h
LIB = lib_common.hpp lib_init_1D.hpp lib_init_2D.hpp lib_meta_1D.hpp lib_meta_2D.hpp
alpha : ${LIB} tb_alpha.cpp
#   Phase-II compilation
	${CC} -o alpha ${SER_OPT_FLAGS} tb_alpha.cpp
#   Phase-I compilation with debugging aid
#	${CC} -o alpha ${PAR_DEBUG_FLAGS} tb_alpha.cpp
meta_1D : ${LIB} tb_meta_1D.cpp
#   Phase-II compilation with parallelization
	${CC} -o meta_1D_NlogStarN_par ${PAR_OPT_FLAGS} tb_meta_1D.cpp
#   Phase-II compilation without parallelization
	${CC} -o meta_1D_NlogStarN_ser ${SER_OPT_FLAGS} tb_meta_1D.cpp
#   Phase-I compilation with parallel debugging aid
#	${CC} -o meta_1D ${PAR_DEBUG_FLAGS} tb_meta_1D.cpp
#   Phase-I compilation with serial debugging aid
#	${CC} -o meta_1D ${SER_DEBUG_FLAGS} tb_meta_1D.cpp
meta_2D : ${LIB} tb_meta_2D.cpp
#   Phase-II compilation with parallelization
	${CC} -o meta_2D_3Star_par ${PAR_OPT_FLAGS} tb_meta_2D.cpp
#   Phase-II compilation without parallelization
#	${CC} -o meta_2D_1Star_omp ${SER_OPT_FLAGS} -openmp tb_meta_2D.cpp
#   Phase-I compilation with parallel debugging aid
#	${CC} -o meta_2D_2Star_par_dbg ${PAR_DEBUG_FLAGS} tb_meta_2D.cpp
#   Phase-I compilation with serial debugging aid
#	${CC} -o meta_2D_2Star_ser_dbg ${SER_DEBUG_FLAGS} tb_meta_2D.cpp
clean: 
	rm -f *.o *.i *.out alpha meta_*
