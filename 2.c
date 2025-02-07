#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PI 3.14159265358979323846

double teylor(int k, double x) {
    return pow(-1, k) * pow(x, 2*k+1) / tgamma(2*k+2);
}

int main() {
    int K, N, n;
    scanf("%d %d %d", &K, &N, &n);

    FILE *file = fopen("file.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }
    
    for (int i = 0; i < K; i++) {
        double x = 2 * PI * i / N;
        double sum = 0.0;
        int fd[2];
        pipe(fd);

        for (int k = 0; k < n; k++) {
            pid_t pid = fork();
            if (pid == 0) {
                close(fd[0]);
                double term = teylor(k, x);
                printf("Process %d computed term[%d] = %.10f\n", getpid(), k, term);
                write(fd[1], &term, sizeof(double));
                close(fd[1]);
                exit(0);
            }
        }
        
        close(fd[1]);
        for (int k = 0; k < n; k++) {
            double term;
            read(fd[0], &term, sizeof(double));
            sum += term;
            wait(NULL);
        }
        close(fd[0]);

        printf("y[%d] = %.10f\n", i, sum);
        fprintf(file, "y[%d] = %.10f\n", i, sum);
    }
    
    fclose(file);
    return 0;
}
