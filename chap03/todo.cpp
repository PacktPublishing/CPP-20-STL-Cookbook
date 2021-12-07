//  todo.cpp
//  as of 2021-11-23 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <map>

using std::format;
using std::cout;
using std::string;
using std::multimap;

using todomap = multimap<int, string>;

void rprint(todomap& todo) {
    for(auto it = todo.rbegin(); it != todo.rend(); ++it) {
        cout << format("{}: {}\n", it->first, it->second);
    }
    cout << '\n';
}

int main() {
    todomap todo {
        {1, "wash dishes"},
        {0, "watch teevee"},
        {2, "do homework"},
        {0, "read comics"}
    };
    rprint(todo);
}
