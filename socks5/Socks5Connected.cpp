#include "Socks5Connected.h"

Socks5Connected::Socks5Connected(QObject *parent) : QObject(parent)
{
    setObjectName("Socks5Connected");
    remtoSocket = (QTcpSocket *) parent;
}

/**
  运行
 * @brief Run
 */
void Socks5Connected::Run(){
    QTcpSocket * localSocket = (QTcpSocket *)remtoSocket->parent();

    Socks5AuthStateed * socks5AuthStateed = localSocket->findChild<Socks5AuthStateed*>("Socks5AuthStateed");

    connect(localSocket,SIGNAL(readyRead()),this,SLOT(connectSocks5ReadyRead()));
    connect(remtoSocket,SIGNAL(disconnected()),this,SLOT(connectRemtoSocks5Disconnected()));
    connect(remtoSocket,SIGNAL(readyRead()),this,SLOT(remtoSocketReadyRead()));
    connect(remtoSocket,SIGNAL(connected()),this,SLOT(remtoSocketConnected()));
    connect(remtoSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(remtoSocketError(QAbstractSocket::SocketError)));

    //绑定
    if(socks5AuthStateed->outAddress.toString() != "0.0.0.0"){
        //linux
        //ip address add 192.168.1.254/24 dev eth0
        QString strCmd = QString("ip address add %1/24 dev %2").arg(
                    socks5AuthStateed->outAddress.toString()).arg(Param::config->networkCard);
        QProcess::startDetached(strCmd);

        remtoSocket->bind(socks5AuthStateed->outAddress);
    }
    //连接
    remtoSocket->connectToHost(socks5AuthStateed->address,socks5AuthStateed->port);
}

/**
  TCP读取数据
 * @brief connectSocks5ReadyRead
 */
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

/**
  远程TCP断开连接
 * @brief connectSocks5Disconnected
 */
void Socks5Connected::connectRemtoSocks5Disconnected(){
    QTcpSocket * remtoSocket = (QTcpSocket *)sender();

    remtoSocket->deleteLater();
}

/**
  远程TCP连接成功
 * @brief remtoSocketConnected
 */
void Socks5Connected::remtoSocketConnected(){
    QTcpSocket * remtoSocket = (QTcpSocket *)sender();

    qWarning()<<"TCP:"<<remtoSocket->localAddress().toString()<<"---"<<remtoSocket->localPort();

    QTcpSocket * localSocket = (QTcpSocket *)remtoSocket->parent();

    Socks5AuthStateed * socks5AuthStateed = localSocket->findChild<Socks5AuthStateed*>("Socks5AuthStateed");

    QByteArray buff = socks5AuthStateed->toByte(remtoSocket->peerAddress(),remtoSocket->peerPort());
    localSocket->write(buff,buff.length());
    localSocket->waitForBytesWritten();
}

/**
  远程TCP读取数据
 * @brief remtoSocketReadyRead
 */
void Socks5Connected::remtoSocketReadyRead(){
    QTcpSocket * remtoSocket = (QTcpSocket *)sender();

    QTcpSocket * localSocket = (QTcpSocket *)remtoSocket->parent();

    QByteArray byte = remtoSocket->readAll();

    localSocket->write(byte,byte.length());
    localSocket->waitForBytesWritten();
}

/**
  远程TCP错误
 * @brief remtoSocketError
 */
void Socks5Connected::remtoSocketError(QAbstractSocket::SocketError error){
    QTcpSocket * remtoSocket = (QTcpSocket *)sender();
    qWarning()<<this<<error;
    remtoSocket->disconnected();
}
