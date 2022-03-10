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

    void parse(QByteArray& byte,QString& error);

    QByteArray toByte(SocksAuthEnum socksAuthEnum);
signals:

public slots:
    void authStateSocks5();
};

#endif // SOCKS5AUTHSTATE_H
