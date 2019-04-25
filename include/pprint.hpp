#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>
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

    template <typename T>
    void print(T value) {
      print_internal(value, 0, true, 0);
    }

  private:

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value == true, void>::type
    print_internal(T value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << value << (newline ? "\n" : "");
    }

    template <typename T>
    typename std::enable_if<std::is_null_pointer<T>::value == true, void>::type
    print_internal(T value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << "null" << (newline ? "\n" : "");
    }

    void print_internal(float value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << value << 'f' << (newline ? "\n" : "");
    }

    void print_internal(double value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << value << (newline ? "\n" : "");
    }

    void print_internal(const std::string& value, size_t indent = 0, bool newline = false,
			size_t level = 0) {
      std::cout << std::string(indent, ' ') << value << (newline ? "\n" : "");
    }
    
    void print_internal(const char * value, size_t indent = 0, bool newline = false,
			size_t level = 0) {
      std::cout << std::string(indent, ' ') << value << (newline ? "\n" : "");
    }    

    void print_internal(bool value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') <<
	(value ? "true" : "false") << (newline ? "\n" : "");
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

    template <typename T>
    typename std::enable_if<std::is_class<T>::value == true, void>::type
    print_internal(T value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << type(value) << (newline ? "\n" : "");
    }

    template <typename T>
    void print_internal(const std::vector<T>& value, size_t indent = 0, bool newline = false,
			size_t level = 0) {
      if (level == 0) {
	if (value.size() == 0) {
	  print_internal("[", 0, false);
	}
	else if (value.size() == 1) {
	  print_internal("[", 0, false);
	  print_internal(value.front(), 0, false, level + 1);
	}
	else if (value.size() > 0) {
	  print_internal("[", 0, true);
	  print_internal(value.front(), indent + 4, false, level + 1);
	  if (value.size() > 1 && is_specialization<T, std::vector>::value == false)
	    print_internal(", ", 0, true);
	  else if (is_specialization<T, std::vector>::value)
	    print_internal(", ", 0, true);
	  for (size_t i = 1; i < value.size() - 1; i++) {
	    print_internal(value[i], indent + 4, false, level + 1);
	    if (is_specialization<T, std::vector>::value == false)
	      print_internal(", ", 0, true);
	    else
	      print_internal(", ", 0, true);	    
	  }
	  if (value.size() > 1) {
	    print_internal(value.back(), indent + 4, true, level + 1);
	  }
	}
	if (value.size() == 0)
	  print_internal("]\n");
	else if (is_specialization<T, std::vector>::value == false)
	  print_internal("]\n");
	else
	  print_internal("\n]\n");
      }
      else {
	if (value.size() == 0) {
	  print_internal("[", indent, false);
	}
	else if (value.size() == 1) {
	  print_internal("[", indent, false);
	  print_internal(value.front(), 0, false, level + 1);
	}
	else if (value.size() > 0) {
	  print_internal("[", indent, false);
	  print_internal(value.front(), 0, false, level + 1);
	  if (value.size() > 1)
	    print_internal(", ", 0, false);
	  for (size_t i = 1; i < value.size() - 1; i++) {	      
	    print_internal(value[i], 0, false, level + 1);
	    print_internal(", ", 0, false);
	  }
	  if (value.size() > 1) {
	    print_internal(value.back(), 0, false, level + 1);
	  }
	}
	print_internal("]", 0, false);
      }
      
    }

  };
  
}
