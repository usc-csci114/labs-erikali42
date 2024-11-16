#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include <stdexcept>
#include "List.h"

template <typename T>
class Node {
public:
    T value;
    Node* next;

    Node(T v) : value(v), next(nullptr) {}
};

template <typename T>
class LinkedList : public List<T> {
public:
    LinkedList();
    ~LinkedList(); // Destructor to clean up
    void append(T v) override;
    void insert(size_t idx, T v) override;
    T at(size_t idx) override;
    void set(T v);
    void remove(size_t idx) override;
    size_t find(T v) override;
    size_t size() override;
    bool empty() override;

private:
    size_t m_size;
    Node<T>* head;
    Node<T>* tail;
};

// Constructor
// Initializes m_capacity to 2 and m_size to 0, and allocates an array for storing elements
template <typename T>
ArrayList<T>::ArrayList()
    : m_capacity(2), m_size(0) {
    data = new T[m_capacity]; // Dynamically allocate memory for the array
}

// Append method
// Adds a new element to the end of the list. If capacity is reached, it resizes the array.
template <typename T>
void ArrayList<T>::append(T v) {
    if (m_size == m_capacity) { // If the array is full, resize
        resize();
    }
    data[m_size++] = v; // Add the new element and increment the size
}

// Insert method
// Inserts a new element at a specific index. If the index is out of bounds, throws an exception.
template <typename T>
void ArrayList<T>::insert(size_t idx, T v) {
    if (idx > m_size) { // Ensure index is within valid range
        throw std::range_error("Index out of bounds");
    }
    if (m_size == m_capacity) { // If the array is full, resize
        resize();
    }
    // Shift elements to make room for the new element at the specified index
    for (size_t i = m_size; i > idx; --i) {
        data[i] = data[i - 1];
    }
    data[idx] = v; // Insert the new element at the given index
    ++m_size; // Increment the size of the list
}

// At method
// Retrieves the element at a specific index. Throws an exception if the index is out of bounds.
template <typename T>
T ArrayList<T>::at(size_t idx) {
    if (idx >= m_size) { // Ensure index is within valid range
        throw std::range_error("Index out of bounds");
    }
    return data[idx]; // Return the element at the specified index
}

// Set method
// Sets the last element to the provided value. Throws an exception if the list is empty.
template <typename T>
void ArrayList<T>::set(T v) {
    if (m_size == 0) { // Check if the list is empty
        throw std::range_error("Cannot set value in an empty list");
    }
    data[m_size - 1] = v; // Set the last element to the new value
}

// Remove method
// Removes the element at the specified index. Throws an exception if the index is out of bounds.
template <typename T>
void ArrayList<T>::remove(size_t idx) {
    if (idx >= m_size) { // Ensure index is within valid range
        throw std::range_error("Index out of bounds");
    }
    // Shift elements to fill the gap left by the removed element
    for (size_t i = idx; i < m_size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --m_size; // Decrement the size of the list
}

// Find method
// Searches for the first occurrence of a value in the list and returns its index.
// Returns -1 if the value is not found.
template <typename T>
size_t ArrayList<T>::find(T v) {
    for (size_t i = 0; i < m_size; ++i) {
        if (data[i] == v) { // If the value is found, return its index
            return i;
        }
    }
    return -1; // Return -1 if the value is not found
}

// Size method
// Returns the current number of elements in the list
template <typename T>
size_t ArrayList<T>::size() {
    return m_size; // Return the size of the list
}

// Empty method
// Returns true if the list is empty (size is 0), otherwise false
template <typename T>
bool ArrayList<T>::empty() {
    return m_size == 0; // Return true if the list is empty, false otherwise
}

// Resize method
// Doubles the capacity of the array and copies the existing elements to the new array
template <typename T>
void ArrayList<T>::resize() {
    m_capacity *= 2; // Double the capacity of the array
    T* newData = new T[m_capacity]; // Allocate new array with increased capacity
    for (size_t i = 0; i < m_size; ++i) {
        newData[i] = data[i]; // Copy elements from the old array to the new one
    }
    delete[] data; // Free the old array's memory
    data = newData; // Update the data pointer to point to the new array
}

#endif