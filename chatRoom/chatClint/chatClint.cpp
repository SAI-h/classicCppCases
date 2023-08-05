#include "chatClint.h"
#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include <pthread.h>
#include <iostream>
#include <string>

ChatClint::ChatClint(const char* netAddr, const char* port, const std::string UsrName):NetUnity(), UsrName(UsrName) {
    memset(&serv_addr, 0, sizeof serv_addr);
    serv_addr.sin_family = AF_INET;                     // 地址族:互联网协议ipv4地址
    serv_addr.sin_addr.s_addr = inet_addr(netAddr);     // 将获取到的字符串形式的ip地址转换为可用于网络通信的地址
    serv_addr.sin_port = htons(atoi(port));             // 将端口号转换为可用于网络通信的短整型量
}

// 和服务器建立连接
bool ChatClint::connectServer() {
    return connect(sockID, (sockaddr*)&serv_addr, sizeof serv_addr) != -1;
}

// 接收来自于服务器端的数据
int ChatClint::recvData(int targetSockID) {
    int getLen = recv(targetSockID, msg, BUF_SIZE - 1, 0);
    fputs("\33[2K\r", stdout);          // 清空当前行
    fputs(msg, stdout);                 // 将当前行的数据置为由服务器端发送过来的数据
    fputc('\n', stdout);
    if(!strcmp("Bye~", msg)) return -1; // 退出通信
    char dest[6];
    strncpy(dest, msg, 5);
    dest[5] = '\0';
    if(!strcmp(dest, "[Usr]")) {        // 该信息是服务器转发其他用户的信息
        fputs("[Self]", stdout);        // 重载自己的输入框
        fputs(UsrName.c_str(), stdout);
        fputs(": ", stdout);
        fflush(stdout);                 // 使得待打印输出的内容呈现在屏幕上
    }
    return getLen;
}

// 将数据发送至服务器端
int ChatClint::sendData(int targetSockID) {
    fputs("[Self]", stdout);            // 显示输入框
    fputs(UsrName.c_str(), stdout);
    fputs(": ", stdout);
    fflush(stdout);
    fgets(msg, BUF_SIZE - 1, stdin);
    int end = strlen(msg);
    msg[end - 1] = '\0';
    if(!strcmp(msg, "quit()")) {        // 退出通信
        send(targetSockID, msg, end, 0);
        return -1;
    }
    else {                              // 正常发送带有自己身份标识的信息数据
        char sendMsg[BUF_SIZE + strlen(UsrName.c_str()) + 2];
        std::string usr = "[Usr]" + UsrName + ": ";
        strcpy(sendMsg, usr.c_str());
        strcat(sendMsg, msg);
        send(targetSockID, sendMsg, strlen(sendMsg) + 1, 0);
        return strlen(sendMsg) + 1;
    }
}

// 创建读写线程
void ChatClint::threadMaking() {
    argList arg = {this, sockID};
    pthread_create(&recvThread, NULL, handleRecv, (void*)&arg);
    pthread_create(&sendThread, NULL, handleSend, (void*)&arg);
    pthread_join(recvThread, NULL);
    pthread_join(sendThread, NULL);
}

// 处理读线程
void* ChatClint::handleRecv(void* arg) {
    ChatClint* ptr = ((argList*)arg)->ptr;
    int sock = ((argList*)arg)->sock;
    while(ptr->recvData(sock) != -1);
    return NULL;
}

// 处理写线程
void* ChatClint::handleSend(void* arg) {
    ChatClint* ptr = ((argList*)arg)->ptr;
    int sock = ((argList*)arg)->sock;
    while(ptr->sendData(sock) != -1);
    return NULL;
}