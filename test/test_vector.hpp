#pragma once
#include <pprint.hpp>

#include "catch2/catch.hpp"

TEST_CASE("Print empty vector (line_terminator = '\n', indent = 2)",
	  "[std::vector]") {
  std::vector<int> foo {};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(foo);

  const std::string expected = "[]\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print simple 1-element vector (line_terminator = '\n', indent = 2)",
	  "[std::vector]") {
  std::vector<int> foo {1};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(foo);

  const std::string expected = "[1]\n";

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

TEST_CASE("Print vector of vectors (line_terminator = '\n', indent = 2)",
	  "[std::vector]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::vector<std::vector<int>>{{1, 2, 3}, {4}, {5, 6}, {}});

  const std::string expected = "[\n"
    "  [1, 2, 3], \n" 
    "  [4], \n" 
    "  [5, 6], \n"
    "  []"
    "\n]\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print nested vector (line_terminator = '\n', indent = 2)",
	  "[std::vector]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  const std::string expected = "[\n"
    "  [1, 2, 3], \n" 
    "  [4, 5, 6], \n" 
    "  [7, 8, 9]"
    "\n]\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Compact Print nested vector (line_terminator = '\n', indent = 2)",
	  "[std::vector]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  const std::string expected = "[[1, 2, 3], [4, 5, 6], [7, 8, 9]]\n"; 

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Compact Print empty 3D matrix (line_terminator = '\n', indent = 2)",
	  "[std::vector]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(std::vector<std::vector<std::vector<int>>>{});

  const std::string expected = "[]\n"; 

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print another nested matrix (line_terminator = '\n', indent = 2)",
	  "[std::vector]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::vector<std::vector<std::vector<int>>>{ {{1, 2, 3}, {4, 5, 6}},
	{{7, 8, 9}, {10, 11, 12}} });

  const std::string expected = "[\n"
    "  [[1, 2, 3], [4, 5, 6]], \n"
    "  [[7, 8, 9], [10, 11, 12]]"
    "\n]\n";

  REQUIRE(stream.str() == expected);
}
