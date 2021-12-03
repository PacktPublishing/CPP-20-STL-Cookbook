//  insert-map.cpp
//  as of 2021-11-13 bw [bw.org]

#include <format>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

using std::format;
using std::cout;
using std::map;
using std::unordered_map;
using std::string;

struct BigThing {
    string v_;
    BigThing(const char * v) : v_(v) {
        cout << format("BigThing constructed {}\n", v_);
    }
};

using Mymap = map<string, BigThing>;   // convenience alias

void printm(Mymap& m) {
    for(auto& [k, v] : m) {
        cout << format("[{}:{}] ", k, v.v_);
    }
    cout << "\n";
}

int main() {
    Mymap m;

    m.try_emplace("Miles", "Trumpet");
    m.try_emplace("Hendrix", "Guitar");
    m.try_emplace("Krupa", "Drums");
    m.try_emplace("Zappa", "Guitar");
    m.try_emplace("Liszt", "Piano");
    printm(m);

    cout << "\n";
    cout << "emplace(Hendrix)\n";
    m.emplace("Hendrix", "Singer");
    cout << "try_emplace(Zappa)\n";
    m.try_emplace("Zappa", "Composer");
    printm(m);

    const char * key{"Zappa"};
    const char * payload{"Composer"};
    if(auto [it, success] = m.try_emplace(key, payload); !success) {
        cout << "update\n";
        it->second = payload;
    }
    printm(m);
}
