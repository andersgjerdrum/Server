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
#include "ISocket.h"

namespace MifuneCore 
{

	class Socket : public ISocket
	{
		sockaddr_in clientAddress;
		int socketDescriptor = -1 ;
	public:
		Socket(int socket, sockaddr_in clientAddress);
		Socket();
		void CloseSocket();
		void Connect(wchar_t ipAddr, int port);
		void Send(char * buffer, int startaddr, int buffersize);
		void Recieve(char * buffer, int startaddr, int buffersize);
		void BindSocket(unsigned int port);
		void OpenSocket();
		void ListenSocket();
		ISocket& AcceptSocket();
	};
}