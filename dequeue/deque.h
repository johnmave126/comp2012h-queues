/*
 * Dequeue for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * deque.h
 *
 * header file for dequeue
 */

#ifndef _DEQUE_H
#define _DEQUE_H

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

//Declaration of dequeue
template<typename T>
class Deque {
    public:
        //Declare iterator class
        class Iterator;
        
        /* default constructor/destructor */
        Deque();
        ~Deque();
        
        /* copy constructor */
        Deque(const Deque<T>& q);
        
        /* assign operator */
        Deque<T>& operator=(const Deque<T>& q);
        
        /*
         * isEmpty
         *
         * return true if the dequeue is empty
         */
        inline bool isEmpty() const;
        
        /*
         * size
         *
         * return the size of the dequeue
         */
        inline int size() const;
        
        /*
         * addFirst
         *
         * item: the item to add
         *
         * insert the item at the front of the dequeue
         */
        inline void addFirst(T item);
        
        /*
         * addLast
         *
         * item: the item to add
         *
         * insert the item at the end of the dequeue
         */
        inline void addLast(T item);
        
        /*
         * removeFirst
         *
         * throw runtime_error if trying to remove from an empty deque
         *
         * delete and return the first item in dequeue
         */
        T removeFirst();
        
        /*
         * removeLast
         *
         * throw runtime_error if trying to remove from an empty deque
         *
         * delete and return the last item in dequeue
         */
        T removeLast();
        
        /*
         * iterator
         *
         * return an iterator that can iterate from front to end
         */
        Iterator iterator() const;
        
    private:
        //Declare nested class Node
        class Node;
        
        //The pseudo head
        Node *head;
        
        //The pseudo end
        Node *end;
        
        //The size of deque
        int length;
};

//Iterator class
template<typename T>
class Deque<T>::Iterator {
    public:
        /* default constructor/destructor */
        Iterator();
        ~Iterator();
        
        /* conversion constructor
         *
         * The iterator will point to the first element of Deque
         * If the deque is empty, point to the first
         */
        Iterator(const Deque&);
        
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
         * a deque destroyed, or the iterator points to no node
         */
        T& operator*();
        T* operator->();
        
        /* dereference operators
         *
         * const version
         * throw runtime_error if the node pointed to belongs to
         * a deque destroyed, or the iterator points to no node
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
         * a deque destroyed, or the iterator points to no node.
         * If the iterator comes to the end of the deque, there 
         * will be no change to the iterator.
         */
        Iterator& operator++();
        Iterator operator++(int);
        
