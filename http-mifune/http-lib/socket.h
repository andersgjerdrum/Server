#pragma once
#include <iostream>
#ifdef WIN32

#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")

#elif __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "socket.h"
namespace MifuneCore 
{
	class Socket
	{
		sockaddr_in clientAddress;
		int socketDescriptor = -1 ;
	public:
		Socket(int socket, sockaddr_in clientAddress);
		Socket();
		void CloseSocket();
		void Connect(char *ipAddr, int port);
		int Send(char * buffer, int startaddr, int buffersize);
		int Recieve(char * buffer, int startaddr, int buffersize);
		void BindSocket(unsigned int port);
		void OpenSocket();
		void ListenSocket();
		Socket* AcceptSocket();
	};
}