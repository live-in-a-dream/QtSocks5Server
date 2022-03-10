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

    /**
      运行
     * @brief Run
     */
    void Run();
private:
    QUdpSocket * remtoSocket;
signals:

public slots:
    /**
      UDP读取数据
     * @brief udpSocks5ReadyRead
     */
    void udpSocks5ReadyRead();
    /**
      远程UDP读取
     * @brief remtoSocketReadyRead
     */
    void remtoSocketReadyRead();
    /**
      远程UDP断开连接
     * @brief udpSocks5Disconnected
     */
    void udpRemtoSocks5Disconnected();
    /**
      UDP错误
     * @brief udpSocketError
     */
    void udpSocketError(QAbstractSocket::SocketError);
};

#endif // SOCKS5UDPCONNECTION_H
