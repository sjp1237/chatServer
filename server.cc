#include"server.h"

  bool Server::Init(const std::string& ip,short port,
                    EventLoop* loop)
  {
    InetAddress addr(ip,port);
    m_server.reset(new TcpServer(loop,addr,"chatserver",TcpServer::kReusePort));
    m_server->setConnectionCallback(std::bind(&Server::OnConnection,this,_1));
    m_server->start();
    return true;
}



 void Server::OnConnection(const TcpConnectionPtr& conn)
 {
    if(conn->connected()){
        
    }
    else{
        OnClose(conn);
    }
 }


void Server::OnClose(const TcpConnectionPtr& conn)
{
    
}