//  transform.cpp
//  as of 2022-01-17 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using std::format;
using std::cout;
using std::string;
using std::string_view;

char char_upper(const char& c) {
    return static_cast<char>(std::toupper(c));
}

char char_lower(const char& c) {
    return static_cast<char>(std::tolower(c));
}

char rot13(const char& x) {
    auto rot13a = [](char x, char a)->char { 
        return a + (x - a + 13) % 26; 
    };
    if (x >= 'A' && x <= 'Z') return rot13a(x, 'A');
    if (x >= 'a' && x <= 'z') return rot13a(x, 'a');
    return x;
}
 
string& title_case(string& s) {
    auto begin = s.begin();
    auto end = s.end();
    *begin++ = char_upper(*begin);  // first element
    bool space_flag{ false };
    for(auto it{ begin }; it != end; ++it) {
        if(*it == ' ') {
            space_flag = true;
        } else {
            if(space_flag) *it = char_upper(*it);
            space_flag = false;
        }
    }
    return s;
}

int main() {
    string s{ "hello jimi\n" };
    cout << s;

    std::transform(s.begin(), s.end(), s.begin(), char_upper);
    cout << s;

    for(auto& c : s) c = rot13(c);
    cout << s;

    for(auto& c : s) c = rot13(char_lower(c));
    cout << s;

    cout << title_case(s);
}
