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
#include "param.h"
class Socks5AuthStateed : public QObject
{
    Q_OBJECT
public:
    explicit Socks5AuthStateed(QObject *parent = nullptr);

    qint8 version;

    qint8 command;

    qint8 rsv;

    qint8 addressType;

    QHostAddress address;

    qint16 port;

    QHostAddress outAddress;

    /**
     * 解析socks5客户端数据
     * @brief parse
     * @param byte
     * @param error
     */
    void parse(QByteArray& byte,QString& error);

    /**
      返回socks5成功数据
     * @brief toByte
     * @param ip
     * @param port
     * @return
     */
    QByteArray toByte(QHostAddress ip,qint16 port);
signals:

public slots:
    /**
      客户端发送的数据接受槽
     * @brief authStateedSocks5
     */
    void authStateedSocks5();

};

#endif // SOCKS5AUTHSTATEED_H
