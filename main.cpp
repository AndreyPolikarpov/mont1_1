#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <map>
#include <cstring>

//#include "alloc_my.hpp"
#include "vector_my.hpp"

int main() {

  
  try {
    /*
    std::map<int, int, std::less<int>, alloc_my<std::pair<const int, int>>> m;  
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[4] = 4;
    m[5] = 5;
    m[6] = 6;
    m[7] = 7;

    std::cout << " size: "<< m.size() << std::endl;

    for(size_t i=0; i<m.size(); ++i)
      std::cout << m[i] << " : " << i << std::endl;
    */
      //Почему ниже не работает? нужно добавить "хвост" -окончание ?
    //for(const auto &[first,second] : m) 
    //  std::cout << first << " : " << second << std::endl;
    
    my_vector <int>vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

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

