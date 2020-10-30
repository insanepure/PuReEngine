#define _WINSOCK_DEPRECATED_NO_WARNINGS
#ifndef _SOCKET_H_
#define _SOCKET_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <string>
#pragma comment(lib,"WS2_32")

// To Do: Linux implementation

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        enum ESocketProtocol { TCP,UDP};
        enum ESelect {Read,Write};
        enum ESocketType {Client,Host,Broadcasted,Broadcaster};

        class CSocket
        {
        private:
            /// @brief Whether the Socket has been Initialized or not
            ///
            bool m_Initialized;
            /// @brief Port to listen/port to connect to
            ///
            int m_Port;
            /// @brief Ip to connect to if not host
            ///
            std::string m_pIP;
            /// @brief if client, server address, else, our address
            ///
            SOCKADDR_IN m_Address;
            /// @brief Socket used for connections
            ///
            SOCKET m_Sock;
            /// @brief Type of the Socket
            ///
            ESocketType m_Type;
        public:
            /// @brief Initializes an Instance of Socket
            ///
            CSocket();
            /// @brief Destroyes an Instance of Socket
            ///
            ~CSocket();
        public:
            /// @brief Initializes an Instance of Socket
            ///
            /// @param Socket used
            /// @param Which select type
            /// @param timeout value
            ///
            /// @returns Error or one if works
            ///
            long Select(SOCKET a_Sock, ESelect a_Select, int a_MicroSeconds);
            /// @brief Cleanup Memory, close Socket etc
            ///
            void Cleanup();
            /// @brief Initializes an Instance of Socket
            ///
            /// @param Which type the connection is
            /// @param Protocol to use
            /// @param port from which we listem/we connect to
            /// @param ip from which we receive data
            ///
            bool Initialize(ESocketType a_Type, ESocketProtocol a_Protocol, int a_Port, std::string a_pIP);
            /// @brief Whether this Socket is working or not
            ///
            /// @returns true for works, false for not
            ///
            bool IsWorking();
            /// @brief Set the blocking Mode
            ///
            /// @param Which to change
            /// @param if it should block or not
            ///
            void SetMode(SOCKET s, bool a_Block);
            /// @brief Return the IP
            ///
            /// @returns IP as String
            ///
            std::string GetIP();
            /// @brief Return the Socket
            ///
            /// @returns the Socket used
            SOCKET GetSocket();
            /// @brief Listen for Clients, blocking
            ///
            /// @returns if a Client is there or an error happend
            bool Listen();
            /// @brief Accept a Client
            ///
            /// @param Data of the Client
            ///
            /// @returns Socket of the accepted Client
            SOCKET Accept(SOCKADDR_IN* a_pClientData);
            /// @brief Returns The Error
            ///
            /// @returns The Error as INT
            ///
            int GetError();
            /// @brief Receive Data TCP
            ///
            /// @param from who we receive
            /// @param buffer to which we write the data
            /// @param length of the buffer
            ///
            /// @returns error code as long
            ///
            long Receive(SOCKET from, char* a_pBuffer, int a_Length);
            /// @brief Send Data TCP
            ///
            /// @param to who we send it to
            /// @param buffer we send
            /// @param length of the buffer
            ///
            /// @returns error code as long
            ///
            long Send(SOCKET to, const char* a_pData, int a_Length);

            /// @brief Receive Data conectionless
            ///
            /// @param buffer to which we write the data
            /// @param length of the buffer
            /// @param server we receive our data from
            ///
            /// @returns error code as long
            ///
            long ReceiveFrom(char* a_pBuffer, int a_Length, SOCKADDR_IN* a_pServer);
            /// @brief Broadcast Data across the LAN
            ///
            /// @param buffer we send
            /// @param length of the buffer
            ///
            /// @returns error code as long
            ///
            long Broadcast(const char* a_pData, int a_Length);
            /// @brief Send Data conectionless
            ///
            /// @param client we send our data to
            /// @param buffer we send
            /// @param length of the buffer
            ///
            /// @returns error code as long
            ///
            long SendTo(SOCKADDR_IN a_Client, const char* a_pData, int a_Length);
            /// @brief Get Address
            ///
            /// @return Our Address
            ///
            SOCKADDR_IN GetAddress();
        };
    }
}
#endif /* _SOCKET_H_ */