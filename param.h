#ifndef PARAM_H
#define PARAM_H

#include "QObject"
#include "qDebug"
#include "QString"
#include "DataEncry.h"
#include "Config.h"
#include "Enum.h"

class Param
{
public:
    Param() {}

    /**
      基本配置
     * @brief config
     */
    static Config* config;

    /**
      数据加密方式
     * @brief dataEncry
     */
    static DataEncry* dataEncry;


    //初始化
    static void Init(int argc, char *argv[]);

};


#endif // PARAM_H
