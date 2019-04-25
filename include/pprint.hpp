#include <iostream>
#include <type_traits>

namespace pprint {

  // Some utility structs to check template specialization
  template<typename Test, template<typename...> class Ref>
  struct is_specialization : std::false_type {};

  template<template<typename...> class Ref, typename... Args>
  struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

  class PrettyPrinter {
  public:

    PrettyPrinter() :
      indent_(0),
      newline_(true) {}

    template <typename T>
    void print(T value) {
      print_internal(value);
    }

  private:

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value == true, void>::type
    print_internal(T value) {
      std::cout << std::string(indent_, ' ') << value << (newline_ ? "\n" : "");
    }

    void print_internal(float value) {
      std::cout << std::string(indent_, ' ') << value << 'f' << (newline_ ? "\n" : "");
    }    

    void print_internal(double value) {
      std::cout << std::string(indent_, ' ') << value << (newline_ ? "\n" : "");
    }

    void print_internal(bool value) {
      std::cout << std::string(indent_, ' ') <<
	(value ? "true" : "false") << (newline_ ? "\n" : "");
    }
    
    size_t indent_;
    bool newline_;
  };
  
}
