#include <zisa/math/space_filling_curve.hpp>

namespace zisa {

std::tuple<std::bitset<2>, HilbertTable::orientation_t>
HilbertTable::operator()(const std::bitset<2> &coords,
                         orientation_t orientation) const {
  orientation_t SR = 0, SL = 1, NR = 2, NL = 3;
  orientation_t WU = 4, WD = 5, EU = 6, ED = 7;

  std::bitset<2> OO("00"), OI("01"), IO("10"), II("11");

  if (orientation == SR) {
    auto a = std::array<std::tuple<std::bitset<2>, orientation_t>, 4>{
        std::tuple{OO, WU}, {II, ED}, {OI, SR}, {IO, SR}};

    return a[coords.to_ulong()];
  }

  if (orientation == SL) {
    auto a = std::array<std::tuple<std::bitset<2>, orientation_t>, 4>{
        std::tuple{II, WD}, {OO, EU}, {IO, SL}, {IO, SR}};

    return a[coords.to_ulong()];
  }

  if (orientation == NR) {
    auto a = std::array<std::tuple<std::bitset<2>, orientation_t>, 4>{
        std::tuple{OI, NR}, {IO, NR}, {OO, WD}, {II, EU}};

    return a[coords.to_ulong()];
  }

  if (orientation == NL) {
    auto a = std::array<std::tuple<std::bitset<2>, orientation_t>, 4>{
        std::tuple{IO, NL}, {OI, NL}, {II, WU}, {OO, ED}};

    return a[coords.to_ulong()];
  }

  if (orientation == WU) {
    auto a = std::array<std::tuple<std::bitset<2>, orientation_t>, 4>{
        std::tuple{OO, SR}, {OI, WU}, {II, NL}, {IO, WU}};

    return a[coords.to_ulong()];
  }

  if (orientation == WD) {
    auto a = std::array<std::tuple<std::bitset<2>, orientation_t>, 4>{
        std::tuple{II, SL}, {IO, WD}, {OO, NR}, {OI, WD}};

    return a[coords.to_ulong()];
  }

  if (orientation == EU) {
    auto a = std::array<std::tuple<std::bitset<2>, orientation_t>, 4>{
        std::tuple{OI, EU}, {OO, SL}, {IO, EU}, {II, NR}};

    return a[coords.to_ulong()];
  }

  if (orientation == ED) {
    auto a = std::array<std::tuple<std::bitset<2>, orientation_t>, 4>{
        std::tuple{IO, ED}, {II, SR}, {OI, ED}, {OO, NL}};

    return a[coords.to_ulong()];
  }

  LOG_ERR("Failed.");
}
}