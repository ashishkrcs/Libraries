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
void LinkedList::printAllLLElements(void) {
    SinglyLinkedList *temp;
    if(head == NULL) {
        cout << endl << "No elements."<< endl;
        return;
    }
    temp = head;
    do {
        cout << temp->data << endl;
        temp = temp->next;

    } while (NULL != temp);

}

/**
 *
 */
LinkedList::LinkedList(void) {
    head = NULL;

}

/**
 *
 * @param data
 * @return
 */
STATUS LinkedList::appendNode(int data) {
    //create new node
    SinglyLinkedList *newNode = new SinglyLinkedList();
    newNode->data = data;
    newNode->next = NULL;

    if(head == NULL) {
        head = newNode;
        return SUCCESS;

    } else {
        //find last node
        SinglyLinkedList *lastNodePtr = findLastNode();
        if(lastNodePtr == NULL) {
            //weird, both head and last node are null.
            return FAILURE;
        } else {
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
STATUS LinkedList::addNodeAtHead(int data) {
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
STATUS LinkedList::addNodeAfter(SinglyLinkedList *prevNode, int data) {
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
STATUS LinkedList::deleteNode(SinglyLinkedList *nodePtr) {
    int bFound = 0;
    if(NULL == head) {
        return FAILURE;
    }
    SinglyLinkedList *temp = head, *prev;
    if(head == nodePtr) {
        head = head->next;
        delete(temp);
        return SUCCESS;
    }
    while(temp != nodePtr && temp != NULL) {
        prev = temp;
        temp = temp->next;
        bFound++;
    }
    if(bFound) {
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
STATUS LinkedList::deleteNodeWithKey(int key) {
    if(NULL == head) {
        return FAILURE;
    }

    SinglyLinkedList *temp=head, *prev;
    int bFound = 0;
    if(head->data == key) {
        head = head->next;
        delete(temp);
        return SUCCESS;
    }

    while(NULL != temp && bFound == 0) {
        prev = temp;
        temp = temp->next;
        if(temp->data == key) {
            bFound++;// can be used for deleting all key nodes.
            //need to take care of integer wrap-around for a very large linked list.
            cout << "Found: "<< temp->data;
            prev->next = temp->next;
            delete(temp);

        }

    }

    if(bFound == 0) {
        return FAILURE;
    } else {
        return SUCCESS;
    }
}

/**
 *
 * @return
 */
SinglyLinkedList* LinkedList::findLastNode() {
    if(head == NULL) {
        return NULL;
    }

    SinglyLinkedList *temp = head;
    while(temp->next != NULL) {
        temp = temp->next;

    }

    return temp;
}

/**
 *
 */
LinkedList::~LinkedList(void) {
    emptyTheList();
    head = NULL;
    cout <<"Done" <<endl;
}

/**
 * Assumes there's no loop within the linked List.
 */
void LinkedList::emptyTheList(void) {
    SinglyLinkedList *temp = head;
    //first break the loop
    detectLoop(TRUE);
    while(head != NULL) {
        head = head->next;
        delete temp;
        temp = head;

    }
}

/**
 *
 * @return
 */
SinglyLinkedList* LinkedList::getHead() {
    return head;
}

/**
 * return data at nth Node. N (index) starts at 0.
 * @param index
 * @return
 */
int LinkedList::getNthNode(int index) {
    int count = 0;
    SinglyLinkedList *temp = head;
    while(count < index && temp != NULL) {
        temp = temp->next;
        count++;
    }
    //cout <<"Count::"<< count<<endl;
    if(count == index && temp != NULL) {
        return temp->data;
    }

    assert(0);


}

/**
 * return pointer to nth Node. N (index) starts at 0.
 * @param index
 * @return
 */
SinglyLinkedList* LinkedList::getNthNodeRef(int index) {
    int count = 0;
    SinglyLinkedList *temp = head;
    while(count < index && temp != NULL) {
        temp = temp->next;
        count++;
    }
    //cout <<"Count::"<< count<<endl;
    if(count == index && temp != NULL) {
        return temp;
    }

    assert(0);


}

/**
 *  Function to get the middle of the linked list
 *
 */
void LinkedList::printMiddle() {
    if(head == NULL) {
        return;
    }
    SinglyLinkedList *slowPtr = head, *fastPtr=head;
    if(head->next != NULL) {
        //2 or more elements.
        fastPtr = head->next->next;
        slowPtr = slowPtr->next;
    } else {
        //only 1 elements in the list. print 1st and exit.
        cout << slowPtr->data <<endl;
        return;
    }
    //slowPtr = slowPtr->next;
    while(fastPtr !=NULL) {
        if(fastPtr->next != NULL) {
            fastPtr = fastPtr->next->next;
            slowPtr = slowPtr->next;

        }
    }
    cout << slowPtr->data;
}

/**
 * Counts the no. of occurences of a node
 *   (search_for) in a linked list (head)
 * @param search_for
 * @return
 */
int LinkedList::countOccurrences( int search_for)
{
    SinglyLinkedList* current = head;
    int count = 0;
    while (current != NULL)
    {
        if (current->data == search_for)
            count++;
        current = current->next;
    }
    return count;
}

/**
 * FLoyd's Cycle Algorithm: Detects point of loop too.
 * @param bBreakTheLoop: if TRUE, break the loop and
 * point the loop node to NULL.
 * @return
 */
int LinkedList::detectLoop(int bBreakTheLoop = FALSE) {
    SinglyLinkedList *slowPtr = head, *fastPtr = head;
    while(fastPtr != NULL && fastPtr->next != NULL && slowPtr) {
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;
        if(slowPtr == fastPtr) {
            if(bBreakTheLoop) {
                slowPtr->next = NULL;
            }
            return TRUE;

        }
    }

    return FALSE;
}


/**
 * Function to reverse the linked list  Note that this
 * function may change the head
 * @param head_ref: pass head to reverse entire list.
 */
void LinkedList::reverse(SinglyLinkedList** head_ref)
{
    SinglyLinkedList* prev   = NULL;
    SinglyLinkedList* current = *head_ref;
    cout << "New list Before:\n" <<endl;
    while(current != NULL) {
        cout << "Original list: " << current->data << endl;
        current = current->next;

    }
    current = *head_ref;
    SinglyLinkedList* next;
    while (current != NULL)
    {

        next  = current->next;
        cout << "courr data:" <<current->data << " next:"<< endl;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;

    //print list after reversing
    current = *head_ref;
    cout << "New list After: \n" <<endl;
    while(current != NULL) {
        cout << "Reversed list: " << current->data << endl;
        current = current->next;

    }
}

/**
 *
 * @param head1
 * @param head2
 */
BOOL LinkedList::compareLists(SinglyLinkedList *head1, SinglyLinkedList *head2) {
    SinglyLinkedList *temp1=head1, *temp2=head2;
    while(temp1 && temp2) {
        if(temp1->data == temp2->data) {
            temp1 = temp1->next;
            temp2 = temp2->next;
        } else {
            return FALSE;
        }

    }

    /* Both are empty reurn 1*/
    if (temp1 == NULL && temp2 == NULL)
        return TRUE;

    /* Will reach here when one is NULL
      and other is not */
    return FALSE;
}

/**
 *
 * @param nodeData
 */
void LinkedList::sortedInsert(int nodeData) {
    SinglyLinkedList *temp, *newNode = new SinglyLinkedList;
    newNode->data = nodeData;
    if(head == NULL || head->data > nodeData) {
        newNode->next = head;
        head = newNode;
    } else {
        temp = head;
        while(temp->next && temp->next->data < nodeData) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

/**
 * Assumes there's no loop in the Linked list.
 * @return
 */
int LinkedList::countNodes() {
    SinglyLinkedList *temp = head;
    int count = 0;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

/**
 * @brief ...Helper fn to update the head of the linked list object. Caller fn needs to 
 * take care to delete any nodes not accessible from this new head.
 * 
 * @param newHead ...Pointer to new head. Must not be NULL.
 * @return STATUS
 */
STATUS LinkedList::updateHead(SinglyLinkedList *newHead) {
    STATUS retVal = FAILURE;
    if(newHead) {
        this->head = newHead;
        retVal = SUCCESS;
    }

    return retVal;

}


