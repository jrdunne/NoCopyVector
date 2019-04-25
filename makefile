FLAGS = -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Weffc++ -Iinclude/ -std=c++17
OPTIM = -O3
CC=g++ $(FLAGS) $(OPTIM)

TESTROOT = test/
SRCROOT = src/
INCLUDEROOT = include/
OBJROOT = bin/

SRCEXTS = .cc
HDREXTS = .h

TESTSOURCES 	= $(wildcard $(addprefix $(TESTROOT)test*, $(SRCEXTS)))
SOURCES 		= $(wildcard $(addprefix $(SRCROOT)*, $(SRCEXTS)))
HEADERS 		= $(wildcard $(addprefix $(INCLUDEROOT)*, $(HDREXTS)))
OBJS 			= $(addprefix $(OBJROOT), $(addsuffix .o, $(basename $(foreach cc, $(SOURCES), $(cc:src/%=%)))))

all: test

# Generic rules for compiling a source file to an object file
bin/%.o : $(SRCROOT)%$(SRCEXTS)
	$(CC) -c $< -o $@

%.o : %$(SRCEXTS)
	$(CC) -c $< -o $@

SHELL := /bin/bash
tests := $(addsuffix .test, $(basename $(TESTSOURCES)))

.PHONY: test testall test/test-%.test
test: $(tests)

test/test-%.test: $(TESTROOT)test-%$(SRCEXTS)
	${CC} -o $@ $<

testall: test

clean:
	rm -f $(OBJS)
	rm -f $(tests)

