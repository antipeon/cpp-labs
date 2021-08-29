#ifndef CIRCULAR_BUFFERIMPL_HPP
#define CIRCULAR_BUFFERIMPL_HPP

#include "circular_buffer.hpp"

template <typename T>
CircularBuffer<T>::CircularBuffer(size_t capacity)
    : capacity_{capacity}, size_{0} {
  ptr_ = new T[capacity];
  start_ = ptr_;
}

template <typename T>
T& CircularBuffer<T>::operator[](size_t i) {
  return ptr_[index(i)];
}

template <typename T>
const T& CircularBuffer<T>::operator[](size_t i) const {
  return ptr_[index(i)];
}

template <typename T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer& buffer)
    : size_{buffer.size_},
      capacity_{buffer.capacity_},
      ptr_{new T[buffer.capacity_]} {
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

template <typename T>
T& CircularBuffer<T>::front() {
  return operator[](0);
}

template <typename T>
const T& CircularBuffer<T>::front() const {
  return operator[](0);
}

template <typename T>
T& CircularBuffer<T>::back() {
  return operator[](size_ - 1);
}

template <typename T>
const T& CircularBuffer<T>::back() const {
  return operator[](size_ - 1);
}

template <typename T>
void CircularBuffer<T>::PushBack(const T& element) {
  if (size_ != capacity_) {
    ++size_;
  } else {
    ++start_;
  }
  back() = element;
}

template <typename T>
const T CircularBuffer<T>::PopBack() {
  const auto& return_value = back();
  --size_;
  return return_value;
}

template <typename T>
void CircularBuffer<T>::PushFront(const T& element) {
  if (size_ != capacity_) {
    ++size_;
  }

  // decrement start circularly
  if (start_ != ptr_) {
    --start_;
  } else {
    start_ = ptr_ + capacity_ - 1;
  }

  front() = element;
}

template <typename T>
const T CircularBuffer<T>::PopFront() {
  const auto& return_value = front();
  --size_;

  // increment start_ circularly
  if (start_ - ptr_ == capacity_ - 1) {
    start_ = ptr_;
  } else {
    ++start_;
  }

  return return_value;
}

template <typename T>
void CircularBuffer<T>::ChangeCapacity(size_t new_capacity) {
  auto new_ptr = new T[new_capacity];
  const auto new_size = std::min(size_, new_capacity);
  for (size_t i = 0; i < new_size; i++) {
    new_ptr[i] = operator[](i);
  }
  delete[] ptr_;
  size_ = new_size;
  capacity_ = new_capacity;
  ptr_ = start_ = new_ptr;
}

// iterator
template <typename T>
typename CircularBuffer<T>::iterator& CircularBuffer<T>::iterator::operator+=(
    size_t i) {
  cur_ = ptr_ + (cur_ - ptr_ + i) % capacity_;
  diff_from_start_ += i;
  return *this;
}

template <typename T>
typename CircularBuffer<T>::iterator&
CircularBuffer<T>::iterator::operator++() {
  return *this += 1;
}

template <typename T>
typename CircularBuffer<T>::iterator CircularBuffer<T>::iterator::operator++(
    int) {
  auto return_iterator = *this;
  *this += 1;
  return return_iterator;
}

template <typename T>
typename CircularBuffer<T>::iterator CircularBuffer<T>::iterator::operator+(
    size_t i) const {
  auto return_iterator = *this;
  return return_iterator += i;
}

template <typename T>
typename CircularBuffer<T>::iterator& CircularBuffer<T>::iterator::operator-=(
    size_t i) {
  cur_ = ptr_ + (cur_ - ptr_ - i + capacity_) % capacity_;
  diff_from_start_ -= i;
  return *this;
}

template <typename T>
typename CircularBuffer<T>::iterator&
CircularBuffer<T>::iterator::operator--() {
  return *this -= 1;
}

template <typename T>
typename CircularBuffer<T>::iterator CircularBuffer<T>::iterator::operator--(
    int) {
  auto return_iterator = *this;
  *this -= 1;
  return return_iterator;
}

template <typename T>
typename CircularBuffer<T>::iterator CircularBuffer<T>::iterator::operator-(
    size_t i) const {
  auto return_iterator = *this;
  return return_iterator -= i;
}

template <typename T>
T& CircularBuffer<T>::iterator::operator*() {
  return *cur_;
}

template <typename T>
T& CircularBuffer<T>::iterator::operator[](size_t i) {
  return *(*this + i);
}

template <typename T>
auto CircularBuffer<T>::iterator::operator-(const iterator& iterator) const {
  return diff_from_start_ - iterator.diff_from_start_;
}

template <typename T>
bool CircularBuffer<T>::iterator::operator==(const iterator& iterator) const {
  return diff_from_start_ == iterator.diff_from_start_;
}

template <typename T>
bool CircularBuffer<T>::iterator::operator!=(const iterator& iterator) const {
  return !(*this == iterator);
}

template <typename T>
bool CircularBuffer<T>::iterator::operator<(const iterator& iterator) const {
  return (iterator - *this) > 0;
}

template <typename T>
bool CircularBuffer<T>::iterator::operator>(const iterator& iterator) const {
  return iterator < *this;
}

#endif  // CIRCULAR_BUFFERIMPL_HPP
