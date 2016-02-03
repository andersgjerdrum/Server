
#include "socket.h"


namespace MifuneCore
{


	void  Socket::OpenSocket()
	{

#ifdef WIN32

		WSADATA wsaData;
		WSAStartup(0x0202, &wsaData);

#endif

		this->socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	void Socket::ListenSocket()
	{
		if (listen(this->socketDescriptor, 5) < 0)
		{
			if (this->socketDescriptor)
			{
				CloseSocket();
			}
		}
	}



	Socket::Socket(int socket, sockaddr_in clientAddress)
	{
		this->socketDescriptor = socket, this->clientAddress = clientAddress;
	}

	Socket::Socket()
	{
	}

	void  Socket::CloseSocket()
	{

#ifdef WIN32
		closesocket(this->socketDescriptor);
		WSACleanup();

#elif __linux__
		close(this->socketDescriptor);
#endif

	}

	void Socket::Connect(char *ipAddr, int port)
	{
		struct sockaddr_in destination;
		destination.sin_port = htons(13374);
		destination.sin_addr.s_addr = inet_addr(ipAddr);
		if (connect(this->socketDescriptor, (struct sockaddr *)&destination, sizeof(destination)) != 0)
		{
			if (this->socketDescriptor)
			{
				CloseSocket();
			}
		}
		this->clientAddress = destination;
	}

	int Socket::Send(char *buffer, int startaddr, int buffersize)
	{
		return send(this->socketDescriptor, buffer, buffersize, startaddr);
	}

	int Socket::Recieve(char* buffer, int startaddr, int buffersize)
	{
 		return recv(this->socketDescriptor, buffer, buffersize, startaddr);
	}

	void  Socket::BindSocket(unsigned int port)
	{
		struct sockaddr_in destination;
		destination.sin_family = AF_INET;
		destination.sin_port = htons(port);
		destination.sin_addr.s_addr = INADDR_ANY;
		if (bind(this->socketDescriptor, (struct sockaddr *)&destination, sizeof(destination)) < 0)
		{
			if (this->socketDescriptor)
			{
				CloseSocket();
			}
		}
	}

	ISocket* Socket::AcceptSocket()
	{
		struct sockaddr_in  clientAddress;
		int clientSize = sizeof(clientAddress);

		int socketDescriptor = accept(this->socketDescriptor, (struct sockaddr *)&clientAddress, (int *)&clientSize);

		if (this->socketDescriptor < 0)
		{
			if (this->socketDescriptor)
			{
				CloseSocket();
			}
		}


		return new Socket(socketDescriptor, clientAddress);
	}
}