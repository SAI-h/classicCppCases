#ifndef _ChatClint_
#define _ChatClint_
#include "../netUnity/netUnity.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

class ChatClint :public NetUnity{
    public:
        enum {
            START = 0,
            RUNNING = 1
        };
        typedef struct{
            ChatClint* ptr;
            int sock;
        }argList;
        ChatClint(const char* netAddr, const char* port, const std::string UsrName);
        bool connectServer();
        int recvData(int targetSockID) override;
        int sendData(int targetSockID) override;
        void threadMaking();
        static void* handleRecv(void* arg);
        static void* handleSend(void* arg);
    private:
        sockaddr_in serv_addr;
        pthread_t recvThread, sendThread;
        int status;
        std::string UsrName;
};

#endif // _ChatClint_