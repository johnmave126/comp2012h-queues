CC=gcc
CPP=g++
AR=ar
RM=rm
CP=cp
CFLAGS=-O2 -Wextra -Wall -g -Idequeue -Irandomized_queue
CPPFLAGS=$(CFLAGS)

TMP_PATH=build_tmp
SRC_PATH=src
BIN_PATH=bin

all: deque_test rand_test Subset

DEQUE_PATH=dequeue
DEQUE=$(SRC_PATH)/main_deque.cpp $(DEQUE_PATH)/deque.h
DEQUE_TEST_O=$(TMP_PATH)/main_deque.o

RANDQUE_PATH=randomized_queue
RANDQUE=$(SRC_PATH)/main_rand.cpp $(RANDQUE_PATH)/randomized_queue.h
RANDQUE_TEST_O=$(TMP_PATH)/main_rand.o

SUBSET=$(SRC_PATH)/Subset.cpp $(RANDQUE_PATH)/randomized_queue.h
SUBSET_O=$(TMP_PATH)/Subset.o

$(DEQUE_TEST_O): $(DEQUE)
	$(CPP) -o $(DEQUE_TEST_O) -c $(CPPFLAGS) $(SRC_PATH)/main_deque.cpp

deque_test: $(DEQUE_TEST_O) $(DEQUE) $(BIN_PATH)
	$(CPP) -o $(BIN_PATH)/deque_test $(CPPFLAGS) $(DEQUE_TEST_O)

$(RANDQUE_TEST_O): $(RANDQUE)
	$(CPP) -o $(RANDQUE_TEST_O) -c $(CPPFLAGS) $(SRC_PATH)/main_rand.cpp

rand_test: $(RANDQUE_TEST_O) $(RANDQUE) $(BIN_PATH)
	$(CPP) -o $(BIN_PATH)/rand_test $(CPPFLAGS) $(RANDQUE_TEST_O)

$(SUBSET_O): $(SUBSET)
	$(CPP) -o $(SUBSET_O) -c $(CPPFLAGS) $(SRC_PATH)/Subset.cpp

Subset: $(SUBSET_O) $(BIN_PATH)
	$(CPP) -o $(BIN_PATH)/Subset $(CPPFLAGS) $(SUBSET_O)

.PHONY: $(BIN_PATH)
$(BIN_PATH):
	mkdir -p $(BIN_PATH)

.PHONY: clean
clean:
	rm -f $(TMP_PATH)/*.o $(BIN_PATH)/*