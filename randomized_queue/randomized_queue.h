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

using std::runtime_error;

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
		Node *arr;
		
		//The size of randomized queue
		int length;
		
		//The array size of the inner array
		int arr_size;
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
		
		/* conversion constructor
		 *
		 * The iterator will point to the node specified
		 */
		Iterator(Node&);
		
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
		 *
		 * const to const comparison
		 * if any of the iterator compared is not initialized or not valid
		 * false will be returned
		 */
		bool operator==(const Iterator&) const;
		bool operator!=(const Iterator&) const;
		
		/* comparison operators
		 *
		 * const to non-const comparison
		 * if any of the iterator compared is not initialized or not valid
		 * false will be returned
		 */
		bool operator==(Iterator&) const;
		bool operator!=(Iterator&) const;
		
		/* comparison operators
		 *
		 * non-const to const comparison
		 * if any of the iterator compared is not initialized or not valid
		 * false will be returned
		 */
		bool operator==(const Iterator&);
		bool operator!=(const Iterator&);
		
		/* comparison operators
		 *
		 * non-const to non-const comparison
		 * if any of the iterator compared is not initialized or not valid
		 * false will be returned
		 */
		bool operator==(Iterator&);
		bool operator!=(Iterator&);
		
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
		 * node: the node to start finding
		 *
		 * return the address of the nearest valid node found
		 * NULL for none found.
		 */
		Node* findValid() const;
		
		/*
		 * shiftNode
		 *
		 * node: the node to change to
		 *
		 * change the node the iterator pointing to to node
		 */
		void shiftNode(Node* node);
		
		//Pointer to random element array
		Node *arr_elem;
		
		//size fo the array
		int size_arr;
};

//Node for double linked list
//All members are public for randomized queue to modify
//These details are hided to outside classes
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
:data(new T(*(t.data))), prev(NULL), next(NULL),
 cnt(0) {
}

template<typename T>
typename RandomizedQueue<T>::Node& RandomizedQueue<T>::Node::operator=(const RandomizedQueue<T>::Node& t) {
	//Only copy data, leave prev/next and other stuff not changed
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
		//Recycle the prev node if applicable
		if(node->prev) {
			decCnt(node->prev);
		}
		//Recycle the next node if applicable
		if(node->next) {
			decCnt(node->next);
		}
		//Delete the node
		delete node;
	}
}

/* RandomizedQueue Iterator */
template<typename T>
RandomizedQueue<T>::Iterator::Iterator()
:elem(NULL) {
}

template<typename T>
RandomizedQueue<T>::Iterator::~Iterator() {
	if(elem) {
		//Decrement reference count
		Node::decCnt(elem);
	}
}

template<typename T>
RandomizedQueue<T>::Iterator::Iterator(const RandomizedQueue<T>& q)
:elem(q.iterator().elem) {
	//Increace reference count
	elem->cnt++;
}

template<typename T>
RandomizedQueue<T>::Iterator::Iterator(RandomizedQueue<T>::Node& p)
:elem(&p) {
	//Increace reference count
	elem->cnt++;
}

template<typename T>
typename RandomizedQueue<T>::Iterator& RandomizedQueue<T>::Iterator::operator=(const RandomizedQueue<T>::Iterator& itr) {
	if(elem) {
		//Decrement reference count
		Node::decCnt(elem);
	}
	//Copy and increase reference count
	elem = itr.findValid();
	if(elem) {
		elem->cnt++;
	}
	return (*this);
}

template<typename T>
T& RandomizedQueue<T>::Iterator::operator*() {
	if(!elem) {
		throw runtime_error("Uninitialized iterator!");
	}
	Node* t = findValid();
	if(!t) {
		//Clear the iterator
		Node::decCnt(elem);
		elem = NULL;
		throw runtime_error("Iterator no longer valid!");
	}
	shiftNode(t);
	if(!elem->data) {
		//head or end of a deque
		throw runtime_error("Empty deque!");
	}
	return *(elem->data);
}

template<typename T>
T* RandomizedQueue<T>::Iterator::operator->() {
	//Reuse operator*
	return &(*(*this));
}

template<typename T>
T& RandomizedQueue<T>::Iterator::operator*() const{
	if(!elem) {
		throw runtime_error("Uninitialized iterator!");
	}
	Node* t = findValid();
	if(!t || elem != t) {
		//Not valid or pointed to a invalid one
		throw runtime_error("Iterator no longer valid!");
	}
	if(!elem->data) {
		//head or end of a deque
		throw runtime_error("Empty deque!");
	}
	return *(elem->data);
}

