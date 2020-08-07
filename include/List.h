#ifndef LIST_H
#define LIST_H

#include "ListNode.h"

template <typename T>
class List //linked list of ListNode objects
{
public:
	List();
	~List();
	void insertNewNode(T); //fucntion used to insert new node in order in the list
	void print(); //prints the contents of the linked list
	ListNode<T>* search(T); //searches for a value in the linked list and returns the point to object that contains that value

private:
	ListNode<T> *startPtr; //stores the pointer of first object in the linked list
	ListNode<T> *endPtr; //stored the pointer of the last object in the linked list
	bool isEmpty(); //utility functions used to see if the list contains no elements
	void insertBegin(T); //inserts new node before the first node in the list
	void insertEnd(T); //inserts new node after the last node in the list
};



template <typename T>
List<T>::List() //creates list with start and end as NULL
{
	startPtr = NULL;
	endPtr = NULL;
}

template <typename T>
List<T>::~List()
{
	if ( !isEmpty() ) // List is not empty
	{
		ListNode<T> *currentPtr = startPtr;
		ListNode<T> *tempPtr;

		while ( currentPtr != 0 ) // delete remaining nodes
		{
			tempPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			delete tempPtr;
		}
	}
}

template <typename T>
bool List<T>::isEmpty()
{
	if(startPtr == NULL && endPtr == NULL) //if the start pointer and end pointer are NULL then the list is empty
		return 1;
	else
		return 0;
}

template <typename T>
void List<T>::insertBegin(T dataIn)
{
	if(isEmpty()) //if the list is empty create first element of the list
	{
		ListNode<T> * newPtr = new ListNode<T>(dataIn); //creates new node
		startPtr = newPtr; //start and end pointer are same becuase there is only one object in list
		endPtr = newPtr;
	}else //if node(s) exist in list insert additional object before the first
	{
		ListNode<T> * newPtr = new ListNode<T>(dataIn);
		newPtr->nextPtr = startPtr; //the next pointer of the new node points to the node that was previously first
		startPtr = newPtr; //the pointer for the new node is now the starting node
	}
}

template <typename T>
void List<T>::insertEnd(T dataIn)
{
	if(isEmpty()) //if the list is empty create first element of the list (same as first case in insert at begin)
	{
		ListNode<T> * newPtr = new ListNode<T>(dataIn);
		startPtr = newPtr;
		endPtr = newPtr;
	}else //if node(s) exist in the list then insert new node at the end of the list
	{
		ListNode<T> * newPtr = new ListNode<T>(dataIn);
		endPtr->nextPtr = newPtr; //the current last node's next pointer points to the new node
		endPtr = newPtr; //the new node is now the last node in the list
	}
}

template <typename T>
void List<T>::insertNewNode(T dataIn) //general funtionn to insert new node the proper order in the list
{
	if(isEmpty()) //if there is no nodes in the list simply insert at beginning
	{
		insertBegin(dataIn);
	}else //otherwise
	{
		if(dataIn < startPtr->data) //if the data of the new object is less than than the data of first node in list insert at beginning
		{
			insertBegin(dataIn);
		}
		else if(dataIn >= endPtr->data) //if the data of the new object is greater than than the data of last node in list insert at end
		{
			insertEnd(dataIn);
		}
		else //the new node is being inserted in order but not at the beginning or end
		{
			ListNode<T> * currentPtr = startPtr;
			ListNode<T> * newPtr = new ListNode<T>(dataIn); //creates new node
			while(currentPtr != endPtr) //runs until the end of the list is reached
			{
				if((newPtr->data < currentPtr->nextPtr->data) && (newPtr->data >= currentPtr->data)) //if the data of the new node is less the data in the next node and greater than the data in the current node, insert after current node
				{
					ListNode<T> * next = currentPtr->nextPtr;
					currentPtr->nextPtr = newPtr; //current nodes next pointer now points to the new node
					newPtr->nextPtr = next; //the new nodes next pointer now points the node previously after the current node
					break;
				}
				currentPtr = currentPtr->nextPtr; //moves to the next node in the list
			}
		}
	}
}

template <typename T>
void List<T>::print()
{
//	if(isEmpty())
//	{
//		cout << "The list is empty" << endl;
//
//	}else
//	{
//		ListNode<T> * currentPtr = startPtr;
//
//		cout << "The contents of the list is: ";
//		while(currentPtr != NULL) //prints until the end of the list is reached
//		{
//			cout << currentPtr->data << ' ';
//			currentPtr = currentPtr->nextPtr; //moves to next node in list
//		}
//		cout << endl;
//	}
}

template <typename T>
ListNode<T>* List<T>::search(T key) //search functions that searches for node that contains data equal to the key
{
	ListNode<T>* nodePtr;
	bool found = false;

	nodePtr = startPtr;

	while((!found) && (nodePtr != NULL)) //runs through list until data is found within a node or end of list is reached
	{
		if(nodePtr->data == key) //if the node's data equals the key then the node has been found
			found = true;
		else
			nodePtr = nodePtr->nextPtr; //moves to next node in list
	}
	return nodePtr; //returns pointer to the node that contains data equal to key (NULL if not found)
}
#endif