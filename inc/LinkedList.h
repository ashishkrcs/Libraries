/*
 * LinkedList.h
 *
 *  Created on: 08-Dec-2014
 *      Author: ashish
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
typedef enum{
	SUCCESS=10,
	FAILURE
}STATUS;
class LinkedList{

public:
	struct SinglyLinkedList{
		int data;
		SinglyLinkedList *next;
	};
private:
	SinglyLinkedList *head;

public:
	void printAllLLElements(void);
	STATUS addNode(int data);
	STATUS deleteNode(SinglyLinkedList *nodePtr);
	LinkedList();
	SinglyLinkedList* findLastNode();
	~LinkedList();
	void emptyTheList(void);

};


#endif /* LINKEDLIST_H_ */
