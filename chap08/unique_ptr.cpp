//  unique_ptr.cpp
//  as of 2022-02-12 bw [bw.org]

#include <format>
#include <iostream>
#include <string_view>
#include <memory>

using std::cout;
using std::format;
using std::string_view;
using std::make_unique;
using std::unique_ptr;

struct Thing {
    string_view thname{"unk"};

    Thing() {
        cout << format("default ctor: {}\n", thname);
    }

    Thing(const string_view& n) : thname(n) {
        cout << format("param ctor: {}\n", thname);
    }

    ~Thing() {
        cout << format("dtor: {}\n", thname);
    }
};

void process_thing(const unique_ptr<Thing>& p) {
    if(p) cout << format("processing: {}\n", p->thname);
    else cout << "invalid pointer\n";
}

int main() {
    auto p1 = make_unique<Thing>("Thing 1");
    process_thing(p1);
    process_thing(make_unique<Thing>("Thing 2"));

    auto p2 = std::move(p1);
    process_thing(p1);
    process_thing(p2);

    p2.reset(new Thing("Thing 3"));
    process_thing(p2);

    cout << "end of main()\n";
}
