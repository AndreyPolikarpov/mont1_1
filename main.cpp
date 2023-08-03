#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <map>
#include <cstring>

#include "vector_my.hpp"
#include "lib.h"

int factorial(int i) {
  if(i==0) 
    return 1;
  else
   return i*factorial(i-1); 
}

int main() {

  
  try {
    //_1_
    std::map<int, int> m1;
    for(int i=0; i<10; ++i)
      m1.emplace(i, factorial(i));

    //_2_
    std::map<int, int, std::less<int>, alloc_my<std::pair<const int, int>>> m2;
    for(int i=0; i<10; ++i)
      m2.emplace(i, factorial(i));
    
    for(size_t i=0; i<m2.size(); ++i)
      std::cout << i << " : " << m2[i] << std::endl;

    //_3_
    my_vector_allocator<int> vec_loca;

    for(int i=0; i<10; ++i)
      vec_loca.push_back(i);
    
    //_4_
    my_vector <int>vec;
    for(int i=0; i<10; ++i)
      vec.push_back(i);

    my_iterator<int> iter_begin{vec.begin<int>()};
    my_iterator<int> iter_end{vec.end<int>()};
    
    while (iter_begin != iter_end) {
       std::cout << *iter_begin << std::endl;
      ++iter_begin;
    }
    
  } catch (const std::range_error &re) {
    std::cerr << re.what() << std::endl;
  }
  return 0;
}