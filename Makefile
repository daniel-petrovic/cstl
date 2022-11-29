OBJECTS= ./build/vector.o
INCLUDES= -I./include
MUNIT_OBJECTS= ./build/munit.o

.PHONY: make_dirs

all: make_dirs $(OBJECTS)
	ar rcs ./build/cstl.o ${OBJECTS}

make_dirs:
	mkdir -p ./build/helpers

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
	rm -f ./build/cstl.o
	rm -f ${OBJECTS}