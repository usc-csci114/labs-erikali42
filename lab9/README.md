## Lab 9 Implementing a Hash Table
In this lab we will see that implementing a hash table using chaining is actually quite straight forward!

### Hash tables w/chaining
See the lecture slides for complete notes. Hash tables are data structures that implement the map ADT. They work by _hashing_ the key to an integer that is then used as an index into an array-like data structure. This gives O(1) insertion, removal and lookup! Of course there is a tradeoff: collisions. Because the potential key-space is much-much larger than the size of the table, we expect two keys to occasionally hash to the same value. This is called a collision.

We can deal with collisions in several ways. The most straightforward is to make the table with a secondary data structure like a linked list or map. The table then doesn't directly store the key,value items, we must look in the linked-list or map.

We need a secondary data structure to handle _collisions_. A collision is where we try to store two key,value pairs in our hash table, but the keys _hash to the same index_. Thus we need some way to store more than one key, value pair at a particular index in the table. The map does this for us.

At some point we may decide to resize the table whereby we increase the size of the vector or array and then re-insert all of the items.

If the table size is _m_ and the number of items in the table is _n_, then we can define 𝛼 (alpha) as _load factor_ or _n/m_. If we manage the load factor so it does not get above a constant (e.g. 1) then we can still get average O(1) even with resizes and collisions.

A visualization of a hash table with chaining is below:
![](https://media.geeksforgeeks.org/wp-content/cdn-uploads/implementing-own-hash-table.png)

For our secondary data structure we will use a `std::map<>`, which has some advantages. Using a `std::map<>` will help enforce the 'no duplicate keys' rule that the map ADT specifies. Our implementation will be tempated for the key and value types.

### Hash table class

Below is the starting code for the HashTable class. We will examine the data members and member functions in detail.

```c++
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
```

#### The data memebers

```c++
	std::vector< std::map<K,V> > table;
	void resize();
	size_t size_;
	size_t alpha;
	uint64_t hash(K key);
```

- `std::vector< std::map<K,V> > table;` This is the table for the HashTable. It is a vector of maps. Each `std::map<K,V>` holds the key,value pairs for all keys that hashed to that index.
- `void resize()` Private member function used to resize the data structure when ⍺ (alpha) exceeds one and we need to resize the table.
- `size_t size_`Data member to hold the current number of items in the hash table (not the size of the table!)
- `size_t alpha` Data member used to trigger resize. Initialized to `1` in the `HashTable::HashTable()` constructor.
- `uint64_t hash(key)` Private member function used to return the hash (integer) of a key.

#### The member functions

Your task is to implement the following member functions.

```c++
template <typename K, typename V>
void HashTable<K,V>::insert(K key, V value)
{

}
```

Insert a key, value pair into the hash table. 

- Check to see if we need to resize. If `size_ + 1`diveded by the table size is greater than alpha, resize.
- Find the index for the key by hashing the key and modding by the table size: `size_t idx = hash(key) % table.size()`
- Use this index to insert the key,value pair into the map at `table[idx]`. This is one line.
- Increment `size_`

------



```c++
template <typename K, typename V>
V HashTable<K,V>::find(K key)
{

}
```

Find and return the value for a given key.

- Get the index similar to `insert()` and index into the table to get a map
- Check to see if an entry in that map exists with the given key (lookup the `.count()` method)
  - If the key exists, return the value
  - If the key does not exist, `throw std::range_error("Key not found.")`

------

```c++
template <typename K, typename V>
void HashTable<K,V>::remove(K key)
{
		
}
```

Remove a key,value pair (if it exists)

- Get the index similar to `insert()` and index into the table to get a map
- Check to see if an entry in that map exists with the given key.
  - If the key exists, use `.erase()` to remove the entry from the map
  - If the key does not exists, `throw std::range_error("Key not found.")`

------

```c++
template <typename K, typename V>
size_t HashTable<K,V>::size()
{

}

template <typename K, typename V>
bool HashTable<K,V>::empty()
{

}
```

Return the current size (number of entries in the table).

Return `true` if the size is zero.

------

```c++
template <typename K, typename V>
void HashTable<K,V>::resize()
{
	std::cout << "resizing " << table.size() << " -> " << table.size()*2 << std::endl;

}
```

Resize the hash table so that `table.size()` grows by 2x.

- Make a copy of the existing `table` called `old_table`
- Resize `table` to size zero and then to size `2*old_table.size()` to clear out the old entries on `table`
- Set `size_` to zero
- For every location in `old_table`  (old table is a vector, so you can iterate with an index or with iterators), pull out the map into a temporary variable (best if you do it with a reference)
- For every item in the map (use iterators) call `insert()` to insert the key, value pair into `table`
  - Remember for the map iterator you can use `->first` and `->second` to get the key and value for that item.

------

#### Compiling your hash map

To compile your hash map all you need to do is compile your test code since the hash map is a "header-only" implementation:

```bash
clang++ -o test hash_test.cpp -std=c++11
```

If you need to run your code in the debugger:

```bash
clang++ -o test hash_test.cpp -std=c++11 -O0 -g
```

#### Testing your hash map

The lab code contains a .cpp with some simple test cases for your hash map. Ensure that these test cases run without crashing

After your hash map passes the simple tests, write a new .cpp file that uses the `measuring time` techniques to prove that the average insertion cost is _O(1)_. I suggest creating a hash table that maps ints to ints `HashTable<int,int>`. Then insert N keys, where the keys are the numbers 0 to N-1 and the values are a random number (see the provided test code for an example of how to get a random value). Measure how long just the inserts take. Then increase N and repeat. If you take 10-20 data points with fairly large values for N you should be able to show a linear relationship between N and the runtime.
