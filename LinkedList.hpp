#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
  struct Node {
    T data;
    Node* prev;
    Node* next;
  };

  Node* head;
  Node* tail;
  unsigned int count;

	static void PrintForwardRecr(Node* node) {
    if(!node) { return; }

    std::cout << ' ' << node->data;
    PrintForwardRecr(node->next);
  }


  static void PrintReverseRecr(Node* node) {
    if(!node) { return; }

    std::cout << ' ' << node->data;
    PrintReverseRecr(node->prev);
  }

public:
	// Behaviors
	void printForward() const {
		if(!head) { return; }
		std::cout << ' ' << head->data;

    PrintForwardRecr(head->next);
    std::cout << std::endl;
	}
	
	void printReverse() const {
		if(!tail) { return; }
    std::cout << ' ' << tail->data;

    PrintForwardRecr(tail->prev);
    std::cout << std::endl;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return count; }
	Node* getHead() { return head; }
	const Node* getHead() const { return head; }
	Node* getTail() { return tail; }
	const Node* getTail() const {return tail; }

	// Insertion
	void addHead(const T& data) {
    // First, construct a node using data
    Node* head = new Node{
      data,
      nullptr,
      this->head
    };

    // Then, insert the node where it belongs.
    if (!this->head) {
      this->head = this->tail = head;
    }
    else {
      this->head->prev = head;
      this->head = head;
    }

    ++count;
	}
	
	void addTail(const T& data) {
    // First, construct a node using data
    Node* tail = new Node{
      data,
      this->tail,
      nullptr
    };

    if (!this->tail) {
      this->tail = this->head = tail;
    }
    else {
      this->tail->next = tail;
      this->tail = tail;
    }

    ++count;
	}

	// Removal
	bool removeHead() {
		if (!this->head) { return false; }

		--count;
    if (this->head == this->tail) {
      delete this->head;
      this->head = this->tail = nullptr;
      return true;
    }
  
    /*
    Node* next = this->head->next;
    delete this->head;
    if (next) {
    	next->prev = nullptr;
	    this->head = next;
    } else {
    	this->head = this->tail = nullptr;
    }*/

    Node* next = this->head->next;
    delete this->head;
    next->prev = nullptr;
    this->head = next;

    return true;
  }
  
	bool removeTail() {
		if (!this->tail) { return false; }

		--count;
    if (this->head == this->tail) {
      delete this->head;
      this->head = this->tail = nullptr;
      return true;
    }
    
    Node* prev = this->tail->prev;
    delete this->tail;
    if (prev) {
    	prev->next = nullptr;
	    this->tail = prev;
    } else {
    	this->tail = this->head = nullptr;
    }

    return true;
  }
  
	void clear() {
		while(removeHead());
  }

private:
  void CopyNodeChain(Node* head) {
    if (!head) { return; }
    addTail(head->data);
    CopyNodeChain(head->next);
  }

public:
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
    clear();
    CopyNodeChain(rhs.head);
    count = rhs.count;
    return *this;
	}
	
	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) {
		CopyNodeChain(list.head);
    count = list.count;
	}

	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
	}
	
	~LinkedList() {
		clear();
		head = tail = nullptr;
		count = 0;
	}
};


