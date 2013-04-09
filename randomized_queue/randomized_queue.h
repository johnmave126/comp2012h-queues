/*
 * Randomized Queue for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * randomized_queue.h
 *
 * header file for randomized queue
 */

#ifndef _RANDOMIZED_QUEUE_H
#define _RANDOMIZED_QUEUE_H

#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using std::runtime_error;
using std::sort;

#ifndef RANDOMIZED_QUEUE_BASE
#define RANDOMIZED_QUEUE_BASE 32
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef NULL
#define NULL 0
#endif

//Declaration of randomized queue
template<typename T>
class RandomizedQueue {
	public:
		//Declare iterator class
		class Iterator;
		
		/* default constructor/destructor */
		RandomizedQueue();
		~RandomizedQueue();
		
		/* copy constructor */
		RandomizedQueue(const RandomizedQueue<T>& q);
		
		/* assign operator */
		RandomizedQueue<T>& operator=(const RandomizedQueue<T>& q);
		
		/*
		 * isEmpty
		 *
		 * return true if the randomized queue is empty
		 */
		bool isEmpty() const;
		
		/*
		 * size
		 *
		 * return the size of the randomized queue
		 */
		int size() const;
		
		/*
		 * enqueue
		 *
		 * item: the item to add
		 *
		 * insert the item in the queue
		 */
		void enqueue(T item);
		
		/*
		 * dequeue
		 *
		 * throw runtime_error if trying to remove from an queue
		 *
		 * delete and return a random item in randomized queue
		 */
		T dequeue();
		
		/*
		 * sample
		 *
		 * throw runtime_error if trying to sample from an empty deque
		 *
		 * return a random item in randomized queue
		 */
		T sample() const;
		
		/*
		 * iterator
		 *
		 * return an iterator that can iterate from front to end
		 */
		Iterator iterator();
		
	private:
		//Declare nested class Node
		class Node;
		
		//The array to store data
		Node **arr_elem;
		
		//The size of randomized queue
		int length;
		
		//The array size of the inner array
		int size_arr;
};

//Iterator class
template<typename T>
class RandomizedQueue<T>::Iterator {
	public:
		/* default constructor/destructor */
		Iterator();
		~Iterator();
		
		/* conversion constructor
		 *
		 * The iterator will point to the first element of RandomizedQueue
		 * If the randomized queue is empty, point to the first
		 */
		Iterator(const RandomizedQueue&);
		
		/* copy constructor */
		Iterator(const Iterator&);
		
		/* assign operator */
		Iterator& operator=(const Iterator&);
		
		/* dereference operators
		 *
		 * non-const version
		 * throw runtime_error if the node pointed to belongs to
		 * a randomized queue destroyed, or the iterator points to no node
		 */
		T& operator*();
		T* operator->();
		
		/* dereference operators
		 *
		 * const version
		 * throw runtime_error if the node pointed to belongs to
		 * a randomized queue destroyed, or the iterator points to no node
		 */
		T& operator*() const;
		T* operator->() const;
		
		/* comparison operators
		 * I found that comparison betwwen Iterators in randomized queue
		 * is never pratical. So I omit the definition of comparison operator
		 * for this.
		 */
		
		/* prefix/postfix ++ operator
		 *
		 * throw runtime_error if the node pointed to belongs to
		 * a randomized queue destroyed, or the iterator points to no node.
		 * If the iterator comes to the end of the deque, there 
		 * will be no change to the iterator.
		 */
		Iterator& operator++();
		Iterator operator++(int);
		
		/* prefix/postfix -- operator
		 *
		 * throw runtime_error if the node pointed to belongs to
		 * a randomized queue destroyed, or the iterator points to no node.
		 * If the iterator comes to the beginning of the deque, there 
		 * will be no change to the iterator.
		 */
		Iterator& operator--();
		Iterator operator--(int);
		
	private:
		/*
		 * findValid
		 *
		 * return the index of the nearest valid node found
		 * size_arr for none found.
		 */
		int findValid() const;
		
		/*
		 * findValidRev
		 *
		 * return the index of the nearest valid node found
		 * size_arr for none found.
		 * The reverse version of the above function.
		 */
		int findValidRev() const;
		
		/*
		 * shiftNode
		 *
		 * idx: the index of the node to change to
		 *
		 * change the node the iterator pointing to to node
		 */
		void shiftNode(int idx);
		
