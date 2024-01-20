.PHONY: run-main
run-main: build-main
	./main.out

.PHONY: build-main
build-main: build-lib
	g++ main.cpp numericpp.a -o main.out

.PHONY: build-lib
build-lib:
	g++ -c gquad.cpp root.cpp util.cpp finitediff.cpp diffsolve.cpp
	ar rcs numericpp.a gquad.o root.o util.o finitediff.o diffsolve.o
	rm *.o