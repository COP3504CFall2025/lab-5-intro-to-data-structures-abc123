#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
    public:
    virtual void push(const T& item) = 0;
    virtual T pop() =0;
    virtual T peek() const = 0;
    virtual std::size_t getSize() const noexcept =0;
    virtual ~StackInterface() = default;
};


template <typename T>
class QueueInterface {
    public:
    virtual void enqueue(const T& item) =0;
    virtual T dequeue() =0;
    virtual T peek() const =0;
    virtual std::size_t getSize() const noexcept =0;
    virtual ~QueueInterface() = default;
};


template <typename T>
class DequeInterface {
    virtual void pushFront(const T& item);
    virtual void pushBack(const T& item);
    virtual T popFront();
    virtual T popBack();
    virtual const T& front() const;
    virtual const T& back() const;
    virtual std::size_t getSize() const noexcept;
    virtual ~DequeInterface() = default;
};

