#include "Socks5AuthState.h"

Socks5AuthState::Socks5AuthState(QObject *parent) : QObject(parent)
{
    setObjectName("Socks5AuthState");
}


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

    if(!methods.contains(SocksAuthEnum::USERPASS) && !methods.contains(SocksAuthEnum::NOT_AUTH)){
        qWarning()<<"不支持其他加密方式:"<<version;
        return;
    }

    //
    QByteArray buff;

    if(Param::authMode == SocksAuthEnum::NOT_AUTH){
        buff = toByte(SocksAuthEnum::NOT_AUTH);

        Socks5AuthStateed * socks5AuthStateed = new Socks5AuthStateed(localSocket);

        connect(localSocket,SIGNAL(readyRead()),socks5AuthStateed,SLOT(authStateedSocks5()));
    }
    //用户密码验证
    else if(Param::authMode == SocksAuthEnum::USERPASS){
        buff = toByte(SocksAuthEnum::USERPASS);

        Socks5AuthStateUser * socks5AuthStateUser = new Socks5AuthStateUser(localSocket);

        connect(localSocket,SIGNAL(readyRead()),socks5AuthStateUser,SLOT(authStateUserSocks5()));
    }
    //发送
    localSocket->write(buff,buff.length());
    localSocket->waitForBytesWritten();
}

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


QByteArray Socks5AuthState::toByte(SocksAuthEnum socksAuthEnum){
    QByteArray byte;
    byte.append((char)version);
    byte.append((char)socksAuthEnum);
    return byte;
}
