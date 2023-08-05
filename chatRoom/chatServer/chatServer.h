#ifndef _ChatServer_
#define _ChatServer_
#include "../netUnity/netUnity.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>

class ChatServer :public NetUnity {
    public:
        typedef struct {                                // 用于规范使用传入线程函数的参数
            ChatServer* ptr;
            int cln_sock;
        } argList;
        enum {
            WAITING = 5                                 // 进行服务器处理的等待队列长度
        };
        ChatServer(char* port);
        bool SockBindToAddr();                          // 将套接字和网络地址进行绑定
        bool setListening();                            // 服务器设置监听
        int acceptDataSwap();                           // 接收新的客户端连接请求
        int recvData(int targetSockID) override;        // 接收来自客户端的数据信息
        int sendData(int sendingSource) override;       // 将数据信息转发给其他的客户端
        void lock();                                    // 上锁,保证临界区仅有一个线程可以访问
        void unlock();                                  // 解锁
        void addClnSock(const int& cln_sock);           // 将客户端套接字信息存入服务队列
        void threadMaking(const int& cln_sock);         // 创建线程服务客户端
        static void* handleCln(void* arg);              // 线程处理函数
        void rmClnSock(const int& cln_sock);            // 客户端退出,移除位于服务队列的客户端套接字信息
    private:
        sockaddr_in addr;                               // 自身的网络地址
        pthread_mutex_t mutex;                          // 互斥锁
        pthread_t pid;                                  // 线程号
        std::vector<int> clnSockArr;                    // 服务队列,主要为了明确当前有哪线客户端处于在线状态,将数据发送给这些在线客户端(发送数据的客户端除外)
};


#endif // _ChatServer_