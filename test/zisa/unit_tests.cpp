// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

int main( int argc, char* argv[] ) {
  int result = Catch::Session().run( argc, argv );
  return result;
}