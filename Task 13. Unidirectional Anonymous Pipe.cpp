#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
using namespace std;

int main() {
    int fd[2];
    if (pipe(fd) == -1) { cerr << "pipe failed" << endl; return 1; }

    pid_t pid = fork();
    if (pid < 0) { cerr << "fork failed" << endl; return 1; }

    if (pid == 0) {
        close(fd[1]);
        char buffer[100];
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n < 0) n = 0;
        buffer[n] = '\0';
        cout << "Child read from pipe : " << buffer << endl;
        close(fd[0]);
    } else {
        close(fd[0]);
        const char* msg = "Hello Child from Kernel Pipe";
        write(fd[1], msg, strlen(msg));
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}
