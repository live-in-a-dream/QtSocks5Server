#include "DataEncry.h"

DataEncry::DataEncry()
{

}


/**
  初始化
 * @brief DataEncry::Init
 * @param argc
 * @param argv
 */
void DataEncry::Init(int argc, char *argv[]){
    for(int i=0;i<argc;i++){
        QString p(argv[i]);
        //是否aes加密
        if(p.contains("-aes")){
            isAes = true;
            qWarning()<<"-aes:"<<isAes;
        }
        //加密方式qaesEncry
        if(p.contains("-qaesEncry=")){
            qaesEncry = (QAESEncryption::Aes)p.split("=")[1].toInt();
            qWarning()<<"qaesEncry:"<<qaesEncry;
        }
        //加密方式qaesMode
        if(p.contains("-qaesMode=")){
            qaesMode = (QAESEncryption::Mode)p.split("=")[1].toInt();
            qWarning()<<"qaesMode:"<<qaesMode;
        }
        //加密方式authmode
        if(p.contains("-qaesPadding=")){
            qaesPadding = (QAESEncryption::Padding)p.split("=")[1].toInt();
            qWarning()<<"qaesPadding:"<<qaesPadding;
        }
    }
}
