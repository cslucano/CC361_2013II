all: compile gen

compile: p1_gen.cpp p1_mmap.cpp p1_read.cpp
	g++ p1_gen.cpp -o p1_gen
	g++ p1_mmap.cpp -o p1_mmap
	g++ p1_read.cpp -o p1_read
gen: p1_gen
	./p1_gen a.txt b.txt c.txt
test: test.sh
	./test.sh
clean:
	rm a.txt b.txt c.txt
	rm p1_gen p1_mmap p1_read
