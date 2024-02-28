#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<muduo/base/Logging.h>


using namespace muduo;
using namespace muduo::net;


class Server
{
   public:
   Server()=default;
   Server(const Server&)=delete;
   ~Server()=default;
   Server& operator=(const Server&)=delete;

   bool Init(const std::string& ip,short port,EventLoop* loop);

   protected:
   void OnConnection(const TcpConnectionPtr& conn);
   void OnClose(const TcpConnectionPtr& conn);

   private:
   std::shared_ptr<TcpServer> m_server;
   //std::map<std::string,ClientSessionPtr> m_mapclient;
};

typedef std::pair<std::string,TcpConnectionPtr> ConnPair;
//typedef std::map<std::string,ClientSessionPtr>::iterator ConnIter;

