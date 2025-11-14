#pragma once

#include <cstddef>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* array;                 // underlying dynamic array
    std::size_t capacity;    // total allocated capacity
    std::size_t size;        // number of stored elements
    std::size_t head;       // index of front element
    std::size_t tail;        // index after the last element (circular)

    static constexpr std::size_t scale_factor = 2;

    
    T* grow() {
        capacity *= scale_factor;
        T* new_array = new T[capacity];
        size_t j = 0;
        for(size_t i = head; i != tail; i = WrappedAdd(i)) {
            new_array[j] = array[i];
            ++j;
        }

        return new_array;
    }

    size_t WrappedSub(size_t num) const {
        return (num - 1 + capacity) % capacity;
    }

    size_t WrappedAdd(size_t num) const {
        return (num + 1) % capacity;
    }
    
public:
    // Big 5
    explicit ABDQ(std::size_t capacity) {
        this->array = new T[capacity];
        this->capacity = capacity;
        this->size = 0;
        this->head = 0;
        this->tail = 0;
    }
    
    ABDQ() : ABDQ(4) {}
    
    ABDQ(const ABDQ& other) : ABDQ(other.capacity) {
        array = new T[capacity];
        
        size_t j = 0;
        for(size_t i = other.head; i != other.tail; i = other.WrappedAdd(i)) {
            array[j] = other.array[i];
            ++j;
        }

        head = 0;
        tail = other.size;
        size = other.size;
    }
    
    ABDQ(ABDQ&& other) noexcept {
        this->array = other.array;
        this->capacity = other.capacity;
        this->size = other.size;
        this->head = other.head;
        this->tail = other.tail;
    }
    
    ABDQ& operator=(const ABDQ& other) {
        capacity = other.capacity;
        T* new_array = new T[capacity];
        
        size_t j = 0;
        for(size_t i = other.head; i != other.tail; i = other.WrappedAdd(i)) {
            array[j] = other.array[i];
            ++j;
        }

        head = 0;
        tail = size;
        size = other.size;

        delete[] array;
        array = new_array;
        return *this;
    }
    
    ABDQ& operator=(ABDQ&& other) noexcept {
    		if (this == &other) {
            return *this;
        }
        delete[] array;
        this->array = other.array;
        this->capacity = other.capacity;
        this->size = other.size;
        this->head = other.head;
        this->tail = other.tail;

        return *this;
    }
    
    ~ABDQ() override {
        delete[] array;
        array = nullptr; 
        capacity = size = head = 0;
        tail = 0;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size >= capacity) {
            T* new_array = grow();
            head = 0;
            tail = size;
            delete[] array;
            array = new_array;
        }

        head = WrappedSub(head);
        array[head] = item;
        size += 1;
    }
    void pushBack(const T& item) override {
        if (size >= capacity) {
            T* new_array = grow();
            head = 0;
            tail = size;
            delete[] array;
            array = new_array;
        }

        array[tail] = item;
        tail = WrappedAdd(tail);
        size += 1;
    }

    // Deletion
    void shrinkIfNeeded() {
        T* old_array = array;
        if (capacity <= 4 || 4 * size < capacity) { return; }
        
        size_t new_cap = capacity / scale_factor;
        T* new_array = new T[new_cap];

        size_t j = 0;
        for(size_t i = head; i != tail; i = WrappedAdd(i)) {
            new_array[j] = array[i];
            ++j;
        }
        delete[] old_array;
        capacity = new_cap;
    }
    
    T popFront() override {
        if (size == 0) {
            throw std::runtime_error("Index out of bounds.");
        }

        size_t old_head = head;
        head = WrappedAdd(head);
        size -= 1;
        T out = array[old_head];
        shrinkIfNeeded();
        return out;
    }
    
    T popBack() override {
        if (size == 0) {
            throw std::runtime_error("Index out of bounds.");
        }

        // size_t old_back = back;
        tail = WrappedSub(tail);
        size -= 1;
        T out = array[tail];
        shrinkIfNeeded();
        return out;
    }

    // Access
    const T& front() const override {
        if (size == 0) {
            throw std::runtime_error("Index out of bounds.");
        }

        return array[head];
    }
    
    const T& back() const override {
        if (size == 0) {
            throw std::runtime_error("Index out of bounds.");
        }

        return array[WrappedSub(tail)];
    }

    // Getters
    std::size_t getSize() const noexcept override { return size; }

    void PrintForward() {
        if (size == 0) { return; }

        std::cout << head << ": " << array[head];

        
        for(size_t i = WrappedAdd(head); i != tail; i = WrappedAdd(i)) {
            std::cout << ", " << i << ": " << array[i];
        }

        std::cout << std::endl;
    }
};
