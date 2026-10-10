#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

struct Proc { string id; int at, bt, rem, ct = 0, tat = 0, wt = 0; bool queued = false; };

int main() {
    int quantum = 2;
    vector<Proc> p = {{"P1", 0, 3, 3}, {"P2", 0, 2, 2}, {"P3", 0, 4, 4}};
    int n = p.size(), time = 0, completed = 0;
    queue<int> q;

    auto admit = [&]() {
        for (int i = 0; i < n; i++)
            if (!p[i].queued && p[i].at <= time) { q.push(i); p[i].queued = true; }
    };

    cout << "Quantum = " << quantum << endl << "Execution : ";
    admit();
    bool first = true;
    while (completed < n) {
        if (q.empty()) {
            time++;
            admit();
            continue;
        }
        int i = q.front(); q.pop();
        int slice = min(quantum, p[i].rem);
        if (!first) cout << " -> ";
        first = false;
        cout << p[i].id << " (" << slice << " ms)";
        p[i].rem -= slice;
        time += slice;
        admit();
        if (p[i].rem > 0) q.push(i);
        else {
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            completed++;
        }
    }
    cout << endl;

    printf("PID | Turnaround | Wait\n");
    for (auto& x : p) printf("%-3s | %-10d | %d\n", x.id.c_str(), x.tat, x.wt);
    return 0;
}
