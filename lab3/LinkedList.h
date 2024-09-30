#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include <stdexcept>
#include "List.h"

template <typename T>
class Node {
	T value;
	Node* next;
};

template <typename T>
class LinkedList : public List<T> {
public:
	LinkedList();
	void append(T v);
	void insert(size_t idx, T v);
	T at(size_t idx);
	void set(T v);
	void remove(size_t idx);
	size_t find(T v);
	size_t size();
	bool empty();

private:

	size_t m_size;
	Node<T>* head;
	Node<T>* tail;
};

template <typename T>
LinkedList<T>::LinkedList()
{
	
}

template <typename T>
void LinkedList<T>::append(T v)
{

}

template <typename T>
void LinkedList<T>::insert(size_t idx, T v)
{
	
}

template <typename T>
T LinkedList<T>::at(size_t idx)
{
	
}

template <typename T>
void LinkedList<T>::set(T v)
{
	
}

template <typename T>
void LinkedList<T>::remove(size_t idx)
{
	
}

template <typename T>
size_t LinkedList<T>::find(T v)
{
	
}

template <typename T>
size_t LinkedList<T>::size()
{
	
}

template <typename T>
bool LinkedList<T>::empty()
{
	
}

#endif
