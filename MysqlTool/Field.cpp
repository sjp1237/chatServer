#include"Field.h"

Field::Field():
m_isnull(true),m_type(EDY_TYPE_NONE)
{
    
}

Field::~Field(){}



void Field::SetValue(const char* value,size_t nLen){
    if (value ==NULL||(nLen==0)){
        m_isnull = true;
        m_value.clear() 
        ;return;
  
    }
    m_value.resize(nLen) ;
    memcpy ((char*)m_value.c_str(), value,nLen) ;
    m_isnull=false;

}