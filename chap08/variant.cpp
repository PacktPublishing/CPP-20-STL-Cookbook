//  variant.cpp
//  as of 2022-02-01 bw [bw.org]

#include <format>
#include <iostream>
#include <variant>
#include <list>
#include <string_view>

using std::format;
using std::cout;
using std::list;
using std::string_view;

class Animal {
    string_view _name{};
    string_view _sound{};
    Animal();
public:
    Animal(string_view n, string_view s) : _name{ n }, _sound{ s } {}
    void speak() const {
        cout << format("{} says {}\n", _name, _sound);
    }
    void sound(string_view s) {
        _sound = s;
    }
};

class Cat : public Animal {
public:
    Cat(string_view n) : Animal(n, "meow") {}
};

class Dog : public Animal {
public:
    Dog(string_view n) : Animal(n, "arf!") {}
};

class Wookie : public Animal {
public:
    Wookie(string_view n) : Animal(n, "grrraarrgghh!") {}
};

using v_animal = std::variant<Cat, Dog, Wookie>;

struct animal_speaks {
    void operator()(const Dog& d) const { d.speak(); }
    void operator()(const Cat& c) const { c.speak(); }
    void operator()(const Wookie& w) const { w.speak(); }
};

int main() {
    list<v_animal> pets{ Cat{"Hobbes"}, Dog{"Fido"}, Cat{"Max"}, Wookie{"Chewie"} };

    cout << "visit:\n";
    for (const v_animal& a : pets) {
        visit(animal_speaks{}, a);
    }
    cout << "\n";

    cout << "index:\n";
    for(const v_animal &a : pets) {
        auto idx{ a.index() };
        if(idx == 0) get<Cat>(a).speak();
        if(idx == 1) get<Dog>(a).speak();
        if(idx == 2) get<Wookie>(a).speak();
    }
    cout << "\n";

    cout << "get_if:\n";
    for (const v_animal& a : pets) {
        if(const auto c{ get_if<Cat>(&a) }; c) {
            c->speak();
        } else if(const auto d{ get_if<Dog>(&a) }; d) {
            d->speak();
        } else if(const auto w{ get_if<Wookie>(&a) }; w) {
            w->speak();
        }
    }
    cout << "\n";

    size_t n_cats{}, n_dogs{}, n_wookies{};
    for(const v_animal& a : pets) {
        if(holds_alternative<Cat>(a)) ++n_cats;
        if(holds_alternative<Dog>(a)) ++n_dogs;
        if(holds_alternative<Wookie>(a)) ++n_wookies;
    }
    cout << format("there are {} cat(s), "
                   "{} dog(s), "
                   "and {} wookie(s)\n",
                   n_cats, n_dogs, n_wookies);
}
