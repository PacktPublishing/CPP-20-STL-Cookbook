//  fib-generator.cpp
//  as of 2021-12-03 bw [bw.org]

#include <format>
#include <iostream>
#include <string_view>
#include <algorithm>
#include <ranges>

using std::format;
using std::cout;
using std::string_view;

namespace ranges = std::ranges;

void printc(const auto & v, const string_view s = "") {
    if(s.size()) cout << format("{}: ", s);
    for(auto e : v) cout << format("{} ", e);
    cout << '\n';
}

class fib_generator {
    using fib_t = unsigned long;

    fib_t stop_{};
    fib_t count_ { 0 };
    fib_t a_ { 0 };
    fib_t b_ { 1 };

    constexpr void do_fib() {
        const fib_t old_b = b_;
        b_ += a_;
        a_  = old_b;
    }

public:
    using iterator_concept  = std::forward_iterator_tag;
    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::remove_cv_t<fib_t>;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const fib_t*;
    using reference         = const fib_t&;

    explicit fib_generator(fib_t stop = 0) : stop_{ stop } {}

    fib_t operator*() const { return b_; }

    constexpr fib_generator& operator++() {
        do_fib();
        ++count_;
        return *this;
    }

    fib_generator operator++(int) {
        auto temp{ *this };
        ++*this;
        return temp; 
    }

    bool operator!=(const fib_generator &o) const {
        return count_ != o.count_; 
    }

    bool operator==(const fib_generator&o) const { 
        return count_ == o.count_; 
    }

    const fib_generator& begin() const { return *this; }

    const fib_generator end() const { 
        auto sentinel = fib_generator();
        sentinel.count_ = stop_;
        return sentinel;
    }

    fib_t size() { return stop_; }

};

int main() {
    printc(fib_generator(10));

    fib_generator fib(10);
    auto x = ranges::views::transform(fib, [](unsigned long x){ return x * x; });
    printc(x, "squared:");
}
