#include "Socks5Start.h"


Socks5Start::Socks5Start(QObject *parent) : QObject(parent)
{

}

/**
  启动运行
 * @brief start
 * @param port
 */
void Socks5Start::start(qint16 port){
    server = new QTcpServer;

    if(!server->listen(QHostAddress::Any,port)){
        qWarning()<<"监听失败";
        return;
    }
    qWarning()<<"开始监听:"<<port;

    connect(server,SIGNAL(newConnection()),this,SLOT(listingSocks5Connect()));
}

/**
  监听连接
 * @brief listingSocks5Connect
 */
void Socks5Start::listingSocks5Connect(){
    QTcpServer * server = (QTcpServer *)sender();
    if(!server->hasPendingConnections()){
        qWarning()<<"没有连接";
    }

    QTcpSocket * localSocket = server->nextPendingConnection();

    Socks5AuthState * socks5AuthState = new Socks5AuthState(localSocket);
    //销毁
    connect(localSocket,SIGNAL(disconnected()),this,SLOT(localSocketDisconnected()));
    //读取
    connect(localSocket,SIGNAL(readyRead()),socks5AuthState,SLOT(authStateSocks5()));
    //错误
    connect(localSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(localSocketError(QAbstractSocket::SocketError)));
}

/**
  连接断开
 * @brief localSocketDisconnected
 */
void Socks5Start::localSocketDisconnected(){
    QTcpSocket * localSocket = (QTcpSocket *)sender();

    localSocket->deleteLater();
}

/**
  连接错误
 * @brief localSocketError
 * @param error
 */
void Socks5Start::localSocketError(QAbstractSocket::SocketError error){
    QTcpSocket * localSocket = (QTcpSocket *)sender();
    qWarning()<<this<<error;
    localSocket->disconnected();
}
