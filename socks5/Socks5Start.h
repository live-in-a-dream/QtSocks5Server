#ifndef SOCKS5START_H
#define SOCKS5START_H

#include <QObject>
#include "qtcpserver.h"
#include "qtcpsocket.h"
#include <QPointer>
#include "Socks5AuthState.h"
#include "param.h"


class Socks5Start : public QObject
{
    Q_OBJECT
public:
    explicit Socks5Start(QObject *parent = nullptr);

    /**
      启动运行
     * @brief start
     * @param port
     */
    void start(qint16 port);

private:
    QTcpServer* server;
signals:

public slots:
    /**
      监听连接
     * @brief listingSocks5Connect
     */
    void listingSocks5Connect();

    /**
      连接断开
     * @brief localSocketDisconnected
     */
    void localSocketDisconnected();

    /**
      连接错误
     * @brief localSocketError
     * @param error
     */
    void localSocketError(QAbstractSocket::SocketError error);
};

#endif // SOCKS5START_H
