#ifndef CONFIG_H
#define CONFIG_H
#include "QString"
#include "QMap"
#include "Enum.h"
#include "qDebug"
class Config
{
public:
    Config();
    /**
      监听端口号
     * @brief port
     */
    int port = 8888;
    /**
      用户名和密码
     * @brief user
     */
    QMap<QString,QString> userPass;
    /**
      认证方式 1无需认证 2需要认证用户密码
     * @brief isLog
     */
    Socks5AuthEnum authMode = Socks5AuthEnum::USERPASS;
    /**
      Log日志是否输出
     * @brief isLog
     */
    bool isLog = true;


    /**
      网卡
     * @brief networkCard
     */
    QString networkCard = "eth0";
    /**
       服务IP
     * @brief serverIp
     */
    QString serverIp = "127.0.0.1";
    /**
      服务端口
     * @brief serverPort
     */
    qint16 serverPort = 8080;
    /**
      Http|Https
     * @brief httpS
     */
    QString httpS = "http";

    /**
      网址路径
     * @brief httpS
     */
    QString domain = "";


    /**
      初始化
     * @brief DataEncry::Init
     * @param argc
     * @param argv
     */
    void Init(int argc, char *argv[]);
};

#endif // CONFIG_H
