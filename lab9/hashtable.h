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
    // Check if resize is needed
    if (static_cast<double>(size_ + 1) / table.size() > alpha) {
        resize();
    }

    // Find the index for the key
    size_t idx = hash(key) % table.size();

    // Insert the key-value pair into the map at the calculated index
    table[idx][key] = value;

    // Increment the size
    size_++;
}

template <typename K, typename V>
V HashTable<K,V>::find(K key)
{
    // Find the index for the key
    size_t idx = hash(key) % table.size();

    // Check if the key exists in the map at the index
    if (table[idx].count(key)) {
        return table[idx][key];
    }

    // If the key does not exist, throw an exception
    throw std::range_error("Key not found.");
}


template <typename K, typename V>
void HashTable<K,V>::remove(K key)
{
    // Find the index for the key
    size_t idx = hash(key) % table.size();

    // Check if the key exists in the map at the index
    if (table[idx].count(key)) {
        // Remove the key-value pair
        table[idx].erase(key);
        size_--;
    } else {
        // If the key does not exist, throw an exception
        throw std::range_error("Key not found.");
    }
}


template <typename K, typename V>
size_t HashTable<K,V>::size()
{
    return size_;
}

template <typename K, typename V>
bool HashTable<K,V>::empty()
{
    return size_ == 0;
}

template <typename K, typename V>
void HashTable<K,V>::resize()
{
    std::cout << "Resizing " << table.size() << " -> " << table.size() * 2 << std::endl;

    // Make a copy of the existing table
    auto old_table = table;

    // Resize the table
    table.clear();
    table.resize(old_table.size() * 2);

    // Reset size
    size_ = 0;

    // Rehash all elements from the old table
    for (const auto& bucket : old_table) {
        for (const auto& pair : bucket) {
            insert(pair.first, pair.second);
        }
    }
}

#endif
