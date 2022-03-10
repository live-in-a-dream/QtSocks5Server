#ifndef SOCKS5CONNECTED_H
#define SOCKS5CONNECTED_H

#include <QObject>
#include "qtcpserver.h"
#include "qtcpsocket.h"
#include "Socks5AuthState.h"
#include "param.h"
class Socks5Connected : public QObject
{
    Q_OBJECT
public:
    explicit Socks5Connected(QObject *parent = nullptr);

signals:

public slots:
    void remtoSocketConnected();
    void remtoSocketReadyRead();
    void connectSocks5ReadyRead();
};

#endif // SOCKS5CONNECTED_H
