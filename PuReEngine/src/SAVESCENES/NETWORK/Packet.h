#pragma once

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
struct ClientsReceivePacket
{
  // Header
  HeadPacket Head;
  // Raw Data
  int Clients;
  char* buffer;
};
struct ClientsPacket
{
  // Header
  HeadPacket Head;
  // Raw Data
  int Clients;
  float* X;
  float* Y;
};

struct MovePacket
{
  // Header
  HeadPacket Head;
  // Raw Data
  float X;
  float Y;
};

struct WhoMovePacket
{
  // Header
  HeadPacket Head;
  // Raw Data
  int Who;
  float X;
  float Y;
};