CC=gcc
CPP=g++
AR=ar
RM=rm
CP=cp
CFLAGS=-O2 -Wextra -Wall -g
CPPFLAGS=$(CFLAGS) 

all: deque_test

DEQUE=deque.h
DEQUE_TEST_O=main_deque.o

.cpp.o:
	$(CPP) -c $(CPPFLAGS) $*.cpp

$(DEQUE_TEST_O): $(DEQUE)

deque_test: $(DEQUE_TEST_O) $(DEQUE)
	$(CPP) -o deque $(CPPFLAGS) $(DEQUE_TEST_O)

