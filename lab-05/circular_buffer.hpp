#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <cstddef>
#include <cstdint>

template <typename T>
class CircularBuffer {
 public:
  CircularBuffer() = default;
  CircularBuffer(size_t capacity);
  CircularBuffer(const CircularBuffer&);
  // CircularBuffer(CircularBuffer&&);

  ~CircularBuffer();

  CircularBuffer& operator=(const CircularBuffer&);
  // CircularBuffer& operator=(CircularBuffer&&);

  void PushFront(const T&);
  T PopFront();
  void PushBack(const T&);
  // void PushBack(T&&);
  void PopBack();

  T& front();
  const T& front() const;
  T& back();
  const T& back() const;

  T& operator[](size_t i);
  const T& operator[](size_t i) const;

  void ChangeCapacity(int32_t new_capacity);
  size_t size() const { return size_; };

 private:
  size_t size_;
  size_t capacity_;

  T* ptr_ = nullptr;
  T* start_;

  size_t index(size_t i) const { return (start_ - ptr_ + i) % capacity_; };
};

//#include "circular_buffer-impl.hpp"

#endif  // CIRCULARBUFFER_HPP