		/* used for sort */
		struct _rnd_s {
			int number;
			int idx;
		};
		
		static bool cmp_rnd_s(const _rnd_s& a, const _rnd_s& b) {
			return (a.number < b.number);
		}
		
		//Pointer to random element array
		Node **arr_elem;
		
		//size fo the array
		int size_arr;
		
		//current location
		int loc;
};

//Node for array
//All members are public for randomized queue to modify
//These details are hidden to outside classes
template<typename T>
class RandomizedQueue<T>::Node {
	public:
		/* default constructor/destructor */
		Node();
		~Node();
		
		/* conversion constructor */
		Node(const T&);
		
		/* copy constructor */
		Node(const Node&);
		
		/* assign operator */
		Node& operator=(const Node&);
		
		/*
		 * decCnt
		 *
		 * node: the node to be decreased count
		 *
		 * static function
		 * Decrease reference count of a node. Free the memory if necessary
		 */
		static void decCnt(Node *node);
		
		//Store the data
		T *data;
		
		//Reference count
		int cnt;
};

//Implementation begins
/* RandomizedQueue Node */
template<typename T>
RandomizedQueue<T>::Node::Node()
:data(NULL), cnt(0) {
}

template<typename T>
RandomizedQueue<T>::Node::~Node() {
	if(data) {
		delete data;
	}
}

template<typename T>
RandomizedQueue<T>::Node::Node(const T& t)
:data(new T(t)), cnt(0) {
}

template<typename T>
RandomizedQueue<T>::Node::Node(const RandomizedQueue<T>::Node& t)
:data(new T(*(t.data))), cnt(0) {
}

template<typename T>
typename RandomizedQueue<T>::Node& RandomizedQueue<T>::Node::operator=(const RandomizedQueue<T>::Node& t) {
	data = new T(t.data);
	return *this;
}

template<typename T>
void RandomizedQueue<T>::Node::decCnt(RandomizedQueue<T>::Node *node) {
	node->cnt--;
	if(node->cnt == 0) {
		//Recycle the memory
		if(node->data) {
			//Free data space
			delete node->data;
			node->data = NULL;
		}
		//Delete the node
		delete node;
	}
}

/* RandomizedQueue Iterator */
template<typename T>
RandomizedQueue<T>::Iterator::Iterator()
:arr_elem(NULL), size_arr(0), loc(0) {
}

template<typename T>
RandomizedQueue<T>::Iterator::~Iterator() {
	if(arr_elem) {
		//Decrement reference count
		if(loc < size_arr) {
			Node::decCnt(arr_elem[loc]);
		}
		delete [] arr_elem;
	}
}

template<typename T>
RandomizedQueue<T>::Iterator::Iterator(const RandomizedQueue<T>& q)
:arr_elem(new RandomizedQueue<T>::Node*[q.size()]),
 size_arr(q.size()), loc(0) {
	int i;
	if(size_arr == 0) {
		return;
	}
	_rnd_s *shuffle = new _rnd_s[q.size()];
	//Generate a iterating sequence
	//First generate a random number array
	for(i = 0; i < size_arr; i++) {
		shuffle[i].number = rand();
		shuffle[i].idx = i;
	}
	//Sort it to get random idx sequence
	sort(shuffle, shuffle + size_arr, cmp_rnd_s);
	for(i = 0; i < q.size(); i++) {
		arr_elem[i] = q.arr_elem[shuffle[i].idx];
	}
	//Initialize reference count
	arr_elem[loc]->cnt++;
	delete [] shuffle;
}

template<typename T>
typename RandomizedQueue<T>::Iterator& RandomizedQueue<T>::Iterator::operator=(const RandomizedQueue<T>::Iterator& itr) {
	int i;
	if(arr_elem) {
		if(loc < size_arr) {
			//Decrement reference count
			Node::decCnt(arr_elem[loc]);
		}
		delete [] arr_elem;
		arr_elem = NULL;
	}
	//Copy and increase reference count
	size_arr = itr.size_arr;
	loc = itr.findValid();
	if(loc < size_arr) {
		itr.arr_elem[loc]->cnt++;
	}
	if(size_arr > 0) {
		arr_elem = new Node*[size_arr];
		for(i = 0; i < size_arr; i++) {
			arr_elem[i] = itr.arr_elem[i];
		}
	}
	return (*this);
}

