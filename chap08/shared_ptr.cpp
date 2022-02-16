//  shared_ptr.cpp
//  as of 2022-02-12 bw [bw.org]

#include <format>
#include <iostream>
#include <string_view>
#include <memory>

using std::cout;
using std::format;
using std::string_view;
using std::make_shared;
using std::shared_ptr;

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

void check_thing_ptr(const shared_ptr<Thing>& p) {
    if(p) cout << format("{} use count: {}\n", p->thname, p.use_count());
    else cout << "invalid pointer\n";
}

int main() {
    shared_ptr<Thing> p1{ new Thing("Thing 1") };
    auto p2 = make_shared<Thing>("Thing 2");

    {
        cout << "make 4 copies of p1:\n";
        auto pa = p1;
        auto pb = p1;
        auto pc = p1;
        auto pd = p1;
        check_thing_ptr(p1);
        pb.reset();
        p1.reset();
        check_thing_ptr(pd);
    }

    check_thing_ptr(p1);
    check_thing_ptr(p2);
    cout << "end of main()\n";
}
