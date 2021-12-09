# Makefile for working stuff

INCLUDE = /home/billw/include
GCC = g++-11 -std=c++2b -I${INCLUDE}
GCC17 = g++-11 -std=c++17 -I${INCLUDE}
CLANG = clang-cpp-12 -std=c++2a -I${INCLUDE}
GCC_MODULES = g++-11 -std=c++2b -fmodules-ts -I${INCLUDE}
LINKFLAGS = -lfmt
EXTRA_FLAGS = -fconcepts-diagnostics-depth=2 

all: working working.s iterator-constraint seq iterator-traits iterator-adapters \
        fib-generator reverse-iterator sentinel zip-iterator container-iterator

working: working.o
	${GCC} working.o ${LINKFLAGS} -o working

working.s: working.cpp
	${GCC} -c working.cpp -S -Fverbose-asm -O2 -o working.s

working.o: working.cpp ${INCLUDE}/bwprint.h
	${GCC} -c working.cpp -o working.o

iterator-constraint: iterator-constraint.cpp
	${GCC} iterator-constraint.cpp ${LINKFLAGS} -o iterator-constraint

seq: seq.cpp
	${GCC} seq.cpp ${LINKFLAGS} -o seq

iterator-traits: iterator-traits.cpp
	${GCC} iterator-traits.cpp ${LINKFLAGS} -o iterator-traits

iterator-adapters: iterator-adapters.cpp
	${GCC} iterator-adapters.cpp ${LINKFLAGS} -o iterator-adapters

fib-generator: fib-generator.cpp 
	${GCC} fib-generator.cpp ${LINKFLAGS} -o fib-generator

reverse-iterator: reverse-iterator.cpp 
	${GCC} reverse-iterator.cpp ${LINKFLAGS} -o reverse-iterator

sentinel: sentinel.cpp 
	${GCC} sentinel.cpp ${LINKFLAGS} -o sentinel

zip-iterator: zip-iterator.cpp 
	${GCC} zip-iterator.cpp ${LINKFLAGS} -o zip-iterator

container-iterator: container-iterator.cpp 
	${GCC} container-iterator.cpp ${LINKFLAGS} -o container-iterator

clean: 
	rm \
          container-iterator \
          zip-iterator \
          sentinel \
          reverse-iterator \
          fib-generator \
          iterator-adapters \
          iterator-traits \
          seq \
          iterator-constraint \
	  working.o working.s working 

