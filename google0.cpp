#include <iostream>
#include <cassert>
#include <string>
#include <experimental/optional>
#include <algorithm>

// Problem: given a collection of integers and a sum, find two elements with the same value that
// sum to the given sum.

// find index of V in array
// array is sorted
// linear search of elements worst case O(N)
template<int N>
std::experimental::optional<int> find_index(int const (&arr)[N], int const value) {
    // TODO: binary search, need one that returns an index (maybe upper_bound or lower_bound)
    for (auto i = 0; i < N; ++i) {
        auto const c = arr[i];
        if (c == value) { // found it
            return i; // return the index where value was found
        }
        // If current element is greater than the value, we can stop (re: array is sorted)
        else if (c > value) {
            break;
        }
    }
    return {};
}

template<int N>
bool check_neighbors(int const (&arr)[N], int const value, int const index) {
    assert(index > -1 && index < N);
    // it's ok to create references, as long as we don't read them until we make sure their valid.
    auto &prev = arr[index - 1];
    auto &next = arr[index + 1];

    // 1. Check edge cases
    if (index == 0) { // only check to right
        return next == value;
    } else if (index == N - 1) { // only check to left
        return prev == value;
    }

    // hot path
    return (next == value) || (prev == value);
}

// Assumptions: collection is an array.
//
// The solution if it exists is two entries with values equal to half the sum.
// 1. Find index of half the sum, if present.
// 2. If found, then examine neighbor values within the array.
// 3. If either neighbor values matchc our value, we found an answer.
// 4. Otherwise return none.
template<std::size_t N>
bool find(int const (&arr)[N], int const sum) {
    if ((sum % 2) != 0) return false; // Odd numbers
    if (N < 2) return false; // Not enough elements in collection.

    auto value = sum / 2;
    auto index = find_index(arr, value);
    if (!index) return false;

    return check_neighbors(arr, value, *index);
}

std::string make_msg(int const sum, bool const found) {
    std::string const prefix = found ? "FOUND IT!" : "NOPE";
    return prefix + std::string{"', sum: '"} + std::to_string(sum) + std::string{"'"};
}

int main()
{
    int arr[] = {3, 3, 4, 5, 6, 7, 7, 8, 9, 9, 12};

    for (auto i = 0; i < 30; ++i) {
        auto const found = find(arr, i);
        std::cout << make_msg(i, found)  << std::endl;
    }
}

