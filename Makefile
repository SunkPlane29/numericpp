.PHONY: run
run: build
	./main.exe

.PHONY: build
build:
	g++ *.cpp -o main.exe