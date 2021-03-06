/* Random.hpp
 *
 * Kubo Ryosuke
 */

#ifndef SUNFISH_COMMON_MATH_RANDOM_HPP__
#define SUNFISH_COMMON_MATH_RANDOM_HPP__

#include "../Def.hpp"
#include <random>
#include <ctime>
#include <cstdint>

namespace sunfish {

template <class GenType>
class BaseRandom {
public:
  BaseRandom() : rgen(static_cast<unsigned>(time(NULL))) {
  }
  BaseRandom(const BaseRandom&) = delete;
  BaseRandom(BaseRandom&&) = delete;

  uint16_t int16() {
    std::uniform_int_distribution<uint16_t> dst16;
    return dst16(rgen);
  }

  uint16_t int16(uint16_t num) {
    std::uniform_int_distribution<uint16_t> dst16(0, num-1);
    return dst16(rgen);
  }

  uint32_t int32() {
    std::uniform_int_distribution<uint32_t> dst32;
    return dst32(rgen);
  }

  uint32_t int32(uint32_t num) {
    std::uniform_int_distribution<uint32_t> dst32(0, num-1);
    return dst32(rgen);
  }

  uint64_t int64() {
    std::uniform_int_distribution<uint64_t> dst64;
    return dst64(rgen);
  }

  uint64_t int64(uint64_t num) {
    std::uniform_int_distribution<uint64_t> dst64(0, num-1);
    return dst64(rgen);
  }

  unsigned bit() {
    std::uniform_int_distribution<unsigned> dstBit(0, 1);
    return dstBit(rgen);
  }

  template <class T>
  unsigned nonuniform(unsigned num, T&& weightFunc) {
    uint64_t total = 0;
    for (unsigned i = 0; i < num; i++) {
      total += weightFunc(i);
    }

    uint64_t r = int64(total);

    for (unsigned i = 0; i < num - 1; i++) {
      uint64_t w = weightFunc(i);
      if (r < w) {
        return i;
      }
      r -= w;
    }
    return num - 1;
  }

  template <class Iterator>
  void shuffle(Iterator begin, Iterator end) {
    size_t n = end - begin;
    for (size_t i = 0; i + 1 < n; i++) {
      size_t t = i + int64(n - i);
      auto tmp = begin[i];
      begin[i] = begin[t];
      begin[t] = tmp;
    }
  }

private:
  GenType rgen;

};

using Random = BaseRandom<std::mt19937>;

} // namespace sunfish

#endif //SUNFISH_COMMON_MATH_RANDOM_HPP__
