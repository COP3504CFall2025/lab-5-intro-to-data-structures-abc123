#pragma once
#include <iostream>
using namespace std;


template <typename T>
class LinkedList {
public:
		struct Node {
		T data;
		Node* prev;
		Node* next;
	};

	// Behaviors
	void printForward() const{
		Node* curNode = head;
		while(curNode!=nullptr){
			std::cout<<curNode->data<<std::endl;
		    curNode = curNode->next;
		}
	}


	void printReverse() const{
		Node* curNode = tail;
		while(curNode!=nullptr){
			std::cout<<curNode->data<<std::endl;
		    curNode = curNode->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{
		return count;
	}
	Node* getHead(){
		return head;
	}
	const Node* getHead() const{
		return head;
	}
	Node* getTail(){
		return tail;
	}
	const Node* getTail() const{
		return tail;
	}

	// Insertion
	void addHead(const T& data){
		Node* cur = new Node{data, nullptr, head};
		if(head!=nullptr)head->prev = cur;
		head = cur;
		if(tail==nullptr) tail = cur;
		count++;
	}
	void addTail(const T& data){
		Node* cur = new Node{data, tail, nullptr};
		if(tail!=nullptr)tail->next = cur;
		tail = cur;
		if(head==nullptr)head = cur;
		count++;
	}

	// Removal
	bool removeHead(){
		if(head == nullptr){return false;}
		if(count == 1){
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}
		Node* head_x = head;
		head = head->next;
		head->prev = nullptr;
		delete head_x;
		count--;
		return true;
	}

	bool removeTail(){
		if(tail == nullptr){return false;}
		if(count == 1){
			delete tail;
			count--;
			head = nullptr;
			tail = nullptr;
			return true;
		}
		Node* tail_x = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete tail_x;
		count--;
		return true;
	}

	void clear(){
		while(removeHead()){}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if(this == &other ){return *this;}
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
//1=1
//do not clear untill full copy
	LinkedList<T>& operator=(const LinkedList<T>& other){
		if(this == &other ){return *this;}
		LinkedList temp = LinkedList();
		Node* curNode = other.head;
		while(curNode!=nullptr){
			temp.addTail(curNode->data);
		    curNode = curNode->next;
		}
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(count, temp.count);


		return *this;


	}

	// Construction/Destruction
	LinkedList(){
		Node* node = nullptr;
		count = 0;
		head = node;
		tail = node;
	}

	LinkedList(const LinkedList<T>& list){
		Node* node = nullptr;
		count = 0;
		head = node;
		tail = node;
		Node* curNode = list.head;
		while(curNode!=nullptr){
			addTail(curNode->data);
		    curNode = curNode->next;
		}

	}

	LinkedList(LinkedList<T>&& other) noexcept{
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList(){
		Node* curNode = head;
		Node* node_x  = curNode;
		while(curNode!=nullptr){
			node_x  = curNode;
		    curNode = curNode->next;
			delete node_x;
		}

	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


