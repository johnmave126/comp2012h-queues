/*
 * Dequeue for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * Subset.cpp
 *
 * Subset, a little tool
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include "randomized_queue.h"

using namespace std;

void print_help() {
	cout << "Usage: Subset [OPTION]... NUMBER..." << endl;
	cout << "Print a subset string of NUMBER from standard input" << endl;
	cout << endl;
	cout << "  -h                    display this help and exit" << endl;
	cout << endl;
	cout << "Subset takes strings from standard input, and splits it by white-space." << endl;
	cout << "Then it outputs exactly NUMBER lines.  The order is completely random and" << endl;
	cout << "the elements are unique. " << endl;
	cout << endl;
	cout << "Note that NUMBER should be positive.  If NUMBER is greater than the number" << endl;
	cout << "of strings got.  All the strings will be displayed in random order." << endl;
	cout << endl;
	cout << "Written by TAN, Shuhao <stanab@stu.ust.hk>" << endl;
}

int main(int argc, char ** argv){
	int i;
	long int num_output = -1;
	char *error_ptr;
	string tmp;
	RandomizedQueue<string> rq;
	RandomizedQueue<string>::Iterator itr;
	
	//Process command-line input
	if(argc < 2) {
		//No input
		cout << "Subset: missing operand" << endl;
		cout << "Try `Subset -h' for more information." << endl;
		exit(EXIT_FAILURE);
	}
	
	//Omit the filename
	for(i = 1; i < argc; i++) {
		if(argv[i][0] == '-') {
			if(strlen(argv[i]) != 2) {
				cout << "Subset: unknown option: " << argv[i] << endl;
				cout << "Try `Subset -h' for more information." << endl;
				exit(EXIT_FAILURE);
			}
			switch(argv[i][1]) {
				case 'h':
					//Help
					print_help();
					exit(EXIT_SUCCESS);
				default:
					//Unrecognized
					cout << "Subset: unknown option: " << argv[i] << endl;
					cout << "Try `Subset -h' for more information." << endl;
					exit(EXIT_FAILURE);
			}
		}
		else {
			//Test if this is a number
			num_output = strtol(argv[i], &error_ptr, 10);
			if(num_output == 0L) {
				if(error_ptr == argv[i] || *error_ptr != '\0') {
					//Nothing converted
					cout << "Subset: invalid input" << endl;
					cout << "Try `Subset -h' for more information." << endl;
					exit(EXIT_FAILURE);
				}
			}
			
			if(num_output <= 0L) {
				cout << "Subset: positive NUMBER needed" << endl;
				cout << "Try `Subset -h' for more information." << endl;
				exit(EXIT_FAILURE);
			}
			
			//Go on to process stdin
			break;
		}		
	}
	
	//Process stdin
	while(cin >> tmp) {
		rq.enqueue(tmp);
	}
	
	if(num_output > rq.size()) {
		num_output = rq.size();
	}
	
	//Set seed
	srand((unsigned)time(NULL));
	
	//Initialize iterator
	itr = rq.iterator();
	for(i = 0; i < num_output; i++, itr++) {
		cout << (*itr) << endl;
	}
	return 0;
}
