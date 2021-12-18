//  function.cpp
//  as of 2021-12-08 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <vector>
#include <functional>

using std::format;
using std::cout;
using std::string;
using std::deque;
using std::list;
using std::vector;
using std::function;

struct hello {
    void greeting() const { cout << "Hello Bob\n"; }
    void operator()() { greeting(); }
};

int main() {
    deque<int> d;
    list<int> l;
    vector<int> v;

    auto print_c = [](auto& c) {
        for(auto i : c) cout << format("{} ", i);
        cout << '\n';
    };

    auto push_c = [](auto& container) {
        return [&container](auto value) {
            container.push_back(value);
        };
    };

    const vector<std::function<void(int)>> 
        consumers { push_c(d), push_c(l), push_c(v) };

    for(auto &c : consumers) {
        for (int i{0}; i < 10; ++i) {
            c(i);
        }
    }

    print_c(d);
    print_c(l);
    print_c(v);

    hello bob{};
    const function<void(const hello&)> h1 = &hello::greeting;
    const function<void(void)> h2 = std::bind(&hello::greeting, &bob);
    const function<void(void)> h3 = hello();    // functor
    h1(bob);
    h2();
    h3();
}
