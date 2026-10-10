#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

long counter = 0;
mutex mtx;

void safe_increment() {
    for (int i = 0; i < 100000; i++) {
        mtx.lock();
        counter = counter + 1;
        mtx.unlock();
    }
}

int main() {
    thread t1(safe_increment);
    thread t2(safe_increment);
    t1.join();
    t2.join();
    cout << "Final counter with Mutex : " << counter << endl;
    return 0;
}
