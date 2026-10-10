#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

int main() {
    pid_t pid = fork();
    if (pid < 0) { cerr << "fork failed" << endl; return 1; }
    if (pid == 0) {
        cout << "Child PID : " << getpid() << " terminating now" << endl;
        exit(0);
    } else {
        cout << "Parent sleeping for 10 s without wait(). Inspect via 'ps -l'" << endl;
        sleep(2);

        char cmd[128];
        snprintf(cmd, sizeof(cmd), "ps -o pid,ppid,stat,comm -p %d", pid);
        system(cmd);
        sleep(8);
        wait(NULL);
        cout << "Parent cleaned up child. Exiting." << endl;
    }
    return 0;
}
