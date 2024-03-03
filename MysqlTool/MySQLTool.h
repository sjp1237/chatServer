#ifndef MYSQLTOOL_H
#define MYSQLTOOL_H


#include<string>
#include<iostream>
#include <mysql.h>
#include <errmsg.h>
#include"QueryResult.h"

using namespace std;


class MySQLTool{
public:
    MySQLTool();
    ~MySQLTool();
    bool connect(const string& host,const string& user,const string& passwd, const string& db);
   // bool connect(const string& host,const string& user,const string& passwd,const string& db);
    //QueryResult Query (const string& sql);
    QueryResultPtr Query(const string& sql);
     bool Execute(const string& sql);
     bool Execute(const string& sql,uint32_t& nAffectedCount,int& nErrno);

     inline string GetDBName(){return m_dbname;};

private:
    MYSQL*  m_mysql;
    string m_host;
    string m_user;
    string m_passwd;
    string m_dbname;
};
#endif