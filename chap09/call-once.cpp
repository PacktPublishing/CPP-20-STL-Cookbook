//  call-once.cpp
//  as of 2022-03-07 bw [bw.org]

#include <format>
#include <iostream>
#include <thread>
#include <mutex>
#include <list>

using std::format;
using std::cout;
using std::list;
using std::thread;

constexpr size_t max_threads{ 25 };
std::once_flag init_flag;

void do_init(size_t id) {
    cout << format("do_init ({}): ", id);
}

void do_print(size_t id) {
    std::call_once(init_flag, do_init, id);
    cout << format("{} ", id);
}

int main() {
    list<thread> spawn;

    for (size_t id{}; id < max_threads; ++id) {
        spawn.emplace_back(do_print, id);
    }
    for (auto& t : spawn) t.join();
    cout << '\n';
}
