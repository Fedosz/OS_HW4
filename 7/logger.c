#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>

const char status_OK = 1;
const char status_FINISH = 0;

int fd;

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    
    if (res == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Inet_aton(const char *src, void *dst) {
    int res = inet_aton(src, dst);

    if (res == 0) {
        printf("inet_aton failed");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror("inet_aton failed");
        exit(EXIT_FAILURE);
    }
}

void readChecker(int nread) {
    if (nread == -1) {
        perror("read failed\n");
        exit(EXIT_FAILURE);
    }

    if (nread == 0) {
        printf("END OF FILE occured\n");
    }
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);

    if (n < 0 || n > 20) {
        printf("n must be in range [0; 20]!\n");
        exit(-1);
    }
    
    fd = Socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);

    Inet_aton("127.0.0.1", &addr.sin_addr);

    int nread;
    pid_t server_pid, client_pid, logger_pid = getpid();
    while (1) {
        socklen_t addr_len = sizeof(addr);

        nread = recvfrom(fd, &server_pid, sizeof(server_pid), 0, (struct sockaddr *) &addr, &addr_len);
        readChecker(nread);
        printf("logger MSG(%d): server_ID - %d\n", logger_pid, server_pid);
        
        nread = recvfrom(fd, &client_pid, sizeof(client_pid), 0, (struct sockaddr *) &addr, &addr_len);
        readChecker(nread);
        printf("logger MSG(%d): client_ID - %d\n\n", logger_pid, client_pid);
    }

    close(fd);

    return 0;
}
