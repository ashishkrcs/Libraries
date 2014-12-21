/*
 * LinkedList.h
 *
 *  Created on: 08-Dec-2014
 *      Author: ashish
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
typedef enum {
    SUCCESS=10,
    FAILURE
} STATUS;

typedef enum {
    FALSE = 0,
    TRUE
} BOOL;

struct SinglyLinkedList {
    int data;
    SinglyLinkedList *next;
};

class LinkedList {
private:
    SinglyLinkedList *head;

public:
    void printAllLLElements(void);
    STATUS appendNode(int data);
    STATUS deleteNode(SinglyLinkedList *nodePtr);
    LinkedList();
    LinkedList(SinglyLinkedList* head1, SinglyLinkedList* head2);//new LL from 2 sorted lists
    SinglyLinkedList* findLastNode();
    ~LinkedList();
    void emptyTheList(void);
    STATUS addNodeAtHead(int data);
    STATUS addNodeAfter(SinglyLinkedList *prevNode, int data);
    SinglyLinkedList *getHead();
    STATUS deleteNodeWithKey(int key);
    int getNthNode(int index);
    SinglyLinkedList* getNthNodeRef(int index);
    void printMiddle();
    int countOccurrences( int search_for);
    int detectLoop(int);
    void reverse(SinglyLinkedList** head_ref);
    BOOL compareLists(SinglyLinkedList *head1, SinglyLinkedList *head2);
    void sortedInsert(int nodeData);
    int countNodes();
    STATUS updateHead(SinglyLinkedList *newHead);
    BOOL operator==( LinkedList& otherList);
};


#endif /* LINKEDLIST_H_ */
/*


In Short: When passing by value, such as in above code, make sure you pass pointer to value you want to change. And we want to change value of head pointer, to insert node at beginning and hence as per rule we pass pointer to head pointer.

i'll use a visual representation to help explaining:
Visual -
pointer_to_head -> head -> first_node -> second_node -> .... -> NULL

Now, lets say i want to insert a new_first_node in the beginning, i.e. before first_node.
Visual -
pointer_to_head -> head -> new_first_node -> first_node -> second_node -> .... -> NULL

As you can see now, head is pointing to new_first_node instead first_node.

So, we had to CHANGE value of head pointer such that it points to new_first_node

now when i declare (Incorrect):
void append(struct node* head, int new_data) {

//insert new node at head

}

In above function, i'm passing a copy of head pointer and when i change its value, it wont reflect outside of this function scope.

now when i declare (Correct):

void append(struct node** pointer_to_head, int new_data) {

//insert new node at head

}

In above function, i pass a copy of pointer_to_head, and i'm not interested in changing its value, coz i only want to change value of head pointer.
*/