#ifndef SOCKS5AUTHSTATE_H
#define SOCKS5AUTHSTATE_H

#include <QObject>
#include "qtcpserver.h"
#include "qtcpsocket.h"
#include <QPointer>
#include "Socks5AuthStateUser.h"
#include "param.h"
class Socks5AuthState : public QObject
{
    Q_OBJECT
public:
    explicit Socks5AuthState(QObject *parent = nullptr);


    qint8 version;

    qint8 methodsCount;

    QList<qint8> methods;

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
    QByteArray toByte(Socks5AuthEnum socksAuthEnum);
signals:

public slots:
    /**
      认证最后一步的数据接受
     * @brief authStateSocks5
     */
    void authStateSocks5();
};

#endif // SOCKS5AUTHSTATE_H
