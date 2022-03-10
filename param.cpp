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
  认证方式 1无需认证 2需要认证用户密码
 * @brief isLog
 */
SocksAuthEnum Param::authMode  = SocksAuthEnum::USERPASS;

/**
  Log日志是否输出
 * @brief isLog
 */
bool Param::isLog  = true;




void Param::Init(int argc, char *argv[]){
    for(int i=0;i<argc;i++){
        QString p(argv[i]);
        //端口
        if(p.contains("-port=") || p.contains("-p=")){
            Param::port = p.split("=")[1].toInt();
            qWarning()<<"port:"<<Param::port;
        }
        //用户名
        if(p.contains("-username=")||p.contains("-u=")){
            Param::user = p.split("=")[1];
            qWarning()<<"username:"<<Param::user;
        }
        //密码
        if(p.contains("-passwd=")||p.contains("-pwd=")){
            Param::pass = p.split("=")[1];
            qWarning()<<"passwd:"<<Param::pass;
        }
        //认证方式
        if(p.contains("-authmode=")||p.contains("-amode=")){
            Param::authMode = p.split("=")[1].toInt();
            qWarning()<<"passwd:"<<Param::authMode;
        }
        //打印日志在txt文本
        Param::isLog = p.contains("-log")?true:false;
        qWarning()<<"isLog:"<<Param::isLog;
    }
}
