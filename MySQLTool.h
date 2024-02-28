

#include<string>
#include<iostream>
#include"QueryResult.h"
using namespace std;


class MySQLTool{
public:
    MySQLTool();
    ~MySQLTool();
    bool connect(const string& host,const string& user,const string& passwd, const string& db);
   // bool connect(const string& host,const string& user,const string& passwd,const string& db);
    //QueryResult Query (const string& sql);
   // QueryResultPtr Query(const string& sql,uint32_t& nAffectedCount,int&nErrno);
  //  bool Execute(const string& sql);
    //bool Execute(const string& sql,uint32_t& nAffectedCount,int& nErrno);
private:
    MYSQL*  m_mysql;
    string m_host;
    string m_user;
    string m_passwd;
    string m_dbname;
};