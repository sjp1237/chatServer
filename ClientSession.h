

#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<muduo/base/Logging.h>

using namespace muduo;
using namespace muduo::net;

class ClientSession
{
    public:
    ClientSession(const TcpConnectionPtr& conn);
    ClientSession(const ClientSession&)=delete;
    ClientSession& operator=(const ClientSession&)=delete;
    ~ClientSession();

    operator std::string(){
        return m_sessionid;
    }

    private:
    std::string m_sessionid;
};

typedef std::shared_ptr<ClientSession> ClientSessionPtr;