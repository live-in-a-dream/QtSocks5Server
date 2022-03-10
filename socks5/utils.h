#ifndef UTILS_H
#define UTILS_H

#include "QString"
#include "QList"
#include "param.h"
#include "QSettings"
#include "QMutex"
#include "QJsonDocument"
#include "QJsonObject"
#include "qdebug.h"
#include "QFile"
#include "QDir"
#include "QCoreApplication"
#include "QProcess"
#include "QCryptographicHash"
#include "qt_windows.h"
#include "QProcess"
#include <tlhelp32.h>
#include "qt_windows.h"
#include <Psapi.h>
#include "QDateTime"
//端口号取值范围【0-65535】，其中1023以前预留给了常用应用程序
//一般在1024之后取端口号
#define PORT_DOWN 1024	//起始端口号
#define PORT_UP 65535	//终止端口号

//判断字符串是空和空串
bool isEmptySting(QString str);
//是否是纯数值
bool isDigitString(QString src);
//是否是IP
bool IsIP(QString IP);
//获取当前时间
QString getCurrDateTime();


class Utils
{
public:
    Utils();

    static Utils* Instance()
    {
        static QMutex mutex;
        if (!m_instance) {
            QMutexLocker locker(&mutex);
            if (!m_instance)
                m_instance = new Utils;
        }

        return m_instance;
    }

    //读取配置文件
    void ReadIni();

private:
    //开发环境
    #ifdef Qt_DEV
        QString ininame = "host-dev.ini";
    #endif
    //测试环境
    #ifdef Qt_TEST
        QString ininame = "host-test.ini";
    #endif
    //生产环境
    #ifdef Qt_PROD
        QString ininame = "host-prod.ini";
    #endif

    static Utils* m_instance;
};

#endif // UTILS_H
