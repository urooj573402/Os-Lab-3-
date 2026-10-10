#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>
using namespace std;

int main() {
    int shm_fd = shm_open("/shm_os_lab", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) { perror("shm_open"); return 1; }
    ftruncate(shm_fd, 1024);
    char* ptr = (char*)mmap(0, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) { perror("mmap"); return 1; }

    pid_t pid = fork();
    if (pid < 0) { cerr << "fork failed" << endl; return 1; }

    if (pid == 0) {
        sleep(1);
        cout << "Child read from SHM : " << ptr << endl;
    } else {
        strcpy(ptr, "OS Shared Memory Payload");
        wait(NULL);
        munmap(ptr, 1024);
        shm_unlink("/shm_os_lab");
    }
    return 0;
}
