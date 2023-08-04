#include "chatServer.h"
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fstream>
#include <iostream>
#include <string.h>

// 输出报错信息
void error_handling(char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) { 
    char port[5] = "";
    if(argc == 1) { // 开启默认端口号
        std::ifstream fin;
        fin.open("server_config.dat", std::ios::in);
        std::string IPstr, IP, PORTstr, PORT;
        fin >> IPstr >> IP >> PORTstr >> PORT;
        strcpy(port, PORT.c_str());
        fin.close();
    }
    else {
        printf("Usage-Enable default port: %s\n", argv[0]);
        return 0;
    }
    ChatServer server(port);
    if(!server.SockBindToAddr()) error_handling((char*)"sock() error");
    if(!server.setListening()) error_handling((char*)"listen() error");
    fputs("Server is running...\n", stdout);
    while(true) {
        int cln_sock = server.acceptDataSwap();
        printf("User[%d] connected...\n", cln_sock);
        server.addClnSock(cln_sock);
        server.threadMaking(cln_sock);
    }
    return 0;
}