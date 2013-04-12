/*
 * Dequeue for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * main_deque.cpp
 *
 * To check the correctness of deque
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include "deque.h"

using namespace std;

void test_suite1() {
	//Test the correctness of basic operation
	int i;
	Deque<int> q;
	Deque<int>::Iterator itr;
	
	cout << "Begin Test Suite 1:" << endl;
	
	q.addFirst(1);
	q.addFirst(2);
	q.addFirst(3);
	q.addLast(4);
	q.addLast(5);
	q.addLast(6);
	q.addFirst(7);
	q.addLast(8);
	q.addFirst(9);
	q.addLast(10);
	
	itr = q.iterator();
	cout << "deque: " << q.size() << endl;
	for(i = 0; i < q.size(); i++, ++itr) {
		cout << (*itr) << endl;
	}
	cout << endl;
	
	//Test removing
	cout << "removing: " << q.removeFirst() << endl;
	cout << "removing: " << q.removeFirst() << endl;
	cout << "removing: " << q.removeLast() << endl;
	cout << "removing: " << q.removeLast() << endl;
	cout << "removing: " << q.removeFirst() << endl;
	cout << "removing: " << q.removeLast() << endl;
	cout << "removing: " << q.removeFirst() << endl;
	
	itr = q.iterator();
	cout << "deque: " << q.size() << endl;
	for(i = 0; i < q.size(); i++, ++itr) {
		cout << (*itr) << endl;
	}
	cout << endl;
	
	cout << "removing: " << q.removeFirst() << endl;
	cout << "removing: " << q.removeFirst() << endl;
	cout << "removing: " << q.removeLast() << endl;
	cout << "deque: " << q.size() << endl;
	
	//Empty now, test empty exception
	try {
		cout << "removing: " << q.removeFirst() << endl;
	}
	catch(runtime_error& e) {
		cerr << "exception caught: " << e.what() << '\n';
	}
	
	cout << "End Test Suite 1" << endl << endl;
}

void test_suite2() {
	//Test the correctness of basic iterator operation
	int i;
	Deque<int> q;
	Deque<int>::Iterator itr;
	
	cout << "Begin Test Suite 2:" << endl;
	
	q.addFirst(1);
	q.addFirst(2);
	q.addFirst(3);
	q.addLast(4);
	q.addLast(5);
	q.addLast(6);
	q.addFirst(7);
	q.addLast(8);
	q.addFirst(9);
	q.addLast(10);
	
	//Test iteration from first to last
	itr = q.iterator();
	cout << "deque: " << q.size() << endl;
	for(i = 0; i < q.size(); i++, ++itr) {
		cout << (*itr) << endl;
	}
	try {
		itr++;
	}
	catch(runtime_error &e) {
		cerr << "exception caught: " << e.what() << '\n';
	}
	cout << endl;
	
	//Test iteration from last to first
	for(i = 0; i < q.size(); i++, --itr) {
		try {
			cout << (*itr) << endl;
		}
		catch(runtime_error &e) {
			cerr << "exception caught: " << e.what() << '\n';
		}
	}
	try {
		itr--;
	}
	catch(runtime_error &e) {
		cerr << "exception caught: " << e.what() << '\n';
	}
	cout << endl;
	
	//Test bi-direction move
	itr++;
	cout << (*itr) << endl;
	++itr;
	cout << (*itr) << endl;
	++itr;
	++itr;
	--itr;
	cout << (*itr) << endl;
	itr--;
	cout << (*itr) << endl;
	cout << endl;
	
	//Test auto ajustment
	while(q.size() > 1) {
		q.removeFirst();
	}
	try {
		cout << (*itr) << endl;
	}
	catch(runtime_error &e) {
		cerr << "exception caught: " << e.what() << '\n';
	}
	try {
		itr++;
	}
	catch(runtime_error &e) {
		cerr << "exception caught: " << e.what() << '\n';
	}
	
	//Test empty exception
	q.removeFirst();
	try {
		cout << (*itr) << endl;
	}
	catch(runtime_error &e) {
		cerr << "exception caught: " << e.what() << '\n';
	}
	try {
		itr++;
	}
	catch(runtime_error &e) {
		cerr << "exception caught: " << e.what() << '\n';
	}
	
	cout << "End Test Suite 2" << endl << endl;
}

int main(void){
	srand(time(0));
	
	test_suite1();
	test_suite2();
}
