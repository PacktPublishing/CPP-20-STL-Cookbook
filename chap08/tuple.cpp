//  tuple.cpp
//  as of 2022-02-10 bw [bw.org]

#include <format>
#include <iostream>
#include <tuple>

using std::cout;
using std::format;
using std::tuple;
using std::get;

template<typename... T>
constexpr void print_t(const tuple<T...>& tup) {
    auto lpt =
        [&tup] <size_t... I> (std::index_sequence<I...>) constexpr {
            (..., ( cout <<
                format((I? ", {}" : "{}"), get<I>(tup))
            ));
            cout << '\n';
        };
    lpt(std::make_index_sequence<sizeof...(T)>());
}

template<typename... T>
constexpr int sum_t(const tuple<T...>& tup) {
    int accum{};
    auto lpt =
        [&tup, &accum] <size_t... I> (std::index_sequence<I...>) constexpr {
            (..., ( 
                accum += get<I>(tup)
            ));
        };
    lpt(std::make_index_sequence<sizeof...(T)>());
    return accum;
}

int main() {
    tuple lables{ "ID", "Name", "Scale" };
    tuple employee{ 123456, "John Doe", 3.7 };
    tuple nums{ 1, 7, "forty-two", 47, 73L, -111.11 };
    
    print_t(lables);
    print_t(employee);
    print_t(nums);

    tuple ti1{ 1, 2, 3, 4, 5 };
    tuple ti2{ 9, 10, 11, 12, 13, 14, 15 };
    tuple ti3{ 47, 73, 42 };
    auto sum1{ sum_t(ti1) };
    auto sum2{ sum_t(ti2) };
    auto sum3{ sum_t(ti3) };
    cout << format("sum of ti1: {}\n", sum1);
    cout << format("sum of ti2: {}\n", sum2);
    cout << format("sum of ti3: {}\n", sum3);
}
