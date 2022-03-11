#include "Socks5AuthState.h"

Socks5AuthState::Socks5AuthState(QObject *parent) : QObject(parent)
{
    setObjectName("Socks5AuthState");
}

/**
  认证最后一步的数据接受
 * @brief authStateSocks5
 */
void Socks5AuthState::authStateSocks5(){
    QTcpSocket * localSocket = (QTcpSocket *)sender();

    disconnect(localSocket,SIGNAL(readyRead()),this,SLOT(authStateSocks5()));

    QByteArray byte = localSocket->readAll();

    qWarning()<<"协议:"<<byte;

    QString error;
    parse(byte,error);

    if(!error.isEmpty()){
        qDebug()<<"authStateSocks5:"<<error;
        return;
    }
    if(version != SocksVersion::SOCKS5){
        qWarning()<<"不支持其他协议:"<<version;
        return;
    }

    if(!methods.contains(Socks5AuthEnum::USERPASS) && !methods.contains(Socks5AuthEnum::NOT_AUTH)){
        qWarning()<<"不支持其他加密方式:"<<version;
        return;
    }

    //
    QByteArray buff;

    if(Param::config->authMode == Socks5AuthEnum::NOT_AUTH){
        buff = toByte(Socks5AuthEnum::NOT_AUTH);

        Socks5AuthStateed * socks5AuthStateed = new Socks5AuthStateed(localSocket);

        connect(localSocket,SIGNAL(readyRead()),socks5AuthStateed,SLOT(authStateedSocks5()));
    }
    //用户密码验证
    else if(Param::config->authMode == Socks5AuthEnum::USERPASS){
        buff = toByte(Socks5AuthEnum::USERPASS);

        Socks5AuthStateUser * socks5AuthStateUser = new Socks5AuthStateUser(localSocket);

        connect(localSocket,SIGNAL(readyRead()),socks5AuthStateUser,SLOT(authStateUserSocks5()));
    }
    //发送
    localSocket->write(buff,buff.length());
    localSocket->waitForBytesWritten();
}

/**
 * 解析socks5客户端数据
 * @brief parse
 * @param byte
 * @param error
 */
void Socks5AuthState::parse(QByteArray& byte,QString& error){
    if(byte.length() < 3){
        error = "协议长度不正确";
        return;
    }

    version = byte[0];

    methodsCount = byte[1];

    for(int i=0;i<methodsCount;i++){
        methods.append(byte[2+i]);
    }
}

/**
  返回socks5成功数据
 */
QByteArray Socks5AuthState::toByte(Socks5AuthEnum socksAuthEnum){
    QByteArray byte;
    byte.append((char)version);
    byte.append((char)socksAuthEnum);
    return byte;
}
