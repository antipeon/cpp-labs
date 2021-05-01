#include <iostream>

#include "circular_buffer.hpp"

template <typename Buffer>
void PrintBuffer(Buffer&& buffer) {
  for (auto&& i : buffer) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

template <typename Buffer>
void PrintReverseBuffer(Buffer&& buffer) {
  for (auto it = buffer.rbegin(); it != buffer.rend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

template <typename Buffer>
void InsertSomeElements(Buffer&& buffer) {
  buffer.PushBack(1);
  buffer.PushBack(2);
  buffer.PushBack(3);
  buffer.PopFront();
  buffer.PopFront();
  buffer.PushBack(4);
  buffer.PushFront(5);
  buffer.PushFront(6);
  buffer.PushFront(7);
}

void TestIterators() {
  std::cout << "Testing (-reverse)Iterators..." << std::endl;
  size_t capacity = 4;
  CircularBuffer<int32_t> buffer(capacity);
  InsertSomeElements(buffer);
  PrintBuffer(buffer);
  PrintReverseBuffer(buffer);
}

void TestChangeCapacity() {
  std::cout << "Testing ChangeCapacity..." << std::endl;
  size_t capacity = 4;
  CircularBuffer<int32_t> buffer(capacity);
  InsertSomeElements(buffer);
  std::cout << "capacity = " << capacity << ": " << std::endl;
  PrintBuffer(buffer);

  capacity = 3;
  buffer.ChangeCapacity(capacity);
  std::cout << "new decreased capacity = " << capacity << ": " << std::endl;
  PrintBuffer(buffer);

  capacity = 9;
  buffer.ChangeCapacity(capacity);
  std::cout << "new increased capacity = " << capacity << ": " << std::endl;
  PrintBuffer(buffer);
}

int main() {
  TestIterators();
  std::cout << std::endl;
  TestChangeCapacity();
  return 0;
}
