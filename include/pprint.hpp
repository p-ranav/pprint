#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
#include <array>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <variant>
#include <algorithm>
#include <optional>
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

  template<typename ...>
  using to_void = void;
  
  template<typename T, typename = void>
  struct is_container : std::false_type
  {};
  
  template<typename T>
  struct is_container<T,
		    to_void<decltype(std::declval<T>().begin()),
			    decltype(std::declval<T>().end()),
			    typename T::value_type
			    >> : std::true_type // will  be enabled for iterable objects
  {};
  
  class PrettyPrinter {
  public:

    PrettyPrinter() :
      indent_(0),
      newline_(true),
      dereference_pointers_(false) {}

    void indent(size_t indent) {
      indent_ = indent;
    }

    void newline(bool newline) {
      newline_ = newline;
    }

    void dereference_pointers(bool value) {
      dereference_pointers_ = value;
    }    

    template <typename T>
    void print(T value) {
      print_internal(value, 0, newline_, 0);
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
      std::cout << std::string(indent, ' ') << "nullptr" << (newline ? "\n" : "");
    }

    void print_internal(float value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << value << 'f' << (newline ? "\n" : "");
    }

    void print_internal(double value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << value << (newline ? "\n" : "");
    }

    void print_internal(const std::string& value, size_t indent = 0, bool newline = false,
			size_t level = 0) {
      std::cout << std::string(indent, ' ') << "\"" << value << "\"" << (newline ? "\n" : "");
    }
    
    void print_internal(const char * value, size_t indent = 0, bool newline = false,
			size_t level = 0) {
      std::cout << std::string(indent, ' ') << "\"" << value << "\"" << (newline ? "\n" : "");
    }

    void print_internal(char value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << "'" << value << "'" << (newline ? "\n" : "");
    }    

    void print_internal_without_quotes(const std::string& value, size_t indent = 0,
				       bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << value << (newline ? "\n" : "");
    }
    
    void print_internal_without_quotes(const char * value, size_t indent = 0,
				       bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << value << (newline ? "\n" : "");
    }    

    void print_internal_without_quotes(char value, size_t indent = 0, bool newline = false,
				       size_t level = 0) {
      std::cout << std::string(indent, ' ') << value << (newline ? "\n" : "");
    }        
    
    void print_internal(bool value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') <<
	(value ? "true" : "false") << (newline ? "\n" : "");
    }

    template <typename T>
    typename std::enable_if<std::is_pointer<T>::value == true, void>::type
    print_internal(T value, size_t indent = 0, bool newline = false, size_t level = 0) {
      if (value == nullptr) {
	return print_internal(nullptr, indent, newline, level);
      }
      if (!dereference_pointers_) {
	std::cout << std::string(indent, ' ') << "<" << type(value) << " at "
		  << value << ">" << (newline ? "\n" : "");
      }
      else {
	return print_internal(*value, indent, newline, level);
      }
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
    typename std::enable_if<std::is_enum<T>::value == true, void>::type
    print_internal(T value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << value
		<< (newline ? "\n" : "");
    }    

    template <typename T>
    typename std::enable_if<std::is_class<T>::value == true &&
			    std::is_enum<T>::value == false &&
			    is_specialization<T, std::variant>::value == false &&
			    is_specialization<T, std::vector>::value == false &&
			    is_specialization<T, std::list>::value == false &&
			    is_specialization<T, std::deque>::value == false &&
			    is_specialization<T, std::set>::value == false &&
			    is_specialization<T, std::multiset>::value == false &&
			    is_specialization<T, std::unordered_set>::value == false &&
			    is_specialization<T, std::unordered_multiset>::value == false &&			    
			    is_specialization<T, std::map>::value == false &&
			    is_specialization<T, std::multimap>::value == false &&
			    is_specialization<T, std::unordered_map>::value == false &&
			    is_specialization<T, std::unordered_multimap>::value == false, void>::type
    print_internal(T value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << "<Object " << type(value) << ">"
		<< (newline ? "\n" : "");
    }

    template <typename T>
    typename std::enable_if<std::is_member_function_pointer<T>::value == true, void>::type
    print_internal(T value, size_t indent = 0, bool newline = false, size_t level = 0) {
      std::cout << std::string(indent, ' ') << "<Object.method " << type(value)
		<< ">"
		<< (newline ? "\n" : "");
    }

    template <typename Container>
    typename std::enable_if<is_specialization<Container, std::vector>::value, void>::type    
    print_internal(const Container& value, size_t indent = 0, bool newline = false,
		   size_t level = 0) {
      typedef typename Container::value_type T;
      if (level == 0) {
	if (value.size() == 0) {
	  print_internal_without_quotes("[", 0, false);
	}
	else if (value.size() == 1) {
	  print_internal_without_quotes("[", 0, false);
	  print_internal(value.front(), 0, false, level + 1);
	}
	else if (value.size() > 0) {
	  print_internal_without_quotes("[", 0, true);
	  print_internal(value.front(), indent + indent_, false, level + 1);
	  if (value.size() > 1 && is_container<T>::value == false)
	    print_internal_without_quotes(", ", 0, true);
	  else if (is_container<T>::value)
	    print_internal_without_quotes(", ", 0, true);
	  for (size_t i = 1; i < value.size() - 1; i++) {
	    print_internal(value[i], indent + indent_, false, level + 1);
	    if (is_container<T>::value == false)
	      print_internal_without_quotes(", ", 0, true);
	    else
	      print_internal_without_quotes(", ", 0, true);	    
	  }
	  if (value.size() > 1) {
	    print_internal(value.back(), indent + indent_, true, level + 1);
	  }
	}
	if (value.size() == 0)
	  print_internal_without_quotes("]\n");
	else if (is_container<T>::value == false)
	  print_internal_without_quotes("]\n");
	else
	  print_internal_without_quotes("\n]\n");
      }
      else {
	if (value.size() == 0) {
	  print_internal_without_quotes("[", indent, false);
	}
	else if (value.size() == 1) {
	  print_internal_without_quotes("[", indent, false);
	  print_internal(value.front(), 0, false, level + 1);
	}
	else if (value.size() > 0) {
	  print_internal_without_quotes("[", indent, false);
	  print_internal(value.front(), 0, false, level + 1);
	  if (value.size() > 1)
	    print_internal_without_quotes(", ", 0, false);
	  for (size_t i = 1; i < value.size() - 1; i++) {	      
	    print_internal(value[i], 0, false, level + 1);
	    print_internal_without_quotes(", ", 0, false);
	  }
	  if (value.size() > 1) {
	    print_internal(value.back(), 0, false, level + 1);
	  }
	}
	print_internal_without_quotes("]", 0, false);
      }
      
    }

    template <typename T, unsigned long int S>
    void print_internal(const std::array<T, S>& value, size_t indent = 0, bool newline = false,
		   size_t level = 0) {
      if (level == 0) {
	if (value.size() == 0) {
	  print_internal_without_quotes("[", 0, false);
	}
	else if (value.size() == 1) {
	  print_internal_without_quotes("[", 0, false);
	  print_internal(value.front(), 0, false, level + 1);
	}
	else if (value.size() > 0) {
	  print_internal_without_quotes("[", 0, true);
	  print_internal(value.front(), indent + indent_, false, level + 1);
	  if (value.size() > 1 && is_container<T>::value == false)
	    print_internal_without_quotes(", ", 0, true);
	  else if (is_container<T>::value)
	    print_internal_without_quotes(", ", 0, true);
	  for (size_t i = 1; i < value.size() - 1; i++) {
	    print_internal(value[i], indent + indent_, false, level + 1);
	    if (is_container<T>::value == false)
	      print_internal_without_quotes(", ", 0, true);
	    else
	      print_internal_without_quotes(", ", 0, true);	    
	  }
	  if (value.size() > 1) {
	    print_internal(value.back(), indent + indent_, true, level + 1);
	  }
	}
	if (value.size() == 0)
	  print_internal_without_quotes("]\n");
	else if (is_container<T>::value == false)
	  print_internal_without_quotes("]\n");
	else
	  print_internal_without_quotes("\n]\n");
      }
      else {
	if (value.size() == 0) {
	  print_internal_without_quotes("[", indent, false);
	}
	else if (value.size() == 1) {
	  print_internal_without_quotes("[", indent, false);
	  print_internal(value.front(), 0, false, level + 1);
	}
	else if (value.size() > 0) {
	  print_internal_without_quotes("[", indent, false);
	  print_internal(value.front(), 0, false, level + 1);
	  if (value.size() > 1)
	    print_internal_without_quotes(", ", 0, false);
	  for (size_t i = 1; i < value.size() - 1; i++) {	      
	    print_internal(value[i], 0, false, level + 1);
	    print_internal_without_quotes(", ", 0, false);
	  }
	  if (value.size() > 1) {
	    print_internal(value.back(), 0, false, level + 1);
	  }
	}
	print_internal_without_quotes("]", 0, false);
      }
      
    }    

    template <typename Container>
    typename std::enable_if<is_specialization<Container, std::list>::value ||
			    is_specialization<Container, std::deque>::value, void>::type    
    print_internal(const Container& value, size_t indent = 0, bool newline = false,
		   size_t level = 0) {
      typedef typename Container::value_type T;
      if (level == 0) {
	if (value.size() == 0) {
	  print_internal_without_quotes("[", 0, false);
	}
	else if (value.size() == 1) {
	  print_internal_without_quotes("[", 0, false);
	  print_internal(value.front(), 0, false, level + 1);
	}
	else if (value.size() > 0) {
	  print_internal_without_quotes("[", 0, true);
	  print_internal(value.front(), indent + indent_, false, level + 1);
	  if (value.size() > 1 && is_container<T>::value == false)
	    print_internal_without_quotes(", ", 0, true);
	  else if (is_container<T>::value)
	    print_internal_without_quotes(", ", 0, true);

	  typename Container::const_iterator iterator;
	  for (iterator = std::next(value.begin()); iterator != std::prev(value.end()); ++iterator) {
	    print_internal(*iterator, indent + indent_, false, level + 1);
	    if (is_container<T>::value == false)
	      print_internal_without_quotes(", ", 0, true);
	    else
	      print_internal_without_quotes(", ", 0, true);	    
	  }
	  
	  if (value.size() > 1) {
	    print_internal(value.back(), indent + indent_, true, level + 1);
	  }
	}
	if (value.size() == 0)
	  print_internal_without_quotes("]\n");
	else if (is_container<T>::value == false)
	  print_internal_without_quotes("]\n");
	else
	  print_internal_without_quotes("\n]\n");
      }
      else {
	if (value.size() == 0) {
	  print_internal_without_quotes("[", indent, false);
	}
	else if (value.size() == 1) {
	  print_internal_without_quotes("[", indent, false);
	  print_internal(value.front(), 0, false, level + 1);
	}
	else if (value.size() > 0) {
	  print_internal_without_quotes("[", indent, false);
	  print_internal(value.front(), 0, false, level + 1);
	  if (value.size() > 1)
	    print_internal_without_quotes(", ", 0, false);

	  typename Container::const_iterator iterator;
	  for (iterator = std::next(value.begin()); iterator != std::prev(value.end()); ++iterator) {
	    print_internal(*iterator, 0, false, level + 1);
	    print_internal_without_quotes(", ", 0, false);	    
	  }

	  if (value.size() > 1) {
	    print_internal(value.back(), 0, false, level + 1);
	  }
	}
	print_internal_without_quotes("]", 0, false);
      }
      
    }

    template <typename Container>
    typename std::enable_if<is_specialization<Container, std::set>::value ||
			    is_specialization<Container, std::multiset>::value ||
			    is_specialization<Container, std::unordered_set>::value ||
			    is_specialization<Container, std::unordered_multiset>::value, void>::type    
    print_internal(const Container& value, size_t indent = 0, bool newline = false,
		   size_t level = 0) {
      typedef typename Container::value_type T;
      if (level == 0) {
	if (value.size() == 0) {
	  print_internal_without_quotes("{", 0, false);
	}
	else if (value.size() == 1) {
	  print_internal_without_quotes("{", 0, false);
	  print_internal(*(value.begin()), 0, false, level + 1);
	}
	else if (value.size() > 0) {
	  print_internal_without_quotes("{", 0, true);
	  print_internal(*(value.begin()), indent + indent_, false, level + 1);
	  if (value.size() > 1 && is_container<T>::value == false)
	    print_internal_without_quotes(", ", 0, true);
	  else if (is_container<T>::value)
	    print_internal_without_quotes(", ", 0, true);

	  typename Container::const_iterator iterator;
	  for (iterator = std::next(value.begin()); iterator != std::prev(value.end()); ++iterator) {
	    print_internal(*iterator, indent + indent_, false, level + 1);
	    if (is_container<T>::value == false)
	      print_internal_without_quotes(", ", 0, true);
	    else
	      print_internal_without_quotes(", ", 0, true);	    
	  }
	  
	  if (value.size() > 1) {
	    print_internal(*(std::prev(value.end())), indent + indent_, true, level + 1);
	  }
	}
	if (value.size() == 0)
	  print_internal_without_quotes("}\n");
	else if (is_container<T>::value == false)
	  print_internal_without_quotes("}\n");
	else
	  print_internal_without_quotes("\n}\n");
      }
      else {
	if (value.size() == 0) {
	  print_internal_without_quotes("{", indent, false);
	}
	else if (value.size() == 1) {
	  print_internal_without_quotes("{", indent, false);
	  print_internal(*(value.begin()), 0, false, level + 1);
	}
	else if (value.size() > 0) {
	  print_internal_without_quotes("{", indent, false);
	  print_internal(*(value.begin()), 0, false, level + 1);
	  if (value.size() > 1)
	    print_internal_without_quotes(", ", 0, false);

	  typename Container::const_iterator iterator;
	  for (iterator = std::next(value.begin()); iterator != std::prev(value.end()); ++iterator) {
	    print_internal(*iterator, 0, false, level + 1);
	    print_internal_without_quotes(", ", 0, false);	    
	  }

	  if (value.size() > 1) {
	    print_internal(*(std::prev(value.end())), 0, false, level + 1);
	  }
	}
	print_internal_without_quotes("}", 0, false);
      }
      
    }    

    template <typename T>
    typename std::enable_if<is_specialization<T, std::map>::value == true ||
			    is_specialization<T, std::multimap>::value == true ||
			    is_specialization<T, std::unordered_map>::value == true ||
			    is_specialization<T, std::unordered_multimap>::value == true, void>::type
    print_internal(const T& value, size_t indent = 0, bool newline = false, size_t level = 0) {
      typedef typename T::mapped_type Value;
      if (level == 0) {
	if (value.size() == 0) {
	  print_internal_without_quotes("{", 0, false);
	}
	else if (value.size() == 1) {
	  print_internal_without_quotes("{", 0, false);
	  for (auto& kvpair : value) {
	    print_internal(kvpair.first, 0, false, level + 1);
	    print_internal_without_quotes(" : ", 0, false);
	    print_internal(kvpair.second, 0, false, level + 1);
	  }
	}
	else if (value.size() > 0) {
	  size_t count = 0;
	  for (auto& kvpair : value) {
	    if (count == 0) {
	      print_internal_without_quotes("{", 0, true);
	      print_internal(kvpair.first, indent + indent_, false, level + 1);
	      print_internal_without_quotes(" : ", 0, false);
	      print_internal(kvpair.second, 0, false, level + 1);
	      if (value.size() > 1 && is_container<Value>::value == false)
		print_internal_without_quotes(", ", 0, true);
	      else if (is_container<Value>::value)
		print_internal_without_quotes(", ", 0, true);
	    }
	    else if (count + 1 < value.size()) {
	      print_internal(kvpair.first, indent + indent_, false, level + 1);
	      print_internal_without_quotes(" : ", 0, false);
	      print_internal(kvpair.second, 0, false, level + 1);
	      if (is_container<Value>::value == false)
		print_internal_without_quotes(", ", 0, true);
	      else
		print_internal_without_quotes(", ", 0, true);
	    }
	    else {
	      print_internal(kvpair.first, indent + indent_, false, level + 1);
	      print_internal_without_quotes(" : ", 0, false);
	      print_internal(kvpair.second, 0, true, level + 1);
	    }
	    count += 1;
	  }	  
	}
	if (value.size() == 0)
	  print_internal_without_quotes("}\n");
	else if (is_container<Value>::value == false)
	  print_internal_without_quotes("}\n");
	else
	  print_internal_without_quotes("\n}\n");
      }
      
      else {
	if (value.size() == 0) {
	  print_internal_without_quotes("{", indent, false);
	}
	else if (value.size() == 1) {
	  print_internal_without_quotes("{", indent, false);
	  for (auto& kvpair : value) {
	    print_internal(kvpair.first, 0, false, level + 1);
	    print_internal_without_quotes(" : ", 0, false);
	    print_internal(kvpair.second, 0, false, level + 1);
	  }
	}
	else if (value.size() > 0) {
	  size_t count = 0;
	  for (auto& kvpair : value) {
	    if (count == 0) {
	      print_internal_without_quotes("{", indent, false);
	      print_internal(kvpair.first, 0, false, level + 1);
	      print_internal_without_quotes(" : ", 0, false);
	      print_internal(kvpair.second, 0, false, level + 1);
	      print_internal_without_quotes(", ", 0, false);
	    }
	    else if (count + 1 < value.size()) {
	      print_internal(kvpair.first, indent + indent_, false, level + 1);
	      print_internal_without_quotes(" : ", 0, false);
	      print_internal(kvpair.second, 0, false, level + 1);
	      print_internal_without_quotes(", ", 0, false);
	    }
	    else {
	      print_internal(kvpair.first, 0, false, level + 1);
	      print_internal_without_quotes(" : ", 0, false);
	      print_internal(kvpair.second, 0, false, level + 1);
	    }
	    count += 1;
	  }	  
	}
	print_internal_without_quotes("}", 0, false);
      }
    }

    template <typename Key, typename Value>
    void print_internal(std::pair<Key, Value> value, size_t indent = 0, bool newline = false,
			size_t level = 0) {
      print_internal_without_quotes("(", indent);
      print_internal(value.first, 0, false);
      print_internal_without_quotes(", ");
      print_internal(value.second, 0, false);
      print_internal_without_quotes(")", 0, newline, level);
    }

    template <class ...Ts>
    void print_internal(std::variant<Ts...> value, size_t indent = 0,
			bool newline = false, size_t level = 0) {
      std::visit([=](const auto& value) { print_internal(value, indent, newline, level); }, value);
    }

    template <typename T>
    void print_internal(std::optional<T> value, size_t indent = 0,
			bool newline = false, size_t level = 0) {
      if (value) {
	print_internal(value.value(), indent, newline, level);
      }
      else {
	print_internal_without_quotes("nullopt", indent, newline, level);
      }
    }

    size_t indent_;
    bool newline_;
    bool dereference_pointers_;

  };
  
}
