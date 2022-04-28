//  producer-consumer.cpp
//  as of 2022-03-29 bw [bw.org]

#include <format>
#include <iostream>
#include <deque>
#include <tuple>
#include <condition_variable>
#include <thread>

using std::format;
using std::cout;
using std::mutex;
using std::thread;

using namespace std::chrono_literals;
namespace this_thread = std::this_thread;

using guard_t = std::lock_guard<std::mutex>;
using lock_t = std::unique_lock<std::mutex>;

constexpr size_t num_items{ 10 };
constexpr auto delay_time{ 200ms };

std::deque<size_t> q{};
std::mutex mtx{};
std::condition_variable cond{};
bool finished{};

void producer() {
    for(size_t i{}; i < num_items; ++i) {
        this_thread::sleep_for(delay_time);
        guard_t x{ mtx };
        q.push_back(i);
        cond.notify_all();
    }

    guard_t x{ mtx };
    finished = true;
    cond.notify_all();
}

void consumer() {
    while(!finished) {
        lock_t lck{ mtx };
        cond.wait(lck, []{ return !q.empty() || finished; });
        while(!q.empty()) {
            cout << format("Got {} from the queue\n", q.front());
            q.pop_front();
        }
    }
}

int main() {
    thread t1{ producer };
    thread t2{ consumer };
    t1.join();
    t2.join();
    cout << "finished!\n";
}
