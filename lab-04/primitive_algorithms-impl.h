#include <vector>
#include <cstdint>


namespace kinda_std {
template<typename InputIterator, typename Predicate>
bool all_of(InputIterator first, InputIterator last, Predicate p) {
  for (InputIterator it = first; it != last; ++it) {
    if (!p(*it)) {
      return false;
    }
  }
  return true;
}


template<typename InputIterator, typename Predicate>
bool any_of(InputIterator first, InputIterator last, Predicate p) {
  return !all_of(first, last, !p);
}

template<typename InputIterator, typename Predicate>
bool none_of(InputIterator first, InputIterator last, Predicate p) {
  return all_of(first, last, !p);
}

template<typename InputIterator, typename Predicate>
bool one_of(InputIterator first, InputIterator last, Predicate p) {
  bool found = false;
  for (InputIterator it = first; it != last; ++it) {
    if (p(*it)) {
      if (!found) {
        found = true;
      } else {
        //more than one
        return false;
      }
    }
  }
  return found;
}

template<typename ForwardIterator, typename Comparator>
bool is_sorted(ForwardIterator first, ForwardIterator last, Comparator compare) {
  for (ForwardIterator it = first; it != last; ++it) {
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



template <typename T>
struct Less {
  bool operator()(const T& left_arg, const T& right_arg) const {
    return left_arg < right_arg;
  }
};

template <typename T>
struct LessThan {
  T less_than;
  LessThan(const T& less_than) : less_than(less_than) {}
  bool operator()(T item) const {
    return item < less_than;
  }
};

} // namespace kinda_std





