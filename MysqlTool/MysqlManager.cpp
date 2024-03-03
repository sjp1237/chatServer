#include"MysqlManager.h"


MySqlManager::MySqlManager(){
    sTableInfo info;
    info.sName = "t_user";
    info.mapField["f_id"] = { "f_id","bigint (20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'","bigint(20)"};
    info.mapField["f_user_id"] = { "f_user_id","bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
    info.mapField["f_username"]= { "f_username","varchar(64) NOT NULL COMMENT '用户名'","varchar(64)"};
    info.mapField["f_nickname"] = { "f_nickname","varchar(64) NOT NULL COMMENT '用户昵称'","varchar(64)" };
    info.mapField["f_password"] = { "f_password","varchar(64) NOT NULL COMMENT '用户密码'","varchar(64)" };
    info.mapField["f_facetype"] = { "f_facetype","int(10) DEFAULT 0 COMMENT '用户头像类型'","int(10)" };
    info.mapField["f_customface"] = { "f_customface","varchar(32) DEFAULT NULL COMMENT '自定义头像名'","varchar(32)"};
    info.mapField["f_customfacefmt"] = { "f_customfacefmt", "varchar(6) DEFAULT NULL COMMENT '自定义头像格式'","varchar (6)" };
    info.mapField["f_gender"] = {"f_gender", "int(2) DEFAULT 0 COMMENT '性别'","int(2)" };
    info.mapField["f_birthday"] = {"f_birthday","bigint(20) DEFAULT 19900101 COMMENT '生日'","bigint(20)" };
    info.mapField["f_signature"] = {"f_signature" ,"varchar(256) DEFAULT NULL COMMENT '地址'","varchar(256)" };
    info.mapField["f_address"] = {"f_address", "varchar(256) DEFAULT NULL COMMENT '地址'","varchar(256)" };
    info.mapField["f_phonenumber"]= { "f_phonenumber","varchar(64) DEFAULT NULL COMMENT '电话'","varchar(64)"};
    info.mapField["f_mail"] = {"f_mail", "varchar(256) DEFAULT NULL COMMENT '邮箱'","varchar(256)" };
    info.mapField["f_owner_id"] = {"f_owner_id","bigint(20) DEFAULT 0 COMMENT '群账号群主userid'", "bigint(20)" };
    info.mapField["f_register_time"] = {"f_register_time","datetime NOT NULL COMMENT '注册时间'","datetime" };
    info.mapField["f_remark"] = { "f_remark","varchar(64) NULL COMMENT '备注'","varchar(64)"};
    info.mapField["f_update_time"] = {"f_update_time", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间'","timestamp"};
    info.sKey ="PRIMARY KEY(f_user_id),INDEX f_user_id(f_user_id),KEY f_id(f_id)";
    m_mapTable.insert (TablePair(info.sName,info)) ;


    info. mapField.clear() ;

    //聊天内容
    info. sName = "t_chatmsg";
    info.mapField["f_id"] = {"f_id", "bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'","bigint(20)" };
    info.mapField["f_senderid"] = { "f_senderid", "bigint(20) NOT NULL COMMENT '发送者id'", "bigint (20)" };
    info.mapField ["f_targetid"] = {"f_targetid","bigint(20) NOT NULL COMMENT '接收者id'", "bigint(20)" };
    info.mapField["f_msgcontent"] = {"f_msgcontent","BLOB NOT NULL COMMENT '聊天内容'","BLOB"};
    info.mapField["f_create_time"] = { "f_create_time", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT'更新时间'","timestamp"};
    info.mapField["f_remark"] = { "f_remark", "varchar(64) NULL COMMENT '备注'","varchar(64)" };
    info.sKey = "PRIMARY KEY(f_id),INDEX f_id(f_id)" ;
    m_mapTable.insert(TablePair(info.sName,info)) ;

    info.mapField.clear();
    info.sName = "t_user_relationship" ;
   // info.m_strName = "t_use'lationship";
    info.mapField["f_id"] = {"f_id", "bigint (20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'","bigint(20)"};
    info.mapField["f_user_id1"] = {"f_user_id1", "bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
    info.mapField["f_user_id2"] = { "f_user_id2","bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
    info.mapField["f_remark"] = { "f_remark","varchar(64) NULL COMMENT '备注'","varchar(64)" };
    info.mapField["f_create_time"] = {"f_create_time"," timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间'","timestamp"};
    info.sKey ="PRIMARY KEY(f_id),INDEX f_id(f_id)" ;
    m_mapTable.insert (TablePair(info.sName,info));

}
MySqlManager::~MySqlManager(){


}

bool MySqlManager::Init(const string& host,const string& user,const string& passwd,const string& dbname,unsigned int port=3306 ){
    m_mysql.reset (new MySQLTool());
    if (m_mysql->connect(host,user,passwd,dbname)== false){
         cout<< "connect mysql failed! \r\n" ;
        return false;
    }
    if (CheckDatabase() == false){
        if (CreateDatabase() ==false)
             return false;
    }
    TableIter it = m_mapTable.begin();
    for (; it != m_mapTable.end() ; it++){
        if (CheckTable(it->second)== false){
            cout<<it->second.sName<< "is not exit"<<endl;
           if (CreateTable(it->second)== false) {
                return false;
           }
        }
        cout<<it->second.sName<< "is exist"<<endl;
    }
    return true;
}

 
QueryResultPtr MySqlManager::Query(const string& sql){
    if (m_mysql == NULL)
        return QueryResultPtr();
    return m_mysql->Query(sql);
}

 bool MySqlManager::Execute(const string& sql) {
    if (m_mysql==NULL)return false;
     return m_mysql->Execute(sql);
}


bool MySqlManager::CheckDatabase(){
    if (m_mysql ==NULL)return false;
    QueryResultPtr result = m_mysql->Query("show databases;");
    if (NULL == result){
        cout<< "no database found in mysql! \rin";
        return false;
    }
    Field* pRow = result->Fetch() ;
    string dbname = m_mysql->GetDBName();
    while (pRow !=NULL) {
         string name = pRow[0].GetString();
         if (name == dbname){
             result->EndQuery () ;
             return true;
         }
        if (result->NextRow()== false)break;
        pRow = result->Fetch();
    }
    //cout<< "database not found!\r\n" ;
    result->EndQuery();
    return false;
}

bool MySqlManager::CreateDatabase(){
    if (m_mysql ==NULL) {
        return false;
    }
    stringstream sql;
    sql<<"create database" <<m_mysql->GetDBName()<<";";
    uint32_t naffect = 0;
    int nErrno = 0;
    if (m_mysql->Execute(sql.str(),naffect,nErrno)== false){
        return false;
    }
    if (naffect== 1)
    {
        return true ;
    }
    return false;
}

bool MySqlManager::CheckTable(const sTableInfo& info){
    if (m_mysql ==NULL){
        return false;
    }
    stringstream sql;

    //生成查询表结构
    sql <<"desc " << info.sName << " ;";
    QueryResultPtr result = m_mysql->Query(sql.str());
    if (result ==NULL){
        if (CreateTable(info)== false){
             return false;
        }
        return true;
    }

    //比较 表结构
    map<string,sFieldInfo> rest;
    rest.insert(info.mapField.begin(),info.mapField.end());
    map<string,sFieldInfo> mapChange;
    result->NextRow();
    Field* pRow = result->Fetch() ;

    while (pRow != NULL) {
        //获取查询结果中的字段名和类型
        string name = pRow[0].GetString();
        string type = pRow[1].GetString();
        auto iter = info.mapField.find(name) ;
        if (iter == info.mapField.end()){
            return false;
        }

        if(result->NextRow()==false) break;
        pRow=result->Fetch();
    }
    return true;
}

bool MySqlManager::CreateTable(const sTableInfo& info){
    if (m_mysql ==NULL)return false;
    if (info.mapField.size()== 0)
        return false;
    stringstream sql;
    sql.str("");
    sql <<"create table if not exists " << info.sName<<"(";
    
    FieldConstIter it = info.mapField.begin() ;
    for (; it != info.mapField. end(); it++){
        if (it != info.mapField.begin()){
            sql <<"," ;
        }
        sFieldInfo field = it->second;
        sql<< field.sName<<" "<< field.sType;
    }

    if (info.sKey.size()>=0){
        sql<< ","<<info.sKey;
    }

    sql<<");";
    //sql <<") default charset=utf-8, ENGINE=InnoDB;";
    cout << "Generated SQL: " << sql.str() << endl;
    return m_mysql->Execute(sql.str());
}


// bool MySqlManager::UpdateTable(const sTableInfo& info){
//     //1.检测表在不在
//     //2.
// }