#Makefile for lab00, Justin Tjoa, CS32, W19

CXX=clang++
# CXX=g++

helloWorld: helloWorld.o
	${CXX} $^ -o $@

helloWorld.o: helloWorld.cpp
	${CXX} -c $^

arrayFuncs: arrayFuncs.o tester.o
	${CXX} $^ -o $@

arrayFuncs.o: arrayFuncs.cpp 
	${CXX} -c arrayFuncs.cpp 

tester.o: tester.cpp
	${CXX} -c tester.cpp

lab00Test: lab00Test.o tddFuncs.o arrayFuncs.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f *.o helloWorld lab00Test
