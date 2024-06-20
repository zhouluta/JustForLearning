#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

int main(){
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        std::cout << "Create listen socket error." << std::endl;
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9999);
    if(bind(listenfd, (struct sockaddr *)&addr, sizeof(addr)) == -1){
        std::cout << "Bind listen socket error." << std::endl;
        return -1;
    }

    if(listen(listenfd, SOMAXCONN) == -1){
        std::cout << "Listen error." << std::endl;
        return -1;
    }

    while(true){
        struct  sockaddr_in addr_client;
        socklen_t socket_client_len = sizeof(addr_client);
        int clientfd = accept(listenfd, (struct sockaddr*)&addr_client, &socket_client_len);
        if(clientfd != -1){
            char buf_recv[1024] = {0};
            char buf_send[1024] = {0};
            int ret = recv(clientfd, buf_recv, 1024, 0);
            if(ret > 0){
                std::cout << "Recive data from client: " << buf_recv << std::endl;
                std::cout << "Send something to client: \n"; 
                std::cin >> buf_send;
                ret = send(clientfd, buf_send, strlen(buf_send), 0);
                if(ret != strlen(buf_send)){
                    std::cout << "Send error." << std::endl;
                    return -1;
                }
            }else{
                std::cout << "Recive error." << std::endl;
                return -1;
            }
        }
        close(clientfd);
    }
    close(listenfd);

    return 0;
}