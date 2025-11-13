#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
  void push(const T& item) = 0;
  T pop() = 0;
  T peek() const = 0;
  std::size_t getSize() const noexcept = 0;
};


template <typename T>
class QueueInterface {
  void enqueue(const T& item) = 0;
  T dequeue() = 0;
  T peek() const = 0;
  std::size_t getSize() const noexcept = 0;
};


template <typename T>
class DequeInterface {
  void pushFront(const T& item) = 0;
  void pushBack(const T& item) = 0;
  T popFront() = 0;
  T popBack() = 0;
  const T& front() const = 0;
  const T& back() const = 0;
  std::size_t getSize() const noexcept = 0;
};

