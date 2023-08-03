#include <bits/iterator_concepts.h>
#include <cstddef>
#include <iostream>
#include <memory>

#include "alloc_my.hpp"

template <class T, class Allocator = alloc_my<T> >
class my_vector {
public:

  my_vector() = default;
  my_vector(std::initializer_list<T> values) {
    alloc.construct(values);
  }

  template<class U>
  U* begin() {
      return alloc.template first_element<U>();
  }
  template<class U>
  U* end() { return (alloc.template last_element<U>());}

  void push_back(T x) {
      alloc.construct(alloc.allocate(1), x);
      ++size;
  }

  void pop_back() {
    if(size) {
      alloc.deallocate(alloc.last_element(), 1);
      --size;
    } else {
      std::cerr << "my_vector пуст" << std::endl;
    }
  }

  std::size_t size_vect() {
    return size;
  }

  bool empty() {
    return (size) ? false : true;
  }

  T operator[](size_t i) {
    return *(alloc.first_element() + i);
  }
private:
  std::size_t size = 0;    
  Allocator alloc;  
};

template <class T>
class my_iterator {
public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;

  //my_iterator(pointer ptr) : i_p_(ptr) {};
  explicit my_iterator(pointer p) : i_p_(p) {};

  reference operator*() const {return *i_p_;}
  pointer operator->() { return i_p_;}

  my_iterator& operator++() { i_p_++; return *this;}
  my_iterator operator++(int) { my_iterator tmp = *this; ++(*this); return tmp;}

  friend bool operator==(const my_iterator &a, const my_iterator &b) {return a.i_p_ == b.i_p_;}
  friend bool operator!=(const my_iterator &a, const my_iterator &b) {return a.i_p_ != b.i_p_;}

  bool operator==(const my_iterator &iter) { return i_p_ == iter.i_p_;}
  bool operator!=(const my_iterator &iter) { return i_p_ != iter.i_p_;}

private:
  pointer i_p_;
};

template <class T, class Allocator = std::allocator<T> >
class my_vector_allocator {
public:
void push_back(const T& x) {
    if (size == capacity) {
        T* newData = alloc.allocate(capacity);
        std::copy(data, data + capacity * sizeof(T), newData); //naive
        std::swap(newData, data);
        alloc.deallocate(newData, capacity);
    }
  
   ::new((void*)(data + size * sizeof(T))) T(x);
    ++size;
}

private:
    std::size_t size = 0;
    std::size_t capacity = 0;
    T* data = nullptr;

    Allocator alloc;
};
