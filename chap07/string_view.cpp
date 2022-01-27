//  string_view.cpp
//  as of 2022-01-15 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <string_view>

using std::format;
using std::cout;
using std::string;
using std::string_view;

int main() {
    char text[]{ "hello" };
    string_view sv1{ text };
    string_view sv2{ sv1 };
    string_view sv3{ sv2 };
    string_view sv4{ sv3 };

    string str1{ text };
    string str2{ str1 };
    string str3{ str2 };
    string str4{ str3 };

    text[0] = 'J';

    cout << format("sv1: {} {}\n", (void*)sv1.data(), sv1);
    cout << format("sv2: {} {}\n", (void*)sv2.data(), sv2);
    cout << format("sv3: {} {}\n", (void*)sv3.data(), sv3);
    cout << format("sv4: {} {}\n", (void*)sv4.data(), sv4);

    cout << format("str1: {} {}\n", (void*)str1.data(), str1);
    cout << format("str2: {} {}\n", (void*)str2.data(), str2);
    cout << format("str3: {} {}\n", (void*)str3.data(), str3);
    cout << format("str4: {} {}\n", (void*)str4.data(), str4);
}
