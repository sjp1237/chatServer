
#include"MySQLTool.h"

#include"QueryResult.h"


MySQLTool::MySQLTool()
{
    m_mysql = NULL;
}

MySQLTool::~MySQLTool(){
    if (m_mysql != NULL){
       MYSQL* tmp = m_mysql;
        m_mysql = NULL;
        mysql_close(tmp);
    }
}



bool MySQLTool::connect(const string& host,const string& user,const string& passwd,const string& db){
    if (m_mysql != nullptr) {
        MYSQL* tmp = m_mysql;
        m_mysql = nullptr;
        mysql_close(tmp);
    }

    m_mysql = mysql_init(m_mysql);

    //m_mysql = mysql_real_connect(m_mysql, host.c_str(),user.c_str(),passwd.c_str),db.c_str(),NLL,0);
      m_mysql = mysql_real_connect(m_mysql, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), 0, nullptr, 0);
    cout<< host<< std::endl << user << std::endl << passwd << std::endl << db << std::endl;
    if (m_mysql != nullptr) {
        m_host = host;
        m_user = user;
        m_passwd = passwd;
        m_dbname = db;
        mysql_query(m_mysql, "set names utf8;");
        std::cout << "connect mysql success!\r\n";
        return true;
    }
    cout<< "connect mysql failed!r\n";
    return false;
}


//执行语句并获取结果集
shared_ptr<QueryResult> MySQLTool::Query(const string& sql)
{
    if (m_mysql ==NULL) {
        if (connect(m_host,m_user,m_passwd, m_dbname)== false){
            return nullptr;
        }
    }
    int ret = mysql_real_query(m_mysql,sql.c_str(), sql.size());//成功返回0
    if (ret){
        //查询失败
        uint32_t nErrno = mysql_errno(m_mysql) ;
        cout <<"mysql_real_query call fued! code is :" << nErrno << std::endl;
        if (CR_SERVER_GONE_ERROR ==nErrno) {
             if (connect(m_host,m_user,m_passwd,m_dbname)== false){
                 return nullptr;
            }
            ret = mysql_real_query(m_mysql,sql.c_str(), sql.size());
            if (ret){
                nErrno = mysql_errno(m_mysql);
                cout << "mysql_real_query call failed againl code is :"<< nErrno << std::endl ;
                return nullptr;
            }
         }
         else{
            return nullptr;
         }

    }
    MYSQL_RES* result = mysql_store_result(m_mysql);
    uint32_t rowcount = mysql_affected_rows(m_mysql);// 获取受影响的行数
    cout << "mysql row:"<< rowcount << std::endl ;
    uint32_t cloumncount=mysql_field_count (m_mysql) ;// 获取结果集的列数
    return QueryResultPtr(new QueryResult(result,rowcount,cloumncount));
}

bool MySQLTool::Execute(const string& sql){
    uint32_t nAffectedCount;
    int nErrno;
    return Execute(sql,nAffectedCount,nErrno) ;
}


//只进行语句，不获取结果集
bool MySQLTool::Execute(const string& sql,uint32_t& nAffectedCount,int& nErrno){
    if (m_mysql ==NULL){
         if (connect(m_host,m_user,m_passwd,m_dbname)== false){
             return false;
            }
    }
    int ret = mysql_query(m_mysql,sql.c_str());
    if (ret){
        uint32_t nErrno = mysql_errno (m_mysql);
        cout <<"mysql_query call failed! code is :"<< nErrno << std::endl;
        cout<<"mysql_query call failed"<<mysql_error(m_mysql)<<endl;
        if (CR_SERVER_GONE_ERROR == nErrno){
            if (connect(m_host,m_user,m_passwd, m_dbname)== false){
                return false;
            }
            ret = mysql_query(m_mysql,sql.c_str());
            if (ret){
                nErrno = mysql_errno(m_mysql);
                cout <<"mysql_query call failed again! code is :" << nErrno << std::endl;
                cout<<"mysql_query call failed"<<mysql_error(m_mysql)<<endl;
                return false;
            }
        }
    } 
    errno=0;
    nAffectedCount=mysql_affected_rows(m_mysql);
    return true;
}