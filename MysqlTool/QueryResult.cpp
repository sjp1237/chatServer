#include"QueryResult.h"

QueryResult::QueryResult(MYSQL_RES* result,int32_t rowcount,uint32_t cloumncout)
        :m_result (result),m_rowcount(rowcount), m_cloumncout(cloumncout)
{
    m_CurrentRow.resize(m_cloumncout);
    m_vecFieldName.resize(m_cloumncout);
    MYSQL_FIELD* fields = mysql_fetch_fields(m_result) ;
    for (uint32_t i= 0; i< cloumncout; i++){
        m_vecFieldName[i] = fields[i].name;
      //  m_CurrentRow[i].SetType(toEDYType(fields[i].type)) ;//设置类型
        m_CurrentRow[i].SetName (m_vecFieldName[i]);//设置列名
    }
}

QueryResult::~QueryResult() {}

bool QueryResult::NextRow()
{
    if (m_result == NULL)return false;
    MYSQL_ROW row = mysql_fetch_row(m_result) ;//获取下一行的数据
    if (row ==NULL){
    //TOD0:结束查询'
        return false;
    }
    uint32_t* pFieldLength = (uint32_t*)mysql_fetch_lengths(m_result);
    for (uint32_t i = 0; i < m_cloumncout ; i++){
        if (row[i] ==NULL){
          m_CurrentRow[i].SetValue (NULL,0);
        }
        else {
        //TOD0:设置field的值
          m_CurrentRow[i].SetValue(row[i], pFieldLength[i]);
        }
    }
    return true;
}


void QueryResult::EndQuery(){
    m_CurrentRow.clear();
    m_vecFieldName.clear();
    if (m_result) {
        mysql_free_result(m_result);
        m_result = NULL;
    }
    m_rowcount=0;
}


// Field:: DataTypes QueryResult::toEDYType (field_types mysqltype)const{
//     switch (mysqltype){
//         case FIELD_TYPE_TIMESTAMP:
//         case FIELD_TYPE_DATE:
//         case FIELD_TYPE_TIME:
//         case FIELD_TYPE_DATETIME:
//         case FIELD_TYPE_YEAR:
//         case FIELD_TYPE_STRING:
//         case FIELD_TYPE_VAR_STRING:
//         case FIELD_TYPE_BLOB:
//         case FIELD_TYPE_SET:
//         case FIELD_TYPE_NULL:
//             return Field::EDY_TYPE_STRING;
//         case FIELD_TYPE_TINY:
//         case FIELD_TYPE_SHORT:
//         case FIELD_TYPE_LONG:
//         case FIELD_TYPE_LONGLONG:
//         case FIELD_TYPE_INT24:
//         case FIELD_TYPE_ENUM:
//             return Field::EDY_TYPE_INTEGER;

//         case FIELD_TYPE_DECIMAL:
//         case FIELD_TYPE_FLOAT:
//         case FIELD_TYPE_DOUBLE:
//             return Field::EDY_TYPE_FLOAT;
//         default:
//             return Field::EDY_TYPE_NONE;
//      }
//      return Field::EDY_TYPE_NONE;
// }