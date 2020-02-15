#pragma once
#include <pprint.hpp>

#include "catch2/catch.hpp"

TEST_CASE("Print empty list (line_terminator = '\n', indent = 2)",
	  "[std::list]") {
  std::list<int> foo {};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(foo);

  const std::string expected = "[]\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print simple 1-element list (line_terminator = '\n', indent = 2)",
	  "[std::list]") {
  std::list<int> foo {1};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(foo);

  const std::string expected = "[1]\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Compact Print simple list of three elements (line_terminator = '\n', indent = 2)",
	  "[std::list]") {
  std::list<int> foo {1, 2, 3};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(foo);

  const std::string expected = "[1, 2, 3]\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print simple list of three elements (line_terminator = '\n', indent = 2)",
	  "[std::list]") {
  std::list<int> foo {1, 2, 3};

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

TEST_CASE("Print list of lists (line_terminator = '\n', indent = 2)",
	  "[std::list]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::list<std::list<int>>{{1, 2, 3}, {4}, {5, 6}, {}});

  const std::string expected = "[\n"
    "  [1, 2, 3], \n" 
    "  [4], \n" 
    "  [5, 6], \n"
    "  []"
    "\n]\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print nested list (line_terminator = '\n', indent = 2)",
	  "[std::list]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::list<std::list<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  const std::string expected = "[\n"
    "  [1, 2, 3], \n" 
    "  [4, 5, 6], \n" 
    "  [7, 8, 9]"
    "\n]\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Compact Print nested list (line_terminator = '\n', indent = 2)",
	  "[std::list]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(std::list<std::list<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  const std::string expected = "[[1, 2, 3], [4, 5, 6], [7, 8, 9]]\n"; 

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Compact Print empty 3D matrix (list) (line_terminator = '\n', indent = 2)",
	  "[std::list]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(std::list<std::list<std::list<int>>>{});

  const std::string expected = "[]\n"; 

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print another nested matrix (list) (line_terminator = '\n', indent = 2)",
	  "[std::list]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::list<std::list<std::list<int>>>{ {{1, 2, 3}, {4, 5, 6}},
	{{7, 8, 9}, {10, 11, 12}} });

  const std::string expected = "[\n"
    "  [[1, 2, 3], [4, 5, 6]], \n"
    "  [[7, 8, 9], [10, 11, 12]]"
    "\n]\n";

  REQUIRE(stream.str() == expected);
}
