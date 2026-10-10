#include <iostream>
#include <thread>
using namespace std;

long counter = 0;

void increment_task() {
    for (int i = 0; i < 1000000; i++) {
        long tmp = counter;
        if (i % 1000 == 0) this_thread::yield();
        counter = tmp + 1;
    }
}

int main() {
    thread t1(increment_task);
    thread t2(increment_task);
    t1.join();
    t2.join();
    cout << "Expected : 2000000 | Actual counter : " << counter << endl;
    return 0;
}
