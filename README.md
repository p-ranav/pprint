# Pretty Printer for Modern C++

## Highlights

* Header-only library
* Requires C++11
* MIT License

## Quick Start

Simply include pprint.hpp and you're good to go.

```cpp
#include <pprint.hpp>
```

To start printing, create an ```PrettyPrinter```. 

```cpp
pprint::PrettyPrinter printer;
printer.indent(2);
```

## Fundamental Types

```cpp
printer.print(5);
printer.print(3.14f);
printer.print(2.718);
printer.print(true);
printer.print('x');
printer.print("Hello World!");
printer.print(nullptr);
```

```bash
5
3.14f
2.718
true
'x'
"Hello World!"
null
```

## STL Containers

### Sequence Containers: std::vector

```cpp
printer.print(std::vector<int>{1, 2, 3, 4, 5});
```

```bash
[
  1,
  2,
  3,
  4,
  5
]
```

pprint can handle other containers inside vectors:

```cpp
std::cout << "foo = ";
printer.print(std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {}, {7, 8}});
```

```bash
foo = [
  [1, 2, 3],
  [4, 5, 6],
  [],
  [7, 8]
]
```

### Associative Containers: std::map

```cpp
printer.print(std::map<std::string, int>{ {"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}});
```

```bash
{
  "a" : 1,
  "b" : 2,
  "c" : 3,
  "d" : 4,
  "e" : 5
}
```

Here's an example of an std::map with compound mapped_type values:

```cpp
  printer.print(std::map<std::string, std::vector<std::pair<int, std::string>>>{ 
    {"foo", {{1, "b"}, {2, "c"}, {3, "d"}}}, 
    {"bar", {{4, "e"}, {5, "f"}, {6, "g"}}}
  });
  ```

```bash
{
  "foo" : [(1, "b"), (2, "c"), (3, "d")], 
  "bar" : [(4, "e"), (5, "f"), (6, "g")]
}
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
