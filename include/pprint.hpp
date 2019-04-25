#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
#endif

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

    template <typename T>
    typename std::enable_if<std::is_null_pointer<T>::value == true, void>::type
    print_internal(T value) {
      std::cout << std::string(indent_, ' ') << "null" << (newline_ ? "\n" : "");
    }

    void print_internal(float value) {
      std::cout << std::string(indent_, ' ') << value << 'f' << (newline_ ? "\n" : "");
    }

    void print_internal(double value) {
      std::cout << std::string(indent_, ' ') << value << (newline_ ? "\n" : "");
    }

    void print_internal(const std::string& value) {
      std::cout << std::string(indent_, ' ') << value << (newline_ ? "\n" : "");
    }
    
    void print_internal(const char * value) {
      std::cout << std::string(indent_, ' ') << value << (newline_ ? "\n" : "");
    }    

    void print_internal(bool value) {
      std::cout << std::string(indent_, ' ') <<
	(value ? "true" : "false") << (newline_ ? "\n" : "");
    }

    template <typename T>
    typename std::enable_if<std::is_class<T>::value == true, void>::type
    print_internal(T value) {
      std::cout << std::string(indent_, ' ') << type(value) << (newline_ ? "\n" : "");
    }

    std::string demangle(const char* name) {
#ifdef __GNUG__
      int status = -4;      
      std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
	  std::free
	  };
      return (status==0) ? res.get() : name;
#else
      return name;
#endif      
    }

    template <class T>
    std::string type(const T& t) {
      return demangle(typeid(t).name());
    }
    
    size_t indent_;
    bool newline_;
  };
  
}