        /* prefix/postfix -- operator
         *
         * throw runtime_error if the node pointed to belongs to
         * a deque destroyed, or the iterator points to no node.
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
        inline void shiftNode(Node* node);
        
        //Pointer to element
        Node *elem;
};

//Node for double linked list
//All members are public for deque to modify
//These details are hided to outside classes
template<typename T>
class Deque<T>::Node {
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
        //Previous and Next node
        Node *prev;
        Node *next;
        //Reference count
        int cnt;
};

//Implementation begins
/* Deque Node */
template<typename T>
Deque<T>::Node::Node()
:data(NULL), prev(NULL), next(NULL),
 cnt(0) {
}

template<typename T>
Deque<T>::Node::~Node() {
    if(data) {
        delete data;
    }
}

template<typename T>
Deque<T>::Node::Node(const T& t)
:data(new T(t)), prev(NULL), next(NULL),
 cnt(0) {
}

template<typename T>
Deque<T>::Node::Node(const Deque<T>::Node& t)
:data(new T(*(t.data))), prev(NULL), next(NULL),
 cnt(0) {
}

template<typename T>
typename Deque<T>::Node& Deque<T>::Node::operator=(const Deque<T>::Node& t) {
    //Only copy data, leave prev/next and other stuff not changed
    data = new T(t.data);
    return *this;
}

template<typename T>
void Deque<T>::Node::decCnt(Deque<T>::Node *node) {
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

/* Deque Iterator */
template<typename T>
Deque<T>::Iterator::Iterator()
:elem(NULL) {
}

template<typename T>
Deque<T>::Iterator::~Iterator() {
    if(elem) {
        //Decrement reference count
        Node::decCnt(elem);
    }
}

template<typename T>
Deque<T>::Iterator::Iterator(const Deque<T>& q)
:elem(q.iterator().elem) {
    //Increace reference count
    elem->cnt++;
}

template<typename T>
Deque<T>::Iterator::Iterator(Deque<T>::Node& p)
:elem(&p) {
    //Increace reference count
    elem->cnt++;
}

template<typename T>
Deque<T>::Iterator::Iterator(const Deque<T>::Iterator& itr)
:elem(itr.findValid()) {
    if(elem) {
        elem->cnt++;
    }
}

template<typename T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator=(const Deque<T>::Iterator& itr) {
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
T& Deque<T>::Iterator::operator*() {
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
    if(!elem->prev && elem->next) {
        //head of a deque
        //Indicate empty deque
        throw runtime_error("Empty deque!");
    }
    if(!elem->next && elem->prev) {
        //end of a deque
        throw runtime_error("End of deque!");
    }
    return *(elem->data);
}

template<typename T>
T* Deque<T>::Iterator::operator->() {
    //Reuse operator*
    return &(*(*this));
}

template<typename T>
T& Deque<T>::Iterator::operator*() const{
    if(!elem) {
        throw runtime_error("Uninitialized iterator!");
    }
    Node* t = findValid();
    if(!t || elem != t) {
        //Not valid or pointed to a invalid one
        throw runtime_error("Iterator no longer valid!");
    }
    if(!elem->prev && elem->next) {
        //head of a deque
        //Indicate empty
        throw runtime_error("Empty deque!");
    }
    if(!elem->next && elem->prev) {
        //end of a deque
        throw runtime_error("End of deque!");
    }
    return *(elem->data);
}

template<typename T>
T* Deque<T>::Iterator::operator->() const{
    //Reuse operator*
    return &(*(*this));
}

template<typename T>
bool Deque<T>::Iterator::operator==(const Deque<T>::Iterator& itr) const {
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
bool Deque<T>::Iterator::operator!=(const Deque<T>::Iterator& itr) const {
    return !((*this) == itr);
}

template<typename T>
bool Deque<T>::Iterator::operator==(Deque<T>::Iterator& itr) const {
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
bool Deque<T>::Iterator::operator!=(Deque<T>::Iterator& itr) const {
    return !((*this) == itr);
}

template<typename T>
bool Deque<T>::Iterator::operator==(const Deque<T>::Iterator& itr) {
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
bool Deque<T>::Iterator::operator!=(const Deque<T>::Iterator& itr) {
    return !((*this) == itr);
}

template<typename T>
bool Deque<T>::Iterator::operator==(Deque<T>::Iterator& itr) {
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
bool Deque<T>::Iterator::operator!=(Deque<T>::Iterator& itr) {
    return !((*this) == itr);
}

template<typename T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator++() {
    if(!elem) {
        throw runtime_error("Uninitialized iterator!");
    }
    if(!elem->prev && elem->next) {
        //head of a deque
        //deque once empty
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
        //deque is empty
        throw runtime_error("Empty deque!");
    }
    //Move to next
    shiftNode(elem->next);
    return (*this);
}

template<typename T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator++(int) {
    //Reuse prefix ++
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator--() {
    if(!elem) {
        throw runtime_error("Uninitialized iterator!");
    }
    Node* t = findValid();
    //Shift to valid node
    shiftNode(t);
    if(!elem) {
        throw runtime_error("Iterator no longer valid!");
    }
    if(!elem->prev && elem->next) {
        //head of deque
        //deque is empty
        throw runtime_error("Empty deque!");
    }
    if(!elem->prev->prev) {
        //beginning of the deque
        throw runtime_error("At the beginning of the deque!");
    }
    //Move to previous
    shiftNode(elem->prev);
    return (*this);
}

template<typename T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator--(int) {
    //Reuse prefix --
    Iterator tmp = *this;
    --(*this);
    return tmp;
}

template<typename T>
typename Deque<T>::Node* Deque<T>::Iterator::findValid() const {
    if(elem->data) {
        //Valid
        return elem;
    }
    if(!elem->next && elem->prev) {
        //End of deque
        //preserve
        return elem;
    }
    Node* t = elem;
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
inline void Deque<T>::Iterator::shiftNode(Deque<T>::Node* node) {
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

/* Deque */
template<typename T>
Deque<T>::Deque()
:head(new Node()), end(new Node()),
 length(0) {
    //Generate an empty list
    head->next = end;
    end->prev = head;
    head->cnt++;
    end->cnt++;
}

template<typename T>
Deque<T>::~Deque() {
    Node *t = head;
    Node *p;
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
Deque<T>::Deque(const Deque<T>& q)
:head(new typename Deque<T>::Node()),
 end(new typename Deque<T>::Node()),
 length(0) {
    Node *t;
    for(t = q.head->next; t->next; t = t->next) {
        //Iterate over the list to do deep copy
        addLast(*(t->data));
    }
}

template<typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& q) {
    Node *t;
    //Empty the deque
    while(!isEmpty()) {
        removeFirst();
    }
    for(t = q.head->next; t->next; t = t->next) {
        //Iterate over the list to do deep copy
        addLast(*(t->data));
    }
    return (*this);
}

template<typename T>
inline bool Deque<T>::isEmpty() const {
    return head->next == end;
}

template<typename T>
inline int Deque<T>::size() const {
    return length;
}

template<typename T>
inline void Deque<T>::addFirst(T item) {
    Node *t = new Node(item);
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
inline void Deque<T>::addLast(T item) {
    Node *t = new Node(item);
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
T Deque<T>::removeFirst() {
    Node *t;
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
    Deque<T>::Node::decCnt(t);
    //Decrease size
    length--;
    return temp;
}

template<typename T>
T Deque<T>::removeLast() {
    Node *t;
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
    Deque<T>::Node::decCnt(t);
    //Decrease size
    length--;
    return temp;
}

template<typename T>
typename Deque<T>::Iterator Deque<T>::iterator() const {
    if(isEmpty()) {
        return Iterator(*head);
    }
    return Iterator(*(head->next));
}

#endif
