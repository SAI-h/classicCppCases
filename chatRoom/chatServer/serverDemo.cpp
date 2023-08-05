#include "chatServer.h"
#include "../tool/tool.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <fstream>
#include <cstring>

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
    // 完成套接字的创建
    ChatServer server(port);
    // tcp应用,将套接字和网络地址进行绑定
    if(!server.SockBindToAddr()) error_handling((char*)"sock() error");
    // 服务器端设置监听(来自客户端的数据请求)
    if(!server.setListening()) error_handling((char*)"listen() error");
    fputs("Server is running...\n", stdout);
    while(true) {
        // 产生了新的客户端请求
        int cln_sock = server.acceptDataSwap();
        printf("User[%d] connected...\n", cln_sock);
        // 将产生的客户端(套接字)存入自己的客户端服务队列
        server.addClnSock(cln_sock);
        // 创建新的线程为该客户服务
        server.threadMaking(cln_sock);
    }
    return 0;
}