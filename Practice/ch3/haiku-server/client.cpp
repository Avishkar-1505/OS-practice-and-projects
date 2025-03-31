#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(){
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5575);
    serverAddress.sin_addr.s_addr = INADDR_ANY;


    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));


    char buff[1024] = {0};

    recv(clientSocket, buff, sizeof(buff), 0);

    std::cout<<"Message From Server:\n"<<buff<<'\n';

    close(clientSocket);

    return 0;

}