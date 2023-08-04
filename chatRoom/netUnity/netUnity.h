#ifndef _NetUnity_
#define _NetUnity_
#define BUF_SIZE 1024

class NetUnity {
    public:
        NetUnity();
        ~NetUnity();
        int getSocketID() const;
        virtual int recvData(int targetSockID);
        virtual int sendData(int targetSockID);
    protected:
        int sockID;
        char msg[BUF_SIZE];
};

#endif // _NetUnity_