CC=gcc
CPP=g++
AR=ar
RM=rm
CP=cp
CFLAGS=-O2 -Wextra -Wall -g
CPPFLAGS=$(CFLAGS) 

all: RANDQUE_test

RANDQUE=randomized_queue.h
RANDQUE_TEST_O=main_rand.o

.cpp.o:
	$(CPP) -c $(CPPFLAGS) $*.cpp

$(RANDQUE_TEST_O): $(RANDQUE)

RANDQUE_test: $(RANDQUE_TEST_O) $(RANDQUE)
	$(CPP) -o RANDQUE $(CPPFLAGS) $(RANDQUE_TEST_O)

