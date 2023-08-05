#ifndef _NetUnity_
#define _NetUnity_
#define BUF_SIZE 1024

class NetUnity {
    public:
        NetUnity();
        ~NetUnity();
        int getSocketID() const;                    // 获取套接字
        virtual int recvData(int targetSockID);     // 接受来自于targetSockID的数据信息
        virtual int sendData(int targetSockID);     // 将数据信息发送至targetSockID对应的客户端
    protected:
        int sockID;                                 // 套接字文件描述符
        char msg[BUF_SIZE];                         // 用于接收/发送数据的字符串
};

#endif // _NetUnity_