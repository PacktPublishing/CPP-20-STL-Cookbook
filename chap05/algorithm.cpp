//  algorithm.cpp
//  as of 2021-12-17 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::format;
using std::cout;
using std::string;
using std::vector;
using std::count_if;

auto is_div_by(int divisor) {
    return [divisor](int i){ return i % divisor == 0; };
}

int main() {
    const vector<int> v{ 1, 7, 4, 9, 4, 8, 12, 10, 20 };

    for( int i : { 3, 4, 5 } ) {
        auto pred = is_div_by(i);
        int count = count_if(v.begin(), v.end(), pred);
        cout << format("numbers divisible by {}: {}\n", i, count);
    }
}
