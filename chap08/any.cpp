//  any.cpp
//  as of 2022-01-30 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <any>
#include <typeinfo>

using std::format;
using std::cout;
using std::string;
using std::list;
using std::vector;
using std::any;
using std::any_cast;

using namespace std::literals;

void p_any(const any& a) {
    if (!a.has_value()) {
        cout << "None.\n";
    } else if (a.type() == typeid(int)) {
        cout << format("int: {}\n", any_cast<int>(a));
    } else if (a.type() == typeid(string)) {
        cout << format("string: \"{}\"\n", any_cast<const string&>(a));
    } else if (a.type() == typeid(list<int>)) {
        cout << "list<int>: ";
        for(auto& i : any_cast<const list<int>&>(a)) cout << format("{} ", i);
        cout << '\n';
    } else {
        cout << format("something else: {}\n", a.type().name());
    }
}

int main() {
    any x{};
    if(x.has_value()) cout << "have value\n";
    else cout << "no value\n";

    x = 42;
    if(x.has_value()) {
        cout << format("x has type: {}\n", x.type().name());
        cout << format("x has value: {}\n", any_cast<int>(x));
    } else {
        cout << "no value\n";
    }

    x = "abc"s;
    cout << format("x is type {} with value {}\n", x.type().name(), any_cast<string>(x));

    x = list{ 1, 2, 3 };
    cout << format("x is type {} with value ", x.type().name());
    for(const int& i : any_cast<list<int>&>(x)) cout << i << ' ';
    cout << '\n';

    try {
        cout << any_cast<int>(x) << '\n';
    } catch(std::bad_any_cast& e) {
        cout << format("any: {}\n", e.what());
    }

    p_any({});
    p_any(47);
    p_any("abc"s);
    p_any(any(list{ 1, 2, 3 }));
    p_any(any(vector{ 1, 2, 3 }));
}
