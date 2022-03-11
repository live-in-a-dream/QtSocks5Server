#include "Config.h"

Config::Config()
{

}

/**
  初始化
 * @brief DataEncry::Init
 * @param argc
 * @param argv
 */
void Config::Init(int argc, char *argv[]){
    for(int i=0;i<argc;i++){
        QString p(argv[i]);
        //端口
        if(p.contains("-port=") || p.contains("-p=")){
            port = p.split("=")[1].toInt();
            qWarning()<<"port:"<<port;
        }
        //用户名和密码
        if(p.contains("-user=")||p.contains("-u=")){
            QString user = p.split("=")[1];

            for(QString str:user.split(",")){
                QString u = str.split("::")[0];
                QString p = str.split("::")[1];
                userPass.insert(u,p);
                qWarning()<<"user:"<<u<<" pass:"<<p;
            }
        }
        //认证方式
        if(p.contains("-authmode=")||p.contains("-amode=")){
            authMode = (Socks5AuthEnum)p.split("=")[1].toInt();
            qWarning()<<"authMode:"<<authMode;
        }
        //打印日志在txt文本
        if(p.contains("-log")){
            isLog = true;
            qWarning()<<"isLog:"<<isLog;
        }

        //网卡名
        if(p.contains("-networkcard=")||p.contains("-nwcard=")){
            networkCard = p.split("=")[1];
            qWarning()<<"networkCard:"<<networkCard;
        }
        //远程IP
        if(p.contains("-serverip=")||p.contains("-sip=")){
            serverIp = p.split("=")[1];
            qWarning()<<"serverIp:"<<serverIp;
        }
        //远程端口
        if(p.contains("-serverport=")||p.contains("-sport=")){
            serverPort = p.split("=")[1].toInt();
            qWarning()<<"serverPort:"<<serverPort;
        }
        //https
        if(p.contains("-https")){
            httpS = "https";
            qWarning()<<"httpS:"<<httpS;
        }
    }
    //请求前缀
    if(serverPort == 80 || serverPort == 443){
        //域名
        domain = httpS+"://"+serverIp;
    }else{
        //域名
        domain = httpS+"://"+serverIp+":"+serverPort;
    }
    qWarning()<<"domain:"<<domain;
}
