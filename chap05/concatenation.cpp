//  concatenation.cpp
//  as of 2021-12-13 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <functional>

using std::format;
using std::cout;
using std::string;

template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts) {
    if constexpr (sizeof...(ts) > 0) {
        return [&](auto ...parameters) { return t(concat(ts...)(parameters...)); };
    } else  {
        return t;
    }
}

int main() {
    auto twice = [](auto i) { return i * 2; };
    auto thrice = [](auto i) { return i * 3; };

    auto combined = concat(thrice, twice, std::plus<int>{});

    std::cout << format("{}\n", combined(2, 3));
}
