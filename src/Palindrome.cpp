/*
 * Dequeue for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * Palindrome.cpp
 *
 * Palindrome, a little tool
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include "deque.h"

using namespace std;

void print_help() {
	cout << "Usage: Palindrome [OPTION]..." << endl;
	cout << "Judge if a sequence is a Watson-Crick complemented palindrome from" << endl;
	cout << "standard input." << endl;
	cout << endl;
	cout << "  -h                    display this help and exit" << endl;
	cout << endl;
	cout << "Palindrome takes strings from standard input, and judges whether" << endl;
	cout << "it is a Watson-Crick complemented palindrome.  That is, the" << endl;
	cout << "{A, C, T, G}-sequence equals its reverse when you replace each" << endl;
	cout << "base with its complement: A-T, C-G." << endl;
	cout << endl;
	cout << "Written by TAN, Shuhao <stanab@stu.ust.hk>" << endl;
}

int main(int argc, char ** argv){
	int i;
	char tmp, left, right;
	bool flag = true;
	Deque<char> dq;
	Deque<char>::Iterator itr;
	
	//Process command-line input
	//Omit the filename
	for(i = 1; i < argc; i++) {
		if(argv[i][0] == '-') {
			if(strlen(argv[i]) != 2) {
				cout << "Palindrome: unknown option: " << argv[i] << endl;
				cout << "Try `Palindrome -h' for more information." << endl;
				exit(EXIT_FAILURE);
			}
			switch(argv[i][1]) {
				case 'h':
					//Help
					print_help();
					exit(EXIT_SUCCESS);
				default:
					//Unrecognized
					cout << "Palindrome: unknown option: " << argv[i] << endl;
					cout << "Try `Palindrome -h' for more information." << endl;
					exit(EXIT_FAILURE);
			}
		}
		else {
			cout << "Palindrome: invalid input" << endl;
			cout << "Try `Palindrome -h' for more information." << endl;
		}		
	}
	
	//Process stdin
	while(cin >> tmp) {
		dq.addLast(tmp);
	}
	
	do {
		if(dq.size() % 2) {
			//odd size must fail
			flag = false;
			break;
		}
		while(dq.size() > 0) {
			left = dq.removeFirst();
			right = dq.removeLast();
			if(left != 'A' && left != 'C' && left != 'G' &&
			 left != 'T' && right != 'A' && right != 'C' &&
			 right != 'G' && right != 'T') {
				//Invalid character
				flag = false;
				break;
			}
			if((left == 'A' && right != 'T') || 
			 (left == 'T' && right != 'A') ||
			 (left == 'C' && right != 'G') ||
			 (left == 'G' && right != 'C')) {
				//Mismatch
				flag = false;
				break;
			}
		}
	}while(false);
	
	if(flag) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}
	return 0;
}
