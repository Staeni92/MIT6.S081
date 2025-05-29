#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RD 0 // pipe的读端
#define WR 1 // pipe的写端

int main(int argc, char *argv[]) {
    int p2c[2];
    int c2p[2];
    pipe(p2c);
    pipe(c2p);
    char buf = 'H';

    int pid = fork();
    if (pid < 0) {
        printf("fock() error!\n");
        close(p2c[RD]);
        close(p2c[WR]);
        close(c2p[RD]);
        close(c2p[WR]);
        exit(1);
    } else if (pid == 0) { // 子进程
        close(p2c[WR]);
        close(c2p[RD]);

        if (read(p2c[RD], &buf, sizeof(char)) != sizeof(char)) {
            printf("child process read() error!\n");
            exit(1);
        } else {
            printf("%d: received ping\n", getpid());
        }

        if (write(c2p[WR], &buf, sizeof(char)) != sizeof(char)) {
            printf("child process write() error!\n");
            exit(1);
        }

        close(c2p[WR]);
        close(p2c[RD]);
        exit(0);
    } else { // 父进程
        close(c2p[WR]);
        close(p2c[RD]);

        if (write(p2c[WR], &buf, sizeof(char)) != sizeof(char)) {
            printf("prarent process write() error!\n");
            exit(1);
        }

        if (read(c2p[RD], &buf, sizeof(char)) != sizeof(char)) {
            printf("parent process read() error!\n");
            exit(1);
        } else {
            printf("%d: received pong\n", getpid());
        }

        close(p2c[WR]);
        close(c2p[RD]);
        exit(0);
    }
}
