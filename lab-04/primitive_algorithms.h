#ifndef PRIMITIVE_ALGORITHMS_H
#define PRIMITIVE_ALGORITHMS_H

namespace kinda_std {

template <typename InputIterator, typename Predicate>
bool all_of(InputIterator first, InputIterator last, const Predicate& p);

template <typename InputIterator, typename Predicate>
bool any_of(InputIterator first, InputIterator last, const Predicate& p);

template <typename InputIterator, typename Predicate>
bool none_of(InputIterator first, InputIterator last, const Predicate& p);

template <typename InputIterator, typename Predicate>
bool one_of(InputIterator first, InputIterator last, const Predicate& p);

template <typename InputIterator, typename Comparator>
bool is_sorted(InputIterator first, InputIterator last,
               const Comparator& compare);

template <typename InputIterator, typename Predicate>
bool is_partitioned(InputIterator first, InputIterator last,
                    const Predicate& p);

template <typename InputIterator, typename T>
InputIterator find_not(InputIterator first, InputIterator last,
                       const T& element);

template <typename BidirectionalIterator, typename T>
BidirectionalIterator find_backward(BidirectionalIterator first,
                                    BidirectionalIterator last,
                                    const T& element);

template <typename BidirectionalIterator, typename Predicate>
bool is_palindrome(BidirectionalIterator first, BidirectionalIterator last,
                   const Predicate& p);

}  // namespace kinda_std

#include "primitive_algorithms-impl.h"

#endif  // PRIMITIVE_ALGORITHMS_H
