#include "Socks5UDPConnection.h"

Socks5UDPConnection::Socks5UDPConnection(QObject *parent) : QObject(parent)
{

}

void Socks5UDPConnection::udpSocks5ReadyRead(){
    QTcpSocket * localSocket = (QTcpSocket *)sender();

    Socks5AuthStateed * socks5AuthStateed = localSocket->findChild<Socks5AuthStateed*>("Socks5AuthStateed");

    QString socketName = socks5AuthStateed->address.toString()
                        +QString::number(socks5AuthStateed->port)
                        +socks5AuthStateed->outAddress.toString();
    QUdpSocket * remtoSocket = localSocket->findChild<QUdpSocket*>(socketName);

    QByteArray byte = localSocket->readAll();

    remtoSocket->writeDatagram(byte,byte.length(),socks5AuthStateed->address,socks5AuthStateed->port);
}

void Socks5UDPConnection::remtoSocketReadyRead(){
    QUdpSocket * remtoSocket = (QUdpSocket *)sender();

    QTcpSocket * localSocket = (QTcpSocket *)remtoSocket->parent();

    QByteArray byte;
    byte.reserve(remtoSocket->pendingDatagramSize());
    remtoSocket->readDatagram(byte.data(),byte.size());

    localSocket->write(byte,byte.length());
    localSocket->waitForBytesWritten();
}

void Socks5UDPConnection::udpSocks5Disconnected(){
    QUdpSocket * remtoSocket = (QUdpSocket *)sender();

    remtoSocket->deleteLater();
}
