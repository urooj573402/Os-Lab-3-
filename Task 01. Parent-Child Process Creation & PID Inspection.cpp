#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Process creation failed" << endl;
        return 1;
    } else if (pid == 0) {
        cout << "Child Process : PID = " << getpid()
             << " , Parent PID = " << getppid() << endl;
    } else {
        cout << "Parent Process : PID = " << getpid()
             << " , Created Child PID = " << pid << endl;
        wait(NULL);
    }
    return 0;
}
