#ifndef __LIST_H__
#define __LIST_H__
template <typename T>
class List {
public:
	virtual void append(T v)=0;
	virtual void insert(size_t idx, T v)=0;
	virtual T at(size_t idx)=0;
	virtual void set(T v)=0;
	virtual void remove(size_t idx)=0;
	virtual size_t find(T v)=0;
	virtual size_t size()=0;
	virtual bool empty()=0;
};

#endif
