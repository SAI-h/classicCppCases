#include "chatClint.h"
#include "../tool/tool.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <ctime>
#include <iostream>
#include <unordered_map>

int main(int argc, char* argv[]) {
    if(argc == 3 && !strcmp(argv[1], "signIn")) {   // 表明想要注册一个新用户
        std::string usr = argv[2];
        std::unordered_map<std::string, std::string> utop;
        init_isExist(utop);
        if(utop.count(usr)) {   // 判定注册的用户名是否已经存在
            printf("Sorry, the current user name has already been registered!\n");
            return 0;
        }
        std::ofstream fout;
        fout.open("chatClint/UsrData.dat", std::ios::out|std::ios::app);
        srand(time(NULL));
        std::string pwd = "";
       while(pwd.size() < 16) {    // 生成16位的随机密码,供用户登录使用
            char append = rand() % 93 + 33;
            // 替换控制台输入会产生奇怪效果的字符
            if(append == ')' || append == '(' || append == '$' || append == '>' || append == '<'
            || append == '|' || append == '&' || append == '\'' || append == '"' || append == '\\') append = '0';
            // if(append == '(') append = '[';         // linux5.0之后，命令是不能带有括号'('和')',因此进行替换
            // else if(append == ')') append = ']';
            pwd += append;
        }
        fout << usr << ' ' << pwd << std::endl;
        fout.close();
        printf("Registered successfully! Your login password is %s!\nPlease keep the password information safe!\n", pwd.c_str());
        return 0;
    } 
    else if(argc == 3) {    // 进行账号登录
        std::unordered_map<std::string, std::string> utop;
        init_isExist(utop);
        std::string usr = argv[1];
        std::string pwd = argv[2];
        if(!utop.count(usr)) {  // 判定账号是否存在
            printf("Sorry, the username you entered is not registered!\n");
            return 0;
        }
        else if(utop[usr] != pwd){  // 判定用户名和密码是否匹配
            printf("Sorry, the password is incorrect!\n");
            return 0;
        }
    }
    else {
        printf("If you do not have an account, please register first: %s signIn [UserName]\n", argv[0]);
        printf("If you want to log in to this chat room, please provide your account number and password: %s [UserName] [Password]\n", argv[0]);
        return 0;
    }
    std::ifstream fin;
    fin.open("server_config.dat", std::ios::in);
    std::string IPstr, IP, PORTstr, PORT;
    // 获取服务器运行的IP和端口号
    fin >> IPstr >> IP >> PORTstr >> PORT;
    ChatClint clnt(IP.c_str(), PORT.c_str(), argv[1]);
    fin.close();
    // 尝试和服务器建立连接
    if(!clnt.connectServer()) error_handling((char*)"connect() error");
    clnt.recvData(clnt.getSocketID());
    // 创建两个线程,一个进行读数据,一个进行写数据
    clnt.threadMaking();
    close(clnt.getSocketID());
    return 0;
}