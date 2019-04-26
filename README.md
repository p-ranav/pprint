# Pretty Printer for Modern C++

## Highlights

* Header-only library
* Requires C++17
* MIT License

## Quick Start

Simply include pprint.hpp and you're good to go.

```cpp
#include <pprint.hpp>
```

To start printing, create an ```PrettyPrinter```. 

```cpp
pprint::PrettyPrinter printer;
```

## Fundamental Types

```cpp
printer.print(5);
printer.print(3.14f);
printer.print(2.718);
printer.print(true);
printer.print('x');
printer.print("Hello, 世界");
printer.print(nullptr);
```

```bash
5
3.14f
2.718
true
'x'
"Hello, 世界"
nullptr
```

## STL Sequence Containers

pprint supports a variety of STL sequence containers including ```std::vector```, ```std::list```, ```std::deque```, and ```std::array```. 

Here's an exmaple pretty print of a simple 3x3 matrix:

```cpp
typedef std::array<std::array<int, 3>, 3> Mat3x3;
Mat3x3 matrix;
matrix[0] = {1, 2, 3};
matrix[1] = {4, 5, 6};
matrix[2] = {7, 8, 9};
printer.print(matrix);
```

```bash
[
  [1, 2, 3], 
  [4, 5, 6], 
  [7, 8, 9]
]
```

## STL Associative Containers

Support for associative containers includes pretty printing of ```std::map```, ```std::multimap```, ```std::unordered_map```, ```std::unordered_multimap```, ```std::set```, ```std::multiset```, ```std::unordered_set``` and , ```std::unordered_multiset``` 

```cpp
printer.print(std::map<std::string, std::set<int>>{ 
    {"foo", {1, 2, 3, 3, 2, 1}}, {"bar", {7, 6, 5, 4}}});
```

```bash
{
  "bar" : {4, 5, 6, 7}, 
  "foo" : {1, 2, 3}
}
```

## Type-safe Unions (std::variant)

```cpp

```cpp
// Construct a vector of values
std::vector<std::variant<bool, int, int *, float, std::string, std::vector<int>,		      
       std::map<std::string, std::map<std::string, int>>, 
       std::pair<double, double>>> var;
var.push_back(5);
var.push_back(nullptr);
var.push_back(3.14f);
var.push_back(std::string{"Hello World"});
var.push_back(std::vector<int>{1, 2, 3, 4});
var.push_back(std::map<std::string, std::map<std::string, int>>{{"a",{{"b",1}}}, {"c",{{"d",2}, {"e",3}}}});
var.push_back(true);
var.push_back(std::pair<double, double>{1.1, 2.2});

// Print the vector
pprint::PrettyPrinter printer;
printer.indent(2);
printer.print(var);
```

```bash
[
  5, 
  nullptr,
  3.14f, 
  "Hello World", 
  [1, 2, 3, 4], 
  {"a" : {"b" : 1}, "c" : {"d" : 2, "e" : 3}}, 
  true, 
  (1.1, 2.2)
]
```

## Optional Values (std::optional)

```cpp
std::optional<int> opt = 5;
std::optional<int> opt2;

printer.print(opt);
printer.print(opt2);
```

```bash
5
nullopt
```

## Classes

### Pointer to member function

```cpp
class Bar {
public:
  void Foo() {}
};
printer.print(&Bar::Foo);
```

```bash
<Object.method void (main::Bar::*)()>
```

## Contribution
Contributions are welcome, have a look at the [CONTRIBUTING.md](CONTRIBUTING.md) document for more information.

## License
The project is available under the [MIT](https://opensource.org/licenses/MIT) license.
