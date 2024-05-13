#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <errno.h>

#define INVALID_FD  -1

int main(int argc, char* argv[]){
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == INVALID_FD){
        std::cout << "Create Scoket Error.\n";
        return -1;
    }

    int oldSocketFlag = fcntl(listenfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK; 
    if(fcntl(listenfd, F_SETFL, newSocketFlag) == -1){
        close(listenfd);
        std::cout << "Set Listen Socket To Nonblock Mode Error.\nClose Listen Socket.\n";
        return -2;
    }

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, (char*)&on, sizeof(on));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9999);
    if(bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        close(listenfd);
        std::cout << "Bind Listen Socket Error.\nClose Listen Scoket.\n";
        return -3;
    }

    if(listen(listenfd, SOMAXCONN) == -1){
        close(listenfd);
        std::cout << "Listen Socket Error.\nClose Listen Socket.\n";
        return -4;
    }

    std::vector<pollfd> fds;
    pollfd listen_fd_info;
    listen_fd_info.fd = listenfd;
    listen_fd_info.events = POLLIN;
    listen_fd_info.revents = 0;
    fds.push_back(listen_fd_info);

    bool exist_invalid_fd;
    int n;
    while(true){
        exist_invalid_fd = false;
        n = poll(&fds[0], fds.size(), 1000);
        if(n < 0){
            if(errno == EINTR){
                continue;
            }
            break;
        }else if(n == 0){
            continue;
        }

        for(size_t i = 0; i < fds.size(); ++i){
            if(fds[i].revents & POLLIN){
                if(fds[i].fd == listenfd){
                    struct sockaddr_in clientaddr;
                    socklen_t clientaddrlen = sizeof(clientaddr);
                    int clientfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientaddrlen);
                    if(clientfd != -1){
                        int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
                        int newSocketFlag = oldSocketFlag | O_NONBLOCK;
                        if(fcntl(clientfd, F_SETFL, newSocketFlag) == -1){
                            close(clientfd);
                            std::cout << "Set Client Socket To Nonblock Mode Error.\nClose Client Socket.\n";
                        }else{
                            struct pollfd client_fd_info;
                            client_fd_info.fd = clientfd;
                            client_fd_info.events = POLLIN;
                            client_fd_info.revents = 0;
                            fds.push_back(client_fd_info);
                            std::cout << "New Client Accepted, Clientfd: " << clientfd << std::endl;
                        }
                    }else{
                        char buf[64] = {0};
                        int m = recv(fds[i].fd, buf, 64, 0);
                        if(m < 0){
                            if(errno != EINTR && errno != EWOULDBLOCK){
                                for(std::vector<pollfd>::iterator iter = fds.begin(); iter != fds.end(); ++iter){
                                    if(iter->fd == fds[i].fd){
                                        std::cout << "Client Disconnected, Clientfd: " << fds[i].fd << std::endl;
                                        close(fds[i].fd);
                                        std::cout << "Close Client Socket.\n";
                                        iter->fd = INVALID_FD;
                                        exist_invalid_fd = true;
                                        break;
                                    }
                                }
                            }
                        }else{
                            std::cout << "Recive From Client: " << buf << ", Clientfd: " << fds[i].fd << std::endl;
                        }
                    }
                }
            }else if(fds[i].revents & POLLERR){

            }
        }
    }

    for(std::vector<pollfd>::iterator iter = fds.begin(); iter != fds.end(); ++iter){
        close(iter->fd);
    }

    return 0;
}