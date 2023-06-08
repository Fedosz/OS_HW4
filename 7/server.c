#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    
    if (res == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);

    if (res == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);
    int serverfd = Socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serv, client;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = INADDR_ANY;

    Bind(serverfd,(struct sockaddr *) &serv, sizeof(serv));

    socklen_t addrlen = sizeof(client);

    char data[5];
    data[0] = 0; // honey / 10
    data[1] = 0; // honey % 10
    data[2] = n; // bees in hive
    data[3] = 0; // bites
    data[4] = 1;

    int flag = n + 1;

    while (flag != 0) {
        
        char buf[2];
        recvfrom(serverfd, buf, 2, 0, (struct sockaddr *) &client, &addrlen);

        printf("msg accepted\n");

        if (buf[0] == 1) { //is Vinni
            if (buf[1] == 2) { //3 bites
                data[4] = 0;
            } else {
                printf("Vinni arrived\n");
                int honey = data[0] * 10 + data[1];

                printf("%d honey in the hive\n", honey);

                char answer[2];

                answer[0] = 1;
                answer[1] = 2;

                if (honey >= 15) {
                    answer[0] = 2; // enough honey
                    if (data[2] < 3) {
                        answer[1] = 2;
                    }
                } 

                sendto(serverfd, answer, 2, 0, (struct sockaddr *) &client, addrlen);
            }
        } else { // is Bee
            if (buf[1] == 2) { //arrives
                printf("Bee arrives with the honey\n");
                data[2]++;
                int honey = data[0] * 10 + data[1];
                honey++;
                data[0] = honey / 10;
                data[1] = honey % 10;
                char answer[2];
                answer[0] = 1;
                answer[1] = 1;
                sendto(serverfd, answer, 2, 0, (struct sockaddr *) &client, addrlen);
            } else { //wants to fly for honey

                printf("Bee wants to fly away\n");
                char answer[2];
                answer[0] = 1;
                answer[1] = 1;

                if (data[2] > 1 && data[0] * 10 + data[1] + n - data[2] < 30) {
                    answer[0] = 2; //can fly
                    data[2]--;
                }

                if (data[4] = 0) {
                    answer[1] = 2;
                }

                sendto(serverfd, answer, 2, 0, (struct sockaddr *) &client, addrlen); // answer if bee can fly away
            }
        }

        if (data[4] = 0) {
            flag--;
        }

    }

    close(serverfd);

    printf("Hive is going to sleep");

    return 0;
} 
