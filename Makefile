CC=gcc
CPP=g++
AR=ar
RM=rm
CP=cp
CFLAGS=-O0 -Wextra -Wall -g -Idequeue -Irandomized_queue
CPPFLAGS=$(CFLAGS)

TMP_PATH=build_tmp
SRC_PATH=src
BIN_PATH=bin

all: deque_test rand_test Subset Palindrome

DEQUE_PATH=dequeue
DEQUE=$(SRC_PATH)/main_deque.cpp $(DEQUE_PATH)/deque.h
DEQUE_TEST_O=$(TMP_PATH)/main_deque.o

RANDQUE_PATH=randomized_queue
RANDQUE=$(SRC_PATH)/main_rand.cpp $(RANDQUE_PATH)/randomized_queue.h
RANDQUE_TEST_O=$(TMP_PATH)/main_rand.o

SUBSET=$(SRC_PATH)/Subset.cpp $(RANDQUE_PATH)/randomized_queue.h
SUBSET_O=$(TMP_PATH)/Subset.o

PALIN=$(SRC_PATH)/Palindrome.cpp $(DEQUE_PATH)/deque.h
PALIN_O=$(TMP_PATH)/Palindrome.o

$(DEQUE_TEST_O): $(DEQUE) $(TMP_PATH)
	$(CPP) -o $(DEQUE_TEST_O) -c $(CPPFLAGS) $(SRC_PATH)/main_deque.cpp

deque_test: $(DEQUE_TEST_O) $(DEQUE) $(BIN_PATH)
	$(CPP) -o $(BIN_PATH)/deque_test $(CPPFLAGS) $(DEQUE_TEST_O)

$(RANDQUE_TEST_O): $(RANDQUE) $(TMP_PATH)
	$(CPP) -o $(RANDQUE_TEST_O) -c $(CPPFLAGS) $(SRC_PATH)/main_rand.cpp

rand_test: $(RANDQUE_TEST_O) $(RANDQUE) $(BIN_PATH)
	$(CPP) -o $(BIN_PATH)/rand_test $(CPPFLAGS) $(RANDQUE_TEST_O)

$(SUBSET_O): $(SUBSET) $(TMP_PATH)
	$(CPP) -o $(SUBSET_O) -c $(CPPFLAGS) $(SRC_PATH)/Subset.cpp

Subset: $(SUBSET_O) $(BIN_PATH)
	$(CPP) -o $(BIN_PATH)/Subset $(CPPFLAGS) $(SUBSET_O)

$(PALIN_O): $(PALIN) $(TMP_PATH)
	$(CPP) -o $(PALIN_O) -c $(CPPFLAGS) $(SRC_PATH)/Palindrome.cpp

Palindrome: $(PALIN_O) $(BIN_PATH)
	$(CPP) -o $(BIN_PATH)/Palindrome $(CPPFLAGS) $(PALIN_O)

$(TMP_PATH):
	mkdir -p $(TMP_PATH)

$(BIN_PATH):
	mkdir -p $(BIN_PATH)

.PHONY: clean
clean:
	rm -f $(TMP_PATH)/*.o $(BIN_PATH)/*