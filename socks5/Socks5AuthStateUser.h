#ifndef SOCKS5AUTHSTATEUSER_H
#define SOCKS5AUTHSTATEUSER_H

#include <QObject>
#include "qtcpserver.h"
#include "qtcpsocket.h"
#include <QPointer>
#include "Socks5AuthStateed.h"
#include "param.h"
class Socks5AuthStateUser : public QObject
{
    Q_OBJECT
public:
    explicit Socks5AuthStateUser(QObject *parent = nullptr);
    qint8 version;

    qint8 userLength;

    QByteArray user;

    qint8 passLength;

    QByteArray password;

    /**
     * 解析socks5客户端数据
     * @brief parse
     * @param byte
     * @param error
     */
    void parse(QByteArray& byte,QString& error);

    /**
      返回socks5成功数据
     */
    QByteArray toByte();
signals:

public slots:
    /**
      用户认证的客户端接受数据
     * @brief authStateUserSocks5
     */
    void authStateUserSocks5();
};

#endif // SOCKS5AUTHSTATEUSER_H
