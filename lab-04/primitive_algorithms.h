#ifndef PRIMITIVE_ALGORITHMS_H
#define PRIMITIVE_ALGORITHMS_H

namespace kinda_std {

template<typename InputIterator, typename Predicate>
bool all_of(InputIterator first, InputIterator last, Predicate p);

template<typename InputIterator, typename Predicate>
bool any_of(InputIterator first, InputIterator last, Predicate p);

template<typename InputIterator, typename Predicate>
bool none_of(InputIterator first, InputIterator last, Predicate p);

template<typename InputIterator, typename Predicate>
bool one_of(InputIterator first, InputIterator last, Predicate p);

template<typename InputIterator, typename Comparator>
bool is_sorted(InputIterator first, InputIterator last, Comparator compare);

} // namespace kinda_std



#include "primitive_algorithms-impl.h"

#endif // PRIMITIVE_ALGORITHMS_H
