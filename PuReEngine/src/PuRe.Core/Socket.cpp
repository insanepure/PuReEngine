#include "include/PuReEngine/Socket.h"

namespace PuReEngine
{
    namespace Core
    {

        // **************************************************************************
        // **************************************************************************
        CSocket::CSocket()
        {
            this->m_Initialized = false;
        }

        // **************************************************************************
        // **************************************************************************

        CSocket::~CSocket()
        {
            this->Cleanup();
        }

        // **************************************************************************
        // **************************************************************************
        bool CSocket::Initialize(ESocketType a_Type, ESocketProtocol a_Protocol, int a_Port, std::string a_pIP)
        {
            this->Cleanup();
            int iResult;
            WSADATA wsa;
            // Initialize Winsock
            iResult = WSAStartup(MAKEWORD(2, 2), &wsa);
            if (iResult != 0)
            {
                printf("WSAStartup Error: %d\n", iResult);
                return false;
            }
            else
            {
                this->m_Initialized = true;
                //Create Socket
                if (a_Protocol == TCP)
                    this->m_Sock = socket(AF_INET, SOCK_STREAM, 0);
                else
                    this->m_Sock = socket(AF_INET, SOCK_DGRAM, 0);

                if (this->m_Sock == INVALID_SOCKET)
                {
                    printf("Socket Initialization Error: %ld\n", WSAGetLastError());
                    return false;
                }

                if (a_Type == ESocketType::Host)
                {
                    //Set address if host
                    this->m_Address.sin_family = AF_INET;
                    this->m_Address.sin_port = (USHORT)htons((u_short)a_Port);
                    this->m_Address.sin_addr.s_addr = ADDR_ANY;
                    //bind address so we can listen
                    long result = bind(this->m_Sock, (SOCKADDR*)&this->m_Address, sizeof(SOCKADDR_IN));
                    if (result == SOCKET_ERROR)
                    {
                        printf("Socket Bind Error: %ld\n", WSAGetLastError());
                        this->Cleanup();
                        return false;
                    }
                }
                else if (a_Type == ESocketType::Client)
                {
                    //set address from which we receive something
                    this->m_Address.sin_family = AF_INET;
                    this->m_Address.sin_port = (USHORT)htons((u_short)a_Port);
                    this->m_Address.sin_addr.s_addr = inet_addr(a_pIP.c_str());
                    //connect to server
                    long result = connect(this->m_Sock, (SOCKADDR*)&this->m_Address, sizeof(SOCKADDR));
                    if (result == SOCKET_ERROR)
                    {
                        printf("Socket Connect Error: %ld\n", WSAGetLastError());
                        this->Cleanup();
                        return false;
                    }
                }
                else if (a_Type == ESocketType::Broadcaster || a_Type == ESocketType::Broadcasted)
                {
                    char broadcast = '1';
                    setsockopt(this->m_Sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
                    //Set address if host
                    this->m_Address.sin_family = AF_INET;
                    this->m_Address.sin_port = (USHORT)htons((u_short)a_Port);
                    this->m_Address.sin_addr.s_addr = INADDR_ANY;
                    //bind address so we can listen
                    if (a_Type == ESocketType::Broadcasted)
                    {
                        long result = bind(this->m_Sock, (SOCKADDR*)&this->m_Address, sizeof(SOCKADDR_IN));
                        if (result == SOCKET_ERROR)
                        {
                            printf("Socket Bind Error: %ld\n", WSAGetLastError());
                            this->Cleanup();
                            return false;
                        }
                    }
                }
                this->m_pIP = a_pIP;
                this->m_Port = a_Port;
                this->m_Type = a_Type;
                return true;
            }
        }

        // **************************************************************************
        // **************************************************************************
        bool CSocket::IsWorking()
        {
            return this->m_Sock != NULL;
        }

        // **************************************************************************
        // **************************************************************************
        void CSocket::SetMode(SOCKET s, bool a_Block)
        {
            if (s != NULL)
            {
                u_long iMode = 1;
                if (a_Block)
                    iMode = 0;
                ioctlsocket(s, FIONBIO, &iMode);
            }
        }

        // **************************************************************************
        // **************************************************************************
        SOCKET CSocket::GetSocket()
        {
            return this->m_Sock;
        }

        // **************************************************************************
        // **************************************************************************
        void CSocket::Cleanup()
        {
            if (this->m_Sock != INVALID_SOCKET)
                closesocket(this->m_Sock);
            this->m_Sock = NULL;
            if (this->m_Initialized)
                WSACleanup();
            this->m_Initialized = false;
        }
        // **************************************************************************
        // **************************************************************************

        std::string CSocket::GetIP()
        {
            char ac[80];
            std::string ip = "127.0.0.1";
            if (gethostname(ac, sizeof(ac)) != SOCKET_ERROR)
            {
                struct hostent *phe = gethostbyname(ac);
                if (phe->h_addr_list[0] != 0)
                {
                    struct in_addr addr;
                    memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
                    ip = inet_ntoa(addr);
                }
            }
            return ip;
        }
        // **************************************************************************
        // **************************************************************************

        SOCKADDR_IN CSocket::GetAddress()
        {
            return this->m_Address;
        }

        // **************************************************************************
        // **************************************************************************
        bool CSocket::Listen()
        {
            if (listen(this->m_Sock, SOMAXCONN) == SOCKET_ERROR)
            {
                printf("Socket Error: %ld\n", WSAGetLastError());
                this->Cleanup();
                return false;
            }
            return true;
        }

        // **************************************************************************
        // **************************************************************************
        long CSocket::Broadcast(const char* a_pData, int a_Length)
        {
            INTERFACE_INFO InterfaceList[20];
            unsigned long nBytesReturned;
            WSAIoctl(this->m_Sock, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList, sizeof(InterfaceList), &nBytesReturned, 0, 0);

            SOCKADDR_IN client;
            client.sin_family = AF_INET;
            client.sin_port = htons((u_short)this->m_Port);
            int remoteLen = sizeof(SOCKADDR_IN);

            int nNumInterfaces = nBytesReturned / sizeof(INTERFACE_INFO);
            long ret = 0;
            for (int i = 0; i < nNumInterfaces; ++i)
            {
                sockaddr_in *pAddress, *broadcastAddress, *netMask;
                pAddress = (sockaddr_in *)& (InterfaceList[i].iiAddress);
                broadcastAddress = (sockaddr_in *)& (InterfaceList[i].iiBroadcastAddress);
                netMask = (sockaddr_in *)& (InterfaceList[i].iiNetmask);

                u_long host_addr = inet_addr(inet_ntoa(pAddress->sin_addr));   // local IP addr
                u_long net_mask = inet_addr(inet_ntoa(netMask->sin_addr));   // LAN netmask
                u_long net_addr = host_addr & net_mask;         // 172.16.64.0
                u_long dir_bcast_addr = net_addr | (~net_mask); // 172.16.95.255

                //send to set submask
                client.sin_addr.S_un.S_addr = dir_bcast_addr;
                ret += sendto(this->m_Sock, a_pData, a_Length, 0, (SOCKADDR*)&client, remoteLen);
                if (ret < 0)
                    return ret;
                //also send to normal submask
                client.sin_addr.S_un.S_addr = inet_addr(inet_ntoa(broadcastAddress->sin_addr));
                ret += sendto(this->m_Sock, a_pData, a_Length, 0, (SOCKADDR*)&client, remoteLen);
                if (ret < 0)
                    return ret;
            }
            return ret;
        }

        // **************************************************************************
        // **************************************************************************
        SOCKET CSocket::Accept(SOCKADDR_IN* a_pClientData)
        {
            int remoteLen = sizeof(SOCKADDR_IN);
            return accept(this->m_Sock, (SOCKADDR*)a_pClientData, &remoteLen);
        }

        // **************************************************************************
        // **************************************************************************
        int CSocket::GetError()
        {
            return WSAGetLastError();
        }

        // **************************************************************************
        // **************************************************************************
        long CSocket::Select(SOCKET a_Sock, ESelect a_Select, int a_MicroSeconds)
        {
            FD_SET set;
            set.fd_array[0] = a_Sock;
            set.fd_count = 1;

            timeval t;
            t.tv_sec = 0;
            t.tv_usec = a_MicroSeconds;

            switch (a_Select)
            {
            case ESelect::Read:
                if (a_MicroSeconds != 0)
                    return select(0, &set, NULL, NULL, &t);
                else
                    return select(0, &set, NULL, NULL, NULL);
                break;
            case ESelect::Write:
                if (a_MicroSeconds != 0)
                    return select(0, NULL, &set, NULL, &t);
                else
                    return select(0, NULL, &set, NULL, NULL);
                break;
            }
            return 0;
        }

        // **************************************************************************
        // **************************************************************************
        long CSocket::Receive(SOCKET from, char* a_pBuffer, int a_Length)
        {
            return recv(from, a_pBuffer, a_Length, 0);
        }

        // **************************************************************************
        // **************************************************************************
        long CSocket::Send(SOCKET to, const char* a_pBuffer, int a_Length)
        {
            return send(to, a_pBuffer, a_Length, 0);
        }

        // **************************************************************************
        // **************************************************************************
        long CSocket::ReceiveFrom(char* a_pBuffer, int a_Length, SOCKADDR_IN* a_pServer)
        {
            int remoteLen = sizeof(SOCKADDR_IN);
            return recvfrom(this->m_Sock, a_pBuffer, a_Length, 0, (SOCKADDR*)a_pServer, &remoteLen);
        }

        // **************************************************************************
        // **************************************************************************
        long CSocket::SendTo(SOCKADDR_IN a_Client, const char* a_pData, int a_Length)
        {
            int remoteLen = sizeof(SOCKADDR_IN);
            return sendto(this->m_Sock, a_pData, a_Length, 0, (SOCKADDR*)&a_Client, remoteLen);
        }

    }
}