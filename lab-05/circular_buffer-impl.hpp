#ifndef CIRCULAR_BUFFERIMPL_HPP
#define CIRCULAR_BUFFERIMPL_HPP

#include "circular_buffer.hpp"

template <typename T>
CircularBuffer<T>::CircularBuffer(size_t capacity)
    : capacity_{capacity}, size_{0} {
  ptr_ = new T[capacity];
  start_ = ptr_;
}

template<typename T>
T& CircularBuffer<T>::operator[](size_t i) {
    return ptr_[index(i)];
}

template<typename T>
const T& CircularBuffer<T>::operator[](size_t i) const {
    return ptr_[index(i)];
}

template <typename T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer& buffer)
    : size_{buffer.size_},
      capacity_{buffer.capacity_},
      ptr_{static_cast<T*>(new (T[buffer.capacity_]))} {
  for (size_t i = 0; i < size_; i++) {
    operator[](i) = buffer[i];
  }
  start_ = ptr_;
}

template <typename T>
CircularBuffer<T>::~CircularBuffer() {
  for (size_t i = 0; i < capacity_; i++) {
    ptr_[i].~T();
  }
  delete[] ptr_;
}

template <typename T>
CircularBuffer<T>& CircularBuffer<T>::operator=(const CircularBuffer& buffer) {
  size_ = buffer.size;
  capacity_ = buffer.capacity_;
  start_ = buffer.start_;
  for (size_t i = 0; i < size_; i++) {
    operator[](i) = buffer[i];
  }
  return *this;
}

template<typename T>
T& CircularBuffer<T>::front() {
    return operator[](0);
}

template<typename T>
const T& CircularBuffer<T>::front() const {
    return this->operator[](0);
}

template<typename T>
T& CircularBuffer<T>::back() {
    return operator[](size_ - 1);
}

template<typename T>
const T& CircularBuffer<T>::back() const {
    return operator[](size_ - 1);
}

template<typename T>
void CircularBuffer<T>::PushBack(const T& element) {
    if (size_ != capacity_) {
        ++size_;
    } else {
        ++start_;
    }
    back() = element;
}


#endif  // CIRCULAR_BUFFERIMPL_HPP
