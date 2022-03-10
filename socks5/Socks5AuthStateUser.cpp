#include "Socks5AuthStateUser.h"

Socks5AuthStateUser::Socks5AuthStateUser(QObject *parent) : QObject(parent)
{
    setObjectName("Socks5AuthStateUser");
}

/**
  用户认证的客户端接受数据
 * @brief authStateUserSocks5
 */
void Socks5AuthStateUser::authStateUserSocks5(){
    QTcpSocket * localSocket = (QTcpSocket *)sender();

    disconnect(localSocket,SIGNAL(readyRead()),this,SLOT(authStateUserSocks5()));

    QByteArray byte = localSocket->readAll();

//    qWarning()<<"用户认证:"<<byte;

    QString error;
    parse(byte,error);

    if(!error.isEmpty()){
        qDebug()<<"authStateUserSocks5:"<<error;
        return;
    }

    if(version != 0x01){
        qDebug()<<"authStateUserSocks5:"<<"协议错误:"<<version;
        return;
    }

    if(user != Param::user || password != Param::pass){
        qDebug()<<"authStateUserSocks5:"<<"用户密码错误";
        return;
    }

//    if(user != "1" || password != "1"){
//        qDebug()<<"authStateUserSocks5:"<<"用户密码错误:";
//        localSocket->disconnected();
//        return;
//    }

    Socks5AuthStateed * socks5AuthStateed = new Socks5AuthStateed(localSocket);

    connect(localSocket,SIGNAL(readyRead()),socks5AuthStateed,SLOT(authStateedSocks5()));

    QByteArray buff = toByte();
    localSocket->write(buff,buff.length());
    localSocket->waitForBytesWritten();
}

/**
 * 解析socks5客户端数据
 * @brief parse
 * @param byte
 * @param error
 */
void Socks5AuthStateUser::parse(QByteArray& byte,QString& error){
    if(byte.length() < 5){
        error = "用户认证长度不足";
        return;
    }

    version = byte[0];

    userLength = byte[1];

    if(userLength+2+1 > byte.length()){
        error = "用户长度不正确";
        return;
    }

    passLength = byte[userLength+2];

    if(userLength+2+1+passLength > byte.length()){
        error = "密码长度不正确";
        return;
    }

    for(int i=2;i<userLength+2;i++){
        user.append(byte[i]);
    }

    for(int i=2+userLength+1;i<2+userLength+1+passLength;i++){
        password.append(byte[i]);
    }

    qDebug()<<"用户密码:"<<user<<"---"<<password;
}

/**
  返回socks5成功数据
 */
QByteArray Socks5AuthStateUser::toByte(){
    QByteArray byte;
    byte.append((char)0x01);
    byte.append((char)0x00);
    return byte;
}
