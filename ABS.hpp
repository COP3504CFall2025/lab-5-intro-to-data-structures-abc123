#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS(){
        capacity_ =1;
        curr_size_ = 0;
        array_=nullptr;
    }
    explicit ABS(const size_t capacity){
        capacity_ =  capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }
    ABS(const ABS& other){
        capacity_ =  other.capacity;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for(int i =0; i<curr_size_;i++){
            array_[i] = other.array[i];
        }
    }
    ABS& operator=(const ABS& rhs){
        if(this==&rhs){return *this;}
        delete[] array_;
        capacity_ =  rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];
        for(int i =0; i<curr_size_;i++){
            array_[i] = rhs.array[i];
        }
        return *this;
    }

    ABS(ABS&& other) noexcept{
        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        other.array_=nullptr;
        other.curr_size_ =0;
        other.capacity_ =0;
    }
    ABS& operator=(ABS&& other) noexcept{
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

    ~ABS() noexcept override{
        delete[] array_;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override{return curr_size_;}

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept{return capacity_;}

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept{return array_;}

    // Push item onto the stack
    void push(const T& data) override{
        if(capacity_ == 0){
            capacity_ = 1;
            array_ = new T[capacity_];
        }
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
        if(curr_size_!=0){return array_[curr_size_-1];}
        throw std::runtime_error("Empty ABS");

}

//if curr_size <= capacity / 4; capacity /= 2;
    T pop() override{
        if(curr_size_==0){
            throw std::runtime_error("empty pop");
        }
        T temp_t = array_[curr_size_-1];
        curr_size_--;
        if(curr_size_ > 0 && curr_size_<=capacity_/4){
        int newCap = capacity_ / 2;
        T* newArr = new T[newCap];
        for(int i =0; i<curr_size_;i++){
            newArr[i] = array_[i];
        }
        delete[] array_;
        array_ = newArr;
        newArr = nullptr;
        capacity_ = newCap;
        }
        return temp_t;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
