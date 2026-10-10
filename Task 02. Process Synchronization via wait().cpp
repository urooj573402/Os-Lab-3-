#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main() {
    pid_t pid = fork();
    if (pid < 0) { cerr << "fork failed" << endl; return 1; }
    if (pid == 0) {
        cout << "Child executing task ..." << endl;
        sleep(2);
        cout << "Child exiting with code 42" << endl;
        exit(42);
    } else {
        cout << "Parent waiting for child ..." << endl;
        int status = 0;
        wait(&status);
        if (WIFEXITED(status))
            cout << "Parent : Child terminated with exit status "
                 << WEXITSTATUS(status) << endl;
    }
    return 0;
}
