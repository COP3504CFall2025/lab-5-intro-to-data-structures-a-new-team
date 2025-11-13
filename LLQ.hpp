#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() : list(LinkedList<T>()) {}

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        T head;
        if(auto head_ptr = list.getHead()) {
            head = head_ptr->data;
        } else {
            throw std::out_of_range("Index out of bounds.");
        }
        
        list.removeHead();
        return head;
    }

    // Access
    T peek() const override {
        T head;
        if(auto head_ptr = list.getHead()) {
            head = head_ptr->data;
        } else {
            throw std::out_of_range("Index out of bounds.");
        }

        return head;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();   
    }

    void PrintForward() {
        list.printForward();
    }

    void PrintReverse() {
        list.printReverse();
    }
};
