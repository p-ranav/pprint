#pragma once
#include <pprint.hpp>

#include "catch2/catch.hpp"

TEST_CASE("Print empty set (line_terminator = '\n', indent = 2)",
	  "[std::set]") {
  std::set<int> foo {};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(foo);

  const std::string expected = "{}\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print simple 1-element set (line_terminator = '\n', indent = 2)",
	  "[std::set]") {
  std::set<int> foo {1};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(foo);

  const std::string expected = "{1}\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Compact Print simple set of three elements (line_terminator = '\n', indent = 2)",
	  "[std::set]") {
  std::set<int> foo {1, 2, 3};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(foo);

  const std::string expected = "{1, 2, 3}\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print simple set of three elements (line_terminator = '\n', indent = 2)",
	  "[std::set]") {
  std::set<int> foo {1, 2, 3};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(foo);

  const std::string expected = "{\n"
    "  1, \n" 
    "  2, \n" 
    "  3"
    "\n}\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print set of sets (line_terminator = '\n', indent = 2)",
	  "[std::set]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::set<std::set<int>>{{1, 2, 3}, {4}, {5, 6}, {}});

  const std::string expected = "{\n"
    "  {}, \n"
    "  {1, 2, 3}, \n" 
    "  {4}, \n" 
    "  {5, 6}"
    "\n}\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print nested set (line_terminator = '\n', indent = 2)",
	  "[std::set]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::set<std::set<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  const std::string expected = "{\n"
    "  {1, 2, 3}, \n" 
    "  {4, 5, 6}, \n" 
    "  {7, 8, 9}"
    "\n}\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Compact Print nested set (line_terminator = '\n', indent = 2)",
	  "[std::set]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(std::set<std::set<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  const std::string expected = "{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}\n"; 

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Compact Print empty 3D matrix (set) (line_terminator = '\n', indent = 2)",
	  "[std::set]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(std::set<std::set<std::set<int>>>{});

  const std::string expected = "{}\n"; 

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print another nested matrix (set) (line_terminator = '\n', indent = 2)",
	  "[std::set]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::set<std::set<std::set<int>>>{ {{1, 2, 3}, {4, 5, 6}},
	{{7, 8, 9}, {10, 11, 12}} });

  const std::string expected = "{\n"
    "  {{1, 2, 3}, {4, 5, 6}}, \n"
    "  {{7, 8, 9}, {10, 11, 12}}"
    "\n}\n";

  REQUIRE(stream.str() == expected);
}
