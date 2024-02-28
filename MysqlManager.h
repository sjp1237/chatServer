#include "MySQLTool.h"
#include <map>
#include<string>

class MySqlManager
{
    //描述列项
    typedef struct{
        fieldiIfb()= default;
        fieldinfo(const string& name, const string& tp, const string& desc){
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
    bool Init()const(string& host,const string user,const string passwd,const string dbname,unsigned port = 3306);
private:
    bool CheckDatabase ();
    bool CheckTable(const sTableInfo& info);
    bool CreateDatabase();
    bool CreateTable(const sTableInfo& info);
    bool UpdateTable(const sTableInfo& info);

private:
    map<string,sTableInfo> m_mapTable;
    shared_ptr<MySQLTool> m _mysql;
}

typedef std::pair<string,MySqlManager::sTableInfo> TablePair;
typedef map<string,MySqlManager::sTableInfo>::iterator TableIter;
typedef map<string,MySqlManager : :sFieldInfo>:: iterator FieldIter;
typedef map<string,MySqlManager:: sFieldInfo>::const_iteratorFieldConstIter;
