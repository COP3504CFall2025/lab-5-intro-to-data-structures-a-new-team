[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/k_o-7ICN)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21404098)
# **Lab 5: Intro to Data Structures**
***
## **1. LinkedList.hpp**

### **Purpose**

A **templated doubly linked list** used as the internal container for all linked-list-based structures (`LLS`, `LLQ`, `LLDQ`).

### **Core Attributes**

| Variable | Type | Description |
| :-- | :-- | :-- |
| `Node* head` | Pointer | Points to the first node |
| `Node* tail` | Pointer | Points to the last node |
| `unsigned int count` | Unsigned Int | Number of elements |

**Node Structure**:

```cpp
struct Node {
    T data;
    Node* prev;
    Node* next;
};
```


### **Key Methods**

| Method | Behavior | Complexity |
| :-- | :-- | :-- |
| `AddHead(const T&)` | Inserts at the beginning | O(1) |
| `AddTail(const T&)` | Inserts at the end | O(1) |
| `RemoveHead()` | Removes the first node | O(1) |
| `RemoveTail()` | Removes the last node | O(1) |
| `Clear()` | Deletes all nodes | O(n) |
| `getCount()` | Returns node count | O(1) |
| `getHead()` / `getTail()` | Returns pointers to head/tail | O(1) |

### **Utility Visualization**

- `PrintForward()` → Prints elements from head to tail.
- `PrintReverse()` → Prints elements from tail to head.

**All LinkedList-based implementations must properly follow the Big Five** since the list allocates nodes dynamically (`new Node()`).

***

## **2. Interfaces.hpp**

### **Abstract Interfaces Defined**

1. **StackInterface<T>**
2. **QueueInterface<T>**
3. **DequeInterface<T>**

These define *behavioral contracts* for data structure interactions.

### **StackInterface**

Defines standard **LIFO** (Last-In-First-Out) operations:

```cpp
void push(const T& item);
T pop();
T peek() const;
std::size_t getSize() const noexcept;
```


### **QueueInterface**

Defines standard **FIFO** (First-In-First-Out) operations:

```cpp
void enqueue(const T& item);
T dequeue();
T peek() const;
std::size_t getSize() const noexcept;
```


### **DequeInterface**

Defines **double-ended sequential** access operations:

```cpp
void pushFront(const T& item);
void pushBack(const T& item);
T popFront();
T popBack();
const T& front() const;
const T& back() const;
std::size_t getSize() const noexcept;
```

Each inherits no internal data, relying on linked or array containers for definition. All functions mentioned above will be overriden inside the derived classes, and **each interface should be defined as Abstract Base Classes.**

***

## **3. Array-Based Implementations**

These use internal **dynamic arrays** and manage resizing logic.
All implementors of `StackInterface`, `QueueInterface`, or `DequeInterface` **must fully define the Big Five** due to dynamic memory.

***

### **A. ABS.hpp — Array-Based Stack**

Implements `StackInterface<T>` (LIFO).


| Attribute | Type | Description |
| :-- | :-- | :-- |
| `T* array_` | Pointer | Dynamic array storing elements |
| `std::size_t capacity_` | Size_t | Total allocated slots |
| `std::size_t curr_size_` | Size_t | Current stack depth |

**Methods**


| Method                           | Action                                                                                             |
|:---------------------------------|:---------------------------------------------------------------------------------------------------|
| `ABS()`                          | Default Constructor. Default `capacity_` to 1, <br/>`size_` to 0, and create buffer array `data_`. |
| `ABS(const std::size_t capacity)`| Parameterized Constructor. Same behavior as default, <br/>however set `capacity_` to `capacity`    | 
| `push(const T&)`                 | Push at top; doubles capacity if full                                                              |
| `pop()`                          | Removes the last inserted element                                                                  |
| `peek() const`                   | Returns top element                                                                                |
| `getSize()`                      | Returns element count                                                                              |
| `PrintForward()`                 | Prints stack from bottom to top                                                                    |
| `PrintReverse()`                 | Prints stack from top to bottom                                                                    |

All resizing operations double capacity (scale factor = 2).
**Big 5** required to handle possible reallocations.

***

### **B. ABQ.hpp — Array-Based Queue**

Implements `QueueInterface<T>` (FIFO).


| Attribute | Type | Description |
| :-- | :-- | :-- |
| `T* array_` | Dynamic storage |  |
| `std::size_t capacity_` | Total buffer size |  |
| `std::size_t curr_size_` | Number of active elements |  |

**Methods**


| Method                            | Description                                                                                        |
|:----------------------------------|:---------------------------------------------------------------------------------------------------|
| `ABQ()`                           | Default Constructor. Default `capacity_` to 1, <br/>`size_` to 0, and create buffer array `data_`. |
| `ABQ(const std::size_t capacity)` | Parameterized Constructor. Same behavior as default, <br/>however set `capacity_` to `capacity`    | 
| `enqueue(const T&)`               | Adds element to back                                                                               |
| `dequeue()`                       | Removes from front                                                                                 |
| `peek()`                          | Returns front element                                                                              |
| `getSize()`                       | Returns size                                                                                       |
| `PrintForward()`                  | Print front-to-back contents                                                                       |
| `PrintReverse()`                  | Print in reverse order                                                                             |


