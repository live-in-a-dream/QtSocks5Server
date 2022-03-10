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

    /**
      运行
     * @brief Run
     */
    void Run();
private:
    QTcpSocket * remtoSocket;
signals:

public slots:
    /**
      远程TCP连接成功
     * @brief remtoSocketConnected
     */
    void remtoSocketConnected();
    /**
      远程TCP读取数据
     * @brief remtoSocketReadyRead
     */
    void remtoSocketReadyRead();
    /**
      远程TCP断开连接
     * @brief connectSocks5Disconnected
     */
    void connectRemtoSocks5Disconnected();
    /**
      远程TCP错误
     * @brief remtoSocketError
     */
    void remtoSocketError(QAbstractSocket::SocketError);
    /**
      TCP读取数据
     * @brief connectSocks5ReadyRead
     */
    void connectSocks5ReadyRead();

};

#endif // SOCKS5CONNECTED_H
