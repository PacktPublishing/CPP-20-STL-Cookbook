//  atomic.cpp
//  as of 2022-03-03 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <atomic>

using std::format;
using std::cout;
using std::string;
using std::vector;

std::atomic<bool> ready{};
std::atomic<uint64_t> g_count{};
std::atomic_flag winner{};

constexpr int max_count{1000 * 1000};
constexpr int max_threads{100};

string make_commas(const uint64_t& num) {
    string s{ std::to_string(num) };
    for(long l = s.length() - 3; l > 0; l -= 3) {
        s.insert(l, ",");
    }
    return s;
}

void countem (int id) {
    while(!ready) std::this_thread::yield();
    for(int i{}; i < max_count; ++i) ++g_count;
    if(!winner.test_and_set()) {
        std::cout << format("thread {:02} won!\n", id);
    }
};

int main() {
    vector<std::thread> swarm;
    cout << format("spawn {} threads\n", max_threads);
    for(int i{}; i < max_threads; ++i) {
        swarm.emplace_back(countem, i);
    }
    ready = true;
    for(auto& t : swarm) t.join();
    cout << format("global count: {}\n", make_commas(g_count));
    return 0;
}
