#include "Socks5AuthStateed.h"

Socks5AuthStateed::Socks5AuthStateed(QObject *parent) : QObject(parent)
{
    setObjectName("Socks5AuthStateed");
}

/**
  客户端发送的数据接受槽
 * @brief authStateedSocks5
 */
void Socks5AuthStateed::authStateedSocks5(){
    QTcpSocket * localSocket = (QTcpSocket *)sender();

    disconnect(localSocket,SIGNAL(readyRead()),this,SLOT(authStateedSocks5()));

    QByteArray byte = localSocket->readAll();

//    qWarning()<<"最后一道认证:"<<byte;

    QString error;
    parse(byte,error);

    if(!error.isEmpty()){
        qDebug()<<this<<error;
        return;
    }

    if(version != SocksVersion::SOCKS5){
        qWarning()<<this<<"不支持其他协议:"<<version;
        return;
    }

    if(command == Socks5Command::Connect){
        QTcpSocket * remtoSocket = new QTcpSocket(localSocket);

        QString socketName = address.toString()
                +QString::number(port)
                +outAddress.toString();

        remtoSocket->setObjectName(socketName);

        Socks5Connected * socks5Connected = new Socks5Connected(remtoSocket);

        socks5Connected->Run();


    }else if(command == Socks5Command::Bind){
        qWarning()<<this<<"不支持命令:Bind";
    }else if(command == Socks5Command::UDPAssociate){
        QUdpSocket * remtoSocket = new QUdpSocket(localSocket);

        QString socketName = address.toString()
                +QString::number(port)
                +outAddress.toString();

        remtoSocket->setObjectName(socketName);

        Socks5UDPConnection * socks5UDPConnection = new Socks5UDPConnection(remtoSocket);

        socks5UDPConnection->Run();

    }else{
        qWarning()<<this<<"不支持命令:"<<command;
    }
}

/**
 * 解析socks5客户端数据
 * @brief parse
 * @param byte
 * @param error
 */
void Socks5AuthStateed::parse(QByteArray& bytes,QString& error){

    QDataStream stream(&bytes,QIODevice::ReadOnly);

    stream>>version;

    stream>>command;

    stream>>rsv;

    stream>>addressType;

    if(addressType == Socks5AddressType::IPV4){
        if (bytes.length() < 10){
            error = "IPV4长度不足";
            return;
        }
        quint32 ipBytes;
        stream >> ipBytes;
        address = QHostAddress(ipBytes);
        if (address.isNull()){
            error = "IPV4错误";
            return;
        }
    }else if(addressType == Socks5AddressType::IPV6){
        quint8 * ipv6buf = new quint8[16];
        int read = stream.readRawData((char*)ipv6buf,16);
        if (read != 16){
            error = "IPV6长度不足";
            return;
        }
        address = QHostAddress(ipv6buf);
        delete[] ipv6buf;

        if (address.isNull()){
            error = "IPV6错误";
            return;
        }
    }else if(addressType == Socks5AddressType::Domain){
        quint8 nameLengthByte;
        stream >> nameLengthByte;
        if (bytes.length() < 7 + nameLengthByte)
        {
            error = "域名长度不足";
            return;
        }
        QByteArray domainName = QByteArray(nameLengthByte,(char)0);
        if (stream.readRawData(domainName.data(),nameLengthByte) != nameLengthByte)
        {
            error = "域名长度不足";
            return;
        }
        address = QHostInfo::fromName(domainName).addresses().first();
        if (address.isNull()){
            error = "域名错误";
            return;
        }
        qDebug()<<this<<"域名:"<<domainName;
    }else{
        error = "未知得地址类型";
        return;
    }

    stream >> port;

    //出口IP
    quint32 ipBytes;
    stream >> ipBytes;
    outAddress = QHostAddress(ipBytes);
    if (outAddress.isNull())
    {
        error = "出口IP错误";
        return;
    }

    stream.device()->close();

    qDebug()<<this<<"IP:"<<address<<"---"<<port<<"----"<<outAddress;
}

/**
  返回socks5成功数据
 * @brief toByte
 * @param ip
 * @param port
 * @return
 */
QByteArray Socks5AuthStateed::toByte(QHostAddress ip,qint16 port){
    QByteArray byte;
    byte.append((char)version);
    byte.append((char)0x00);

    byte.append((char)0x01);

    byte.append((char)0x01);

    quint32 ip32 = ip.toIPv4Address();
    byte.append((char)((ip32>>24)&0xff));
    byte.append((char)((ip32>>16)&0xff));
    byte.append((char)((ip32>>8)&0xff));
    byte.append((char)((ip32)&0xff));

    byte.append((char)((port >> 8)&0xff));
    byte.append((char)(port & 0xff));
    return byte;
}

