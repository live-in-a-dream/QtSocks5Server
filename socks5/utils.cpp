#include "utils.h"
Utils *Utils::m_instance = 0;
Utils::Utils()
{

}

//判断字符串是空和空串
bool isEmptySting(QString str){
    if(str.isEmpty() || str == ""){
        return  true;
    }
    return false;
}

//是否是纯数值
bool isDigitString(QString src) {
    QRegExp RegExp("[0-9]+");
    return RegExp.exactMatch(src);
}

//是否是IP
bool IsIP(QString IP)
{
    QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return RegExp.exactMatch(IP);
}

//获取当前时间
QString getCurrDateTime(){
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    return current_date;
}



void Utils::ReadIni(){
    //测试配置文件
    QSettings *setting = new QSettings(ininame,QSettings::IniFormat);
    Param::httpS=setting->value("server/HttpS").toString();
    Param::serverIp=setting->value("server/ip").toString();
    Param::serverPort=setting->value("server/port").toString();
    Param::networkCard=setting->value("networkCard").toString();
    //协议
    Param::httpS = Param::httpS == "" ?"http":Param::httpS;
    //默认端口不需要加端口号
    if(Param::serverPort == "80" || Param::serverPort == "443"){
        //域名
        Param::domain = Param::httpS+"://"+Param::serverIp;
    }else{
        //域名
        Param::domain =Param::httpS+"://"+Param::serverIp+":"+Param::serverPort;
    }
    delete setting;
}

