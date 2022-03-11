#ifndef ENUM_H
#define ENUM_H
/**
  socks版本
 * @brief The SocksVersion enum
 */
enum SocksVersion
{
   SOCKS5 = 0x05,
   SOCKS4 = 0x04
};

/**
  socks5认证方式
 * @brief The SocksAuthEnum enum
 */
enum Socks5AuthEnum
{
    NOT_AUTH = 0x00,
    GSSAPI = 0x01,
    USERPASS = 0x02
};

/**
  socks5命令
 * @brief The Socks5Command enum
 */
enum Socks5Command
{
    Connect = 0x01,
    Bind = 0x02,
    UDPAssociate = 0x03
};

/**
  socks5地址类型
 * @brief The Socks5Command enum
 */
enum Socks5AddressType
{
    IPV4 = 0x01,
    Domain = 0x03,
    IPV6 = 0x04
};

class Enum
{
public:
    Enum();
};

#endif // ENUM_H
