//  seq.cpp
//  as of 2021-12-01 bw [bw.org]

#include <format>
#include <iostream>

using std::format;
using std::cout;

template<typename T>
class Seq {
    T start_{};
    T end_{};

public:
    Seq(T start, T end) : start_{ start }, end_{ end } {}

    class iterator {
        T value_{};
    public:
        explicit iterator(T position = 0) : value_{position} {}

        T operator*() const { return value_; }

        iterator& operator++() {
            ++value_;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return value_ != other.value_;
        }
    };

    iterator begin() const { return iterator{start_}; }
    iterator end() const { return iterator{end_}; }
};

int main() {
    Seq<int> r{ 100, 110 };

    for (auto v : r) {
        cout << format("{} ", v);
    }
    cout << '\n';
}
