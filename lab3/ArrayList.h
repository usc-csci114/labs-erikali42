#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__
#include <stdexcept>
#include "List.h"

template <typename T>
class ArrayList : public List<T> {
public:
	ArrayList();
	void append(T v);
	void insert(size_t idx, T v);
	T at(size_t idx);
	void remove(size_t idx);
	size_t find(T v);
	size_t size();
	bool empty();

private:
	void resize(); //double the size of the array and copy the items
	size_t m_capacity;
	size_t m_size;
	T* data;
};

template <typename T>
ArrayList<T>::ArrayList()
{
	
}

template <typename T>
void ArrayList<T>::append(T v)
{

}

template <typename T>
void ArrayList<T>::insert(size_t idx, T v)
{
	
}

template <typename T>
T ArrayList<T>::at(size_t idx)
{
	
}

template <typename T>
void ArrayList<T>::remove(size_t idx)
{
	
}
template <typename T>
size_t ArrayList<T>::find(T v)
{
	
}

template <typename T>
size_t ArrayList<T>::size()
{
	
}

template <typename T>
bool ArrayList<T>::empty()
{
	
}

template <typename T>
void ArrayList<T>::resize()
{
	
}
#endif
