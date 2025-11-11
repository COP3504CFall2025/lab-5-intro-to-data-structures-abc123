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
    LLQ(){
        list = LinkedList<T>();
    }

    // Insertion
    void enqueue(const T& item) override{
        list.addTail(item);
    }

    // Deletion
    T dequeue() override{
        if(list.getCount()==0){throw std::runtime_error("empty pop");}
        T temp = list.getHead()->data;
        list.removeHead();
        return temp;
    }

    // Access
    T peek() const override{
        return list.getHead();
    }

    // Getter
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }

};