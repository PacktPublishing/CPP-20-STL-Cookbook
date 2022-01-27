//  initstruct.cpp
//  as of 2022-01-23 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using std::format;
using std::cout;
using std::cin;
using std::ifstream;
using std::string;
using std::vector;

constexpr const char * fn{ "cities.txt" };

struct City {
    string name;
    unsigned long population;
    double latitude;
    double longitude;
};

// skip BOM for UTF-8 on Windows
void skip_bom(auto& fs) {
    const unsigned char boms[]{ 0xef, 0xbb, 0xbf };
    bool have_bom{ true };
    for(const auto& c : boms) {
        if((unsigned char)fs.get() != c) have_bom = false;
    }
    if(!have_bom) fs.seekg(0);
    return;
}

string make_commas(const unsigned long num) {
    string s{ std::to_string(num) };
    for(int l = (int)s.length() - 3; l > 0; l -= 3) {
        s.insert(l, ",");
    }
    return s;
}

std::istream& operator>>(std::istream& in, City& c) {
    in >> std::ws;
    std::getline(in, c.name);
    in >> c.population >> c.latitude >> c.longitude;
    return in;
}

int main() {
    vector<City> cities;
    ifstream infile(fn, std::ios_base::in);
    if(!infile.is_open()) {
        cout << format("failed to open file {}\n", fn);
        return 1;
    }

    skip_bom(infile);
    for(City c{}; infile >> c;) cities.emplace_back(c);

    cout << format("{} cities imported\n", cities.size());
    for (const auto& [name, pop, lat, lon] : cities) {
        cout << format("{:.<15} pop {:<10} coords {}, {}\n", name, make_commas(pop), lat, lon);
    }
}
