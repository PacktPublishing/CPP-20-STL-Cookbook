//  jump.cpp
//  as of 2021-12-17 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <map>
#include <cctype>

using std::format;
using std::cout;
using std::cin;
using std::getline;
using std::string;
using std::map;

const char prompt(const char * p) {
    std::string r;
    cout << format("{} > ", p);
    getline(cin, r, '\n');

    if(r.size() < 1) return '\0';
    if(r.size() > 1) {
        cout << "Response too long\n";
        return '\0';
    }
    return toupper(r[0]);
}

int main() {
    using jumpfunc = void(*)();
    // alternately, std::function works too:
    // using jumpfunc = std::function<void()>;

    map<const char, jumpfunc> jumpmap {
        { 'A', []{ cout << "func A\n"; } },
        { 'B', []{ cout << "func B\n"; } },
        { 'C', []{ cout << "func C\n"; } },
        { 'D', []{ cout << "func D\n"; } },
        { 'X', []{ cout << "Bye!\n"; } }
    };
    
    char select{};
    while(select != 'X') {
        if((select = prompt("select A/B/C/D/X"))) {
            auto it = jumpmap.find(select);
            if(it != jumpmap.end()) it->second();
            else cout << "Invalid response\n";
        }
    }
}
