#include <bits/iterator_concepts.h>
#include <cstddef>
#include <iostream>
#include <memory>

#include "alloc_my.hpp"

//class my_iterator;

template <class T, class Allocator = alloc_my<T> >
class my_vector {
public:
/*
  //class my_iterator;
  typedef my_iterator<int> iterator;
  typedef my_iterator<const int> const_iterator;
  //typedef my_iterator<const T> const_iterator;
*/

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

/*
  bool operator=(const my_vector &b) {
    std::swap(alloc, b.alloc);
    std::swap(size, b.size);
    ~b.alloc;

    return true;
  }
*/  

private:
  std::size_t size = 0;    
  Allocator alloc;  
};

template <class T>
class my_iterator //: public std::iterator_traits<T> 
{
  //friend class my_vector<T>;
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
  

/*
  my_iterator(const my_iterator &it) : i_p(it.i_p) {};

  my_iterator &operator=(T *p) {
    i_p = p;
    return *this;
  }

  my_iterator &operator++() {
    ++i_p;
    return *this;  
  } 

  typename my_iterator::reference operator*() const {
    return *i_p;
  }
*/
private:   
  //my_iterator(T *p) noexcept : i_p_(p) {};
  //my_iterator(const T *p) noexcept : i_p_(p) {};
  pointer i_p_;
};
