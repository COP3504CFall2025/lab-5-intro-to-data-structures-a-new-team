#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() : list(LinkedList<T>()) {}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        T head;
        if(auto head_ptr = list.getHead()) {
            head = head_ptr->data;
        } else {
            throw std::runtime_error("Index out of bounds.");
        }
        list.removeHead();
        return head;
    }
    
    T popBack() override {
        T tail;
        if(auto tail_ptr = list.getTail()) {
            tail = tail_ptr->data;
        } else {
            throw std::runtime_error("Index out of bounds.");
        }
        list.removeTail();
        return tail;
    }

    // Element Accessors
    const T& front() const override {
        const T* head;
        if(auto head_ptr = list.getHead()) {
            head = &head_ptr->data;
        } else {
            throw std::runtime_error("Index out of bounds.");
        }
        return *head;
    }
    
    const T& back() const override {
        const T* tail;
        if(auto tail_ptr = list.getTail()) {
            tail = &tail_ptr->data;
        } else {
            throw std::runtime_error("Index out of bounds.");
        }

        return *tail;
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






