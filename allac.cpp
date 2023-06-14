#include <iostream>
#include <memory>
#include <stdexcept>
#include <map>
#include <cstring>

namespace{
  const size_t s_max_size_alloc{3};
}

template <class T> 
struct alloc_my{
  using value_type = T;

  void* pool;
  size_t offset;

	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;

  template <typename U>
	struct rebind {
		using other = alloc_my<U>;
	};

  alloc_my() {
    //pool = ::operator new(1000 * sizeof(T));
    pool = malloc(s_max_size_alloc * sizeof(T));
    std::cout << "allocate alloc_my " << pool <<  std::endl;
  }
  ~alloc_my(){
    std::cout << "allocate ~alloc_my " << pool << std::endl;
    //::operator delete(pool); 
    free(pool);
  };

  template <typename U>
  alloc_my(const alloc_my<U> &) {
  }

  T *allocate(std::size_t n) {

    if(offset >= (s_max_size_alloc-1)) 
      throw std::range_error("Превышен размер аллокатора");

    T *p = (T*)pool + offset;
    std::cout << "allocate::offset " << offset << "[n = " << n << "]" << std::endl;
    ++offset;
    return p;
  }

  void deallocate(T *p, std::size_t n) {
    std::memset(p, 0, (sizeof(T) * n));
    --offset;
    std::cout << "deallocate::offset " << "[n = " << n << "]" << offset <<  std::endl;
  }

  template <typename U, typename... Args>
  void construct(U *p, Args &&...args) {
    std::cout << " construct " << p /*<< __PRETTY_FUNCTION__ */<< std::endl;
    ::new ((void *) p) U(std::forward<Args>(args)...);
  }
  
  template <typename U>
  void destroy(U *p) {
    std::cout << " destroy " << p /*<< __PRETTY_FUNCTION__ */<< std::endl;
    p->~U();
  }
};

int main() {

  std::map<int, int, std::less<int>, alloc_my<std::pair<const int, int>>> m;  
  try {
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[4] = 4;
    m[5] = 5;
  } catch (const std::range_error &re) {
    std::cerr << re.what() << std::endl;
  }
  return 0;
}

