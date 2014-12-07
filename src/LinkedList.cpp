/*
 * LinkedList.cpp
 *
 *  Created on: 08-Dec-2014
 *      Author: ashish
 */

#include <iostream>
#include "LinkedList.h"
using namespace std;

int printAllLLElements(SinglyLinkedLis **head){
	SinglyLinkedLis *temp;
	if(*head == NULL){
		return -1;
	}
	temp = *head;
	do{
		cout << temp->data << endl;
		temp = temp->next;

	}while (NULL != temp);

	return 0;
}


