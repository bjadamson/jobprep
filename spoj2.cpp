#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include <istream>
#include <string>
#include <iterator>
#include <vector>
#include <cassert>
#include <sstream>

bool is_prime(int const n) {
    if (n == 1) return false;
    if (n == 2) return true;
    if (n == 3) return true;
    if ((n % 2) == 0) return false;
    if ((n % 3) == 0) return false;

    int i = 5;
    int w = 2;

    while ((i * i) <= n) {
        if ((n % i) == 0) {
            return false;
        }
        i += w;
        w = 6 - w;
    }

    return true;
}
    

int main()
{
    std::string data;
  
    // read number of test cases
    std::getline(std::cin, data);
    int const num_testcases = std::stoi(data);
  
    for (auto i = 0; i < num_testcases; ++i) {
        getline (std::cin, data);
        std::stringstream datastream(data);
        
        // Copy the data from the stream into a vector.
        std::vector<int> vec;
        std::copy(std::istream_iterator<int>(datastream), std::istream_iterator<int>(), std::back_inserter(vec));        
        assert(vec.size() == 2);
        
        int const& m = vec[0];
        int const& n = vec[1];
        
        for (auto j = m; j <= n; ++j) {
            if (is_prime(j)) std::cout << j << std::endl;
        }
        std::cout << std::endl;
    }
}
