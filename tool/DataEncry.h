#ifndef DATAENCRY_H
#define DATAENCRY_H
#include "QAESEncryption.h"
#include "qDebug"
class DataEncry
{
public:
    DataEncry();

    /**
      是否开启AES加密
     * @brief aes
     */
    bool isAes = false;

    /**
      AES加密方式 Aes
     * @brief aes
     */
    QAESEncryption::Aes qaesEncry = QAESEncryption::Aes::AES_128;

    /**
      AES加密方式 Mode
     * @brief aes
     */
    QAESEncryption::Mode qaesMode = QAESEncryption::Mode::ECB;

    /**
      AES加密方式 Padding
     * @brief aes
     */
    QAESEncryption::Padding qaesPadding = QAESEncryption::Padding::PKCS7;

    /**
      初始化
     * @brief DataEncry::Init
     * @param argc
     * @param argv
     */
    void Init(int argc, char *argv[]);
};

#endif // DATAENCRY_H
