#ifndef _ChatServer_
#define _ChatServer_
#include "../netUnity/netUnity.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>

class ChatServer :public NetUnity {
    public:
        typedef struct{
            ChatServer* ptr;
            int cln_sock;
        }argList;
        enum {
            WAITING = 5
        };
        ChatServer(char* port);
        bool SockBindToAddr();
        bool setListening(); 
        int acceptDataSwap();
        int recvData(int targetSockID) override;
        int sendData(int sendingSource) override;
        void lock();
        void unlock();
        void addClnSock(const int& cln_sock);
        void threadMaking(const int& cln_sock);
        static void* handleCln(void* arg);
        void rmClnSock(const int& cln_sock);
    private:
        sockaddr_in addr;
        pthread_mutex_t mutex;
        pthread_t pid;
        std::vector<int> clnSockArr;
};


#endif // _ChatServer_