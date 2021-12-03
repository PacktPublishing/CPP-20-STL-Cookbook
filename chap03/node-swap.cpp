//  node-swap.cpp
//  as of 2021-11-28 bw [bw.org]

#include <format>
#include <iostream>
#include <map>
#include <string>

using std::format;
using std::cout;
using std::map;
using std::string;
using std::swap;

using Racermap = map<unsigned int, string>;

void printm(const Racermap &m)
{
    cout << "Rank:\n";
    for (const auto& [rank, racer] : m) {
        cout << format("{}:{}\n", rank, racer);
    }
}

template<typename M, typename K>
bool node_swap(M & m, K k1, K k2) {
    auto node1{ m.extract(k1) };
    auto node2{ m.extract(k2) };
    if(node1.empty() || node2.empty()) {
        return false;
    }
    swap(node1.key(), node2.key());
    m.insert(move(node1));
    m.insert(move(node2));
    return true;
}

int main() {
    Racermap racers {
        {1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
        {4, "Peach"}, {5, "Donkey Kong Jr."}
    };
    printm(racers);

    node_swap(racers, 3, 5);
    printm(racers);
}
