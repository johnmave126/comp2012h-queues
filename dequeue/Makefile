CC=gcc
C++=g++
AR=ar
RM=rm
CP=cp
CFLAGS=-O2 -Wall -g
C++FLAGS = $(CFLAGS) 

all: deque

DEQUE_OBJ=deque.o

.cpp.o:
	$(C++) -c $(C++FLAGS) $*.cpp

deque: $(DEQUE_OBJ)
	$(C++) -o deque $(C++FLAGS) $(DEQUE_OBJ)
