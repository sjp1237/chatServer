#include"ClientSession.h" 


ClientSession::ClientSession(const TcpConnectionPtr& conn)
{
    m_sessionid=to_string(1);//random_generator是boost库相关的
    TcpConnectionPtr* client=const_cast<TcpConnectionPtr*>(&conn);
    *const_cast<std::string*>(&conn->name())=m_sessionid;
    (*client)->setMessageCallback(std::bind(&ClientSession::OnRead,this,_1,_2,_3));
}



void ClientSession::OnRead(const TcpConnectionPtr& conn,Buffer* buf,Timestamp time){

    while(buf->readableBytes()>=sizeof(int32_t)){
        int32_t packagesize=0;
        packagesize=*(int32_t*)buf->peek();

        if(buf->readableBytes()<sizeof(int32_t)+packagesize){
            return;
        }

        
        buf->retrieve(sizeof(int32_t));//移动Buffer的读取指针，跳过之前读取的int32_t大小的数据
        string msgbuff;
        msgbuff.assign(buf->peek(),packagesize);//将除了int32_t之后的消息数据拷贝到msgbuff里

        buf->retrieve(packagesize);
        cout<<"packagesize:"<<packagesize<<endl;
    //  cout << "Received message from " << conn->peerAddress().toIpPort() << ": " << msgbuff;
        if(Process(conn,msgbuff)!=true){
            cout<<"process error";
        }
    }
}



bool ClientSession::Process(const TcpConnectionPtr& conn,string msgbuff)
{
    //读取请求类型cmd
    //读取序列号
    //读取数据长度
    cout<<msgbuff.data()<<endl;
    BinaryReader reader(msgbuff);
    int cmd=-1;

    if(reader.ReadData<decltype(cmd)>(cmd)==false)
        return false;

    if(reader.ReadData<int>(m_seq)==false)
         return false;

    size_t datalength=0;
    if(reader.ReadData<size_t>(datalength)==false)
        return false;
    string data;
    data.resize(datalength);
    reader.ReadData(data);

    cout<<"cmd: "<<cmd<<endl;
    cout<<"seq: "<<m_seq<<endl;
    cout<<"datalen: "<<datalength<<endl;

    switch (cmd)
    {
    case msg_type_heartbeart:
        cout<<"heartbeart"<<endl;
        break;
    case msg_type_register:

        break;
    case msg_type_login://登录消息

        break ;
    case msg_type_getofriendlist://获取好友列表

         break;
    case msg_type_finduser: //查找用户

        break;
    case msg_type_operatefriend://操作好友
         break;
    case msg_type_updateuserinfo:
        break;
    case msg_type_modifypassword:
        break;
    case msg_type_creategroup:
        break;
    case msg_type_getgroupmembers:
        break;
    case msg_type_chat:
        break;
    case msg_type_multichat:
        break;
    default:
        break;

    }
    return true ;
}


// void ClientSession::onHeartbeatResponse(const TcpConnectionPtr& conn,const string& data){
//     //包的长度4字节不能压缩的，固定格式
//     //命令类型4字节不能压缩的,固定格式
//     //包的序号4字节不能压缩的，固定格式
//     //包的数据包长度（4字节，可以压缩的）+包内容（长度由前面一项来定)
//     BinaryWriter writer;
//     int cmd = msg_type_heartbeart;
//     writer.WriteData<int> (cmd) ;
//     writer. WriteData<int> (m_seq) ;
//     string empty;
//     writer.WriteData(empty);

//     Send(conn,writer);

// }



//  void ClientSession::onRegisterResponse(const TcpConnectionPtr& conn,const string& data)
//  {
//     //{//{"username" :"手机号","nickname":"昵称","password":"密码”}
//     Json::Reader reader;
//     Json::Value root;
//     if (reader.parse(data,root)==false){
//         cout<< "error json:"<< data << endl;return;
//     }
//     if (!root["username"].isString()||
//         !root["nickname"].isString()||
//         !root["password"].isString())
//     {
//         cout<< "error type:"<< data<< endl;
//         return;
//     }
    

//     User user;
//     user.username = root["username"].asString();
//     user.nickname = root["nickname"].asString();
//     user.password = root["password"].asString();
//     BinaryWriter out;
//     string result;
//     Json::Value root;

//     out.WriteData(msg_type_register);
//     out.WriteData(m_seq) ;
//     if(!Singleton<UserManager>::instance().AddUser(user)){
//         cout<<"add user failed! \r\n";
//         root["code"]=100;
//         root["msg"]="register failed";
//         result =root.toStyledString();
//         out.WriteData(result);
//         send(conn,out);
//         return;
//     }
//     else
//     {
//         root["code"]=0;
//         root["msg"]="ok";
//         result =root.toStyledString();
//         out.WriteData(result);
//         Send(conn,out);
//     }
//  }


//  void ClientSession::OnChatResponse(const TepConnectionPtr& conn,const string& data){
//         BinaryWriter writer;
//         writer.WriteData(htonl(msg_type_chat));
//         writer.WriteData(htonl(m_sgay));
//         writer.WriteData(data);
//         //消息发送者
//         writer.WriteData (htonl(m _user->userid)) ;//消息接受者
//         writer.WriteData (htonl(m_target)) ;
//          printf("%s (%d):%s target:%d cur : %d\r\n", _FILE,__LINE,_FUNCTION, m _target, m_user->userid);
//          cout<< data << endl;
//          UserManager& userMgr = Singleton<UserManager>::instance();//写入消息记录
//          if (!userMgr.SaveChatMsgToDb(m_user->userid, m_target, data))
//          {
//             LOG_ERROR <<"Write chat msg to db error,,senderid = "<< m_user->userid < ",targetid = " << m_target << ",chatmsg:"<<data;
//          }
//         IMServer& imserver = Singleton<IMServer>::instance();
//         MsgCacheManager& msgCacheMgr = Singleton<MsgCacheManager>::instance();//单聊消息

//          //群聊消息
//         std::list<UserPtr> friends;//群成员
//         userMgr. GetFriendInfoByUserId(m_target,friends);
//         std::string strUserInfo;
//         bool userOnline = false;
//         for (const auto& iter : friends){
//             //先看目标用户是否在线
//             ClientSessionPtr targetSession = imserver. GetSessionByID(iter->userid);//目标用户不在线，缓存这个消息
//             if (!targetSession){
//                 msgCacheMgr. AddChatMsgCache(iter->userid, writer.toString ());continue;
//                 targetSession->Send (writer);
//             }
//         }

//         printf("%s(%d):%s\r\n",__FILE__,_LINE__,_FUNCTION__);

//     }