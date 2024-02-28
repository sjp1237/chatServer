#include "MySQLTool.h"

int main() {
    MySQLTool mySQLTool;

    // 修改以下信息为你的 MySQL 服务器信息
    std::string host = "localhost";
    std::string user = "root";
    std::string passwd = "password";
    std::string db = "testdb";

    if (!mySQLTool.connect(host, user, passwd, db)) {
        std::cerr << "Connection failed!" << std::endl;
        return 1;
    }

    // 执行查询语句
    std::string querySql = "SELECT * FROM your_table";
    uint32_t affectedCount = 0;
    int errnoQuery = 0;
    // QueryResultPtr queryResult = mySQLTool.Query(querySql, affectedCount, errnoQuery);

    // if (queryResult == nullptr) {
    //     std::cerr << "Query failed! Error code: " << errnoQuery << std::endl;
    //     return 1;
    // }

    // std::cout << "Query succeeded!" << std::endl;
    // std::cout << "Affected rows: " << affectedCount << std::endl;

    // // 执行更新语句
    // std::string updateSql = "UPDATE your_table SET your_column = 'new_value'";
    // uint32_t affectedCountUpdate = 0;
    // int errnoUpdate = 0;

    // if (!mySQLTool.Execute(updateSql, affectedCountUpdate, errnoUpdate)) {
    //     std::cerr << "Update failed! Error code: " << errnoUpdate << std::endl;
    //     return 1;
    // }

    // std::cout << "Update succeeded!" << std::endl;
    // std::cout << "Affected rows: " << affectedCountUpdate << std::endl;

    return 0;
}

