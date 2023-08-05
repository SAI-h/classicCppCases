#include "tool.h"
#include <cstdlib>
#include <cstdio>
#include <fstream>
// 输出错误信息
void error_handling(char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
// 初始化用户信息
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