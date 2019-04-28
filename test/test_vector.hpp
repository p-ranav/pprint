#pragma once
#include <catch.hpp>
#include <pprint.hpp>

TEST_CASE("Print empty vector (line_terminator = '\n', indent = 2)",
	  "[std::vector]") {
  std::vector<int> foo {};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(foo);

  const std::string expected = "[]\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Compact Print simple vector of three elements (line_terminator = '\n', indent = 2)",
	  "[std::vector]") {
  std::vector<int> foo {1, 2, 3};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(foo);

  const std::string expected = "[1, 2, 3]\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print simple vector of three elements (line_terminator = '\n', indent = 2)",
	  "[std::vector]") {
  std::vector<int> foo {1, 2, 3};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(foo);

  const std::string expected = "[\n"
    "  1, \n" 
    "  2, \n" 
    "  3"
    "\n]\n";

  REQUIRE(stream.str() == expected);
}