***

## **4. Linked-List Implementations**

These rely on the `LinkedList<T>` class for internal node management.

***

### **A. LLS.hpp — Linked-List Stack**

Implements `StackInterface<T>`


| Attribute | Type | Purpose |
| :-- | :-- | :-- |
| `LinkedList<T> list` | Internal container | Maintains stack order |

**Methods**


| Operation | Description |
| :-- | :-- |
| `push(const T&)` | Adds node at head |
| `pop()` | Removes and returns head |
| `peek()` | Returns head’s data |
| `getSize()` | Returns node count |
| `PrintForward()` | Uses LinkedList’s forward traversal |
| `PrintReverse()` | Uses LinkedList’s reverse traversal |

All methods O(1).
**Big Five** must correctly copy/move internal list state.

***

### **B. LLQ.hpp — Linked-List Queue**

Implements `QueueInterface<T>`


| Attribute | Type | Purpose |
| :-- | :-- | :-- |
| `LinkedList<T> list` | Internal member | Implements FIFO |

| Method | Description |
| :-- | :-- |
| `enqueue(const T&)` | Adds new tail node |
| `dequeue()` | Removes head node |
| `peek()` | Returns head data |
| `getSize()` | Returns list count |
| `PrintForward()` | Forward traversal |
| `PrintReverse()` | Reverse traversal |

All operations maintain **O(1)** efficiency.

***

### **C. LLDQ.hpp — Linked-List Deque**

Implements `DequeInterface<T>`


| Attribute | Type | Purpose |
| :-- | :-- | :-- |
| `LinkedList<T> list` | Composition | Double-ended linked container |

| Method | Description |
| :-- | :-- |
| `pushFront(const T&)` | Insert head |
| `pushBack(const T&)` | Insert tail |
| `popFront()` / `popBack()` | Remove from front/back |
| `front()` / `back()` | Retrieve end data |
| `getSize()` | Total nodes |
| `PrintForward()` | Forward traversal |
| `PrintReverse()` | Reverse traversal |

Like all link-based structures, LLDQ has **O(1)** double-ended operations and **must follow the Big 5** to manage internal state safely.

***

## **5. ABDQ.hpp — Array-Based Deque**

Implements **DequeInterface<T>** using a **circular buffer** model.

### **Attributes**

| Attribute | Type | Description |
| :-- | :-- | :-- |
| `T* data_` | Pointer | Circular array buffer |
| `std::size_t capacity_` | Total array size |  |
| `std::size_t size_` | Active count |  |
| `std::size_t front_` | Front index pointer |  |
| `std::size_t back_` | Back insertion index |  |

### **Methods**

| Operation                          | Explanation                                                                                                                        |
|:-----------------------------------|:-----------------------------------------------------------------------------------------------------------------------------------|
| `ABDQ()`                           | Default Constructor. Default `capacity_` to 4, <br/>`size_` to 0, `front_` and `back_` to 0, and <br/>create buffer array `data_`. |
| `ABDQ(const std::size_t capacity)` | Parameterized Constructor. Same behavior as default, <br/>however set `capacity_` to `capacity`                                    |
| `pushFront()` / `pushBack()`       | Insert element from either end                                                                                                     |
| `popFront()` / `popBack()`         | Remove element from either end                                                                                                     |
| `front()` / `back()`               | Access extremities                                                                                                                 |
| `ensureCapacity()`                 | Resizes to `capacity_ * 2`                                                                                                         |
| `shrinkIfNeeded()`                 | Reduces to half when sparse                                                                                                        |
| `PrintForward()`                   | Traverses queue order                                                                                                              |
| `PrintReverse()`                   | Traverses reverse order                                                                                                            |

**All array-based classes must implement the Big 5** to safely transfer `data_` ownership during copies and moves.

***

## **6. Summary Hierarchy**

```
             (Interfaces)
     ┌─────────────────────────────┐
     │  StackInterface<T>          │
     │  QueueInterface<T>          │
     │  DequeInterface<T>          │
     └────────────┬────────────────┘
                  │
        ┌─────────┼────────────────────┐
        │          │                    │
   Array-Based   Linked-List           Deque
     (ABS/ABQ)   (LLS/LLQ)          (LLDQ/ABDQ)
```


***

## **7. Implementation Expectations**

1. **Every class with dynamic memory** must explicitly define all **five special member functions** (The Big 5):
    - Destructor
    - Copy Constructor
    - Copy Assignment
    - Move Constructor
    - Move Assignment
2. **LinkedList-based classes** should **delegate these for internal list members**:
    - The contained `LinkedList<T>` handles its Big Five.
    - Derived objects correctly follow composition semantics.
These functions enhance debugging and visual validation for every ADT.
3. **Interfaces define contract, not storage.**
None of the interfaces inherit `LinkedList<T>` — instead, concrete `LLS`, `LLQ`, and `LLDQ` **include** a list as a private attribute.

***

