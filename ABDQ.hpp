#pragma once

#include <cstddef>
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
        
        if (head <= tail) {
            std::memcpy(new_array, array + head, tail - head);
        } else {
            std::memcpy(new_array, array + head, capacity - head);
            std::memcpy(new_array, array, tail);
        }

        head = 0;
        tail = size;
                
        return new_array;
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
    
    ABDQ() : ABDQ(1) {}
    
    ABDQ(const ABDQ& other) : ABDQ(other.capacity) {
        array = new T[capacity];
        
        if (head <= tail) {
            std::memcpy(array, array + head, tail - head);
        } else {
            std::memcpy(array, other.array + other.head, capacity - other.head);
            std::memcpy(array, other.array, other.tail);
        }

        head = 0;
        tail = size;
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
        array = new T[capacity];
        
        if (head <= tail) {
            std::memcpy(array, array + head, tail - head);
        } else {
            std::memcpy(array, other.array + other.head, capacity - other.head);
            std::memcpy(array, other.array, other.tail);
        }

        head = 0;
        tail = size;
        size = other.size;
    }
    
    ABDQ& operator=(ABDQ&& other) noexcept {
        this->array = other.array;
        this->capacity = other.capacity;
        this->size = other.size;
        this->head = other.head;
        this->tail = other.tail;
    }
    
    ~ABDQ() override {
        delete[] array;
        array = nullptr; 
        capacity = size = head = 0;
        tail = 1;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size == capacity) {
            T* new_array = grow();
            delete[] array;
            array = new_array;
        }

        head = (head - 1) % capacity;
        array[head] = item;
        size += 1;
    }
    void pushBack(const T& item) override {
        if (size == capacity) {
            T* new_array = grow();
            delete[] array;
            array = new_array;
        }

        array[head] = item;
        tail = (tail + 1) % capacity;
        size += 1;
    }

    // Deletion
    void shrinkIfNeeded() {
        if (capacity <= 4 || 4 * size < capacity) { return; }

        capacity /= scale_factor;
        T* new_array = new T[capacity];
        
        if (head <= tail) {
            std::memcpy(new_array, array + head, tail - head);
        } else {
            std::memcpy(new_array, array + head, capacity - head);
            std::memcpy(new_array, array, tail);
        }
    }
    
    T popFront() override {
        if (size == 0) {
            throw std::runtime_error("Index out of bounds.");
        }

        size_t old_head = head;
        head = (head + 1) % capacity;
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
        tail = (tail - 1) % capacity;
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

        return array[tail];
    }

    // Getters
    std::size_t getSize() const noexcept override { return size; }

};
