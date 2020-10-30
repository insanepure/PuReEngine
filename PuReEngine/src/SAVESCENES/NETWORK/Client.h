#ifndef _CLIENT_H_
#define _CLIENT_H_
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
namespace Game
{
    class CClient
    {
    public:
        CClient::CClient(sockaddr_in sockaddr)
        {
            this->b1 = sockaddr.sin_addr.S_un.S_un_b.s_b1;
            this->b2 = sockaddr.sin_addr.S_un.S_un_b.s_b2;
            this->b3 = sockaddr.sin_addr.S_un.S_un_b.s_b3;
            this->b4 = sockaddr.sin_addr.S_un.S_un_b.s_b4;
            this->port = sockaddr.sin_port;
            this->sockaddr = sockaddr;
        }

        sockaddr_in CClient::GetAddr()
        {
            return this->sockaddr;
        }

        bool CClient::operator == (sockaddr_in const & o) const
        {
            UCHAR b1, b2, b3, b4;
            USHORT port;

            b1 = o.sin_addr.S_un.S_un_b.s_b1;
            b2 = o.sin_addr.S_un.S_un_b.s_b2;
            b3 = o.sin_addr.S_un.S_un_b.s_b3;
            b4 = o.sin_addr.S_un.S_un_b.s_b4;
            port = o.sin_port;

            return b1 == this->b1 && b2 == this->b2 && b3 == this->b3 && b4 == this->b4 && port == this->port;
        }

        bool CClient::operator ==(const CClient &o) const
        {
            return o == this->sockaddr;
        }

    private:
        sockaddr_in sockaddr;
        UCHAR b1, b2, b3, b4;
        USHORT port;
    };
}

#endif /* _CLIENT_H_ */