#ifndef SOCKS5START_H
#define SOCKS5START_H

#include <QObject>
#include "qtcpserver.h"
#include "qtcpsocket.h"
#include <QPointer>
#include "Socks5AuthState.h"






class Socks5Start : public QObject
{
    Q_OBJECT
public:
    explicit Socks5Start(QObject *parent = nullptr);

    void start(qint16 port);

private:
    QTcpServer* server;
signals:

public slots:
    //监听连接
    void listingSocks5Connect();

    void localSocketDisconnected();
};

#endif // SOCKS5START_H
