#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <cstdio>
using namespace std;

struct Proc { string id; int at, bt, tat = 0, wt = 0; bool done = false; };

int main() {
    vector<Proc> p = {{"P1", 0, 6}, {"P2", 1, 8}, {"P3", 2, 2}};
    int n = p.size(), time = 0, completed = 0;
    vector<int> order;

    while (completed < n) {
        int idx = -1, best = INT_MAX;
        for (int i = 0; i < n; i++)
            if (!p[i].done && p[i].at <= time && p[i].bt < best) { best = p[i].bt; idx = i; }
        if (idx == -1) { time++; continue; }

        time += p[idx].bt;
        p[idx].tat = time - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = true;
        order.push_back(idx);
        completed++;
    }

    cout << "Execution Order : ";
    for (size_t i = 0; i < order.size(); i++)
        cout << p[order[i]].id << (i + 1 < order.size() ? " -> " : "\n");

    printf("PID | Burst | Wait Time | Turnaround Time\n");
    double total = 0;
    for (int i : order) {
        printf("%-3s | %-5d | %-9d | %d\n", p[i].id.c_str(), p[i].bt, p[i].wt, p[i].tat);
        total += p[i].wt;
    }
    printf("Average Waiting Time : %.2f ms\n", total / n);
    return 0;
}
