//  weak_ptr.cpp
//  as of 2022-02-13 bw [bw.org]

#include <format>
#include <iostream>
#include <string_view>
#include <memory>

using std::cout;
using std::format;
using std::string_view;
using std::make_shared;
using std::shared_ptr;
using std::weak_ptr;


struct circB;
struct circA {
    shared_ptr<circB> p;
    ~circA() { cout << "dtor A\n"; }
};

struct circB {
    weak_ptr<circA> p;
    ~circB() { cout << "dtor B\n"; }
};

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

void get_weak_thing(const weak_ptr<Thing>& p) {
    if(auto sp = p.lock()) cout << format("{}: count {}\n", sp->thname, p.use_count());
    else cout << "no shared object\n";
}

int main() {
    auto thing1 = make_shared<Thing>("Thing 1");
    weak_ptr<Thing> wp1;
    cout << format("expired: {}\n", wp1.expired());
    get_weak_thing(wp1);

    cout << "\nassign wp1 = thing1\n";
    wp1 = thing1;
    get_weak_thing(wp1);

    cout << "\nconstruct weak_ptr with shared_ptr\n";
    weak_ptr<Thing> wp2(thing1);
    get_weak_thing(wp2);

    cout << "\nreset thing1\n";
    thing1.reset();
    get_weak_thing(wp1);
    get_weak_thing(wp2);

    cout << "\nresolve circular reference\n";
    auto a = make_shared<circA>();
    auto b = make_shared<circB>();

    a->p = b;
    b->p = a;

    cout << "\nend of main()\n";
}