template<typename T>
T* RandomizedQueue<T>::Iterator::operator->() const{
	//Reuse operator*
	return &(*(*this));
}

template<typename T>
bool RandomizedQueue<T>::Iterator::operator==(const RandomizedQueue<T>::Iterator& itr) const {
	if(!elem || !itr.elem) {
		return false;
	}
	Node* t1 = findValid();
	Node* t2 = itr.findValid();
	if(!t1 || !t2 || t1 != elem || t2 != itr.elem) {
		return false;
	}
	return t1 == t2;
}

template<typename T>
bool RandomizedQueue<T>::Iterator::operator!=(const RandomizedQueue<T>::Iterator& itr) const {
	return !((*this) == itr);
}

template<typename T>
bool RandomizedQueue<T>::Iterator::operator==(RandomizedQueue<T>::Iterator& itr) const {
	if(!elem || !itr.elem) {
		return false;
	}
	Node* t1 = findValid();
	Node* t2 = itr.findValid();
	//Change the current node if needed
	itr.shiftNode(t2);
	if(!t1 || !t2 || t1 != elem) {
		return false;
	}
	return t1 == t2;
}

template<typename T>
bool RandomizedQueue<T>::Iterator::operator!=(RandomizedQueue<T>::Iterator& itr) const {
	return !((*this) == itr);
}

template<typename T>
bool RandomizedQueue<T>::Iterator::operator==(const RandomizedQueue<T>::Iterator& itr) {
	if(!elem || !itr.elem) {
		return false;
	}
	Node* t1 = findValid();
	Node* t2 = itr.findValid();
	//Change the current node if needed
	shiftNode(t1);
	if(!t1 || !t2 || t2 != itr.elem) {
		return false;
	}
	return t1 == t2;
}

template<typename T>
bool RandomizedQueue<T>::Iterator::operator!=(const RandomizedQueue<T>::Iterator& itr) {
	return !((*this) == itr);
}

template<typename T>
bool RandomizedQueue<T>::Iterator::operator==(RandomizedQueue<T>::Iterator& itr) {
	if(!elem || !itr.elem) {
		return false;
	}
	Node* t1 = findValid();
	Node* t2 = itr.findValid();
	//Change the current node if needed
	shiftNode(t1);
	itr.shiftNode(t2);
	if(!t1 || !t2) {
		return false;
	}
	return t1 == t2;
}

template<typename T>
bool RandomizedQueue<T>::Iterator::operator!=(RandomizedQueue<T>::Iterator& itr) {
	return !((*this) == itr);
}

