#pragma once

#include <cstddef>
#include "Interfaces.hpp"
#include <cstring>
#include <iostream>

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
private:
    T* grow() {
        capacity *= scale_factor;
        T* new_array = new T[capacity];
        
        for (size_t i = 0; i < size; ++i) {
            new_array[i] = array[i];
        }

        return new_array;
    }

    T* shrink() {
        capacity /= scale_factor;
        T* new_array = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            new_array[i] = array[i];
        }
        return new_array;
    }
    
public:
    // Big 5 + Parameterized Constructor
    explicit ABS(const size_t capacity) {
        this->array = new T[capacity];
        this->capacity = capacity;
        this->size = 0;
    }
    
    ABS() : ABS(1) {}
    
    ABS(const ABS& other) : ABS(other.capacity) {
        for (size_t i = 0; i < other.size; ++i) {
            array[i] = other.array[i];
        }
        
        size = other.size;
    }
    
    ABS& operator=(const ABS& rhs) {
        capacity = rhs.capacity;
        
        for (size_t i = 0; i < rhs.size; ++i) {
            array[i] = rhs.array[i];
        }
        
        size = rhs.size;

        return *this;
    }
    
    ABS(ABS&& other) noexcept {
        array = other.array;
        capacity = other.capacity;
        size = other.size;

        other.array = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    
    ABS& operator=(ABS&& rhs) noexcept {
    		if (this == &rhs) {
          return *this;
        }
        array = rhs.array;
        capacity = rhs.capacity;
        size = rhs.size;

        rhs.array = nullptr;
        rhs.capacity = 0;
        rhs.size = 0;

        return *this;
    }
    
    ~ABS() override {
        delete[] array;
        array = nullptr;
        capacity = size = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return size;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (size >= capacity) {
            T* new_array = grow();
            delete[] array;
            array = new_array;
        }

        array[size] = data;
        size += 1;
    }

    T peek() const override {
        if (size == 0) {
            throw std::runtime_error("Index out of bounds.");
        }

        return array[size - 1];
    }

    T pop() override {
        if (size == 0) {
            throw std::runtime_error("Index out of bounds.");
        }

        size -= 1;
        T output = array[size];
        /*

        if (capacity >= 4 && 4 * size <= capacity) {
            T* new_array = shrink();
            delete[] array;
            array = new_array;
        }*/
        
        return output;
    }
private:
    void PrintTail(T* tail, size_t size) {
        if (size == 0) { return; }

        std::cout << ' ' << tail[0];
        PrintTail(tail + 1, size - 1);
    }

    void PrintHead(T* head, size_t size) {
        if (size == 0) { return; }

        std::cout << ' ' << head[0];
        PrintHead(head - 1, size - 1);
    }

public:
    void PrintForward() {
        // Print Head
        if (size == 0) { return; }
        
        std::cout << array[0];

        // Print Tail
        PrintTail(array + 1, size - 1);

        std::cout << std::endl;
    }

    void PrintReverse() {
        if (size == 0) { return; }

        std::cout << array[size - 1];

        PrintHead(array + (size - 1), size - 1);
        std::cout << std::endl;
    }

private:
    size_t capacity;
    size_t size;
    T* array;
    static constexpr size_t scale_factor = 2;
};
