#ifndef SOCKS5UDPCONNECTION_H
#define SOCKS5UDPCONNECTION_H

#include <QObject>
#include "qtcpserver.h"
#include "qtcpsocket.h"
#include "Socks5AuthState.h"
#include "QUdpSocket"
#include "param.h"
class Socks5UDPConnection : public QObject
{
    Q_OBJECT
public:
    explicit Socks5UDPConnection(QObject *parent = nullptr);


signals:

public slots:
    void udpSocks5ReadyRead();
    void remtoSocketReadyRead();
    void udpSocks5Disconnected();
};

#endif // SOCKS5UDPCONNECTION_H
