#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

struct Proc { string id; int at, bt, ct = 0, tat = 0, wt = 0; };

int main() {
    vector<Proc> p = {{"P1", 0, 5}, {"P2", 1, 3}, {"P3", 2, 8}};
    sort(p.begin(), p.end(), [](const Proc& a, const Proc& b) { return a.at < b.at; });

    int time = 0;
    for (auto& x : p) {
        if (time < x.at) time = x.at;
        x.ct = time + x.bt;
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
        time = x.ct;
    }

    printf("PID | Arrival | Burst | Completion | Turnaround | Wait\n");
    double total = 0;
    for (auto& x : p) {
        printf("%-3s | %-7d | %-5d | %-10d | %-10d | %d\n", x.id.c_str(), x.at, x.bt, x.ct, x.tat, x.wt);
        total += x.wt;
    }
    printf("Average Waiting Time : %.2f ms\n", total / p.size());
    return 0;
}
