//  container-iterator.cpp
//  as of 2021-12-08 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <initializer_list>
#include <compare>
#include <iterator>
#include <stdexcept>
#include <ranges>
#include <algorithm>

using std::format;
using std::cout;
using std::string;
using std::initializer_list;

namespace ranges = std::ranges;
namespace views = std::ranges::views;

template<typename T>
class Container {
    std::unique_ptr<T[]> c_{};
    size_t n_elements_{};

public:
    Container(initializer_list<T> l) : n_elements_{l.size()} {
        c_ = std::make_unique<T[]>(n_elements_);
        size_t index{0};
        for(T e : l) {
            c_[index++] = e;
        }
    }
    
    Container(size_t sz) : n_elements_{sz} {
        c_ = std::make_unique<T[]>(n_elements_);
    }
    
    size_t size() const {
        return n_elements_;
    }

    const T& operator[](const size_t index) const {
        return c_[index];
    }

    T& at(const size_t index) const {
        if(index > n_elements_ - 1) {
            throw std::out_of_range("Container::at(): index out of range");
        }
        return c_[index];
    }

    bool empty() const {
        return (n_elements_ == 0);
    }

    class iterator {
        T* ptr_;

    public:
        // iterator traits
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::contiguous_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        // iterator constructor with default
        iterator(T* ptr = nullptr) : ptr_{ptr} {}

        // iterator operators 
        iterator& operator++() {
            ++ptr_;
            return *this;
        }

        iterator operator++(int) {
            auto ret = *this;
            ++ptr_;
            return ret;
        }

        iterator& operator--() {
            --ptr_;
            return *this;
        }

        iterator operator--(int) {
            auto ret = *this;
            --ptr_;
            return ret;
        }

        T& operator[](const size_t index) const {
            return *(ptr_ + index);
        }

        // default comparison operator (C++20)
        const auto operator<=>(const iterator& o) const {
            return ptr_ <=> o.ptr_;
        }

        const bool operator==(const iterator& o) const {
            return ptr_ == o.ptr_;
        }

        T& operator*() const {
            return *ptr_;
        }

        T* operator->() const {
            return ptr_;
        }

        iterator operator+(const size_t n) const {
            return iterator(ptr_ + n);
        }

        // non-member operator (n + it)
        friend const iterator operator+(const size_t n, const iterator& o) {
            return iterator(o.ptr_ + n);
        }

        const iterator operator-(const size_t n) {
            return iterator(ptr_ - n);
        }

        const size_t operator-(const iterator& o) {
            return ptr_ - o.ptr_;
        }

        iterator& operator+=(const size_t n) {
            ptr_ += n;
            return *this;
        }

        iterator& operator-=(const size_t n) {
            ptr_ -= n;
            return *this;
        }

    };

    // begin/end call iterator contsructor    
    iterator begin() const { return iterator(c_.get()); }
    iterator end() const { return iterator(c_.get() + n_elements_); }
};

void unit_tests(Container<string>& x) {
    puts("\nunit tests =============================");

    auto a = x.begin();
    auto b = x.begin() + 5;
    auto n = b - a;
    bool r{};

    cout << format("*a: {}\n", *a);
    cout << format("*b: {}\n", *b);
    cout << format("n: {}\n", n);
    
    r = (a += n) == b;
    cout << format("{}: (a += n) == b\n", r);

    a = x.begin();
    r = std::addressof(a += n) == std::addressof(a);
    cout << format("{}: std::addressof(a += n) == std::addressof(a)\n", r);

    a = x.begin();
    auto it1 = (a + n);
    auto it2 = (a += n);
    r = it1 == it2;
    cout << format("{}: (a + n) == (a += n)\n", r);

    a = x.begin();
    r = (a + n) == (n + a);
    cout << format("{}: (a + n) == (n + a)\n", r);
    
    int i{1};
    int j{2};
    r = a + (i + j) == (a + i) + j;
    cout << format("{}: a + (i + j) == (a + i) + j\n", r);

    r = a + 0 == a;
    cout << format("{}: a + 0 == a\n", r);

    b = x.begin() + n;
    r = --b == (a + (n - 1));
    cout << format("{}: --b == (a + (n - 1))\n", r);

    b = x.begin() + n;
    it1 = b += -n;
    b = x.begin() + n;
    it2 = b -= n;
    r = it1 == a && it2 == a;
    cout << format("{}: (b += -n) == a && (b -= n) == a\n", r);

    b = x.begin() + n;
    r = std::addressof(b -= n) == std::addressof(b);
    cout << format("{}: std::addressof(b -= n) == std::addressof(b)\n", r);

    b = x.begin() + n;
    it1 = b - n;
    b = x.begin() + n;
    it2 = b -= n;
    r = it1 == a && it2 == a;
    cout << format("{}: (b - n) == (b -= n)\n", r);

    b = x.begin() + n;
    r = a[n] == *b;
    cout << format("{}: a[n] == *b\n", r);

    r = (a <= b);
    cout << format("{}: (a <= b)\n", r);
}

int main() {
    Container<string> x{"one", "two", "three", "four", "five", 
        "six", "seven", "eight", "nine", "ten" };
    cout << format("Container x size: {}\n", x.size());

    puts("Container x:");
    for(auto e : x) {
        cout << format("{} ", e);
    }
    cout << '\n';

    puts("direct access elements:");
    cout << format("element at(5): {}\n", x.at(5));
    cout << format("element [5]: {}\n", x[5]);
    cout << format("element begin + 5: {}\n", *(x.begin() + 5));
    cout << format("element 5 + begin: {}\n", *(5 + x.begin()));
    cout << format("element begin += 5: {}\n", *(x.begin() += 5));

    puts("views pipe reverse:");
    auto result = x | views::reverse;
    for(auto v : result) cout << format("{} ", v);
    cout << '\n';

    Container<string> y(x.size());
    cout << format("Container y size: {}\n", y.size());
    for(auto e : y) {
        cout << format("[{}] ", e);
    }
    cout << '\n';

    unit_tests(x);
}
