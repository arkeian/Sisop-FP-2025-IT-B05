#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define MSGBUFFER 1024

int main() {
    int fd[2];
    char buffer[MSGBUFFER];

    if (pipe(fd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    switch(fork()) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            close(fd[1]);
            
            ssize_t readRes = read(fd[0], buffer, MSGBUFFER);
            if (readRes <= 0) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            else {
                printf("child: Proses anak (PID: %d) menerima pesan.\n", getpid());
            }

            buffer[readRes] = '\0';

            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] >= 'a' && buffer[i] <= 'z') {
                    buffer[i] -= 32;
                }
            }

            printf("child: Pesan yang sudah diubah: %s\n", buffer);
            exit(EXIT_SUCCESS);
        default:
            close(fd[0]);

            printf("parent: Masukkan pesan yang ingin dikirim: ");
            if (fgets(buffer, MSGBUFFER, stdin) == NULL) {
                perror("fgets");
                exit(EXIT_FAILURE);
            }

            buffer[strcspn(buffer, "\n")] = '\0';

            size_t len = strlen(buffer);

            ssize_t writeRes = write(fd[1], buffer, len);
            if (writeRes <= 0) {
                perror("write");
                exit(EXIT_FAILURE);
            }
            else {
                printf("parent: Proses induk (PID: %d) mengirim pesan.\n", getpid());
            }

            close(fd[1]);

            wait(NULL);

            break;
    }

    return 0;
}