#pragma once
#include <pprint.hpp>

#include "catch2/catch.hpp"

//Enable hashing of sets and unordered_sets (even though they are mutable)
namespace std {
template<typename T>
struct hash<std::set<T>> {
std::size_t operator()(const std::set<T> &cset) const noexcept {
    size_t hash = 0;
    const std::hash<T> h;
    for (const auto &e : cset) {
        hash ^= h(e);
    }
    return hash;
}
};
template<typename T>
struct hash<std::unordered_set<T>> {
std::size_t operator()(const std::unordered_set<T> &cset) const noexcept {
    size_t hash = 0;
    const std::hash<T> h;
    for (const auto &e : cset) {
        hash ^= h(e);
    }
    return hash;
}
};
}

TEST_CASE("Print empty unordered_set (line_terminator = '/n', indent = 2)",
	  "[std::unordered_set]") {
  std::unordered_set<int> foo {};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(foo);

  const std::string expected = "{}\n";

  REQUIRE(stream.str() == expected);
}


TEST_CASE("Print simple 1-element unordered_set (line_terminator = '/n', indent = 2)",
	  "[std::unordered_set]") {
  std::unordered_set<int> foo {1};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(foo);

  const std::string expected = "{1}\n";

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Compact Print simple unordered_set of three elements (line_terminator = '/n', indent = 2)",
	  "[std::unordered_set]") {
  std::unordered_set<int> foo {1, 2, 3};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(foo);

  // Cannot test using equal because hashing algorithm is implementation specific
}

TEST_CASE("Print simple unordered_set of three elements (line_terminator = '/n', indent = 2)",
	  "[std::unordered_set]") {
  std::unordered_set<int> foo {1, 2, 3};

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(foo);

  // Cannot test using equal because hashing algorithm is implementation specific
}


TEST_CASE("Print unordered_set of unordered_set (line_terminator = '/n', indent = 2)",
	  "[std::unordered_set]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::unordered_set<std::unordered_set<int>>{{1, 2, 3}, {4}, {5, 6}, {}});

  // Cannot test using equal because hashing algorithm is implementation specific
}

TEST_CASE("Print nested unordered_set (line_terminator = '/n', indent = 2)",
	  "[std::unordered_set]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::unordered_set<std::set<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  // Cannot test using equal because hashing algorithm is implementation specific
  auto s = stream.str();
  REQUIRE(s.find("{1, 2, 3}") != std::string::npos);
  REQUIRE(s.find("{4, 5, 6}") != std::string::npos);
  REQUIRE(s.find("{7, 8, 9}") != std::string::npos);
}

TEST_CASE("Compact Print nested unordered_set (line_terminator = '/n', indent = 2)",
	  "[std::unordered_set]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(std::unordered_set<std::set<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  // Cannot test using equal because hashing algorithm is implementation specific
  auto s = stream.str();
  REQUIRE(s.find("{1, 2, 3}") != std::string::npos);
  REQUIRE(s.find("{4, 5, 6}") != std::string::npos);
  REQUIRE(s.find("{7, 8, 9}") != std::string::npos);
}

TEST_CASE("Compact Print empty 3D matrix (unordered_set) (line_terminator = '/n', indent = 2)",
	  "[std::unordered_set]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.compact(true);
  printer.print(std::unordered_set<std::unordered_set<std::unordered_set<int>>>{});

  const std::string expected = "{}\n"; 

  REQUIRE(stream.str() == expected);
}

TEST_CASE("Print another nested matrix (unordered_set) (line_terminator = '/n', indent = 2)",
	  "[std::unordered_set]") {

  std::stringstream stream;
  pprint::PrettyPrinter printer(stream);
  printer.print(std::unordered_set<std::unordered_set<std::set<int>>>{ {{1, 2, 3}, {4, 5, 6}},
	{{7, 8, 9}, {10, 11, 12}} });
  // Cannot test using equal because hashing algorithm is implementation specific
  auto s = stream.str();
  REQUIRE(s.find("{1, 2, 3}") != std::string::npos);
  REQUIRE(s.find("{4, 5, 6}") != std::string::npos);
  REQUIRE(s.find("{7, 8, 9}") != std::string::npos);
  REQUIRE(s.find("{10, 11, 12}") != std::string::npos);
}
