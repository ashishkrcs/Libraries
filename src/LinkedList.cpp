/*
 * LinkedList.cpp
 *
 *  Created on: 08-Dec-2014
 *      Author: ashish
 */

#include <iostream>
#include "LinkedList.h"
#include <assert.h>
using namespace std;

/**
 * 
 */
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

/**
 * 
 */
LinkedList::LinkedList(void){
	head = NULL;

}

/**
 * 
 * @param data
 * @return 
 */
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

/**
 * 
 * @param data
 * @return 
 */
STATUS LinkedList::addNodeAtHead(int data){
	//create new node
	SinglyLinkedList *newNode = new SinglyLinkedList();
	newNode->data = data;
	newNode->next = head;
        head = newNode;
			return SUCCESS;
}

/**
 * 
 * @param prevNode
 * @param data
 * @return 
 */
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

/**
 * 
 * @param nodePtr
 * @return 
 */
STATUS LinkedList::deleteNode(SinglyLinkedList *nodePtr){
    int bFound = 0;
    if(NULL == head){
        return FAILURE;
    }
    SinglyLinkedList *temp = head, *prev;
    if(head == nodePtr){
        head = head->next;
        delete(temp);
        return SUCCESS;
    }
    while(temp != nodePtr && temp != NULL){
        prev = temp;
        temp = temp->next;
        bFound++;
    }
    if(bFound){
        prev->next = temp->next;
        delete(temp);
        return SUCCESS;
    }
    return FAILURE;
}

/**
 * 
 * @param key
 * @return 
 */
STATUS LinkedList::deleteNodeWithKey(int key){
    if(NULL == head){
        return FAILURE;
    }
    
    SinglyLinkedList *temp=head, *prev;
    int bFound = 0;
    if(head->data == key){
        head = head->next;
        delete(temp);
        return SUCCESS;
    }
    
    while(NULL != temp && bFound == 0){
        prev = temp;
        temp = temp->next;
        if(temp->data == key){
            bFound++;// can be used for deleting all key nodes.
                     //need to take care of integer wrap-around for a very large linked list.
            cout << "Found: "<< temp->data;
            prev->next = temp->next;
            delete(temp);
            
        }
        
    }
    
    if(bFound == 0){
        return FAILURE;      
    }else{
        return SUCCESS;
    }
}

/**
 * 
 * @return 
 */
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

/**
 * 
 */
LinkedList::~LinkedList(void){
	emptyTheList();
	head = NULL;
	cout <<"Done";
}

/**
 * 
 */
void LinkedList::emptyTheList(void){
	SinglyLinkedList *temp = head;
	while(head != NULL){
		head = head->next;
		delete temp;
		temp = head;

	}
}

/**
 * 
 * @return 
 */
LinkedList::SinglyLinkedList * LinkedList::getHead(){
    return head;
}

/**
 * return data at nth Node. N (index) starts at 0.
 * @param index
 * @return 
 */
int LinkedList::getNthNode(int index){
    int count = 0;
    SinglyLinkedList *temp = head;
    while(count < index && temp != NULL){
        temp = temp->next;   
        count++;
    }
    //cout <<"Count::"<< count<<endl;
    if(count == index && temp != NULL){
        return temp->data;
    }
    
    assert(0);
        
    
}

/**
 * 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char **argv){

	cout<<"ok"<<endl;
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
        cout<<"printing"<<endl;
	list11->printAllLLElements();
        list11->deleteNodeWithKey(4);
        list11->deleteNode(list11->getHead()->next->next);
        cout<<"printing"<<endl;
        list11->printAllLLElements();
        cout <<"3rd element is:"<< list11->getNthNode(2)<<endl;
        cout<<"1st element is:" << list11->getNthNode(0)<<endl;

delete list1;
delete list11;
	return 0;
}
