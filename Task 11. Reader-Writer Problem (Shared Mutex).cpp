#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <chrono>
#include <vector>
using namespace std;

int shared_data = 0;
shared_mutex rw_lock;
mutex cout_mtx;

void reader(int id) {
    shared_lock<shared_mutex> lock(rw_lock);
    lock_guard<mutex> g(cout_mtx);
    cout << "Reader " << id << " read value : " << shared_data << endl;
}

void writer(int id, int val) {
    unique_lock<shared_mutex> lock(rw_lock);
    shared_data = val;
    lock_guard<mutex> g(cout_mtx);
    cout << "Writer " << id << " updated value to : " << shared_data << endl;
}

int main() {
    vector<thread> t;
    auto gap = [] { this_thread::sleep_for(chrono::milliseconds(100)); };

    t.emplace_back(writer, 1, 42); gap();
    t.emplace_back(reader, 1);     gap();
    t.emplace_back(reader, 2);     gap();
    t.emplace_back(writer, 2, 99); gap();
    t.emplace_back(reader, 3);

    for (auto& th : t) th.join();
    return 0;
}
