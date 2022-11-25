OBJECTS= ./build/vector.o
INCLUDES= -I./include
MUNIT_OBJECTS= ./build/munit.o

all: ${OBJECTS}
	gcc -g ${INCLUDES} main.c ${OBJECTS} -o main

./build/vector.o: ./src/vector.c
	gcc -g ${INCLUDES} ./src/vector.c -o ./build/vector.o -c

.PHONY: build_tests
build_tests: ./build/test_vector

./build/test_vector: ./test/test_vector.c ${OBJECTS} ${MUNIT_OBJECTS}
	gcc -g ${INCLUDES} ./test/test_vector.c ${OBJECTS} ${MUNIT_OBJECTS} -o ./build/test_vector

.PHONY: tests
test: build_tests
	./build/test_vector

./build/munit.o: ./test/munit/munit.c
	gcc -g -I./test ./test/munit/munit.c -o ./build/munit.o -c

.PHONY: clean
clean:
	rm -f main
	rm -f ${OBJECTS}