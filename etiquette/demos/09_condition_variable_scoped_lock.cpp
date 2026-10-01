// 09_condition_variable_scoped_lock.cpp — producer/consumer with a condition variable,
// and std::scoped_lock to lock two mutexes without deadlock.
// Build: g++ -std=c++20 -O2 -pthread -Wall -Wextra 09_condition_variable_scoped_lock.cpp -o cv
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

// ---------------- Producer / consumer ----------------
std::mutex              q_mutex;
std::condition_variable q_cv;
std::queue<int>         jobs;
bool                    done = false;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(q_mutex);
            jobs.push(i);
        }                       // unlock BEFORE notifying so the woken thread can grab the lock
        q_cv.notify_one();
    }
    {
        std::lock_guard<std::mutex> lock(q_mutex);
        done = true;            // shared state changes ALWAYS happen under the mutex
    }
    q_cv.notify_all();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(q_mutex);           // unique_lock: wait() must unlock/relock
        q_cv.wait(lock, [] { return !jobs.empty() || done; }); // predicate handles spurious wakeups
        if (jobs.empty()) return;                              // done and drained
        int job = jobs.front();
        jobs.pop();
        lock.unlock();                                         // don't hold the lock while working
        std::cout << "  consumed job " << job << "\n";
    }
}

// ---------------- Deadlock avoidance ----------------
struct Account {
    std::mutex m;
    int balance = 100;
};

// Thread A calls transfer(x, y) while thread B calls transfer(y, x): they request the two
// mutexes in OPPOSITE orders. Locking them one at a time could deadlock; scoped_lock
// acquires both with a deadlock-avoidance algorithm (all-or-nothing).
void transfer(Account& from, Account& to, int amount) {
    std::scoped_lock lock(from.m, to.m);   // C++17
    from.balance -= amount;
    to.balance += amount;
}

int main() {
    std::cout << "Producer/consumer:\n";
    std::thread c(consumer), p(producer);
    p.join();
    c.join();

    std::cout << "Opposite-order transfers with scoped_lock:\n";
    Account x, y;
    std::thread t1([&] { for (int i = 0; i < 100'000; ++i) transfer(x, y, 1); });
    std::thread t2([&] { for (int i = 0; i < 100'000; ++i) transfer(y, x, 1); });
    t1.join();
    t2.join();
    std::cout << "  x = " << x.balance << ", y = " << y.balance << " (total still 200, no deadlock)\n";
}
