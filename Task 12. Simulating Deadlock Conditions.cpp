#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstring>
using namespace std;

mutex mutexA, mutexB;
bool fixed_order = false;

void thread1_work() {
    mutexA.lock();
    cout << "Thread 1 acquired Lock A, waiting for Lock B ..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    mutexB.lock();
    mutexB.unlock();
    mutexA.unlock();
}

void thread2_work() {
    if (fixed_order) {
        mutexA.lock();
        cout << "Thread 2 acquired Lock A, waiting for Lock B ..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        mutexB.lock();
        mutexB.unlock();
        mutexA.unlock();
    } else {
        mutexB.lock();
        cout << "Thread 2 acquired Lock B, waiting for Lock A ..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        mutexA.lock();
        mutexA.unlock();
        mutexB.unlock();
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "fix") == 0) fixed_order = true;
    thread t1(thread1_work);
    thread t2(thread2_work);
    t1.join();
    t2.join();
    cout << "Finished without deadlock" << endl;
    return 0;
}
