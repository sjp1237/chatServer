#ifndef MYSQLMANAGER_H
#define MYSQLMANAGER_H


#include "MySQLTool.h"
#include <map>
#include<string>
#include <utility> 
#include<sstream>

class MySqlManager
{
    //描述列项
public:
    typedef struct sFieldInfo{
        sFieldInfo()= default;
        sFieldInfo(const string& name, const string& tp, const string& desc){
           sName = name;
           sType = tp;
           sDesc = desc;
        }
        string sName;
        string sType;
        string sDesc;
    } sFieldInfo;

    //将各个表组织在sTableInfo里面
    typedef struct {
        string sName;
        map<string,sFieldInfo> mapField;
        string sKey;
   }sTableInfo;
   
public:
    MySqlManager();
    ~MySqlManager();
     bool Init(const string& host,const string& user,const string& passwd,const string& dbname,unsigned int port);
    QueryResultPtr Query(const string & sql);
    bool Execute(const string& sql) ;
private:
     bool CheckDatabase (); 
    bool CreateDatabase();
    bool CheckTable(const sTableInfo& info);
   
     bool CreateTable(const sTableInfo& info);
    // bool UpdateTable(const sTableInfo& info);
private:
    map<string,sTableInfo> m_mapTable;
    shared_ptr<MySQLTool> m_mysql;
};

typedef std::pair<string,MySqlManager::sTableInfo> TablePair;
typedef map<string,MySqlManager::sTableInfo>::iterator TableIter;
typedef map<string,MySqlManager::sFieldInfo>::iterator FieldIter;
typedef map<string,MySqlManager:: sFieldInfo>::const_iterator FieldConstIter;
typedef pair<string,MySqlManager::sFieldInfo> FieldPair;

#endif