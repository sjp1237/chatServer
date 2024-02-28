
#include"MySQLTool.h"




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


// bool MySQLTool::connect(const string& host,const string& user,const string& passwd,const string& db){
//     if (m _mysql != NULL){
//         MYSQL* tmp = m_mysql;
//         m mysql = NULL;
//         mysql_close(tmp);
//     }
//     m_mysql = mysql_init(m _mysql);//mysql 默认是3306
//     m_mysql = mysql_real_connect(m_mysql, host.c_str(),user.c_str(),passwd.c_str(),db.c_str(),NLL,0);
//     cout<< host<< std::endl << user << std::endl << passwd << std::endl << db << std::endl;
//     if (m_mysql != NULL){
//         m_host = host;
//         m_user = user;
//         m_passwd = passwd;
//         m_dbname = db;
//         mysql_query (m_mysql,"set names utf8;");
//         cout<< "connect mysql success!\r\n" ;
//         return true;

//     }
//     cout<< "connect mysql failed!r\n";
//     return false;
// }

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

// QueryResultptr MySQLTool::Query(const string& sql,uint32_t& nAffectedCount,int& nErrno)
// {
//     if (m mysql ==NULL) {
//         if (connect(m_host,m_user,m _passwd, m_dbname)== false){
//             return QueryResultPtr();
//         }
//     }
//     int ret = mysql_real_query(m mysql,sql.c_str(), sql.size());
//     if (ret){
//         uint32_t nErrno = mysql_errno(m mysql) ;
//         cout <<"mysql_real_query call fued! code is :" << nErrno << std::endl;
//         if (CR_SERVER_GONE_ERROR ==nErrno) {
//              if (connect(m_host,m_user,m passwd,m_dbname)== false){
//                  return QueryResultPtr();
//             }
//             ret = mysql_real_query(m mysql,sql.c_str(), sql.size());if (ret){
//                 nErrno = mysql_errno(m _mysql);
//                 cout << "mysql_real_query call failed againl code is :"<< nErrno << std::endl ;
//             }
//      }
//      else{
//         return QueryResultPtr();
//      }
//     MYSQL_RES* result = mysql_store_result(m_mysql);
//     uint32_t rowcount = mysql_affected_rows(m_mysql);
//     uint32_t cloumncount= mysql_field_count (m_mysql) ;
//     return QueryResultPtr(new QueryResult(result,rowcount,cloumncount));
//   }
// }

// bool MySQLTool::Execute(const string& sql){
//     uint32_t nAffectedCount;
//     int nErrno;
//     return Execute(sql,nAffectedCount,nErrno) ;
// }


// bool MySQLTool::Execute(const string& sql,uint32_t& nAffectedCount,int& nErrno){
//     if (m_mysql ==NULL){
//          if (connect(m_host,m_user,m passwd,m_dbname)== false){
//              return QueryResultPtr();
//             }
//     }
//     int ret = mysql_query(m_mysql,sql.c_str());
//     if (ret){
//         uint32_t nErrno = mysql_errno (m_mysql);
//         cout <<"mysql_query call failed! code is :"<< nErrno << std::endl;
//         if (CR_SERVER_GONE_ERROR == nErrno){
//             if (connect(m_host,m_user,m_passwd, m_dbname)== false){
//                 return false;
//             }
//             ret = mysql_query(m_mysql,sql.c_str());
//             if (ret){
//                 nErrno = mysql_errno(m_mysql) ;
//                 cout <<"mysql_query call failed again! code is :" << nErrno << std::endl;
//             }
//         }
//         else {
//             return false;
//         }
//         errno=0;
//         nAffectedCount=mysql_affected_row(m_mysql);
//     }
//     return false;
// }