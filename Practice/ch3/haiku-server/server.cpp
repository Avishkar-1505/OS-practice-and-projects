#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5575);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    const char *haiku = "An old silent pond\nA frog jumps into the pond—-\nSplash! Silence again.\n";


    while(1){

        listen(serverSocket, 3);

        int clientSocket = accept(serverSocket, nullptr, nullptr);

        send(clientSocket, haiku, strlen(haiku), 0);

        close(serverSocket);

    }

    return 0;

}