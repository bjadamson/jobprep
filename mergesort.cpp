#include <iostream>
#include <algorithm>
#include <vector>
 
void print(int const*const a, int n)
{
    int i = 0;
    while(i < n){
        std::cout << a[i] << ",";
        i++;
    }
    std::cout << "\ndone\n";
}

// uses twice the space to implement
std::vector<int> merge(std::vector<int> left, std::vector<int> right) {
    std::vector<int> r;

    // push values onto result vector
    while (!left.empty() && !right.empty()) {
        auto &t = (left.front() <= right.front()) ? left : right;
        r.push_back(*t.begin());
        t.erase(t.begin());
    }

    // now handle extra elements (vectors not same size)
    while (!left.empty()) {
        r.push_back(left.front());
        left.erase(left.begin());
    }
    while (!right.empty()) {
        r.push_back(right.front());
        right.erase(right.begin());
    }
    return r;
}

// 1) A list of lenth one is sorted
std::vector<int> mergesort(std::vector<int> const& list) {
    // base case, length 1 means sorted
    if (list.size() <= 1) {
        return list;
    }

    // sort two halves
    std::vector<int> a, b;
    auto const half = list.size() / 2;
    for(auto i = 0u; i < list.size(); ++i) {
        auto &v = (i < half) ? a : b;
        v.push_back(list[i]);
    }
    auto r = mergesort(a);
    auto r2 = mergesort(b);
    return merge(r, r2);
}
 
int main() {
    std::vector<int> const list = {3, 4, 6, 7, 2, 45, 4, 233, 12, 33, 17};
    print(list.data(), list.size());

    auto const l2 = mergesort(list);
    print(l2.data(), l2.size());
    return 0;
}
