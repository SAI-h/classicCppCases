#include "chatClint.h"
#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include <pthread.h>
#include <iostream>
#include <string>

ChatClint::ChatClint(const char* netAddr, const char* port, const std::string UsrName):NetUnity(), UsrName(UsrName) {
    memset(&serv_addr, 0, sizeof serv_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(netAddr);
    serv_addr.sin_port = htons(atoi(port));
    status = START;
}

bool ChatClint::connectServer() {
    return connect(sockID, (sockaddr*)&serv_addr, sizeof serv_addr) != -1;
}

int ChatClint::recvData(int targetSockID) {
    int getLen = recv(targetSockID, msg, BUF_SIZE - 1, 0);
    fputs("\33[2K\r", stdout);
    fputs(msg, stdout);
    fputc('\n', stdout);
    if(!strcmp("Bye~", msg)) return -1;
    char dest[6];
    strncpy(dest, msg, 5);
    dest[5] = '\0';
    if(!strcmp(dest, "[Usr]")) {
        fputs(">> ", stdout);
        fflush(stdout);
    }
    return getLen;
}

int ChatClint::sendData(int targetSockID) {
    fputs(">> ", stdout);
    fflush(stdout);
    fgets(msg, BUF_SIZE - 1, stdin);
    int end = strlen(msg);
    msg[end - 1] = '\0';
    if(!strcmp(msg, "quit()")) {
        send(targetSockID, msg, end, 0);
        return -1;
    }
    else {
        char sendMsg[BUF_SIZE + strlen(UsrName.c_str()) + 2];
        std::string usr = "[Usr]" + UsrName + ": ";
        strcpy(sendMsg, usr.c_str());
        strcat(sendMsg, msg);
        send(targetSockID, sendMsg, strlen(sendMsg) + 1, 0);
        return strlen(sendMsg) + 1;
    }
}

void ChatClint::threadMaking() {
    argList arg = {this, sockID};
    pthread_create(&recvThread, NULL, handleRecv, (void*)&arg);
    pthread_create(&sendThread, NULL, handleSend, (void*)&arg);
    pthread_join(recvThread, NULL);
    pthread_join(sendThread, NULL);
}

void* ChatClint::handleRecv(void* arg) {
    ChatClint* ptr = ((argList*)arg)->ptr;
    int sock = ((argList*)arg)->sock;
    while(ptr->recvData(sock) != -1);
    return NULL;
}

void* ChatClint::handleSend(void* arg) {
    ChatClint* ptr = ((argList*)arg)->ptr;
    int sock = ((argList*)arg)->sock;
    while(ptr->sendData(sock) != -1);
    return NULL;
}