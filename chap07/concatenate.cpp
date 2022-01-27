//  concatenate.cpp
//  as of 2022-01-16 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>

using std::format;
using std::cout;
using std::string;
using std::ostringstream;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

void timer(string(*f)()) {
    auto t1 = high_resolution_clock::now();
    string s{ f() };
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms = t2 - t1;
    cout << s;
    cout << format("duration: {} ms\n", ms.count());
}

string append_string() {
    cout << "append_string\n";
    string a{ "a" };
    string b{ "b" };
    long n{0};
    while(++n) {
        string x{};
        x.append(a);
        x.append(", ");
        x.append(b);
        x.append("\n");
        if(n >= 10000000) return x;
    }
    return "error\n";
}

string concat_string() {
    cout << "concat_string\n";
    string a{ "a" };
    string b{ "b" };
    long n{0};
    while(++n) {
        string x{};
        x += a + ", " + b + "\n";
        if(n >= 10000000) return x;
    }
    return "error\n";
}

string concat_ostringstream() {
    cout << "ostringstream\n";
    string a { "a" };
    string b { "b" };
    long n{0};
    while(++n) {
        ostringstream x{};
        x << a << ", " << b << "\n";
        if(n >= 10000000) return x.str();
    }
    return "error\n";
}

string concat_format() {
    cout << "append_format\n";
    string a{ "a" };
    string b{ "b" };
    long n{0};
    while(++n) {
        string x{};
        x = format("{}, {}\n", a, b);
        if(n >= 10000000) return x;
    }
    return "error\n";
}

int main() {
    timer(append_string);
    timer(concat_string);
    timer(concat_ostringstream);
    timer(concat_format);
}
