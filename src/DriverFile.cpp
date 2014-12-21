/*
 * Copyright 2014 Ashish Kumar <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "DriverFile.h"
#include "LinkedList.h"

using namespace std;
bool isPalindrome(SinglyLinkedList *headOfList) {
    //1 reverse the seond half of the list
    //2 compare. if equal, then palindrome
    //3 reverse the second half again to bring list to initial state.
    //let's begin

    //1 reverse the second half
    //if number of nodes are odd, mid node must not be compared.
    SinglyLinkedList *slowptr = headOfList, *fastPtr=headOfList, *prev_of_slow_ptr, *midnode = NULL;
    SinglyLinkedList **secondHalf;
    int res = 0;
    if(headOfList != NULL && headOfList->next != NULL) {
        while(slowptr && fastPtr && fastPtr->next) {
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

        SinglyLinkedList *current = *secondHalf;
        cout << "Before compare" << endl;
        while(current != NULL) {
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
 * uses count method to find if 2 lists are intersecting
 * @param len1 : length of first list
 * @param head1 : head of first list
 * @param len2 : length of second list
 * @param head2 : head of second list
 * @return : TRUE if there is an intersection, FALSE otherwise
 */
BOOL detectIntersection(int len1, SinglyLinkedList *head1, int len2, SinglyLinkedList *head2) {

    int diff = 0, count = 0;
    SinglyLinkedList *ptr1 = head1, *ptr2 = head2;
    //move the ptr to the "diff"th node of the larger list.
    if(len1 > len2) {
        diff = len1 - len2;
        while(count++ < diff) {
            ptr1 = ptr1->next;
        }
    } else {
        diff = len2 -len1;
        while(count++ < diff) {
            ptr2 = ptr2->next;
        }
    }

    //Now move together and check for equal pointers
    while(ptr1 && ptr2 && ptr1 != ptr2) {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    if(ptr1 == ptr2) {
        return TRUE;
    } else {
        return FALSE;
    }

}


/**
 * @brief ...
 *
 * @param a ...
 * @param b ...
 * @return void
 */
void swap(int* a, int* b) {
    *a = *a + *b;
    *b = *a - *b;
    *a =*a - *b;
}

/**
 * @brief ...
 *
 * @param head ...
 * @return STATUS: TRUE if any swap occurs, FALSE otherwise
 */
STATUS swapPairWiseLL(SinglyLinkedList *head) {
    SinglyLinkedList  *prev;
    STATUS retVal = FAILURE;
    if(head) { //some basic sanity NULL check
        prev = head;
        while(prev && prev->next) {
            retVal = SUCCESS;
            swap(&(prev->data), &(prev->next->data));
            prev = prev->next->next;
        }
    }

    return retVal;
}



/**
 * @brief ... Moves last element to the front(head). It is the responsibility of the caller
 * to actually set the head of the underlying LinkedList to the new head after this function
 * returns.
 * @param head ... pointer to pointer to head of the linked list. Singce this fn is not a 
 * member fn of class, it would need another class specific fn call to update the class member
 * head (LinkedList::UpdateHead)
 * @return STATUS
 */
STATUS moveToFront(SinglyLinkedList **head) {

    SinglyLinkedList *temp, *prev;
    STATUS retVal = FAILURE;
    if(head && *head) { // basic sanity NULL check
          cout<<"Addr of ptr to head in moveToFront"<< head<<endl;

        prev = *head;
        temp = prev->next;

        while(temp->next) {
            prev = prev->next;
            temp = temp->next;
        }

        prev->next = NULL;
        temp->next = (*head);

        *head = temp;
	retVal = SUCCESS;
    }
    return retVal;


}


void printSinglyLinkedList(SinglyLinkedList* headnode){
  SinglyLinkedList* temp = headnode;
  while(temp){
    cout<<temp->data<<endl;
    
  }
}

/**
 * @brief ...Given two lists sorted in increasing order, 
 * create and return a new list representing the intersection of the two lists. 
 * The new list should be made with its own memory — the original lists should not be changed. For example, 
 * let the first linked list be 1->2->3->4->6 and second linked list be 2->4->6->8, 
 * then your function should create and return a third list as 2->4->6.
 * 
 * @param head1 ...
 * @param head2 ...
 * @return LinkedList*
 */
LinkedList* sortedIntersection(SinglyLinkedList* head1, SinglyLinkedList* head2){
  LinkedList *newList = new LinkedList();
  SinglyLinkedList *temp1 = head1, *temp2 = head2;
  
  while(temp1 && temp2){
    if(temp1->data == temp2->data){
      newList->appendNode(temp1->data);
      temp1 = temp1->next;
      temp2 = temp2->next;
      
    }else if(temp1->data < temp2->data){
            temp1 = temp1->next;
    }else {
            temp2 = temp2->next;
    }
    
  }
  
  if(newList->countNodes() == 0 ){
    delete newList;
    return NULL;
  }
  
  return newList;
  
}

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {

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
    int isLoop = list11->detectLoop(FALSE);
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

#if 0 // swapPairWise test
    cout<< "After pairwise swap"<< endl;
    swapPairWiseLL(sortedList->getHead());
    sortedList->printAllLLElements();
#endif

#if 0 //moveToFront test
    SinglyLinkedList *headLL  = sortedList->getHead();
    moveToFront(&headLL);
    sortedList->updateHead(headLL);
    cout<< "After movetoFront"<< endl;
    sortedList->printAllLLElements();
#endif

#if 0 //sortedIntersection test
    LinkedList *sortedList2 = new LinkedList();
    //sortedList2->sortedInsert(12);
    sortedList2->sortedInsert(142);
    sortedList2->sortedInsert(102);
    sortedList2->sortedInsert(120);
    sortedList2->sortedInsert(9102);
        sortedList2->sortedInsert(912);

cout <<"Second List"<<endl;
    sortedList2->printAllLLElements();
    LinkedList *sortedIntersenctionList  = sortedIntersection(sortedList->getHead(), sortedList2->getHead());
if(sortedIntersenctionList){
  cout <<"Intersection List"<<endl;
  sortedIntersenctionList->printAllLLElements();
}else{
  cout << "No elements in common";
}

  delete sortedList2;

#endif

    return 0;
}