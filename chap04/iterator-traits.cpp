//  iterator-traits.cpp
//  as of 2021-12-01 bw [bw.org]

#include <format>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <ranges>

using std::format;
using std::cout;

namespace ranges = std::ranges;

template<typename T>
class Seq {
    T start_{};
    T end_{};

public:
    Seq(T start, T end) : start_{ start }, end_{ end } {}

    class iterator {
        T value_{};
    public:
        using iterator_concept  = std::forward_iterator_tag;
        using iterator_category = std::forward_iterator_tag;
        using value_type        = std::remove_cv_t<T>;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        explicit iterator(T position = 0) : value_{position} {}

        T operator*() const { return value_; }

        iterator& operator++() {
            ++value_;
            return *this;
        }

        iterator operator++(T) {
            iterator temp = *this;
            ++*this;
            return temp; 
        }

        bool operator!=(const iterator& other) const noexcept {
            return value_ != other.value_;
        }

        bool operator==(const iterator& other) const noexcept {
            return value_ == other.value_;
        }
    };

    iterator begin() const { return iterator{start_}; }
    iterator end() const { return iterator{end_}; }
};

template<typename T>
requires std::forward_iterator<typename T::iterator>
void printc(const T & c) {
    for(auto v : c) {
        cout << format("{} ", v);
    }
    cout << '\n';
}

int main() {
    Seq<int> r{ 100, 110 };

    auto [min_it, max_it] = ranges::minmax_element(r);
    cout << format("{} - {}\n", *min_it, *max_it);

    printc(r);
    
    static_assert(ranges::forward_range<Seq<int>>);
}
