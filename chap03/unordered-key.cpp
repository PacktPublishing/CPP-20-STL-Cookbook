//  unordered-key.cpp
//  as of 2021-11-16 bw [bw.org]

#include <format>
#include <iostream>
#include <unordered_map>
#include <string>

using std::format;
using std::cout;
using std::unordered_map;

struct Coord {
    int x{};
    int y{};
};

using Coordmap = unordered_map<Coord, int>;

bool operator==(const Coord& lhs, const Coord& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

namespace std {
    template<>
    struct hash<Coord> {
        size_t operator()(const Coord& c) const {
            return static_cast<size_t>(c.x)
                 + static_cast<size_t>(c.y);
        }
    };
}

void print_Coordmap(const Coordmap& m) {
    for (const auto& [key, value] : m) {
        cout << format("{{ ({}, {}): {} }} ",
            key.x, key.y, value);
    }
    cout << '\n';
}

int main() {
    Coordmap m {
        { {0, 0}, 1 },
        { {0, 1}, 2 },
        { {2, 1}, 3 } 
    };
    print_Coordmap(m);

    Coord k{ 0, 1 };
    cout << format("{{ ({}, {}): {} }}\n",
        k.x, k.y, m.at(k));
}
