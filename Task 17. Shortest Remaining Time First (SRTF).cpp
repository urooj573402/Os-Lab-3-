#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <cstdio>
using namespace std;

struct Proc { string id; int at, bt, rem, ct = 0, tat = 0, wt = 0; };

int main() {
    vector<Proc> p = {{"P1", 0, 6, 6}, {"P2", 1, 4, 4}, {"P3", 3, 2, 2}};
    int n = p.size(), time = 0, completed = 0, last = -1;
    int segStart = 0;
    vector<string> timeline;

    while (completed < n) {
        int idx = -1, best = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rem > 0) {

                if (p[i].rem < best || (p[i].rem == best && i == last)) { best = p[i].rem; idx = i; }
            }
        }
        if (idx == -1) { time++; continue; }

        if (idx != last) {
            if (last != -1 && time > segStart)
                timeline.push_back("[" + p[last].id + ": " + to_string(segStart) + "-" + to_string(time) + "]");
            segStart = time;
            last = idx;
        }
        p[idx].rem--;
        time++;
        if (p[idx].rem == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }
    timeline.push_back("[" + p[last].id + ": " + to_string(segStart) + "-" + to_string(time) + "]");

    cout << "Timeline : ";
    for (auto& s : timeline) cout << s << " ";
    cout << endl;

    printf("PID | Completion | Waiting Time\n");
    for (auto& x : p) printf("%-3s | %-10d | %d\n", x.id.c_str(), x.ct, x.wt);
    return 0;
}
