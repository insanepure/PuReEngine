#include "include/NetworkHandler.h"

namespace Game
{
    CNetworkHandler::CNetworkHandler(CPlayer** a_ppPlayers) : m_ppPlayers(a_ppPlayers)
    {
    }

    void CNetworkHandler::Set(std::string a_Port, std::string a_IP, bool a_IsHost)
    {
        this->m_IsHost = a_IsHost;
        this->m_pSocket = new PuRe_Socket(a_IP.c_str(), std::stoi(a_Port), a_IsHost);
        this->m_IsSet = true;
        this->m_Round = 1;
        if (!this->m_IsHost)
        {
            HeadPacket h;
            h.type = 0;
            this->m_pSocket->Send(this->m_pSocket->GetAddress(), (char*)&h, sizeof(HeadPacket));
        }
        else
        {
            this->m_ppPlayers[0]->m_isDead = false;
            this->m_ppPlayers[0]->m_IsPlaying = true;
            this->m_ppPlayers[0]->m_JumpHeight = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
        }
    }
    CNetworkHandler::~CNetworkHandler()
    {
        if (this->m_IsSet)
        {
            if (this->m_IsHost)
            {
                HeadPacket head;
                head.type = 5; //endgame
                for (int32 i = 1; i < 4; i++)
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying)
                        this->m_pSocket->Send(this->m_ppPlayers[i]->sockaddr, (char*)&head, sizeof(HeadPacket));
                }
            }
            else
            {
                LeftPacket h;
                h.Head.type = 1;
                h.Who = this->m_PlayerNumber;
                this->m_pSocket->Send(this->m_pSocket->GetAddress(), (char*)&h, sizeof(LeftPacket));
            }
            SAFE_DELETE(this->m_pSocket);
        }
    }
    void CNetworkHandler::HandleData(PuRe_IInput* a_pInput)
    {
        long rc;
        char8 packet[256];
        SOCKADDR_IN sender;
        if (this->m_IsHost)
        {
            if (this->m_GameStarted)
            {
                bool alldead = true;
                for (int32 i = 0; i < 4; i++)
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying&&!this->m_ppPlayers[i]->m_isDead)
                        alldead = false;
                }
                if (alldead)
                {
                    this->m_Round++;
                    this->m_Time = 0.0f;
                    HeadPacket head;
                    if (this->m_Round > 3)
                    {
                        head.type = 5; //endgame
                        this->m_GameEnd = true;
                        for (int32 i = 1; i < 4; i++)
                        {
                            if (this->m_ppPlayers[i]->m_IsPlaying)
                                rc = this->m_pSocket->Send(this->m_ppPlayers[i]->sockaddr, (char*)&head, sizeof(HeadPacket));
                        }
                        this->m_IsSet = false;
                        SAFE_DELETE(this->m_pSocket);
                    }
                    else
                    {
                        head.type = 6; //restart
                        this->m_Time = 0.0f;
                        for (int32 i = 0; i < 4; i++)
                        {
                            if (this->m_ppPlayers[i]->m_IsPlaying)
                            {
                                this->m_ppPlayers[i]->m_isDead = false;
                                this->m_ppPlayers[i]->m_JumpHeight = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
                                if (i != 0)
                                    rc = this->m_pSocket->Send(this->m_ppPlayers[i]->sockaddr, (char*)&head, sizeof(HeadPacket));
                            }
                        }
                    }

                }
            }
            if (a_pInput->KeyPressed(a_pInput->Enter) || a_pInput->GamepadPressed(a_pInput->Pad_Start, 0))
            {
                int32 playerCount = 0;
                for (int32 i = 0; i < 4; i++)
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying)
                        playerCount++;
                }
                if (playerCount > 1)
                {
                    //Game start!!
                    HeadPacket head;
                    head.type = 4;
                    this->m_GameStarted = true;
                    this->m_Time = 0.0f;
                    for (int32 i = 1; i < 4; i++)
                    {
                        if (this->m_ppPlayers[i]->m_IsPlaying)
                        {
                            printf("Send - %i!\n", i);
                            rc = this->m_pSocket->Send(this->m_ppPlayers[i]->sockaddr, (char*)&head, sizeof(HeadPacket));
                        }
                    }
                }
            }
            if (a_pInput->KeyPressed(a_pInput->Space) || a_pInput->GamepadPressed(a_pInput->Pad_A, 0))
            {
                JumpPacket jumper;
                jumper.Head.type = 2;
                jumper.Who = 0;
                printf("-----------------------\n");
                printf("WE JUMPED\n");
                this->m_ppPlayers[0]->Jump();
                for (int32 i = 1; i < 4; i++)
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying)
                    {
                        printf("Send - %i!\n", i);
                        rc = this->m_pSocket->Send(this->m_ppPlayers[i]->sockaddr, (char*)&jumper, sizeof(JumpPacket));
                    }
                }
                printf("-----------------------\n");
            }
            while (this->m_pSocket->Receive(packet, 256, &sender) != -1)
            {
                printf("-----------------------\n");
                printf("Empfangene Daten: %s\n", packet);
                ReceivePacket* rec = (ReceivePacket*)packet;
                printf(" - - - - - - - - - - - \n", packet);
                printf("Type: %i\n", rec->Head.type);
                switch (rec->Head.type)
                {
                case 0:
                {
                    //client joined
                    printf("CLIENT JOINED!!\n");
                    printf(" - - - - - - - - - - - \n");
                    printf("Send to everyone that one joined!\n");
                    //send existing players that one joined
                    int32 clientnum = 0;
                    for (int32 i = 0; i < 4; i++)
                    {
                        if (!this->m_ppPlayers[i]->m_IsPlaying)
                        {
                            clientnum = i;
                            break;
                        }
                    }
                    printf("Client Num: %i!\n",clientnum);
                    if (clientnum != 0&&this->m_GameStarted == false)
                    {
                        SendClientsPacket cv;
                        cv.Head.type = 3;
                        cv.Number = clientnum;
                        //if 0 3 is there, the client should also display 0 3
                        cv.ClientNums[0] = 0;
                        cv.ClientNums[1] = 0;
                        cv.ClientNums[2] = 0;
                        cv.ClientNums[3] = 0;
                        int32 clientnums = 1; //0 is always there, so first is 1

                        for (int32 i = 1; i < 4; i++)
                        {
                            if (this->m_ppPlayers[i]->m_IsPlaying)
                            {
                                cv.ClientNums[clientnums] = i; // 1 is set to 3
                                clientnums++;
                                printf("Send - %i!\n", i);
                                SendClientPacket got;
                                got.Head.type = 0;
                                got.Number = clientnum;
                                rc = this->m_pSocket->Send(this->m_ppPlayers[i]->sockaddr, (char*)&got, sizeof(SendClientPacket));
                            }
                        }
                        //send to the new player amount of existing players
                        printf("Send existing clients to new client.\n");
                        rc = this->m_pSocket->Send(sender, (char*)&cv, sizeof(SendClientsPacket));
                        //now save him
                        this->m_ppPlayers[clientnum]->m_isDead = false;
                        this->m_ppPlayers[clientnum]->m_IsPlaying = true;
                        this->m_ppPlayers[clientnum]->m_JumpHeight = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
                        this->m_ppPlayers[clientnum]->sockaddr = sender;
                    }
                    else
                    {
                        HeadPacket head;
                        head.type = 5;
                        rc = this->m_pSocket->Send(sender, (char*)&head, sizeof(HeadPacket));
                    }
                }
                break;
                case 1:
                {
                    LeftPacket* lefter = (LeftPacket*)rec;
                    if (lefter->Who < 4&&lefter->Who != 0)
                    {
                        printf("CLIENT Left!!\n");
                        printf(" - - - - - - - - - - - \n");
                        printf("Send to everyone that one left!\n");
                        this->m_ppPlayers[lefter->Who]->m_IsPlaying = false;
                        LeftPacket left;
                        left.Head.type = 1;
                        left.Who = lefter->Who;
                        for (int32 i = 1; i < 4; i++)
                        {
                            if (this->m_ppPlayers[i]->m_IsPlaying)
                            {
                                printf("Send - %i!\n", i);
                                rc = this->m_pSocket->Send(this->m_ppPlayers[i]->sockaddr, (char*)&left, sizeof(LeftPacket));
                            }
                        }
                    }
                }
                break;
                case 2:
                {
                    JumpPacket* jumper = (JumpPacket*)rec;
                    if (jumper->Who < 4 && this->m_ppPlayers[jumper->Who]->m_IsPlaying)
                    {
                        printf("Client %i jumped!\n", jumper->Who);
                        this->m_ppPlayers[jumper->Who]->Jump();
                        printf(" - - - - - - - - - - - \n");
                        printf("Send to everyone that one jumped!\n");
                        JumpPacket njump;
                        njump.Head.type = 2;
                        njump.Who = jumper->Who;
                        for (int32 i = 1; i < 4; i++)
                        {
                            if (this->m_ppPlayers[i]->m_IsPlaying)
                            {
                                printf("Send - %i!\n", i);
                                rc = this->m_pSocket->Send(this->m_ppPlayers[i]->sockaddr, (char*)&njump, sizeof(JumpPacket));
                            }
                        }
                    }
                }
                break;
                }
                printf("-----------------------\n\n");
            }
        }
        else
        {
            if (a_pInput->KeyPressed(a_pInput->Space) && this->m_PlayerNumber != 0 || a_pInput->GamepadPressed(a_pInput->Pad_A, 0) && this->m_PlayerNumber != 0)
            {
                JumpPacket jumper;
                jumper.Head.type = 2;
                jumper.Who = this->m_PlayerNumber;
                this->m_pSocket->Send(this->m_pSocket->GetAddress(), (char*)&jumper, sizeof(JumpPacket));
                printf("-----------------------\n");
                printf("WE JUMPED\n");
                printf("-----------------------\n");
            }
            //Get Data from Server
            while (this->m_pSocket->Receive(packet, 256, &sender) != -1)
            {
                printf("-----------------------\n");
                printf("Empfangene Daten: %s\n", packet);
                ReceivePacket* rec = (ReceivePacket*)packet;
                printf(" - - - - - - - - - - - \n", packet);
                printf("Type: %i\n", rec->Head.type);
                switch (rec->Head.type)
                {
                case 0:
                {
                    SendClientPacket* c = (SendClientPacket*)rec;
                    if (c->Number < 4)
                    {
                        printf("Client joined!\n");
                        this->m_ppPlayers[c->Number]->m_IsPlaying = true;
                        this->m_ppPlayers[c->Number]->m_isDead = false;
                        this->m_ppPlayers[c->Number]->m_JumpHeight = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
                    }
                }
                break;
                case 1:
                {
                    LeftPacket* left = (LeftPacket*)rec;
                    if (left->Who < 4 && this->m_ppPlayers[left->Who]->m_IsPlaying)
                    {
                        printf("Client left!\n");
                        this->m_ppPlayers[left->Who]->m_IsPlaying = false;
                    }
                }
                break;
                case 2:
                {
                    JumpPacket* jumper = (JumpPacket*)rec;
                    if (jumper->Who < 4 && this->m_ppPlayers[jumper->Who]->m_IsPlaying)
                    {
                        printf("Client %i jumped!\n", jumper->Who);
                        this->m_ppPlayers[jumper->Who]->Jump();
                    }
                }
                break;
                case 3:
                {
                    //receive packet
                    SendClientsPacket* cv = (SendClientsPacket*)rec;
                    for (int32 i = 0; i < 4; i++)
                    {
                        for (int32 j = 0; j < 4; j++)
                        {
                            if (cv->ClientNums[j] == i)
                            {
                                this->m_ppPlayers[i]->m_IsPlaying = true;
                                this->m_ppPlayers[i]->m_isDead = false;
                                this->m_ppPlayers[i]->m_JumpHeight = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
                            }
                        }
                    }
                    this->m_PlayerNumber = cv->Number;
                    this->m_ppPlayers[cv->Number]->m_IsPlaying = true;
                    this->m_ppPlayers[cv->Number]->m_isDead = false;
                    this->m_ppPlayers[cv->Number]->m_JumpHeight = PuRe_Vector3F(0.0f,0.0f,0.0f);
                }
                break;
                case 4:
                {
                    //receive packet
                    this->m_GameStarted = true;
                    this->m_Time = 0.0f;
                }
                break;
                case 5:
                {
                    //receive packet
                    this->m_GameEnd = true;
                    this->m_IsSet = false;
                    SAFE_DELETE(this->m_pSocket);
                }
                break;
                case 6:
                {
                    //receive packet
                    this->m_Time = 0.0f;
                    this->m_Round++;
                    for (int32 i = 0; i < 4; i++)
                    {
                        if (this->m_ppPlayers[i]->m_IsPlaying)
                        {
                            this->m_ppPlayers[i]->m_isDead = false;
                            this->m_ppPlayers[i]->m_JumpHeight = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
                        }
                    }
                    
                }
                break;
                }
                printf("-----------------------\n\n");
            }
        }


    }
}