

#include<string>
#include<iostream>
#include"QueryResult.h"
using namespace std;


class MySQLTool{
public:
    MySQLTool();
    ~MySQLTool();
    bool connect(const string& host，const string& user，const stringk passwd, const string& db);QueryResult Quory (const string& sql);
    QueryResultPtr Query(const string& sql，uint32_t& nAffectedCount，int&nErrno);
private:
    MYSQI  m_mysql;
    string m_host;
    string m_user;
    string m passwd;
    string m_dbname;
};