/**********************************************************************
 *  Randomized Queues and Deques
 **********************************************************************/

Name: TAN, Shuhao
ID: 20090398
Login: stanab
Hours to complete assignment (optional): 24


/**********************************************************************
 *  Explain briefly how you implemented the randomized queue and deque.
 *  Which data structure did you choose (array, linked list, etc.)
 *  and why?
 **********************************************************************/
The randomized queue uses array and deque uses double-linked list. The
reason to use array for randomized queue is that: the randomized queue
need to access one element randomly. So the data structure should have
high speed to random access an element. So I choose array. Deque needs
to flexibly insert and delete from the data structure. So I choose 
linked list. Since it is bi-direction, I choose double-linked list.


/**********************************************************************
 *  Briefly describe why any sequence of N randomized queue operations,
 *  starting from an empty randomized queue, takes O(N) time.
 **********************************************************************/
Examine all the operations accordingly:
enqueue:
    This operation involves two part: insert and ajust the size.
    Insert is simply to place the item at the last position of the array.
    Since array has O(1) random access time. So insert is O(1).
    Ajust the size is O(2N) = O(N) when the randomized queue needs to 
    enlarge itself. This happens when the space is not enough. However, 
    if we need to enlarge the array, suppose the size before is k, there
    should be at least k/2 enqueue operations. By amortized analysis, the
    ajustment is O(1).

    Thus, the enqueue is O(1).
dequeue:
    This operation also involves two part: delete and ajust the size
    Delete is tricky. Since the order of the elements in the array is
    not important as randomized queue, the algorithm is:
        1. swap the element to delete with the last element of array
        2. release the last element of array
        3. reduce the length of array
    So it achieve O(1) deletion.
    Ajust the size is O(N) when ajustment happens. Similarly, it needs 
    at least k/2 dequeue operation without ajustment when shrinking
    from 2k to k. So by amortized analysis, the ajustment is O(1).

    Thus, the dequeue is O(1)
isEmpty, size:
    These operations just return a number without manipulation. So they
    are O(1).
sample:
    A random number is generated. And the corresponding element is
    returned. So it is O(1)

As disscussed above, each operation is O(1) amortized. So any sequence
of N randomized queue operations, starting from an empty randomized
queue, takes O(N) time.

/**********************************************************************
 *  Briefly describe why each Deque operation takes O(1) time.
 **********************************************************************/
Examine all the operations accordingly:
isEmpty, size:
    These operations just return a number. So they are O(1)=O(N)
addFirst, addLast:
    I have a head node and a tail node for the double-linked list. 
    AddFirst is to insert a node after the head node, and addLast
    is to insert a node before the tail node. Since the access to 
    head and tail is O(1), these operations are O(1).
removeFirst, removeLast:
    This is similar to the operations above. Deletion from head and
    tail takes O(1) time.


/**********************************************************************
 *  How much memory (in bytes) does your data type use to store N items.
 *  Use tilde notation to simplify your answer. Use the memory requirements
 *  for a "typical machine" given in Lecture. In your analysis, don't include
 *  the memory for the items themselves (as this memory is allocated by
 *  the client and depends on the item type.
 *  For a typical machine, refer to page 11 of 
 *  http://www.cs.princeton.edu/courses/archive/spring10/cos226/lectures/02-14Analysis-2x2.pdf 
 **********************************************************************/

RandomizedQueue:
object overhead: 8 bytes
arr_elem Node**: 4 bytes (Assume pointer same as int)
length int: 4 bytes
size_arr int: 4 bytes

Overall: 20 bytes

Dequeue:
object overhead: 8 bytes
head Node*: 4 bytes (Assume pointer same as int)
tail Node*: 4 bytes (Assume pointer same as int)
length int: 4 bytes

Overall: 20 bytes

/**********************************************************************
 *  Known bugs / limitations.
 **********************************************************************/
The size of the data structure cannot exceed the limit of integer. 
The number of iterators pointing to a same element cannot exceed the 
limit of integer.

The following is not a bug. I just alter some behaviours of the Subset
given. 
Instead of taking only one line of standard input, my Subset will read 
until EOF is reached. Strings are splited by white-space character (
defined by isspace()).

/**********************************************************************
 *  List whatever help (if any) that you received and from whom,
 *  including help from staff members or lab TAs.
 **********************************************************************/
Garbage collection : algorithms for automatic dynamic memory management
    by Richard Jones, Rafael Lins
Also, I discussed my ideas of implementation with some of my friends.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
The biggest problem is to ensure that the program will not crash on any
condition. This is quite hard given a iterator is in use. The behaviour
of the iterator is hard to define. Later I came up with the idea of 
lazy deletion of the node. Through reading some books and discussion, 
I successfully implement the data structure in a relatively robust way.

/**********************************************************************
 *  List any other comments here. Feel free to provide any feedback   
 *  on how much you learned from doing the assignment, and whether    
 *  you enjoyed doing it.                                             
 **********************************************************************/
To implement a robust and clever data structure is a long way to go. One
has to consider some ridiculous way of using his data structure. 

And some other stuff:
In fact there are some bugs in the example.
echo A B C | Subset 6
will result in a Float exception.
I guess it is because of mod 0 somewhere in the code. Maybe it can be
fixed later.