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
        int cnt = 0;
	if(head == NULL){
            cout << endl << "No elements."<< endl;
		return;
	}
	temp = head;
	do{
		cout << temp->data << endl;
		temp = temp->next;

	}while (NULL != temp && cnt++ <=5);

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
	cout <<"Done" <<endl;
}

/**
 * Assumes there's no loop within the linked List.
 */
void LinkedList::emptyTheList(void){
	SinglyLinkedList *temp = head;
        //first break the loop
        detectLoop(TRUE);
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
 * return pointer to nth Node. N (index) starts at 0.
 * @param index
 * @return 
 */
LinkedList::SinglyLinkedList* LinkedList::getNthNodeRef(int index){
    int count = 0;
    SinglyLinkedList *temp = head;
    while(count < index && temp != NULL){
        temp = temp->next;   
        count++;
    }
    //cout <<"Count::"<< count<<endl;
    if(count == index && temp != NULL){
        return temp;
    }
    
    assert(0);
        
    
}

/**
 *  Function to get the middle of the linked list
 *
 */
void LinkedList::printMiddle(){
    if(head == NULL){
        return;
    }
    SinglyLinkedList *slowPtr = head, *fastPtr=head;
    if(head->next != NULL){
        //2 or more elements.
        fastPtr = head->next->next;
        slowPtr = slowPtr->next;
    }else{
        //only 1 elements in the list. print 1st and exit.
        cout << slowPtr->data <<endl;
        return;
    }
    //slowPtr = slowPtr->next;
    while(fastPtr !=NULL){
            if(fastPtr->next != NULL){
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
int LinkedList::detectLoop(int bBreakTheLoop = FALSE){
    SinglyLinkedList *slowPtr = head, *fastPtr = head;
    while(fastPtr != NULL && fastPtr->next != NULL && slowPtr){
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;
        if(slowPtr == fastPtr){
            if(bBreakTheLoop){
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
    while(current != NULL){
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
    while(current != NULL){
        cout << "Reversed list: " << current->data << endl;
        current = current->next;
        
    }
}

/**
 * 
 * @param head1 
 * @param head2
 */
BOOL LinkedList::compareLists(SinglyLinkedList *head1, SinglyLinkedList *head2){
    SinglyLinkedList *temp1=head1, *temp2=head2;
    while(temp1 && temp2){
        if(temp1->data == temp2->data){
            temp1 = temp1->next;
            temp2 = temp2->next;
        }else{
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

bool isPalindrome(LinkedList::SinglyLinkedList *headOfList){
    //1 reverse the seond half of the list
    //2 compare. if equal, then palindrome
    //3 reverse the second half again to bring list to initial state.
    //let's begin
    
    //1 reverse the second half
    //if number of nodes are odd, mid node must not be compared.
    LinkedList::SinglyLinkedList *slowptr = headOfList, *fastPtr=headOfList, *prev_of_slow_ptr, *midnode = NULL;
    LinkedList::SinglyLinkedList **secondHalf;
    int res = 0;
    if(headOfList != NULL && headOfList->next != NULL){
    while(slowptr && fastPtr && fastPtr->next){
        fastPtr = fastPtr->next->next;
        /*We need previous of the slow_ptr for
        linked lists  with odd elements */
        prev_of_slow_ptr = slowptr;
        slowptr = slowptr->next;

    }
    
        /* fast_ptr would become NULL when there are even elements in list.
           And not NULL for odd elements. We need to skip the middle node
           for odd case and store it somewhere so that we can restore the
           original list*/
        if (fastPtr != NULL)
        {
            cout << "ODD";
            midnode = slowptr;
            slowptr = slowptr->next;
        }
    
            // Now reverse the second half and compare it with first half
        secondHalf = &slowptr;
        prev_of_slow_ptr->next = NULL; // NULL terminate first half
        LinkedList *tempList = new LinkedList();
        tempList->reverse(secondHalf);  // Reverse the second half
        
        LinkedList::SinglyLinkedList *current = *secondHalf;
        cout << "Before compare" << endl;
        while(current != NULL){
            cout <<" BEF:"<< current->data;
            current = current->next;
        }
        res = tempList->compareLists(headOfList, *secondHalf); // compare
        
                /* Construct the original list back */
         tempList->reverse(secondHalf); // Reverse the second half again
         if (midnode != NULL)  // If there was a mid node (odd size case) which                                                        
                               // was not part of either first half or second half.
         {
            prev_of_slow_ptr->next = midnode;
            midnode->next = *secondHalf;
         }
         else  {
             prev_of_slow_ptr->next = *secondHalf;
         }
}

return res;
}

/**
 * 
 * @param nodeData
 */
void LinkedList::sortedInsert(int nodeData){
    SinglyLinkedList *temp, *newNode = new SinglyLinkedList;
    newNode->data = nodeData;
    if(head == NULL || head->data > nodeData){
        newNode->next = head;
        head = newNode;
    }else{
        temp = head;
        while(temp->next && temp->next->data < nodeData){
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
int LinkedList::countNodes(){
    SinglyLinkedList *temp = head;
    int count = 0;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    
    return count;
}

/**
 * uses count method to find if 2 lists are intersecting
 * @param len1 : length of first list
 * @param head1 : head of first list
 * @param len2 : length of second list
 * @param head2 : head of second list
 * @return : TRUE if there is an intersection, FALSE otherwise
 */
BOOL detectIntersection(int len1, LinkedList::SinglyLinkedList *head1, int len2, LinkedList::SinglyLinkedList *head2){
    
    int diff = 0, count = 0;
    LinkedList::SinglyLinkedList *ptr1 = head1, *ptr2 = head2;
    //move the ptr to the "diff"th node of the larger list.
    if(len1 > len2){
        diff = len1 - len2;
        while(count++ < diff){
            ptr1 = ptr1->next;
        }
     }else{
        diff = len2 -len1;
        while(count++ < diff){
            ptr2 = ptr2->next;
        }
    }
    
    //Now move together and check for equal pointers
    while(ptr1 && ptr2 && ptr1 != ptr2){
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    
    if(ptr1 == ptr2){
        return TRUE;       
    }else{
        return FALSE;   
    }
    
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
        list11->emptyTheList();
        cout<<"Printing after Deleting" <<endl;
        list11->printAllLLElements();
        int isLoop = list11->detectLoop();
        cout << "list11 has loop " << isLoop <<endl;
        list1->appendNode(34);
        list1->appendNode(56);
        list1->printAllLLElements();
        int res = isPalindrome(list1->getHead());
        cout << "List is a palindrome? "<<res <<endl;
                cout << "Head data:" << list1->getNthNodeRef(0)->data << endl;

        list1->printAllLLElements();
#if 0 //loop check      
        list1->getNthNodeRef(3)->next = list1->getNthNodeRef(1); //create loop
        cout << "Head data:" << list1->getNthNodeRef(0)->data << endl;
      //          list1->printAllLLElements();

       isLoop = list1->detectLoop();
        cout << "list1 has loop " << isLoop <<endl;
#endif        
        delete list11;
        delete list1;


        LinkedList *sortedList = new LinkedList();
        sortedList->sortedInsert(12);
        sortedList->sortedInsert(142);
        sortedList->sortedInsert(102);
        sortedList->sortedInsert(12);
        sortedList->sortedInsert(912);
#if 1
        sortedList->printAllLLElements();

#endif        

#if 0
LinkedList *intersectList2 = new LinkedList();        
intersectList2->sortedInsert(10);
intersectList2->getHead()->next = sortedList->getHead()->next->next;

intersectList2->printAllLLElements();

int isIntersection = detectIntersection(sortedList->countNodes(), sortedList->getHead(), intersectList2->countNodes(), intersectList2->getHead());        

cout << "The 2 lists are intersected?" << isIntersection <<endl;

#endif

return 0;
}
