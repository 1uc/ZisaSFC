#ifndef ZISA_SPACE_FILLING_CURVE_HPP_XYGQB
#define ZISA_SPACE_FILLING_CURVE_HPP_XYGQB

#include <zisa/config.hpp>

#include <bitset>

namespace zisa {
template <int N>
std::bitset<N> binary_digits(double x) {
  auto digits = std::bitset<N>{};

  assert(x >= 0);
  assert(x < 1.0);

  for (int i = N - 1; i >= 0; --i) {
    if (x < 0.5) {
      digits[i] = false;
      x = 2.0 * x;
    } else {
      digits[i] = true;
      x = 2.0 * (x - 0.5);
    }
  }

  return digits;
}

class HilbertTable {
public:
  using orientation_t = short;

public:
  std::tuple<std::bitset<2>, orientation_t>
  operator()(const std::bitset<2> &coords, orientation_t orientation) const;
};

template <int N>
std::bitset<2 * N> hilbert_index(const std::bitset<2 * N> &coords) {

  auto hilbert_table = HilbertTable{};

  std::bitset<2 * N> index;
  short orientation = 0;

  for (int i = N - 1; i >= 0; --i) {
    std::bitset<2> xy;
    std::bitset<2> digits;

    xy[1] = coords[i * 2 + 1];
    xy[0] = coords[i * 2];

    std::tie(digits, orientation) = hilbert_table(xy, orientation);

    index[i * 2 + 1] = digits[1];
    index[i * 2] = digits[0];
  }

  return index;
}

template <int N>
std::bitset<2 * N> hilbert_index(double x, double y) {
  auto x_digits = binary_digits<N>(x);
  auto y_digits = binary_digits<N>(y);

  auto coords = std::bitset<2 * N>{};
  for (int i = 0; i < N; ++i) {
    coords[2 * i] = x_digits[i];
    coords[2 * i + 1] = y_digits[i];
  }

  return hilbert_index<N>(coords);
}

}
#endif // ZISA_SPACE_FILLING_CURVE_HPP
