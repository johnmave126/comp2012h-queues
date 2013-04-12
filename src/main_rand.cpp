/*
 * RandomizedQueueue for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * main_rand.cpp
 *
 * To check the correctness of randomized queue
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include "randomized_queue.h"

using namespace std;

void test_suite1() {
	//Test the correctness of basic operation
	int i;
	RandomizedQueue<int> q;
	RandomizedQueue<int>::Iterator itr;
	
	cout << "Begin Test Suite 1:" << endl;
	
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);
	q.enqueue(6);
	q.enqueue(7);
	q.enqueue(8);
	q.enqueue(9);
	q.enqueue(10);
	
	itr = q.iterator();
	cout << "randomized queue: " << q.size() << endl;
	for(i = 0; i < q.size(); i++, ++itr) {
		cout << (*itr) << endl;
	}
	cout << endl;
	
	//Test sampling
	for(i = 0; i < 5; i++) {
		cout << q.sample() << endl;
	}
	
	//Test removing
	cout << "removing: " << q.dequeue() << endl;
	cout << "removing: " << q.dequeue() << endl;
	cout << "removing: " << q.dequeue() << endl;
	cout << "removing: " << q.dequeue() << endl;
	cout << "removing: " << q.dequeue() << endl;
	cout << "removing: " << q.dequeue() << endl;
	cout << "removing: " << q.dequeue() << endl;
	
	itr = q.iterator();
	cout << "randomized queue: " << q.size() << endl;
	for(i = 0; i < q.size(); i++, ++itr) {
		cout << (*itr) << endl;
	}
	cout << endl;
	
	cout << "removing: " << q.dequeue() << endl;
	cout << "removing: " << q.dequeue() << endl;
	cout << "removing: " << q.dequeue() << endl;
	cout << "randomized queue: " << q.size() << endl;
	
	//Empty now, test empty exception
	try {
		cout << "removing: " << q.dequeue() << endl;
	}
	catch(runtime_error& e) {
		cerr << "exception caught: " << e.what() << '\n';
	}
	
	cout << "End Test Suite 1" << endl << endl;
}

void test_suite2() {
	//Test the correctness of basic iterator operation
	int i;
	RandomizedQueue<int> q;
	RandomizedQueue<int>::Iterator itr;
	
	cout << "Begin Test Suite 2:" << endl;
	
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);
	q.enqueue(6);
	q.enqueue(7);
	q.enqueue(8);
	q.enqueue(9);
	q.enqueue(10);
	
	itr = q.iterator();
	cout << "randomized queue: " << q.size() << endl;
	for(i = 0; i < q.size(); i++, ++itr) {
		cout << (*itr) << endl;
	}
	cout << endl;
	
	//Second Test
	itr = q.iterator();
	cout << "randomized queue: " << q.size() << endl;
	for(i = 0; i < q.size(); i++, ++itr) {
		cout << (*itr) << endl;
	}
	cout << endl;
	
	//Backward
	cout << "randomized queue: " << q.size() << endl;
	for(i = 0; i < q.size(); i++, --itr) {
		try{
			cout << (*itr) << endl;
		}
		catch(runtime_error& e) {
			cerr << "exception caught: " << e.what() << '\n';
		}
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
		q.dequeue();
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
	q.dequeue();
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
