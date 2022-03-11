#include "param.h"

/**
  基本配置
 * @brief config
 */
Config* Param::config = new Config;
/**
  数据加密
 * @brief dataEncry
 */
DataEncry* Param::dataEncry = new DataEncry;


void Param::Init(int argc, char *argv[]){
    Param::config->Init(argc,argv);
    Param::dataEncry->Init(argc,argv);
}
