#ifndef _NETWORKHANDLER_H_
#define _NETWORKHANDLER_H_

// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "Player.h"
#include "Client.h"
#include <algorithm>

namespace Game
{
    struct HeadPacket
    {
        int type;
    };
    struct ReceivePacket
    {
        // Header
        HeadPacket Head;
        // Raw Data
        char* buffer;
    };
    struct LeftPacket
    {
        // Header
        HeadPacket Head;
        // Raw Data
        int Who;
    };
    struct JumpPacket
    {
        // Header
        HeadPacket Head;
        // Raw Data
        int Who;
    };
    struct SendClientPacket
    {
        // Header
        HeadPacket Head;
        // Raw Data
        int Number;
    };
    struct SendClientsPacket
    {
        // Header
        HeadPacket Head;
        // Raw Data
        int Number;
        int ClientNums[4];
    };
    class CNetworkHandler
    {
    public:
        /// @brief Port of the Host
        ///
        std::string m_Port;
        /// @brief IP of the Host
        ///
        std::string m_IP;
        /// @brief if he is the host
        ///
        bool m_IsHost;
        /// @brief Player Array
        ///
        CPlayer** m_ppPlayers;
        /// @brief if this Data is Set
        ///
        bool m_IsSet;
        /// @brief Number of this Player
        ///
        int32 m_PlayerNumber;
        /// @brief Time on the network
        ///
        float32 m_Time;
        /// @brief Game started
        ///
        bool m_GameStarted;
        /// @brief Game ended
        ///
        bool m_GameEnd;
        /// @brief Round we are in
        ///
        int32 m_Round;

    private:
        PuRe_Socket* m_pSocket;
    public:
        CNetworkHandler(CPlayer** a_ppPlayers);
        ~CNetworkHandler();
    public:
        void Set(std::string a_Port, std::string a_IP, bool a_IsHost); //Client
        void HandleData(PuRe_IInput* a_pInput);
        
        
    };
}

#endif /* _NETWORKHANDLER_H_ */