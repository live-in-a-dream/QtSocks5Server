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

    void parse(QByteArray& byte,QString& error);

    QByteArray toByte();
signals:

public slots:

    void authStateUserSocks5();
};

#endif // SOCKS5AUTHSTATEUSER_H
