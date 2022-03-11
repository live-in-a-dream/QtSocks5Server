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
    //配置文件
    QSettings *setting = new QSettings(ininame,QSettings::IniFormat);
    Param::config->httpS=setting->value("config/HttpS").toString();
    Param::config->serverIp=setting->value("config/serverIp").toString();
    Param::config->serverPort=setting->value("config/serverPort").toInt();
    Param::config->networkCard=setting->value("config/networkCard").toString();
    Param::config->port=setting->value("config/port").toInt();
    Param::config->authMode=(Socks5AuthEnum)setting->value("config/authMode").toInt();
    Param::config->isLog=setting->value("config/isLog").toBool();
    Param::config->httpS = Param::config->httpS == "" ?"http":Param::config->httpS;

    //DataEncry
    Param::dataEncry->isAes=setting->value("DataEncry/isAes").toBool();
    Param::dataEncry->qaesEncry=(QAESEncryption::Aes)setting->value("DataEncry/qaesEncry").toInt();
    Param::dataEncry->qaesMode=(QAESEncryption::Mode)setting->value("DataEncry/qaesMode").toInt();
    Param::dataEncry->qaesPadding=(QAESEncryption::Padding)setting->value("DataEncry/qaesPadding").toInt();
    Param::dataEncry->qaesKey=setting->value("DataEncry/qaesKey").toString();
    Param::dataEncry->qaesDeviation=setting->value("DataEncry/qaesDeviation").toString();

    delete setting;
}




