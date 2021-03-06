/* CoreUtil.hpp
 *
 * Kubo Ryosuke
 */

#ifndef SUNFISH_CORE_UTIL_COREUTIL_HPP__
#define SUNFISH_CORE_UTIL_COREUTIL_HPP__

#include "../position/Bitboard.hpp"
#include "../move/MoveTables.hpp"

namespace sunfish {

class CoreUtil {
public:

  static void initialize() {
    Bitboard::initialize();
    MoveTables::initialize();
    AggressableTables::initialize();
  }

private:

  CoreUtil();

};

}

#endif // SUNFISH_CORE_UTIL_COREUTIL_HPP__
