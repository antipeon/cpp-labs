#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

namespace kinda_std {

template <typename InputIterator, typename Predicate>
bool all_of(InputIterator first, InputIterator last, const Predicate& p) {
  for (auto it = first; it != last; ++it) {
    if (!p(*it)) {
      return false;
    }
  }
  return true;
}

template <typename InputIterator, typename Predicate>
bool any_of(InputIterator first, InputIterator last, const Predicate& p) {
  return !all_of(first, last, !p);
}

template <typename InputIterator, typename Predicate>
bool none_of(InputIterator first, InputIterator last, const Predicate& p) {
  return all_of(first, last, !p);
}

template <typename InputIterator, typename Predicate>
bool one_of(InputIterator first, InputIterator last, const Predicate& p) {
  bool found = false;
  for (auto it = first; it != last; ++it) {
    if (p(*it)) {
      if (!found) {
        found = true;
      } else {
        // more than one
        return false;
      }
    }
  }
  return found;
}

template <typename ForwardIterator, typename Comparator>
bool is_sorted(ForwardIterator first, ForwardIterator last,
               const Comparator& compare) {
  for (auto it = first; it != last; ++it) {
    if (it == last) {
      break;
    }
    const auto& cur = *it;
    const auto& next = *(it + 1);
    if (!compare(cur, next)) {
      return false;
    }
  }
  return true;
}

template <typename InputIterator, typename Predicate>
bool is_partitioned(InputIterator first, InputIterator last,
                    const Predicate& p) {
  auto it = first;
  for (; it != last && p(*it); ++it)
    ;
  for (; it != last && !p(*it); ++it)
    ;
  if (it != last) {
    return false;
  }
  return true;
}

template <typename InputIterator, typename T>
InputIterator find_not(InputIterator first, InputIterator last,
                       const T& element) {
  for (auto it = first; it != last; ++it) {
    if (*it != element) {
      return it;
    }
  }
  return last;
}

template <typename BidirectionalIterator, typename T>
BidirectionalIterator find_backward(BidirectionalIterator first,
                                    BidirectionalIterator last,
                                    const T& element) {
  const auto r_first = std::make_reverse_iterator(last);
  const auto r_last = std::make_reverse_iterator(first);
  for (auto r_it = r_first; r_it != r_last; ++r_it) {
    if (*r_it == element) {
      return r_it.base() - 1;
    }
  }
  return last;
}

template <typename BidirectionalIterator, typename Predicate>
bool is_palindrome(BidirectionalIterator first, BidirectionalIterator last,
                   const Predicate& p) {
  for (; first != last && first != --last;) {
    if (!p(*(first++), *last)) {
      return false;
    }
  }
  return true;
}

template <typename T>
struct isLess {
  bool operator()(const T& left_arg, const T& right_arg) const {
    return left_arg < right_arg;
  }
};

template <typename T>
struct LessThan {
  T less_than;
  LessThan(const T& less_than) : less_than(less_than) {}
  bool operator()(T item) const { return item < less_than; }
};

template <typename T>
struct isMore {
  bool operator()(const T& left_arg, const T& right_arg) const {
    return right_arg < left_arg;
  }
};

template <typename T>
struct isEqual {
  bool operator()(const T& left_arg, const T& right_arg) const {
    return !(left_arg < right_arg || left_arg > right_arg);
  }
};

}  // namespace kinda_std
