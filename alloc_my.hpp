#include <iostream>
#include <memory>
#include <stdexcept>
#include <cstring>

namespace{
  size_t s_max_size_alloc{3};
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

    if(offset >= (s_max_size_alloc-1)) {
      void *temp = std::malloc((s_max_size_alloc * 2) * sizeof(T));
      if(temp== nullptr) {
        throw std::range_error("Превышен размер аллокатора");  
      }

      std::memcpy(temp, pool, s_max_size_alloc);
      std::free(pool);
      pool = temp;
      s_max_size_alloc = s_max_size_alloc * 2;
      std::cout << "Размер аллокатора увеличился и стал равен : " << s_max_size_alloc << std::endl;
    }

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

  template <typename U>
  U *last_element() {
    return (pool + offset);
  }

  template <typename U>
  U *first_element() {
    return pool;
  }
  
  //size_t size() { return offset;}  
};

template <class T, class U>
constexpr bool operator== (const alloc_my<T>& a1, const alloc_my<U>& a2) noexcept
{
    return &a1 == &a2;
}

template <class T, class U>
constexpr bool operator!= (const alloc_my<T>& a1, const alloc_my<U>& a2) noexcept
{
    return &a1 != &a2;
}