template<typename T>
T& RandomizedQueue<T>::Iterator::operator*() {
	if(!arr_elem) {
		throw runtime_error("Uninitialized iterator!");
	}
	int tid = findValid();
	shiftNode(tid);
	if(tid >= size_arr) {
		//End of a queue
		throw runtime_error("End of randomized queue!");
	}
	return *(arr_elem[loc]->data);
}

template<typename T>
T* RandomizedQueue<T>::Iterator::operator->() {
	//Reuse operator*
	return &(*(*this));
}

template<typename T>
T& RandomizedQueue<T>::Iterator::operator*() const{
	if(!arr_elem) {
		throw runtime_error("Uninitialized iterator!");
	}
	int tid = findValid();
	if(loc != tid) {
		//Not valid or pointed to a invalid one
		throw runtime_error("Iterator no longer valid!");
	}
	if(loc >= size_arr) {
		//End of a queue
		throw runtime_error("End of randomized queue!");
	}
	return *(arr_elem[loc]->data);
}

template<typename T>
T* RandomizedQueue<T>::Iterator::operator->() const{
	//Reuse operator*
	return &(*(*this));
}

template<typename T>
typename RandomizedQueue<T>::Iterator& RandomizedQueue<T>::Iterator::operator++() {
	int new_loc;
	if(!arr_elem) {
		throw runtime_error("Uninitialized iterator!");
	}
	if(size_arr == 0) {
		throw runtime_error("Empty randomized queue!");
	}
	new_loc = findValid();
	//Shift to valid node
	shiftNode(new_loc);
	if(loc == size_arr) {
		throw runtime_error("At the end of the randomized queue!");
	}
	loc++;
	new_loc = findValid();
	shiftNode(new_loc);
	return (*this);
}

template<typename T>
typename RandomizedQueue<T>::Iterator RandomizedQueue<T>::Iterator::operator++(int) {
	//Reuse prefix ++
	Iterator tmp = *this;
	(*this)++;
	return tmp;
}

template<typename T>
typename RandomizedQueue<T>::Iterator& RandomizedQueue<T>::Iterator::operator--() {
	int new_loc;
	if(!arr_elem) {
		throw runtime_error("Uninitialized iterator!");
	}
	if(size_arr == 0) {
		throw runtime_error("Empty randomized queue!");
	}
	new_loc = findValid();
	//Shift to valid node
	shiftNode(new_loc);
	if(loc == 0) {
		throw runtime_error("At the beginning of the randomized queue!");
	}
	loc--;
	new_loc = findValidRev();
	if(new_loc < 0) {
		//Restore
		loc++;
		throw runtime_error("At the beginning of the randomized queue!");
	}
	shiftNode(new_loc);
	return (*this);
}

template<typename T>
typename RandomizedQueue<T>::Iterator RandomizedQueue<T>::Iterator::operator--(int) {
	//Reuse prefix --
	Iterator tmp = *this;
	(*this)--;
	return tmp;
}

template<typename T>
int RandomizedQueue<T>::Iterator::findValid() const {
	int i;
	if(loc == size_arr) {
		//End of iteration
		//Preserve
		return loc;
	}
	if(arr_elem[loc]->data) {
		//Valid
		return loc;
	}
	//Move forward
	for(i = loc + 1; i < size_arr && !arr_elem[i]->data; i++) {
	}
	return i;
}

template<typename T>
int RandomizedQueue<T>::Iterator::findValidRev() const {
	int i;
	if(loc == size_arr) {
		//End of iteration
		//Preserve
		return loc;
	}
	if(arr_elem[loc]->data) {
		//Valid
		return loc;
	}
	//Move backward
	for(i = loc - 1; i >= 0 && !arr_elem[i]->data; i--) {
	}
	return i;
}

template<typename T>
void RandomizedQueue<T>::Iterator::shiftNode(int idx) {
	if(idx != size_arr) {
		//Shift to a existing node
		//Thread safety
		arr_elem[idx]->cnt++;
	}
	if(loc != size_arr) {
		//Release element
		Node::decCnt(arr_elem[loc]);
	}
	loc = idx;
}

