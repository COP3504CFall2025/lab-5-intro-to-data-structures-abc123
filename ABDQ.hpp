#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data;                 // underlying dynamic array
    std::size_t capacity;    // total allocated capacity
    std::size_t size;        // number of stored elements
    std::size_t front_;       // index of front_ element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ(){
        capacity = 1;
        data = new T[capacity];
        size =0;
        front_ =0;
        back_=0;
    }
    explicit ABDQ(std::size_t capacity_){
        capacity = capacity_;
        data = new T[capacity];
        size =0;
        front_ =0;
        back_=0;
    }

    ABDQ(const ABDQ& other){
        capacity = other.capacity;
        size =other.size;
        front_ =other.front_;
        back_=other.back_;
        data = new T[capacity];

        for(int i =0; i<capacity; i++ ){
            data[i] = other.data[i];
        }
    }

    ABDQ(ABDQ&& other) noexcept{

        capacity = other.capacity;
        size =other.size;
        front_ =other.front_;
        back_=other.back_;
        data = other.data;

        other.capacity =1;
        other.size =0;
        other.front_ =0;
        other.back_=0;
        other.data =nullptr;
    }

    ABDQ& operator=(const ABDQ& other){
        if(this==&other){return *this;}
        delete[] data;
        capacity =  other.capacity;
        size = other.size;
        data= new T[capacity];
        for(int i =0; i<capacity;i++){
            data[i] = other.data[i];
        }
        return *this;

    }
    ABDQ& operator=(ABDQ&& other) noexcept{
        if(this==&other){return *this;}
        capacity = other.capacity;
        size =other.size;
        front_ =other.front_;
        back_=other.back_;
        data = other.data;

        other.capacity =1;
        other.size =0;
        other.front_ =0;
        other.back_=0;
        other.data =nullptr;

        return *this;
    }
    ~ABDQ() override{
        delete[] data;
    }

    // Insertion
    void pushFront(const T& item) override{
        if(capacity == 0){capacity = 1;
        data = new T[capacity];
        front_ =0;
        back_ =0;
        data[0] =item;
        size =1;
        return;
    }
        if(size == capacity){
            T* temp = new T[capacity*SCALE_FACTOR];
            for(int i =0; i<capacity; i++){temp[i]=data[i];}
                delete[] data;
                data = temp;
                temp = nullptr;
                capacity = capacity*SCALE_FACTOR;
        }
//https://medium.com/@edwin.cloud/wrapping-your-head-around-circular-buffers-e84cbf549a04 wrap aroud formula
    //implement push front_
        front_ = (front_ - 1 + capacity) % capacity;
        data[front_] = item;
        size++;
    }
    void pushBack(const T& item) override{
        if(capacity == 0){capacity = 1;
        data = new T[capacity];
        front_ =0;
        back_ =0;
        data[0] =item;
        size =1;
        return;
    }
        if(size == capacity){
            T* temp = new T[capacity*SCALE_FACTOR];
            for(int i =0; i<capacity; i++){temp[i]=data[i];}
                delete[] data;
                data = temp;
                temp = nullptr;
                capacity = capacity*SCALE_FACTOR;
        }
    //implemet push back_
    back_ = (back_ + 1) % capacity;
    data[back_] = item;
    capacity++;
    }

    // Deletion
    T popFront() override{
        if(size==0){
            throw std::runtime_error("empty popFront");
        }
        T temp_T = data[front_];

        size--;
        front_ =(front_ + 1) % capacity;
        return temp_T;

    }

    T popBack() override{
        if(size==0){
            throw std::runtime_error("empty popBack");
        }
        T temp_T = data[back_];

        size--;
        back_ =(back_ - 1 + capacity) % capacity;
        return temp_T;
    }

    // Access
    const T& front() const override{return data[front_];}
    const T& back() const override{return data[back_];}

    // Getters
    std::size_t getSize() const noexcept override{return size;}

};
