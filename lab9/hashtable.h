#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <utility>
#include <vector>
#include <map>
#include <stdexcept>
#include <utility>
#include <iostream>

template <typename K, typename V>
class HashTable {
public:
	HashTable();
	~HashTable();
	void insert(K key, V value);
	V find(K key);
	void remove(K key);
	size_t size();
	bool empty();
	
private:
	std::vector< std::map<K,V> > table;
	void resize();
	size_t size_;
	size_t alpha;
	uint64_t hash(K key);
};

template <typename K, typename V>
HashTable<K,V>::HashTable() { table.resize(1); alpha = 1; size_ = 0;};

template <typename K, typename V>
HashTable<K,V>::~HashTable() {};

template <typename K, typename V>
uint64_t HashTable<K,V>::hash(K key)
{
	std::hash<K> hasher;
	return hasher(key);
}

template <typename K, typename V>
void HashTable<K,V>::insert(K key, V value)
{

}

template <typename K, typename V>
V HashTable<K,V>::find(K key)
{

}

template <typename K, typename V>
void HashTable<K,V>::remove(K key)
{
	
}

template <typename K, typename V>
size_t HashTable<K,V>::size()
{

}

template <typename K, typename V>
bool HashTable<K,V>::empty()
{

}

template <typename K, typename V>
void HashTable<K,V>::resize()
{
	std::cout << "resizing " << table.size() << " -> " << table.size()*2 << std::endl;
}
#endif
