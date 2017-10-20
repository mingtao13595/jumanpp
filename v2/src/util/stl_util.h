//
// Created by Arseny Tolmachev on 2017/02/28.
//

#ifndef JUMANPP_STL_UTIL_H
#define JUMANPP_STL_UTIL_H

#include <algorithm>
#include <initializer_list>
#include "common.hpp"

namespace jumanpp {
namespace util {

template <typename C, typename I>
inline bool contains(const C& c, const I& i) {
  for (auto&& x : c) {
    if (x == i) {
      return true;
    }
  }
  return false;
}

template <typename T>
inline bool contains(std::initializer_list<T> data, const T& obj) {
  return contains<std::initializer_list<T>, T>(data, obj);
}

template <typename C1, typename C2>
inline void copy_insert(const C1& data, C2& result) {
  std::copy(std::begin(data), std::end(data), std::back_inserter(result));
}

template <typename C1, typename C2>
inline void copy_buffer(const C1& data, C2& result) {
  JPP_DCHECK_GE(result.size(), data.size());
  std::copy(std::begin(data), std::end(data), std::begin(result));
}

template <typename C1, typename Fn = std::less<typename C1::value_type>>
inline void sort(C1& c, Fn fn = Fn()) {
  std::sort(std::begin(c), std::end(c), fn);
};

template <typename C, typename T>
inline void fill(C& c, const T& t) {
  std::fill(std::begin(c), std::end(c), t);
};

template <typename It, typename Comp>
It part_step(It start, It end, Comp comp) {
  auto sz = std::distance(start, end);
  It pivot{start};
  std::advance(pivot, sz / 2);
  std::swap(*pivot, *start);
  pivot = start;
  ++start;
  --end;
  while (start != end) {
    if (comp(*start, *pivot)) {
      ++start;
    } else {
      std::swap(*start, *end);
      --end;
    }
  }
  std::swap(*pivot, *start);
  return start;
}

template <typename It, typename Comp>
It partition(It start, It end, Comp comp, size_t minSize, size_t maxSize) {
  std::nth_element(start, start + minSize, end, comp);
  return start + minSize;
};

}  // namespace util
}  // namespace jumanpp

#endif  // JUMANPP_STL_UTIL_H
