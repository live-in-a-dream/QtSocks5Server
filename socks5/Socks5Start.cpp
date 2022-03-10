#include "Socks5Start.h"


Socks5Start::Socks5Start(QObject *parent) : QObject(parent)
{

}

void Socks5Start::start(qint16 port){
    server = new QTcpServer;

    if(!server->listen(QHostAddress::Any,port)){
        qWarning()<<"监听失败";
        return;
    }
    qWarning()<<"开始监听:"<<port;

    connect(server,SIGNAL(newConnection()),this,SLOT(listingSocks5Connect()));
}


void Socks5Start::listingSocks5Connect(){
    QTcpServer * server = (QTcpServer *)sender();
    if(!server->hasPendingConnections()){
        qWarning()<<"没有连接";
    }

    QTcpSocket * localSocket = server->nextPendingConnection();

    Socks5AuthState * socks5AuthState = new Socks5AuthState(localSocket);
    //销毁
    connect(localSocket,SIGNAL(disconnected()),this,SLOT(localSocketDisconnected()));
    //
    connect(localSocket,SIGNAL(readyRead()),socks5AuthState,SLOT(authStateSocks5()));
}

void Socks5Start::localSocketDisconnected(){
    QTcpSocket * localSocket = (QTcpSocket *)sender();

    QList<QObject*> objs = localSocket->findChildren<QObject*>();

    for(int i=0;i<objs.size();i++){
        objs.at(i)->deleteLater();
    }

    localSocket->deleteLater();
}
