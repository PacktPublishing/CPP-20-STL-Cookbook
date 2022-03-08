//  multi-producer-consumer.cpp
//  as of 2022-03-06 bw [bw.org]

#include <format>
#include <iostream>
#include <list>
#include <string>
#include <deque>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <chrono>

using std::format;
using std::cout;
using std::string;
using std::list;
using std::mutex;
using std::unique_lock;
using std::async;
using std::future;
using std::condition_variable;

using namespace std::chrono_literals;
namespace this_thread = std::this_thread;

constexpr auto delay_time{ 50ms };
constexpr auto consumer_wait{ 100ms };
constexpr size_t queue_limit{ 5 };
constexpr size_t num_items{ 15 };
constexpr size_t num_producers{ 3 };
constexpr size_t num_consumers{ 5 };

std::deque<string> qs{};
mutex q_mutex{};
condition_variable cv_producer{};
condition_variable cv_consumer{};
bool production_complete{};

void producer(const size_t id) {
    for(size_t i{}; i < num_items; ++i) {
        this_thread::sleep_for(delay_time * id);
        unique_lock<mutex> lock(q_mutex);
        cv_producer.wait(lock, [&]{ return qs.size() < queue_limit; });
        qs.push_back(format("pid {}, qs  {}, item {:02}\n", id, qs.size(), i + 1));
        cv_consumer.notify_all();
    }
}

void consumer(const size_t id) {
    while(!production_complete) {
        unique_lock<mutex> lock(q_mutex);
        cv_consumer.wait_for(lock, consumer_wait, [&]{ return !qs.empty(); });
        if(!qs.empty()) {
            cout << format("cid {}: {}", id, qs.front());
            qs.pop_front();
        }
        cv_producer.notify_all();
    }
}

int main() {
    list<future<void>> producers;
    list<future<void>> consumers;

    for(size_t i{}; i < num_producers; ++i) {
        producers.emplace_back(async(producer, i));
    }

    for(size_t i{}; i < num_consumers; ++i) {
        consumers.emplace_back(async(consumer, i));
    }
    
    for(auto& f : producers) f.wait();
    production_complete = true;
    cout << "producers done.\n";

    for(auto& f : consumers) f.wait();
    cout << "consumers done.\n";
}