/* RandomizedQueue */
template<typename T>
RandomizedQueue<T>::RandomizedQueue()
:arr_elem(new RandomizedQueue<T>::Node*[RANDOMIZED_QUEUE_BASE]),
 length(0), size_arr(RANDOMIZED_QUEUE_BASE) {
 	//Reset array
 	memset(arr_elem, 0, size_arr * sizeof(Node*));
}

template<typename T>
RandomizedQueue<T>::~RandomizedQueue() {
	int i;
	if(arr_elem) {
		for(i = 0; i < length; i++) {
			//Free the data
			if(arr_elem[i]->data) {
				delete arr_elem[i]->data;
				arr_elem[i]->data = NULL;
			}
			//Decrease the reference count
			Node::decCnt(arr_elem[i]);
		}
		delete [] arr_elem;
	}
}

template<typename T>
RandomizedQueue<T>::RandomizedQueue(const RandomizedQueue<T>& q)
:arr_elem(new RandomizedQueue<T>::Node*[q.size_arr]),
 length(0), size_arr(q.size_arr) {
 	int i;
 	for(i = 0; i < q.length; i++) {
 		//Iterate over the list to do deep copy
 		enqueue(*(q.arr_elem[i]->data));
 	}
 	//Clean the rest
 	memset(arr_elem + i, 0, (size_arr - i) * sizeof(Node*));
}

template<typename T>
RandomizedQueue<T>& RandomizedQueue<T>::operator=(const RandomizedQueue<T>& q) {
 	int i;
	//Empty the randomized queue
	for(i = 0; i < length; i++) {
		Node::decCnt(arr_elem[i]);
	}
 	//Clean the pointer
 	memset(arr_elem, 0, length * sizeof(Node*));
	length = 0;
	if(q.size_arr > size_arr) {
		size_arr = q.size_arr;
		delete [] arr_elem;
		arr_elem = new Node**[size_arr];
	}
 	for(i = 0; i < q.length; i++) {
 		//Iterate over the array to do deep copy
 		enqueue(*(q.arr_elem[i]->data));
 	}
}

template<typename T>
bool RandomizedQueue<T>::isEmpty() const {
	return length == 0;
}

template<typename T>
int RandomizedQueue<T>::size() const {
	return length;
}

template<typename T>
void RandomizedQueue<T>::enqueue(T item) {
	Node **new_mem;
	Node *t = new Node(item);
	//Increase reference count
	t->cnt++;
	//Test space
	if(length == size_arr) {
		//Enlarge the array
		new_mem = new Node*[size_arr<<1];
		memcpy(new_mem, arr_elem, size_arr * sizeof(Node*));
		memset(new_mem + size_arr, 0, size_arr * sizeof(Node*));
		size_arr <<= 1;
		delete [] arr_elem;
		arr_elem = new_mem;
	}
	//Increase size
	arr_elem[length] = t;
	length++;
}

template<typename T>
T RandomizedQueue<T>::dequeue() {
	int rm_id;
	Node *t;
	Node **new_mem;
	T temp;
	if(isEmpty()) {
		throw runtime_error("Trying to remove from an empty deque!");
	}
	rm_id = (int)((1.0 * rand() / RAND_MAX) * length);
	//Swap this with the last one in the array
	t = arr_elem[rm_id];
	arr_elem[rm_id] = arr_elem[length - 1];
	//Shrink
	length--;
	//Test space
	if(size_arr > RANDOMIZED_QUEUE_BASE && (size_arr >> 2) >= length) {
		//Shrink array space
		new_mem = new Node*[size_arr >> 1];
		memcpy(new_mem, arr_elem, (size_arr>>1) * sizeof(Node*));
		size_arr >>= 1;
		delete [] arr_elem;
		arr_elem = new_mem;
	}
	temp = *(t->data);
	arr_elem[length] = NULL;
	delete t->data;
	t->data = NULL;
	Node::decCnt(t);
	return temp;
}

template<typename T>
T RandomizedQueue<T>::sample() const {
	int rm_id;
	rm_id = (int)((1.0 * rand() / RAND_MAX) * length);
	return *(arr_elem[rm_id]->data);
}

template<typename T>
typename RandomizedQueue<T>::Iterator RandomizedQueue<T>::iterator() {
	if(isEmpty()) {
		return Iterator();
	}
	return Iterator(*(this));
}

#endif
