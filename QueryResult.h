#include <unistd.h>
#include <mysql.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <errno.h>
#include<vector>
#include"Field.h"
//#include "base/Logging.h"
using namespace std;

enum field_types{
         FIELD_TYPE_TIMESTAMP,
         FIELD_TYPE_DATE,
         FIELD_TYPE_TIME,
         FIELD_TYPE_DATETIME,
         FIELD_TYPE_YEAR,
         FIELD_TYPE_STRING,
         FIELD_TYPE_VAR_STRING,
         FIELD_TYPE_BLOB,
         FIELD_TYPE_SET,
         FIELD_TYPE_NULL,
         FIELD_TYPE_TINY,
         FIELD_TYPE_SHORT,
         FIELD_TYPE_LONG,
         FIELD_TYPE_LONGLONG,
         FIELD_TYPE_INT24,
         FIELD_TYPE_ENUM,
         FIELD_TYPE_DECIMAL,
         FIELD_TYPE_FLOAT,
         FIELD_TYPE_DOUBLE,

}

class QueryResult
{
public:
  
  QueryResult();
 QueryResult(MYSQL_RES* result,int32_t rowcount,uint32_t cloumncout);
  ~QueryResult();
  bool NextRow() ;//true表示还有下一行，并且切换成功; false表示没有了private:

  const Field& operator[](int index)const {
        return m_CurrentRow[index];
  }

  const Field& operator[](const string& name)const {
        return m_CurrentRow[GetFieldIndexByName(name)];
  }

  uint32_t GetFieldCount()const { return m_cloumncout;}
  uint32_t GetRowCount()const { return m_rowcount; }

  vector<string>const& GetFieldNames() const { return m_vecFieldName;}
  void EndQuery() ;
  Field:: DataTypes toEDYType (enum_field_types mysqltype)const;
//  static Field::DataTypes toEDYType(enN field_types mysqltype)const;

private:
    int GetFieldIndexByName (const string& name) const{
        for (uint32_t i =0; i< m_vecFieldName.size(); i++){
              if (m_vecFieldName[i] ==name)return i;    
         }
       return -1;
    }

    vector<Field> m_CurrentRow;
    vector<string> m_vecFieldName ;
    MYSQL_RES* m_result;
    uint32_t m_rowcount;
    uint32_t m_cloumncout;
};

  typedef shared_ptr<QueryResult> QueryResultPtr;
