#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() : list(LinkedList<T>()) {}

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        T head;
        if(auto head_ptr = list.getHead()) {
            head = head_ptr->data;
        } else {
            throw std::runtime_error("Index out of bounds.");
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
            throw std::runtime_error("Index out of bounds.");
        }
        return head;
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void PrintForward() {
        list.printForward();
    }

    void PrintReverse() {
        list.printReverse();
    }

    ~LLS() override = default;
};
