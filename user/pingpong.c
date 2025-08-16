#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RD 0
#define WR 1

int main(int argc, char const *argv[]) {
    char buf = 'P';

    int c2p[2];
    int p2c[2];
    pipe(c2p);
    pipe(p2c);

    int pid = fork();
    if (pid < 0) {
        fprintf(2, "fork failed\n");
        exit(1);
    } else if (pid > 0) {
        close(c2p[WR]);
        close(p2c[RD]);
        if (write(p2c[WR], &buf, sizeof(char)) != sizeof(char)) {
            printf("parent write() error\n");
            exit(1);
        }
        if (read(c2p[RD], &buf, sizeof(char)) != sizeof(char)) {
            printf("parent read() error\n");
            exit(1);
        } else {
            printf("%d: received pong\n", getpid());
        }
        
        close(p2c[WR]);
        close(c2p[RD]);
    } else {
        close(p2c[WR]);
        close(c2p[RD]);
        if (read(p2c[RD], &buf, sizeof(char)) != sizeof(char)) {
            printf("child read() error\n");
            exit(1);
        } else {
            printf("%d: received ping\n", getpid());
        }

        if (write(c2p[WR], &buf, sizeof(char)) != sizeof(char)) {
            printf("child write() error\n");
            exit(1);
        }
        close(c2p[WR]);
        close(p2c[RD]);
    }
    exit(0);
}
