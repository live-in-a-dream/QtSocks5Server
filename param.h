#ifndef PARAM_H
#define PARAM_H

#include "QObject"

class Param
{
public:
    Param() {}
    /**
      监听端口号
     * @brief port
     */
    static int port;
    /**
      用户名
     * @brief user
     */
    static QString user;
    /**
      密码
     * @brief pass
     */
    static QString pass;
    /**
      网卡
     * @brief networkCard
     */
    static QString networkCard;
    /**
       服务IP
     * @brief serverIp
     */
    static QString serverIp;
    /**
      服务端口
     * @brief serverPort
     */
    static QString serverPort;
    /**
      Http|Https
     * @brief httpS
     */
    static QString httpS;

    /**
      网址路径
     * @brief httpS
     */
    static QString domain;

    /**
      Log日志是否输出
     * @brief isLog
     */
    static bool isLog;

};


#endif // PARAM_H
