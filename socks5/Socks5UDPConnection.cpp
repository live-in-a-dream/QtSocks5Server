#include "Socks5UDPConnection.h"

Socks5UDPConnection::Socks5UDPConnection(QObject *parent) : QObject(parent)
{
    setObjectName("Socks5UDPConnection");
    remtoSocket = (QUdpSocket *)parent;
}

/**
  运行
 * @brief Run
 */
void Socks5UDPConnection::Run(){
    QTcpSocket * localSocket = (QTcpSocket *)remtoSocket->parent();

    connect(remtoSocket,SIGNAL(disconnected()),this,SLOT(udpRemtoSocks5Disconnected()));
    connect(localSocket,SIGNAL(readyRead()),this,SLOT(udpSocks5ReadyRead()));
    connect(remtoSocket,SIGNAL(readyRead()),this,SLOT(remtoSocketReadyRead()));
    connect(remtoSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(udpSocketError(QAbstractSocket::SocketError)));

    Socks5AuthStateed * socks5AuthStateed = localSocket->findChild<Socks5AuthStateed*>("Socks5AuthStateed");

    //绑定
    if(socks5AuthStateed->outAddress.toString() != "0.0.0.0"){
        //linux
        //ip address add 192.168.1.254/24 dev eth0
        QString strCmd = QString("ip address add %1/24 dev %2").arg(
                    socks5AuthStateed->outAddress.toString()).arg(Param::config->networkCard) ;
        QProcess::startDetached(strCmd);

        remtoSocket->bind(socks5AuthStateed->outAddress);
    }else{
        remtoSocket->bind(QHostAddress::Any);
    }

    qWarning()<<this<<"UDP:"<<remtoSocket->localAddress().toString()<<"---"<<remtoSocket->localPort();

    QByteArray buff = socks5AuthStateed->toByte(remtoSocket->peerAddress(),remtoSocket->peerPort());
    localSocket->write(buff,buff.length());
    localSocket->waitForBytesWritten();
}

/**
  UDP读取数据
 * @brief udpSocks5ReadyRead
 */
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

/**
  远程UDP读取
 * @brief remtoSocketReadyRead
 */
void Socks5UDPConnection::remtoSocketReadyRead(){
    QUdpSocket * remtoSocket = (QUdpSocket *)sender();

    QTcpSocket * localSocket = (QTcpSocket *)remtoSocket->parent();

    QByteArray byte;
    byte.reserve(remtoSocket->pendingDatagramSize());
    remtoSocket->readDatagram(byte.data(),byte.size());

    localSocket->write(byte,byte.length());
    localSocket->waitForBytesWritten();
}

/**
  UDP错误
 * @brief udpSocketError
 */
void Socks5UDPConnection::udpSocketError(QAbstractSocket::SocketError error){
    QUdpSocket * remtoSocket = (QUdpSocket *)sender();
    qWarning()<<this<<error;
    remtoSocket->disconnected();
}

/**
  远程UDP断开连接
 * @brief udpSocks5Disconnected
 */
void Socks5UDPConnection::udpRemtoSocks5Disconnected(){
    QUdpSocket * remtoSocket = (QUdpSocket *)sender();

    remtoSocket->deleteLater();
}
