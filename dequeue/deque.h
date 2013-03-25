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

//Declaration of dequeue
template<typename T>
class Deque {
	private:
		//Type definition
		//Node for double linked list
		struct node {
			//Store the data
			T *data;
			//Previous and Next node
			node *prev;
			node *next;
			//Reference count
			int cnt;
			//Detached flag
			bool valid;
		};
	
	public:
		/* default constructor/destructor */
		Deque();
		~Deque();
		
		/*
		 * isEmpty
		 *
		 * return true if the dequeue is empty
		 */
		bool isEmpty() const;
		
		/*
		 * size
		 *
		 * return the size of the dequeue
		 */
		int size() const;
		
		/*
		 * addFirst
		 *
		 * item: the item to add
		 *
		 * insert the item at the front of the dequeue
		 */
		void addFirst(T item);
		
		/*
		 * addLast
		 *
		 * item: the item to add
		 *
		 * insert the item at the end of the dequeue
		 */
		void addLast(T item);
		
		/*
		 * removeFirst
		 *
		 * delete and return the first item in dequeue
		 */
		T removeFirst();
		
		/*
		 * removeLast
		 *
		 * delete and return the last item in dequeue
		 */
		T removeLast();
		
		//Iterator class
		class Iterator {
			public:
				
			
			private:
				//Pointer to element
				node *elem;
		};
		//Give permission to Iterator
		friend class Iterator;
		
		//The pseudo end
		const node *end;
		
		//The pointer to head
		node *head;
};

#endif
