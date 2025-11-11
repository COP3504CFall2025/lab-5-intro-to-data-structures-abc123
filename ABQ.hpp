#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Big 5 + Parameterized Constructor
    ABQ(){
        capacity_ =1;
        curr_size_ = 0;
        array_=new T[1];
    }
    explicit ABQ(const size_t capacity){
        capacity_ =  capacity;
        if(capacity_==0)capacity_=1;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }
    ABQ(const ABQ& other){
        capacity_ =  other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for(int i =0; i<curr_size_;i++){
            array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs){
        if(this==&rhs){return *this;}
        delete[] array_;
        capacity_ =  rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];
        for(int i =0; i<curr_size_;i++){
            array_[i] = rhs.arrayz_[i];
        }
        return *this;
    }

    ABQ(ABQ&& other) noexcept{
        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        other.array_=nullptr;
        other.curr_size_ =0;
        other.capacity_ =0;
    }
    ABQ& operator=(ABQ&& other) noexcept{
        if(this==&other){return *this;}
        delete[] array_;
        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        other.array_=nullptr;
        other.curr_size_ =0;
        other.capacity_ =0;
        return *this;
    }

    ~ABQ() noexcept override{
        delete[] array_;
    }

    // Get the number of items in the ABQ
    [[nodiscard]] size_t getSize() const noexcept override{return curr_size_;}

    // Get the max size of the ABQ
    [[nodiscard]] size_t getMaxCapacity() const noexcept{return capacity_;}

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept{return array_;}

    // Push item onto the stack
    void enqueue(const T& data) override{
        /*
        if(capacity_ == 0){
            capacity_ = 1;
            array_ = new T[capacity_];
        }*/

        if(curr_size_ == capacity_){
            T* temp = new T[capacity_*scale_factor_];
            for(int i =0; i<curr_size_; i++){temp[i]=array_[i];}
                delete[] array_;
                array_ = temp;
                temp = nullptr;
                capacity_ = capacity_*scale_factor_;
        }
        curr_size_++;
        array_[curr_size_-1] = data;
    }

    T peek() const override{
        if(curr_size_!=0){
        throw std::runtime_error("Empty ABQ");}
        return array_[0];
}

//if curr_size <= capacity / 4; capacity /= 2;
    T dequeue() override{
        if(curr_size_==0){
            throw std::runtime_error("empty dequeue");
        }
        T temp_t = array_[0];

        curr_size_--;

        //moves all of the data up one and writes over array_[0]
        for(int i =0; i<curr_size_; i++){
            array_[i]=array_[i+1];
        }


        if(capacity_ > 1 && curr_size_<=(capacity_/4)){

            capacity_/=2;
            T* newArr = new T[capacity_];
            for(int i =0; i<curr_size_;i++){
                newArr[i] = array_[i];
            }
            delete[] array_;
            array_ = newArr;
            newArr = nullptr;
        }

        return temp_t;
    }
/*
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept override;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override;
    [[nodiscard]] size_t getMaxCapacity() const noexcept;
    [[nodiscard]] T* getData() const noexcept;

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;
    */

};
