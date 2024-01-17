.PHONY: run-main
run-main: build-lib build-main
	./main.out

.PHONY: build-main
build-main:
	g++ main.cpp numericpp.a -o main.out

.PHONY: build-lib
buildl-lib:
	g++ -c gquad.cpp root.cpp util.cpp
	ar rcs numericpp.a gquad.o root.o util.o
	rm *.o