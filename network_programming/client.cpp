#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 9999
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == -1){
        std::cout << "Create client socket error.\n";
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    server_addr.sin_port = htons(SERVER_PORT);
    if(connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        std::cout << "Connect to server error.\n";
        return -1;
    }else{
        std::cout << "Connect to server success.\n";
    }

    std::cout << "Send something to the server: ";
    char send_buf[BUFFER_SIZE] = {0};
    std::cin >> send_buf;
    int ret = send(clientfd, send_buf, sizeof(send_buf), 0);
    if(ret != sizeof(send_buf)){
        std::cout << "Send message error.\n";
        return -1;
    }

    char recv_buf[BUFFER_SIZE] = {0};
    ret = recv(clientfd, recv_buf, sizeof(recv_buf), 0);
    if(ret > 0){
        std::cout << "Recive message from server: " << recv_buf << std::endl;
    }else{
        std::cout << "Recive data error.\n";
        close(clientfd);
        return -1;
    }

    close(clientfd);

    return 0;


}