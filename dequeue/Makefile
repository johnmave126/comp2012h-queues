CC=gcc
CPP=g++
AR=ar
RM=rm
CP=cp
CFLAGS=-O2 -Wall -g
CPPFLAGS=$(CFLAGS) 

all: deque

DEQUE_OBJ=deque.o

.cpp.o:
	$(CPP) -c $(CPPFLAGS) $*.cpp

deque: $(DEQUE_OBJ)
	$(CPP) -o deque $(CPPFLAGS) $(DEQUE_OBJ)
