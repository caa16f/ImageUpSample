CC := g++
CFLAGS := -std=c++11

SRCS := upsample.cpp

OBJS := ${SRCS:.cpp=.o}

PROGS := ${SRCS:.cpp=}

.PHONY: all
all: ${PROGS}

main: upsample.o
        ${CC} ${CFLAGS} -o $@ $^

test: UnitTest.cpp
        ${CC} ${CFLAGS} -I ~/googletest/googletest/include -L ~/googletest/build/lib UnitTest.cpp -o test -lgtest -lpthread
        ./test

coverage: upsample.o
        ${CC} ${CFLAGS} -fprofile-arcs -ftest-coverage -fPIC upsample.cpp -o coverage
        ./coverage
        ./coverage sample1_input_image.txt
        ./coverage sample1_input_image.txt output.txt
        ~/.local/bin/gcovr -r .

upsample.o: upsample.h upsample.cpp  upsample.hpp
        ${CC} ${CFLAGS} -c $<

clean:
        rm -f ${PROGS} ${OBJS} *.bak *~
