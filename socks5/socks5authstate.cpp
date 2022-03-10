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

    if(!methods.contains(0x02) && methods.contains(0x00)){
        qWarning()<<"不支持其他加密方式:"<<version;
        return;
    }

    Socks5AuthStateUser * socks5AuthStateUser = new Socks5AuthStateUser(localSocket);

    connect(localSocket,SIGNAL(readyRead()),socks5AuthStateUser,SLOT(authStateUserSocks5()));

    //发送
    QByteArray buff = toByte();
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


QByteArray Socks5AuthState::toByte(){
    QByteArray byte;
    byte.append((char)0x05);
    byte.append((char)0x02);
    return byte;
}
