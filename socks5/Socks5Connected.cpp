#include "Socks5Connected.h"

Socks5Connected::Socks5Connected(QObject *parent) : QObject(parent)
{
    setObjectName("Socks5Connected");
}

void Socks5Connected::connectSocks5ReadyRead(){
    QTcpSocket * localSocket = (QTcpSocket *)sender();

    Socks5AuthStateed * socks5AuthStateed = localSocket->findChild<Socks5AuthStateed*>("Socks5AuthStateed");

    QString socketName = socks5AuthStateed->address.toString()
                        +QString::number(socks5AuthStateed->port)
                        +socks5AuthStateed->outAddress.toString();

    QTcpSocket * remtoSocket = localSocket->findChild<QTcpSocket*>(socketName);

    QByteArray byte = localSocket->readAll();

    remtoSocket->write(byte,byte.length());
    remtoSocket->waitForBytesWritten();
}

void Socks5Connected::remtoSocketConnected(){
    QTcpSocket * remtoSocket = (QTcpSocket *)sender();

    qWarning()<<"TCP:"<<remtoSocket->localAddress().toString()<<"---"<<remtoSocket->localPort();

    QTcpSocket * localSocket = (QTcpSocket *)remtoSocket->parent();

    Socks5AuthStateed * socks5AuthStateed = localSocket->findChild<Socks5AuthStateed*>("Socks5AuthStateed");

    QByteArray buff = socks5AuthStateed->toByte(remtoSocket->peerAddress(),remtoSocket->peerPort());
    localSocket->write(buff,buff.length());
    localSocket->waitForBytesWritten();
}


void Socks5Connected::remtoSocketReadyRead(){
    QTcpSocket * remtoSocket = (QTcpSocket *)sender();

    QTcpSocket * localSocket = (QTcpSocket *)remtoSocket->parent();

    QByteArray byte = remtoSocket->readAll();

    localSocket->write(byte,byte.length());
    localSocket->waitForBytesWritten();
}
