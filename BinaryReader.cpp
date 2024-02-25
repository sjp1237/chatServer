#include"BinaryReader.h"



BinaryReader& BinaryReader::operator=(const BinaryReader& reader){
    if(this!=&reader){
        m_buffer=reader.m_buffer;
        m_index=reader.m_index;
    }

    return *this;
}


template<class T>
bool BinaryReader::ReadData(T& data){
    if(m_index+sizeof(T)>m_buffer.size())return false;
    memcpy(&data,m_buffer.c_str()+m_index,sizeof(T));

    m_index+=sizeof(T);
    return true;
}


