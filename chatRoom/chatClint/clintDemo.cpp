#include "chatClint.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <ctime>
#include <iostream>
#include <unordered_map>

void error_handling(char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

void init_isExist( std::unordered_map<std::string, std::string>& utop ) {
    std::ifstream fin;
    fin.open("chatClint/UsrData.dat", std::ios::in);
    while(fin) {
        std::string usr, pwd;
        fin >> usr >> pwd;
        utop[usr] = pwd;
    }
    fin.close();
}

int main(int argc, char* argv[]) {
    if(argc == 3 && !strcmp(argv[1], "signIn")) {
        std::string usr = argv[2];
        std::unordered_map<std::string, std::string> utop;
        init_isExist(utop);
        if(utop.count(usr)) {
            printf("Sorry, the current user name has already been registered!\n");
            return 0;
        }
        std::ofstream fout;
        fout.open("chatClint/UsrData.dat", std::ios::out|std::ios::app);
        srand(time(NULL));
        std::string pwd = "";
        while(pwd.size() < 16) pwd += (char)(rand() % 93 + 33);
        fout << usr << ' ' << pwd << std::endl;
        fout.close();
        printf("Registered successfully! Your login password is %s!\nPlease keep the password information safe!\n", pwd.c_str());
        return 0;
    } 
    else if(argc == 3) {
        std::unordered_map<std::string, std::string> utop;
        init_isExist(utop);
        std::string usr = argv[1];
        std::string pwd = argv[2];
        if(!utop.count(usr)) {
            printf("Sorry, the username you entered is not registered!\n");
            return 0;
        }
        else if(utop[usr] != pwd){
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
    fin >> IPstr >> IP >> PORTstr >> PORT;
    ChatClint clnt(IP.c_str(), PORT.c_str(), argv[1]);
    fin.close();
    if(!clnt.connectServer()) error_handling((char*)"connect() error");
    clnt.recvData(clnt.getSocketID());
    clnt.threadMaking();
    close(clnt.getSocketID());
    return 0;
}