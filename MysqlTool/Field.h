
#ifndef FIELD_H
#define FIELD_H

#include <mysql.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <errno.h>
#include <memory>
#include <cstdint>
#include <unistd.h>
#include<cstring>

using namespace std;
//#include "base/Logging.h"
class Field
{
public:
    typedef enum {
        EDY_TYPE_NONE = 0,
        EDY_TYPE_STRING,
        EDY_TYPE_INTEGER,
        EDY_TYPE_FLOAT,
        EDY_TYPE_BOOL
   }DataTypes;
public:
    Field();
    ~Field();
    void SetType (DataTypes tp) { m_type = tp; }
    DataTypes GetType () const { return m_type;}
    string GetString(){return m_value;}

    void SetName(const string& name) { m_name = name; }
    const string& GetName() { return m_name; }
    void SetValue(const char* value,size_t nLen);
     const string& GetValue() { return m_value; }
     bool isNu11()const { return m_isnull;}
     bool toBool()const{return atoi(m_value.c_str())!=0;}
    int8_t toInt8()const { return static_cast<int8_t>(atoi(m_value.c_str()));}
    uint8_t toUint8()const { return static_cast<uint8_t>(atoi(m_value.c_str()));}
    int32_t toInt32 ()const { return atoi(m_value.c_str());  }
    uint32_t toUint32()const { return (uint32_t)atoi(m_value.c_str());}
    uint64_t toInt64()const { return atoi(m_value.c_str());}
    uint64_t toUint64()const { return (uint64_t)atoi(m_value.c_str());}
    double toFloat () const { return atof(m_value.c_str());}

private:
    string m_value;
    string m_name;
    DataTypes m_type;
    bool m_isnull;//判断这个值是否为空
};

#endif // FIELD_H