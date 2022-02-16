//  alias_ptr.cpp
//  as of 2022-02-14 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <memory>
#include <tuple>

using std::cout;
using std::format;
using std::string;
using std::make_shared;
using std::shared_ptr;
using std::tuple;

struct animal {
    string name{};
    string sound{};

    animal(const string& n, const string& a) : name{n}, sound{a} {
        cout << format("ctor: {}\n", name);
    }

    ~animal() {
        cout << format("dtor: {}\n", name);
    }
};

auto make_animal(const string& n, const string& s) {
    auto ap = make_shared<animal>(n, s);
    auto np = shared_ptr<string>(ap, &ap->name);
    auto sp = shared_ptr<string>(ap, &ap->sound);
    return tuple(np, sp);
}

int main() {
    auto [name, sound] = make_animal("Velociraptor", "Grrrr!");
    cout << format("The {} says {}\n", *name, *sound);
    cout << format("Use count: name {}, sound {}\n", name.use_count(), sound.use_count());
}
