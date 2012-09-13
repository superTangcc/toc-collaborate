CC := icpc
dlink: caller.cpp callee.cpp
	${CC} -rdynamic -o caller caller.cpp -ldl -O3 -std=c++0x
dlink1: caller1.cpp callee.cpp
	${CC} -rdynamic -o caller1 caller1.cpp -ldl -O3 -std=c++0x
lambda: lambda.cpp
	${CC} -o lam -rdynamic -ldl -std=c++0x -O3 lambda.cpp
closure: closure_caller.cpp closure_callee0.cpp closure_callee1.cpp
	${CC} -rdynamic -o closure_caller closure_caller.cpp -ldl -O0 -g -std=c++0x
ref: tb_ref.cpp
	${CC} -rdynamic -o ref tb_ref.cpp -ldl -O0 -g -std=c++0x
size: tb_size.cpp
	${CC} -o size tb_size.cpp 
clean: 
	rm -f *.so caller caller1 lam closure_caller ref size
