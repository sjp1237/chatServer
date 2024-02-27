#include <unistd.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <errno.h>
#include "base/Logging.h"


class QueryResult
{
public:
    QueryResult();
    ~QueryResult();
  bool NextRow() ;//true表示还有下一行，并且切换成功; false表示没有了private:

  const Field& operator[](int index)const {
        return m_CurrentRow[i];
  }
  const Field& operator[](const string& name)const {
        return m_ CurrentRow[GetFieldIndexByName(name)];
  }
  uint32_t GetFieldCount()const { return m_cloumncout;}
  uint32_t GetRowCount()const { return m_rowcount; }

  vector<string>const& GetFieldNames() const { return m_vecFieldName;}
  void EndQuery() ;
  static Field::DataTypes toEDYType(enN field_types mysqltype)const;


private:
    int GetFieldIndexByName (const string& name) {
        for (uint32_t i =0; i< m_vecFieldName.size(); i++){
        if (m_vecFieldName[i] ==name)return i;
        return -1;
    }

    vector<Field> m CurrentRow;
    vector<Field>m_CurrentRow ;
    vector<string> m_vecFieldName ;
    MYSQL_RES* m _result;
    uint32_t m_rowcount;
    uint32_t m_cloumncout;
}
}

  typedef shared_ptr<QueryResult> QueryResultPtr;
