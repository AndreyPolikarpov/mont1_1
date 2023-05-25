#include "lib.h"

std::vector<int> split(const std::string &str, char d)
{
    std::vector<int> r;
    int i{0};
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos) {

      r.push_back(std::atoi(str.substr(start, stop - start).c_str()));
      ++i;      
      start = stop + 1;
      stop = str.find_first_of(d, start);

      if(i > 3) break;
    }

    r.push_back(std::atoi(str.substr(start, stop - start).c_str()));

    return r;
}
