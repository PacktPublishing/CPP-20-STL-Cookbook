//  gather.cpp
//  as of 2022-03-22 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

using std::format;
using std::cout;
using std::string;
using std::vector;

namespace bw {

using std::stable_partition;
using std::pair;
using std::not_fn;

template <typename It, typename Pred>
pair<It, It> gather(It first, It last, It pivot, Pred pred) {
    return { stable_partition(first, pivot, not_fn(pred)),
             stable_partition(pivot, last, pred) };
}

// helper lambdas
constexpr auto midit = [](auto& v) {
    return v.begin() + (v.end() - v.begin()) / 2;
};

constexpr auto is_even = [](auto i) {
    return i % 2 == 0;
};

constexpr auto is_even_char = [](auto c) {
    if(c >= '0' && c <= '9') return (c - '0') % 2 == 0;
    else return false;
};

};

int main() {
    vector<int> vint{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    string jenny{ "867-5309" };

    auto gathered_even = bw::gather(vint.begin(), vint.end(), bw::midit(vint), bw::is_even);
    for(const auto& el : vint) cout << el;
    cout << '\n';
    auto& [it1, it2] = gathered_even;
    for(auto it{ it1 }; it < it2; ++it) cout << *it;
    cout << '\n';

    bw::gather(vint.begin(), vint.end(), vint.begin(), bw::is_even);
    for(const auto& el : vint) cout << el;
    cout << '\n';

    bw::gather(vint.begin(), vint.end(), vint.end(), bw::is_even);
    for(const auto& el : vint) cout << el;
    cout << '\n';

    bw::gather(jenny.begin(), jenny.end(), jenny.end(), bw::is_even_char);
    for(const auto& el : jenny) cout << el;
    cout << '\n';
}