template<typename T>
typename RandomizedQueue<T>::Iterator& RandomizedQueue<T>::Iterator::operator++() {
	if(!elem) {
		throw runtime_error("Uninitialized iterator!");
	}
	if(!elem->prev && elem->next) {
		//head of a deque
		//randomized queue once empty
		if(elem->next->next) {
			//not empty
			shiftNode(elem->next->next);
		}
	}
	Node* t = findValid();
	//Shift to valid node
	shiftNode(t);
	if(!elem) {
		throw runtime_error("Iterator no longer valid!");
	}
	if(!elem->next && elem->prev) {
		//end of the deque
		throw runtime_error("At the end of the deque!");
	}
	if(!elem->data) {
		//head of deque
		//randomized queue is empty
		throw runtime_error("Empty deque!");
	}
	//Move to next
	shiftNode(elem->next);
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
	if(!elem) {
		throw runtime_error("Uninitialized iterator!");
	}
	Node* t = findValid();
	//Shift to valid node
	shiftNode(t);
	if(!elem) {
		throw runtime_error("Iterator no longer valid!");
	}
	if(!elem->data) {
		//head of deque
		//randomized queue is empty
		throw runtime_error("Empty deque!");
	}
	if(!elem->prev->prev) {
		//end of the deque
		throw runtime_error("At the beginning of the deque!");
	}
	//Move to previous
	shiftNode(elem->prev);
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
typename RandomizedQueue<T>::Node* RandomizedQueue<T>::Iterator::findValid() const {
	if(elem->data) {
		//Valid
		return elem;
	}
	if(!elem->next && elem->prev) {
		//End of deque
		//preserve
		return elem;
	}
	RandomizedQueue<T>::Node* t = elem;
	//Iterate forward
	while(!t->data && t->next) {
		t = t->next;
	}
	if(t->data) {
		//Valid
		return t;
	}
	//Now t->next is null
	if(!t->prev) {
		//destroyed deque
		return NULL;
	}
	//End of deque
	//Go backwards
	return t->prev;
}

template<typename T>
void RandomizedQueue<T>::Iterator::shiftNode(RandomizedQueue<T>::Node* node) {
	if(node) {
		//Shift to a existing node
		//Thread safety
		node->cnt++;
		Node::decCnt(elem);
		elem = node;
	}
	else {
		//Release current element
		Node::decCnt(elem);
		elem = NULL;
	}
}

/* RandomizedQueue */
template<typename T>
RandomizedQueue<T>::RandomizedQueue()
:head(new Node()), end(new Node()),
 length(0) {
	//Generate an empty list
	head->next = end;
	end->prev = head;
	head->cnt++;
	end->cnt++;
}

template<typename T>
RandomizedQueue<T>::~RandomizedQueue() {
	RandomizedQueue<T>::Node *t = head;
	RandomizedQueue<T>::Node *p;
	while(t) {
		p = t;
		t = t->next;
		//Make the node independent
		p->prev = NULL;
		p->next = NULL;
		//Free the data
		if(p->data) {
			delete p->data;
			p->data = NULL;
		}
		//Decrease the reference count
		Node::decCnt(p);
	}
}

template<typename T>
RandomizedQueue<T>::RandomizedQueue(const RandomizedQueue<T>& q)
:head(new RandomizedQueue<T>::Node()), end(new RandomizedQueue<T>::Node()),
 length(0) {
 	RandomizedQueue<T>::Node *t;
 	for(t = q.head->next; t->next; t = t->next) {
 		//Iterate over the list to do deep copy
 		addLast(t->data);
 	}
}

template<typename T>
RandomizedQueue<T>& RandomizedQueue<T>::operator=(const RandomizedQueue<T>& q) {
 	RandomizedQueue<T>::Node *t;
	//Empty the deque
	while(!isEmpty()) {
		removeFirst();
	}
 	for(t = q.head->next; t->next; t = t->next) {
 		//Iterate over the list to do deep copy
 		addLast(t->data);
 	}
}

template<typename T>
bool RandomizedQueue<T>::isEmpty() const {
	return head->next == end;
}

template<typename T>
int RandomizedQueue<T>::size() const {
	return length;
}

template<typename T>
void RandomizedQueue<T>::addFirst(T item) {
	RandomizedQueue<T>::Node *t = new RandomizedQueue<T>::Node(item);
	//Increase reference count
	t->cnt++;
	//Link to head->next
	t->next = head->next;
	head->next->prev = t;
	//Link to head
	t->prev = head;
	head->next = t;
	//Increase size
	length++;
}

template<typename T>
void RandomizedQueue<T>::addLast(T item) {
	RandomizedQueue<T>::Node *t = new RandomizedQueue<T>::Node(item);
	//Increase reference count
	t->cnt++;
	//Link to end->prev
	t->prev = end->prev;
	end->prev->next = t;
	//Link to end
	t->next = end;
	end->prev = t;
	//Increase size
	length++;
}

template<typename T>
T RandomizedQueue<T>::removeFirst() {
	RandomizedQueue<T>::Node *t;
	T temp;
	if(isEmpty()) {
		throw runtime_error("Trying to remove from an empty deque!");
	}
	//Detach the first node
	t = head->next;
	t->next->prev = head;
	head->next = t->next;
	//Increase the reference count of head and head->next
	head->cnt++;
	head->next->cnt++;
	//Store the data into temp
	temp = *(t->data);
	//Free the memory of data
	delete t->data;
	t->data = NULL;
	//Decrease the reference count of the detached node
	RandomizedQueue<T>::Node::decCnt(t);
	//Decrease size
	length--;
	return temp;
}

template<typename T>
T RandomizedQueue<T>::removeLast() {
	RandomizedQueue<T>::Node *t;
	T temp;
	if(isEmpty()) {
		throw runtime_error("Trying to remove from an empty deque!");
	}
	//Detach the last node
	t = end->prev;
	t->prev->next = end;
	end->prev = t->prev;
	//Increase the reference count of head and head->next
	end->cnt++;
	end->prev->cnt++;
	//Store the data into temp
	temp = *(t->data);
	//Free the memory of data
	delete t->data;
	t->data = NULL;
	//Decrease the reference count of the detached node
	RandomizedQueue<T>::Node::decCnt(t);
	//Decrease size
	length--;
	return temp;
}

template<typename T>
typename RandomizedQueue<T>::Iterator RandomizedQueue<T>::iterator() {
	if(isEmpty()) {
		return Iterator(*head);
	}
	return Iterator(*(head->next));
}

#endif
