#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T>
class List;

template <typename T>
class ListNode //nodes to be contained with a list
{
	friend class List<T>;

public:
	ListNode(T);
	T getData();

private:
	T data; //templatized data stored in node
	ListNode* nextPtr; //pointer to the next node in list
};

template <typename T>
ListNode<T>::ListNode(T dataIn)
{
	data = dataIn; //stores data in node
	nextPtr = 0; //initializes point to next node to null
}

template <typename T>
T ListNode<T>::getData() //returns data stored in node
{
	return data;
}

#endif