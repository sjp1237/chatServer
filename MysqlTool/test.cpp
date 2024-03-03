// #include "MySQLTool.h"

// int main() {
//     MySQLTool mySQLTool;

//     // 修改以下信息为你的 MySQL 服务器信息
//     std::string host = "localhost";
//     std::string user = "root";
//     std::string passwd = "123456";
//     std::string db = "sjp";

//     if (!mySQLTool.connect(host, user, passwd, db)) {
//         std::cerr << "Connection failed!" << std::endl;
//         return 1;
//     }

//     // 执行查询语句
//     std::string querySql = "SELECT * FROM employees;";
//     uint32_t affectedCount = 0;
//     int errnoQuery = 0;
//      QueryResultPtr queryResult = mySQLTool.Query(querySql);

//     if (queryResult == nullptr) {
//         std::cerr << "Query failed! Error code: " << errnoQuery << std::endl;
//         return 1;
//     }

//     std::cout << "Query succeeded!" << std::endl;

//     // // 执行更新语句
//     std::string updateSql = "update employees set first_name='sjp' where employee_id=1;";
//     uint32_t affectedCountUpdate = 0;
//     int errnoUpdate = 0;

//     if (!mySQLTool.Execute(updateSql, affectedCountUpdate, errnoUpdate)) {
//         std::cerr << "Update failed! Error code: " << errnoUpdate << std::endl;
//         return 1;
//     }

//     // std::cout << "Update succeeded!" << std::endl;
//     // std::cout << "Affected rows: " << affectedCountUpdate << std::endl;

//     return 0;
// }




#include <iostream>
#include "MysqlManager.h"

int main() {
    MySqlManager mysqlManager;

    // 替换以下信息为你的数据库连接信息
    std::string host = "localhost";
    std::string user = "root";
    std::string passwd = "123456";
    std::string db = "sjp";
    const unsigned int port = 3306;

    if (mysqlManager.Init(host, user, passwd, db, port)) {
        std::cout << "Database initialization successful." << std::endl;

        stringstream sql;

        //生成查询表结构
        sql <<"select * from t_user";
        // 在这里可以调用其他接口进行进一步测试

        mysqlManager.Query(sql.str());

    } else {
        std::cout << "Database initialization failed." << std::endl;
    }

    return 0;
}