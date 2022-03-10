#ifndef SOCKS5AUTHSTATEED_H
#define SOCKS5AUTHSTATEED_H

#include <QObject>
#include "qtcpserver.h"
#include "qtcpsocket.h"
#include "QUdpSocket"
#include <QPointer>
#include "Socks5UDPConnection.h"
#include "Socks5Connected.h"
#include "QDataStream"
#include "QHostInfo"
#include "QProcess"
class Socks5AuthStateed : public QObject
{
    Q_OBJECT
public:
    explicit Socks5AuthStateed(QObject *parent = nullptr);

    enum SocksVersion
    {
       SOCKS5 = 0x05,
       SOCKS4 = 0x04
    };

    enum Socks5Command
    {
        Connect = 0x01,
        Bind = 0x02,
        UDPAssociate = 0x03
    };


    qint8 version;

    qint8 command;

    qint8 rsv;

    qint8 addressType;

    QHostAddress address;

    qint16 port;

    QHostAddress outAddress;

    void parse(QByteArray& byte,QString& error);

    QByteArray toByte(QHostAddress ip,qint16 port);
signals:

public slots:

    void connectSocks5Disconnected();
    void udpSocks5Disconnected();
    void authStateedSocks5();

};

#endif // SOCKS5AUTHSTATEED_H
