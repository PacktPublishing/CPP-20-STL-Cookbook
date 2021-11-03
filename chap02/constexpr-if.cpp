//  constexpr-if.cpp
//  as of 2021-11-01 bw [bw.org]

#include <format>
#include <iostream>
#include <type_traits>

using std::format;
using std::cout;

template<typename T>
auto value_of(const T v) {
    if constexpr (std::is_pointer_v<T>) {
        return *v;
    } else {
        return v;
    }
}

int main() {
    int x{47};
    int* y{&x};
    
    cout << format("value is {}\n", value_of(x));  // value
    cout << format("value is {}\n", value_of(y));  // pointer
    return 0;
}
