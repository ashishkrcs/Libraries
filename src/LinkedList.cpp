/*
 * LinkedList.cpp
 *
 *  Created on: 08-Dec-2014
 *      Author: ashish
 */

#include <iostream>
#include "LinkedList.h"
using namespace std;

void LinkedList::printAllLLElements(void){
	SinglyLinkedList *temp;
	if(head == NULL){
            cout << endl << "No elements."<< endl;
		return;
	}
	temp = head;
	do{
		cout << temp->data << endl;
		temp = temp->next;

	}while (NULL != temp);

}

LinkedList::LinkedList(void){
	head = NULL;

}

STATUS LinkedList::appendNode(int data){
	//create new node
	SinglyLinkedList *newNode = new SinglyLinkedList();
	newNode->data = data;
	newNode->next = NULL;

	if(head == NULL){
		head = newNode;
		return SUCCESS;

	}else{
		//find last node
		SinglyLinkedList *lastNodePtr = findLastNode();
		if(lastNodePtr == NULL){
			//weird, both head and last node are null.
			return FAILURE;
		}else{
			lastNodePtr->next = newNode;
			return SUCCESS;
		}

	}

}

STATUS LinkedList::addNodeAtHead(int data){
	//create new node
	SinglyLinkedList *newNode = new SinglyLinkedList();
	newNode->data = data;
	newNode->next = head;
        head = newNode;
			return SUCCESS;
}

STATUS LinkedList::addNodeAfter(SinglyLinkedList *prevNode, int data){
        if(NULL == prevNode ) {
            return FAILURE;
        }	
    //create new node
	SinglyLinkedList *newNode = new SinglyLinkedList();
	newNode->data = data;
        newNode->next = prevNode->next;
        prevNode->next = newNode;
        return SUCCESS;

}

STATUS LinkedList::deleteNode(SinglyLinkedList *nodePtr){

return SUCCESS;
}

LinkedList::SinglyLinkedList* LinkedList::findLastNode(){
	if(head == NULL){
		return NULL;
	}

	SinglyLinkedList *temp = head;
	while(temp->next != NULL){
		temp = temp->next;

	}

	return temp;
}
LinkedList::~LinkedList(void){
	emptyTheList();
	head = NULL;
	cout <<"Done";
}
void LinkedList::emptyTheList(void){
	SinglyLinkedList *temp = head;
	while(head != NULL){
		head = head->next;
		delete temp;
		temp = head;

	}
}

LinkedList::SinglyLinkedList * LinkedList::getHead(){
    return head;
}

int main(int argc, char **argv){

	cout<<"ok";
	LinkedList *list1 =new LinkedList();
	list1->appendNode(7);
	list1->appendNode(45);
	LinkedList *list11 =new LinkedList();
	list11->appendNode(3);
	list11->appendNode(4);
	list11->appendNode(4);
        list11->addNodeAtHead(0);
        list11->addNodeAfter(list11->getHead()->next, 12);
	list1->printAllLLElements();
	list11->printAllLLElements();
delete list1;
delete list11;
	return 0;
}
