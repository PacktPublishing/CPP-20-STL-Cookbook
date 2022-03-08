//  async.cpp
//  as of 2022-03-07 bw [bw.org]

#include <format>
#include <iostream>
#include <string>
#include <list>
#include <chrono>
#include <future>

using std::format;
using std::cout;
using std::string;
using std::list;
using std::chrono::steady_clock;
using std::async;

using launch = std::launch;
using secs = std::chrono::duration<double>;

struct prime_time {
    secs dur{};
    uint64_t count{};
};

prime_time count_primes(const uint64_t& max) {
    prime_time ret{};
    constexpr auto isprime = [](const uint64_t& n) {
        for(uint64_t i{ 2 }; i < n / 2; ++i) {
            if(n % i == 0) return false;
        }
        return true;
    };
    uint64_t start{ 2 };
    uint64_t end{ max };
    auto t1 = steady_clock::now();
    for(uint64_t i{ start }; i <= end ; ++i) {
        if(isprime(i)) ++ret.count;
    }
    ret.dur = steady_clock::now() - t1;
    return ret;
}

int main() {
    constexpr uint64_t MAX_PRIME{ 0x1FFFF };  // largest uint64_t is 0xFFFFFFFFFFFFFFFF
    constexpr size_t num_threads{ 15 };
    list<std::future<prime_time>> swarm;

    cout << "start parallel primes\n";
    auto t1{ steady_clock::now() };
    for(size_t i{}; i < num_threads; ++i) {
        swarm.emplace_back(async(launch::async, count_primes, MAX_PRIME));
    }

    for(auto& f : swarm) {
        static size_t i{};
        auto pt = f.get();
        cout << format("primes({:02}): {} {:.5}\n", ++i, pt.count, pt.dur);
    }

    secs dur_total{ steady_clock::now() - t1 };
    cout << format("total duration: {:.5}s\n", dur_total.count());
}
