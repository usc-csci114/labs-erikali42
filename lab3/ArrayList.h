#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__
#include <stdexcept>
#include "List.h"

template <typename T>
class ArrayList : public List<T> {
public:
    ArrayList();
    void append(T v) override;
    void insert(size_t idx, T v) override;
    T at(size_t idx) override;
    void set(T v);
    void remove(size_t idx) override;
    size_t find(T v) override;
    size_t size() override;
    bool empty() override;

private:
    void resize(); // Double the size of the array and copy the items
    size_t m_capacity;
    size_t m_size;
    T* data;
};

// Constructor
// Initializes the list with a capacity of 2 and size 0
// Allocates memory for the array to store the elements
template <typename T>
ArrayList<T>::ArrayList()
    : m_capacity(2), m_size(0) {
    data = new T[m_capacity]; // Dynamically allocate memory for the array
}

// Append method
// Adds a new element to the end of the list.
// If the array is full, the resize method is called to double the capacity.
template <typename T>
void ArrayList<T>::append(T v) {
    if (m_size == m_capacity) { // If the array is full, resize
        resize();
    }
    data[m_size++] = v; // Add the new element at the end and increment the size
}

// Insert method
// Inserts a new element at the specified index. Throws an exception if the index is out of bounds.
// If the array is full, it resizes before inserting the element.
// Shifts elements to make room for the new element.
template <typename T>
void ArrayList<T>::insert(size_t idx, T v) {
    if (idx > m_size) { // Ensure the index is within valid range
        throw std::range_error("Index out of bounds");
    }
    if (m_size == m_capacity) { // If the array is full, resize
        resize();
    }
    // Shift elements to the right to make room for the new element
    for (size_t i = m_size; i > idx; --i) {
        data[i] = data[i - 1];
    }
    data[idx] = v; // Insert the new element at the specified index
    ++m_size; // Increment the size of the list
}

// At method
// Retrieves the element at the specified index. Throws an exception if the index is out of bounds.
template <typename T>
T ArrayList<T>::at(size_t idx) {
    if (idx >= m_size) { // Check if the index is within bounds
        throw std::range_error("Index out of bounds");
    }
    return data[idx]; // Return the element at the specified index
}

// Set method
// Sets the last element of the list to the provided value.
// Throws an exception if the list is empty.
template <typename T>
void ArrayList<T>::set(T v) {
    if (m_size == 0) { // Check if the list is empty
        throw std::range_error("Cannot set value in an empty list");
    }
    data[m_size - 1] = v; // Set the last element to the new value
}

// Remove method
// Removes the element at the specified index and shifts the remaining elements to fill the gap.
// Throws an exception if the index is out of bounds.
template <typename T>
void ArrayList<T>::remove(size_t idx) {
    if (idx >= m_size) { // Ensure the index is within valid range
        throw std::range_error("Index out of bounds");
    }
    // Shift elements to the left to fill the gap left by the removed element
    for (size_t i = idx; i < m_size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --m_size; // Decrement the size of the list
}

// Find method
// Searches for the first occurrence of the given value and returns its index.
// If the value is not found, returns -1.
template <typename T>
size_t ArrayList<T>::find(T v) {
    for (size_t i = 0; i < m_size; ++i) {
        if (data[i] == v) { // If the element is found, return its index
            return i;
        }
    }
    return -1; // Return -1 if the element is not found
}

// Size method
// Returns the number of elements currently in the list
template <typename T>
size_t ArrayList<T>::size() {
    return m_size; // Return the size of the list
}

// Empty method
// Returns true if the list is empty (size is 0), otherwise returns false
template <typename T>
bool ArrayList<T>::empty() {
    return m_size == 0; // Return true if the list is empty, otherwise false
}

// Resize method
// Doubles the capacity of the list's array and copies the elements to the new array.
template <typename T>
void ArrayList<T>::resize() {
    m_capacity *= 2; // Double the capacity of the array
    T* newData = new T[m_capacity]; // Allocate a new array with the increased capacity
    for (size_t i = 0; i < m_size; ++i) {
        newData[i] = data[i]; // Copy all existing elements to the new array
    }
    delete[] data; // Deallocate the old array's memory
    data = newData; // Point the data pointer to the new array
}

#endif