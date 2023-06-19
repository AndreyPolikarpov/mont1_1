#include <iostream>
#include <memory>

#include "alloc_my.hpp"

template <class T, class Allocator = alloc_my<T> >
class my_vector {
public:

  //class my_iterator;
  typedef my_iterator<int> iterator;
  typedef my_iterator<const int> const_iterator;
  //typedef my_iterator<const T> const_iterator;

  my_vector() = default;
  my_vector(std::initializer_list<T> values) {
    alloc.construct(values);
  }

  my_iterator begin() {
    return my_iterator(alloc.first_element());
  }

  my_iterator end() {
    return my_iterator(alloc.last_element());
  }


  void push_back(T x) {
      alloc.construct(&x);
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
class my_iterator : public std::iterator_traits<T> 
{
  friend class my_vector<T>;
public:
  my_iterator(const my_iterator &it) : i_p(it.i_p) {};

  my_iterator &operator=(T *p) {
    i_p = p;
    return *this;
  }

  bool operator!=(const my_iterator &iter) {
    return i_p != iter.i_p;
  }  
  
  bool operator==(const my_iterator &iter) {
    return i_p == iter.i_p;
  } 

  my_iterator &operator++() {
    ++i_p;
    return *this;  
  } 

  typename my_iterator::reference operator*() const {
    return *i_p;
  }

private:   
  my_iterator(T *p) noexcept : i_p(p) {};
  my_iterator(const T *p) noexcept : i_p(p) {};
  T *i_p;
};
