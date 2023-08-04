#include "chatServer.h"
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

ChatServer::ChatServer(char* port): NetUnity() {
    clnSockArr.clear();
    pthread_mutex_init(&mutex, NULL);
    memset(&addr, 0, sizeof addr);
    addr.sin_family = PF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(port));
}

bool ChatServer::SockBindToAddr() {
    return bind(sockID, (sockaddr*)&addr, sizeof addr) != -1;
}

bool ChatServer::setListening() {
    return listen(sockID, WAITING) != -1;
}

int ChatServer::acceptDataSwap() {
    sockaddr_in clnt_addr;
    socklen_t clnt_addr_sz = sizeof clnt_addr;
    return accept(sockID, (sockaddr*)&clnt_addr, &clnt_addr_sz);
}

int ChatServer::recvData(int targetSockID) {
    return recv(targetSockID, msg, BUF_SIZE - 1, 0);
}

int ChatServer::sendData(int sendingSource) {
    if(!strcmp("quit()", msg)) {
        send(sendingSource, "Bye~", strlen("Bye~") + 1, 0);
        return -1;
    }
    printf("Usr[%d] is sending...\n", sendingSource);
    // clnSockArr是临界资源,应当互斥访问
    lock();
    for(auto cln_sock: clnSockArr)
        if(cln_sock != sendingSource) {
            send(cln_sock, msg, strlen(msg) + 1, 0);
        }
    unlock();
    return strlen(msg) + 1;
}

void ChatServer::lock() {
    pthread_mutex_lock(&mutex);
}

void ChatServer::unlock() {
    pthread_mutex_unlock(&mutex);
}

void ChatServer::addClnSock(const int& cln_sock) {
    lock();
    clnSockArr.push_back(cln_sock);
    unlock();
}

void ChatServer::threadMaking(const int& cln_sock) {
    argList arg = {this, cln_sock};
    pthread_create(&pid, NULL, handleCln, (void*)&arg);
    pthread_detach(pid);
}

void* ChatServer::handleCln(void* arg) {
    ChatServer* ptr = ((argList*)arg)->ptr;
    int cln_sock = ((argList*)arg)->cln_sock;
    char msg[BUF_SIZE];
    sprintf(msg, "Hello User[%d], welcome to our chatroom!\n", cln_sock);
    send(cln_sock, msg, strlen(msg) + 1, 0);
    while(ptr->recvData(cln_sock)) {
        ptr->sendData(cln_sock);
    }
    ptr->rmClnSock(cln_sock);
    return NULL;
}

void ChatServer::rmClnSock(const int& cln_sock) {
    lock();
    for(int i = 0; i < clnSockArr.size(); i ++)
        if(cln_sock == clnSockArr[i]) {
            int j = i;
            while(j < clnSockArr.size() - 1) {
                clnSockArr[j] = clnSockArr[j + 1];
                j ++;
            }
            clnSockArr.pop_back();
            break;
        }
    unlock();
    close(cln_sock);
}