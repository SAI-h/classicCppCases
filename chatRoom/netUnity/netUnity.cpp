#include "netUnity.h"
#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <string.h>

NetUnity::NetUnity() {
    msg[0] = '\0';
    sockID = socket(AF_INET, SOCK_STREAM, 0);
}

NetUnity::~NetUnity() {
    close(sockID);
}

int NetUnity::getSocketID() const{
    return sockID;
}

int NetUnity::recvData(int targetSockID) {
    printf("RecvData method from base class.\n");
    int getLen = recv(targetSockID, msg, BUF_SIZE - 1, 0);
    fputs(msg, stdout);
    return getLen;
}

int NetUnity::sendData(int targetSockID) {
    printf("SendData method from base class.\n");
    fgets(msg, BUF_SIZE - 1, stdin);
    send(targetSockID, msg, strlen(msg), 0);
    return strlen(msg);
}