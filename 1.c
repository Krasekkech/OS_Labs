#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void get_pid(pid_t pid, int num) {
    int hours, minutes, seconds;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    long mili = start.tv_nsec / 100000;

    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;

    if (pid == 0) {
        printf("Child%d process, his pid=%d time: %d:%d:%d:%ld\n", num, getpid(), hours, minutes, seconds, mili);
        printf("Child%d parent process, his pid=%d time: %d:%d:%d:%ld\n", num, getppid(), hours, minutes, seconds, mili);
    } else if (pid > 0)
        printf("Parent process, his pid=%d time: %d:%d:%d:%ld\n", getpid(), hours, minutes, seconds, mili);
    else {
        printf("Fork failed\n");
        return;
    }

}

int main() {
    pid_t pid_1;
    pid_t pid_2;

    pid_1 = fork();
    get_pid(pid_1,1);
    if (pid_1 > 0) {
        pid_2 = fork();
        get_pid(pid_2,2);
        if (pid_2 > 0) {
            system("ps -x | grep '1.exe'");
        }
    }

    return 0;
}
