#include"MysqlManager.h"


IMySqlManager::MySqlManager(){
    sTableInfo info;
    info.sName = "t_user";
    info.mapField["f_id"] = { "f_id","bigint (20) NOT NULL AUTO_INCREMENT COMMENT'自增ID'","bigint(20)"};
    info.m_mapField["f_user_id"] = { "f_user_id","bigint(20) NOT NULL COMENT'用户ID'", "bigint(20)" };
    info.m_mapField["f_username"]= { "f_username","varchar(64) NOT NULL COMMENT'用户名'","varchar(64)"};
    info.m_mapField["f_nickname"] = { "f_nickname","varchar(64) NOT NUL COMENT'用户昵称'","varchar(64)" };
    info.m_mapField["f_password"] = { "f_password","varchar(64) NOT NUL COMENT'用户密码'","varchar(64)" };
    info.m_mapField["f_facetype"] = { "f_facetype","int(10)DEFAULT 0 COMENT'用户头像类型'","int(10)" };
    info.m_mapField["f_customface"] = { "f_customface","varchar(32) DEFALLT NULL COMENT'自定义头像名'","varchar(32)"};
    info.m mapFieldl["i_customfacefmt"] = { "f_customfacefimt", "varchar(6) DEFALT NLL COMENT'自定义头像格式'","varchar (6)" };
    info.m_mapField["f_gender"] = {"f_gender", "int(2) DEFAULT O COMMENT '性别'","int(2)" };
    info.m_mapField["f_birthday"] = {"f_birthday","bigint(20) DEFAULT 19900101 COMENT'生日'","bigint(20)" };
    info.m mapField["f_signature"] = {"f_signature" ,"varchar(256) DEEAULT NULL COMENT'地址'","varchar(256)" };
    info.m_mapField["f_address"] = {"f_address", "varchar(256) DEFAULT NULL COMENT'地址'","varchar(256)" };
    info.m_mapField["f_phonenumber"]= { "f_phonenumber","varchar(64) DEFALT NULL COMENT'电话''","varchar(64)"};
    info.m_mapField["f_mail"] = {"f_mail", "varchar(256) DEFALLT NULL COMMENT'邮箱'","varchar(256)" };
    info.m_mapField["f_owner_id"] = {"f_owner_id","bigint(20) DEAULT O COMENT'群账号群主userid", "bigint(20)" };
    info.m_mapField["f_register_time"] = {"f_register_time","datetime NOT NL COMENT'注册时间'","datetime" };
    info.m_mapField["f_remark"] = { "f_remark","varchar(64) NULL COMENT'备注'","varchar(64)"};
    info.mmapField["f_update_time"] = {"f update_time", "timestamp NOT NUIL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURENT_TIMESTAMP
    COMMENT '更新时间'","timestamp"};
    info.sKey ="PRIMARY KEY (f_user_id),INDEX f_user_id (f_user_id),KEY f_id ( f_id )";
    m_mapTable.insert (TablePair(info.sName,info)) ;
    info. mapField.clear() ;

    //聊天内容
    info. sName = "t_chatmsg";
    info.mapField["f_id"] = {"f_id", "bigint(20) NOT NULL AUTO_INCREMENT COMENT '自增ID'","bigint(20)" };
    info.mapField["f_senderid"] = { "f_senderid", "bigint(20) NOT NLLL COMMENT '发送者id'", "bigint (20)" };
    info.mapField ["f_targetid"] = {"f_targetid","bigint(20) NOT NULL COMMENT'接收者id'", "bigint(20)" };
    info.mapField["f_msgcontent"] = {"f_msgcontent","BLOB NOT NJLL COMMENT'聊天内容'","BLOB"};
    info.mapField["f_oreate_time"] = { "i_create_time", "timestamp NOT NUL DEFALLT CUREXT_TIMESTAMP ON UPDATE CURENT_TIMESTAMPCOMMENT'更新时间'","timestamp"};
    info.mapField["f_remark"] = { "f_remark", "varchar(64) NULL COMENT'备注'","varchar(64)" };
    info.sKey = "PRIMARY KEY (f_id),INDEX f_id (f_id)" ;
    m_mapTable.insert (TablePair(info.sName,info)) ;

    info.mapField.clear();
    info.sName = "t_user relationship" ;
    info.m_strName = "t_use'lationship";
    info.mapField["f_id"] = {"f_id", "bigint (20) NOT NUL AUTO_INCREMENT COMENT '自增ID'","bigint(20)" ;
    info.mapField["f_user_id1"] = {"f_user_idl1", "bigint(20) NOT NULL COMMENT'用户ID'", "bigint(20)" };
    info.mapField["f_user_id2"] = { "f_user_id2","bigint(20) NOT NUL COMMENT '用户ID'", "bigint(20)" };
    info.mapField["f_remark"] = { "f_remark","varchar(64) NULL COMMENT'备注'","varchar(64)" };
    info.mapField["f_create_time"] = {"f_oreate_time"," timestamp NOT NULL DEFAULT CURENT_TIMESTAMIP ON UPDATE CURENT_TIMESTAMP 
    COMMENT ’更新时间’","timestamp"};
    info.sKey ="PRIMARY KEY (f_id),INDEX f_id (f_id)" ;
    m_mapTable.insert (TablePair(info.sName,info));

}
MySqlManager::~MySqlManager(){


}

bool Init(string& host,const string user,const string passwd,const string dbname,unsigned port = 3306){
    m_mysql.reset (new MySQLTool());
    if (m_mysql->connect(host,user,passwd,db,port)== false){
         cout<< "connect mysql failed! \r\n" ;
        return false;
    }
    if (CheckDatabase() == false){
        if (CreateDatabase() ==false)
             return false;
    }
    TableIter it = m _mapTable.begin(;for (; it != m_mapTable.end) ; it++){
        if (CheckTable(it->second. sName)== false){
           if (CreateTable(it->second)== false) {
                return false;
           }
        }
    return true;
}
QueryResultPtr MySqlManage::Query(const string& sql){
    if (m mysql == NULL)
        return QueryResultPtr();
    return m mysql->Query(sql) ;
}

void MySqlManager: :EndQuery () {
    if (m_mysql==NULL)return QueryResultPtr();
    return m_mysq1->EndQuery();
}
bool MySqlManage::CheckDatabase(){
    if (m_mysql ==NULL)return false;
    QueryResultPtr result = m _mysql->Query("show databases;");
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
        pRow = result->Fetch
    }
    cout<< "database not found!\r\n" ;
    result->EndQuery();
    return false;
}

bool MySqlManage::CreateDatabase(){
    if (m mysql ==NULL) {
        return false;
    }
    stringstream sql;
    sql<<"create database " <<m_mysql->GetDBName()<<";";
    uint32_t naffect = 0;
    int nErrno = 0;
    if (m_mysql->Execute(sql,naffect,nErrno)== false){
        return false;
    }
    if (naffect== 1)
    {
        return true ;
    }
    return false;
}

bool MySqlManage::CheckTable(const sTableInfo& info){
    if (m_mysql ==NULL){
        return false;
    }
    stringstream sql;
    sql <<"desc " << info. sName << " ;";
    QueryResultPtr result = m_mysq1->Query(ss);
    if (result ==NULL){
        if (CreateTable(info)== false){
             return false;
        }
        return true;
    }

    map<string,sFieldInfo> rest;
    rest.insert(info.mapField.begin(),info.mapField.end());
    map<string,sFieldInfo> mapChange;
    typedef pair<string,sFieldInfo> FieldPair;
    Field* pRow = result->Fetch() ;
    while (pRow != NULL) {
        string name = pRow[0].GetString();
        string type = pRow[1].GetString();
        FieldIter iter = info.mapField.find(name) ;
        if (iter == info.mapField.end()){
            continue;
        }

        if(iter->second.sType!=type){
            //看看能不能修改
            mapChange.insert(FieldPair(name,iter->second));
            break;
        }

        if(result->NextRow()==false) break;
        pRow=result->Fetch();
    }

    result->EndQuery();

    if(rest.size()>0){
        mapChange.insert(rest.begin,rest.end());
    }

    //修改
        if (rest.size()>0){
            FieldIter it = rest.begin() ;
            for (; it != rest.end(); it++){
                stringstream ss;
                ss<< "alter table " << info.sName <<" add column " << it->second.sName<<
                " " <<it->second.sType<< " ;";
                if (m _mysql->Execute(ss)== false){
                    return false;
                }
            }
        }
        if (mapChange.size() > 0){
           FieldIter iter = mapChange.begin() ;
            for (; iter != mapChange. end(); iter++) {
                    stringstream ss;
                    ss << "alter table " << info.sName<<
                    " modify column" << iter->second.sName <<
                    " " <<iter->second.sType << ";";
                    if (m_mysql->Execute(ss)==false){
                        return false;
                     }
            }
        }
}

bool MySqlManage::CreateTable(const sTableInfo& info){
    if (m mysql ==NULL)return false;
    if (info.mapField.size()== 0)
        return false;
    stringstream sql;
    sql = "create table if not exists " << info.sName<<"(";
    FieldConstIter it = info.mapField.begin() ;
    for (; it != info.mapField. end(); it++){
        if (it != info.mapField.begin()){
            sql <<"," ;
        }
        sFieldInfo field = it->second;
        sql<< field.sName<<" "< field.sType;
    }

    if (info.sKey.size()>0){
        sql<< ","<<info.sKey;
    }
    sql <<") default charset=utf-8, ENGINE=InnoDB;";
    return m mysql->Execute(sql);
}


bool MySqlManage::UpdateTable(const sTableInfo& info){
    //1.检测表在不在
    //2.
}