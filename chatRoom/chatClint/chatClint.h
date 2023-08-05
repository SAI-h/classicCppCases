#ifndef _ChatClint_
#define _ChatClint_
#include "../netUnity/netUnity.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

class ChatClint :public NetUnity{
    public:
        typedef struct {                            // 用于规范使用传入线程函数的参数
            ChatClint* ptr;
            int sock;
        } argList;
        ChatClint(const char* netAddr, const char* port, const std::string UsrName);
        bool connectServer();                       // 和服务器建立连接
        int recvData(int targetSockID) override;    // 接收来自于服务器端的数据
        int sendData(int targetSockID) override;    // 将数据发送至服务器端
        void threadMaking();                        // 创建读写线程
        static void* handleRecv(void* arg);         // 处理读线程的服务函数
        static void* handleSend(void* arg);         // 处理写线程的服务函数
    private:
        sockaddr_in serv_addr;                      // 服务器端的网络地址
        pthread_t recvThread, sendThread;           // 读写线程的线程号
        std::string UsrName;                        // 存储当前用户的用户名
};

#endif // _ChatClint_