#ifndef PARAM_H
#define PARAM_H

#include "QObject"
#include "qDebug"
#include "QString"

/**
  socks版本
 * @brief The SocksVersion enum
 */
enum SocksVersion
{
   SOCKS5 = 0x05,
   SOCKS4 = 0x04
};

/**
  socks5认证方式
 * @brief The SocksAuthEnum enum
 */
enum Socks5AuthEnum
{
    NOT_AUTH = 0x00,
    GSSAPI = 0x01,
    USERPASS = 0x02
};

/**
  socks5命令
 * @brief The Socks5Command enum
 */
enum Socks5Command
{
    Connect = 0x01,
    Bind = 0x02,
    UDPAssociate = 0x03
};

/**
  socks5地址类型
 * @brief The Socks5Command enum
 */
enum Socks5AddressType
{
    IPV4 = 0x01,
    Domain = 0x03,
    IPV6 = 0x04
};


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
      认证方式 1无需认证 2需要认证用户密码
     * @brief isLog
     */
    static Socks5AuthEnum authMode;

    /**
      Log日志是否输出
     * @brief isLog
     */
    static bool isLog;






    //初始化
    static void Init(int argc, char *argv[]);

};


#endif // PARAM_H
