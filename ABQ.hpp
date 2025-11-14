#pragma once

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{
private:
    size_t capacity;
    size_t size;
    T* array;
    static constexpr size_t scale_factor = 2;

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
    // Constructors + Big 5
    explicit ABQ(const size_t capacity) {
        this->array = new T[capacity];
        this->capacity = capacity;
        this->size = 0;
    }
    
    ABQ() : ABQ(1) {}
    
    ABQ(const ABQ& other) : ABQ(other.capacity) {
        for (size_t i = 0; i < other.size; ++i) {
            array[i] = other.array[i];
        }
        size = other.size;
    }
    
    ABQ& operator=(const ABQ& rhs) {
        capacity = rhs.capacity;

        for (size_t i = 0; i < rhs.size; ++i) {
            array[i] = rhs.array[i];
        }
        size = rhs.size;

        return *this;
    }
    
    ABQ(ABQ&& other) noexcept {
        array = other.array;
        capacity = other.capacity;
        size = other.capacity;

        other.array = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    ABQ& operator=(ABQ&& rhs) noexcept {
        array = rhs.array;
        capacity = rhs.capacity;
        size = rhs.capacity;

        rhs.array = nullptr;
        rhs.capacity = 0;
        rhs.size = 0;

        return *this;
    }

    ~ABQ() override {
        delete[] array;
        array = nullptr;
        capacity = size = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override { return size; }
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity; }
    [[nodiscard]] T* getData() const noexcept { return array; }

    // Insertion
    void enqueue(const T& data) override {
        if (size >= capacity) {
            T* new_array = grow();
            delete[] array;
            array = new_array;
        }

        array[size] = data;
        size += 1;
    }

    // Access
    T peek() const override {
        if (size == 0) {
            throw std::runtime_error("Index out of bounds.");
        }
        
        return array[0];
    }

    // Deletion
    T dequeue() override {
        if (size == 0) {
            throw std::runtime_error("Index out of bounds.");
        }

        T output = array[0];

        for (size_t i = 0; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        size -= 1;

        if (capacity >= 4 && 4 * size <= capacity) {
            T* new_array = shrink();
            delete[] array;
            array = new_array;
        }

        return output;
    }

    void PrintForward() {
        if (size == 0) { return; }
        
        std::cout << array[0];
        
        for (size_t i = 1; i < size ; ++i) {
            std::cout << ' ' << array[i];
        }
    }

    void PrintReverse() {
        if (size == 0) { return; }
        
        std::cout << array[size - 1];
        
        for (size_t i = size - 2; i > 0 ; --i) {
            std::cout << ' ' << array[i];
        }
    }
};
