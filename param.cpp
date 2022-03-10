#include "param.h"


int Param::port = 8888;

QString Param::user = "admin";

QString Param::pass = "123456";

/**
  网卡
 * @brief networkCard
 */
QString Param::networkCard = "eth0";
/**
   服务IP
 * @brief serverIp
 */
QString Param::serverIp = "127.0.0.1";
/**
  服务端口
 * @brief serverPort
 */
QString Param::serverPort = 0;
/**
  Http|Https
 * @brief httpS
 */
QString Param::httpS = "http";
/**
  网址路径
 * @brief httpS
 */
QString Param::domain = "";

/**
  Log日志是否输出
 * @brief isLog
 */
bool Param::isLog  = true;
