#include <zisa/testing/testing_framework.hpp>

#include <zisa/math/space_filling_curve.hpp>

TEST_CASE("Space Filling Curve; basics", "[math][sfc]") {

  REQUIRE(zisa::binary_digits<4>(0.25) == std::bitset<4>("0100"));
  REQUIRE(zisa::binary_digits<4>(0.5) == std::bitset<4>("1000"));
  REQUIRE(zisa::binary_digits<4>(0.75) == std::bitset<4>("1100"));
  REQUIRE(zisa::binary_digits<4>(0.625) == std::bitset<4>("1010"));
  REQUIRE(zisa::binary_digits<4>(0.9999) == std::bitset<4>("1111"));
  REQUIRE(zisa::binary_digits<4>(0.00001) == std::bitset<4>("0000"));

  REQUIRE(std::bitset<6>(42) == std::bitset<6>("101010"));

  auto level2 = std::vector<std::tuple<std::bitset<4>, std::bitset<4>>>{
      {std::bitset<4>("0000"), std::bitset<4>("0000")},
      {std::bitset<4>("0001"), std::bitset<4>("0001")},
      {std::bitset<4>("0100"), std::bitset<4>("1110")},
      {std::bitset<4>("0101"), std::bitset<4>("1111")},

      {std::bitset<4>("0010"), std::bitset<4>("0011")},
      {std::bitset<4>("0011"), std::bitset<4>("0010")},
      {std::bitset<4>("0110"), std::bitset<4>("1101")},
      {std::bitset<4>("0111"), std::bitset<4>("1100")},

      {std::bitset<4>("1000"), std::bitset<4>("0100")},
      {std::bitset<4>("1001"), std::bitset<4>("0111")},
      {std::bitset<4>("1100"), std::bitset<4>("1000")},
      {std::bitset<4>("1101"), std::bitset<4>("1011")},

      {std::bitset<4>("1010"), std::bitset<4>("0101")},
      {std::bitset<4>("1011"), std::bitset<4>("0110")},
      {std::bitset<4>("1110"), std::bitset<4>("1001")},
      {std::bitset<4>("1111"), std::bitset<4>("1010")}};

  for (auto [in, out] : level2) {
    REQUIRE(zisa::hilbert_index<2>(in) == out);
  }

  auto level3 = std::vector<std::tuple<std::bitset<6>, std::bitset<6>>>{
      {std::bitset<6>("011000"), std::bitset<6>("110110")},
      {std::bitset<6>("011001"), std::bitset<6>("110111")},
      {std::bitset<6>("011010"), std::bitset<6>("110101")},
      {std::bitset<6>("011011"), std::bitset<6>("110100")},
  };

  for (auto [in, out] : level3) {
    REQUIRE(zisa::hilbert_index<3>(in) == out);
  }

  auto xy_l2 = std::vector<std::bitset<4>>{std::bitset<4>("0000"),
                                           std::bitset<4>("0001"),
                                           std::bitset<4>("1110"),
                                           std::bitset<4>("1111"),

                                           std::bitset<4>("0011"),
                                           std::bitset<4>("0010"),
                                           std::bitset<4>("1101"),
                                           std::bitset<4>("1100"),

                                           std::bitset<4>("0100"),
                                           std::bitset<4>("0111"),
                                           std::bitset<4>("1000"),
                                           std::bitset<4>("1011"),

                                           std::bitset<4>("0101"),
                                           std::bitset<4>("0110"),
                                           std::bitset<4>("1001"),
                                           std::bitset<4>("1010")};

  for (int j = 0; j < 4; ++j) {
    double y = (2.0 * j + 1.0) / 8.0;

    for (int i = 0; i < 4; ++i) {
      double x = (2.0 * i + 1.0) / 8.0;

      REQUIRE(zisa::hilbert_index<2>(x, y) == xy_l2[i + 4 * j]);
    }
  }
}