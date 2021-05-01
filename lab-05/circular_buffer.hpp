#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <iterator>

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
  // void PushFront(T&&);
  const T PopFront();
  void PushBack(const T&);
  // void PushBack(T&&);
  const T PopBack();

  const T& front() const;
  T& front();
  const T& back() const;
  T& back();
  const T& operator[](size_t i) const;
  T& operator[](size_t i);

  void ChangeCapacity(size_t new_capacity);
  size_t size() const { return size_; }

  // random access iterator
  class iterator {
   private:
    T* ptr_;
    size_t size_;
    size_t capacity_;
    T* cur_;
    T* start_;
    int64_t diff_from_start_;

   public:
    iterator(T* ptr, T* cur, size_t size, size_t capacity, T* start,
             int64_t diff_from_start)
        : ptr_{ptr},
          cur_{cur},
          size_{size},
          diff_from_start_{diff_from_start},
          capacity_{capacity},
          start_{start} {}

    iterator& operator=(const iterator& iterator) = default;

    iterator& operator+=(size_t);
    iterator& operator++();
    iterator operator++(int);
    iterator operator+(size_t) const;
    iterator& operator-=(size_t);
    iterator& operator--();
    iterator operator--(int);
    iterator operator-(size_t) const;

    T& operator*();
    T& operator[](size_t);

    auto operator-(const iterator& iterator) const;

    bool operator==(const iterator& iterator) const;
    bool operator!=(const iterator& iterator) const;
    bool operator<(const iterator& iterator) const;
    bool operator>(const iterator& iterator) const;

    // typedefs for iterator_traits
    typedef std::random_access_iterator_tag iterator_category;
    typedef decltype(std::declval<iterator>() -
                     std::declval<iterator>()) difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
  };

  typedef std::reverse_iterator<iterator> reverse_iterator;

  iterator begin() {
    return iterator(ptr_, start_, size_, capacity_, start_, 0);
  }
  iterator end() {
    return iterator(ptr_, ptr_ + index(size_), size_, capacity_, start_, size_);
  }

  reverse_iterator rbegin() { return std::make_reverse_iterator(end()); }
  reverse_iterator rend() { return std::make_reverse_iterator(begin()); }

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;

  T* ptr_ = nullptr;
  T* start_ = nullptr;

  size_t index(size_t i) const { return (start_ - ptr_ + i) % capacity_; };
};

#endif  // CIRCULARBUFFER_HPP

#include "circular_buffer-impl.hpp"
