//  template-deduction.cpp
//  as of 2021-11-01 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <typeinfo>
#include <tuple>

using std::cout, std::format, std::string;
using namespace std::literals;  // for "literal string"s syntax

// simple template function 
template<typename T1, typename T2>
string f(const T1 a, const T2 b) {
    return format("{} {}", typeid(T1).name(), typeid(T2).name());
}

// simple template class
template<typename T1, typename T2, typename T3>
class Things {
    T1 v1{};
    T2 v2{};
    T3 v3{};
public:
    explicit Things(T1 p1, T2 p2, T3 p3)
    : v1{p1}, v2{p2}, v3{p3} {}
    string print() {
        return format("{}, {}, {}\n",
            typeid(v1).name(),
            typeid(v2).name(),
            typeid(v3).name()
        );
    }
};

// requires template deduction guide 
template <typename T>
class Sum {
    T v{};
public:
    template <typename... Ts>
    Sum(Ts&& ... values) : v{ (values + ...) } {}
    const T& value() const { return v; }
};

// template deduction guide 
template <typename... Ts>
Sum(Ts&& ... ts) -> Sum<std::common_type_t<Ts...>>;

int main() {
    // simple template function
    cout << format("T1 T2: {}\n", f(47, 47L));
    cout << format("T1 T2: {}\n", f(47L, 47.0));
    cout << format("T1 T2: {}\n", f(47.0, "47"));

    // test the simple template class
    Things thing1{ 1, 47.0, "three" };

    // test the template deduction guide 
    Sum s1 { 1u, 2.0, 3, 4.0f };
    Sum s2 { "abc"s, "def" };
    auto v1 = s1.value();
    auto v2 = s2.value();

    cout << format("s1 is {} {}, s2 is {} {}",
        typeid(v1).name(), v1, typeid(v2).name(), v2);

}
