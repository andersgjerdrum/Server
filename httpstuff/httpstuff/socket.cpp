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

namespace MifuneCore {


	int OpenSocket()
	{

#ifdef WIN32

		WSADATA wsaData;
		WSAStartup(0x0202, &wsaData);

#endif

		int thisSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (thisSocket < 0)
		{
			printf("\nSocket Creation FAILED!");
			return 0;
		}
	}

	int ListenSocket(int thisSocket)
	{
		printf("\nListening on 13374...");
		if (listen(thisSocket, 5) < 0)
		{
			printf("\nListening on Socket FAILED!\n");
			if (thisSocket)
			{
				CloseSocket(thisSocket);
			}
			return -1;
		}
		return 0;
	}


	void CloseSocket(int thisSocket)
	{

#ifdef WIN32
		closesocket(thisSocket);
		WSACleanup();

#elif __linux__
		close(thisSocket);
#endif

	}

	int BindSocket(int thisSocket)
	{
		struct sockaddr_in destination;
		destination.sin_family = AF_INET;
		destination.sin_port = htons(13374);
		destination.sin_addr.s_addr = INADDR_ANY;
		if (bind(thisSocket, (struct sockaddr *)&destination, sizeof(destination)) < 0)
		{
			printf("\nBinding Socket FAILED!\n");
			if (thisSocket)
			{
				CloseSocket(thisSocket);
			}
			return -1;
		}
		return 0;
	}

	int AcceptSocket(int thisSocket, sockaddr_in clientAddress)
	{
		int clientSize = sizeof(clientAddress);
		thisSocket = accept(thisSocket, (struct sockaddr *)&clientAddress, (int *)&clientSize);

		if (thisSocket < 0)
		{
			printf("\nSocket Connection FAILED!\n");
			if (thisSocket)
			{
				CloseSocket(thisSocket);
			}
			return -1;
		}
		return 0;
		printf("\nConnection Established!");
	}
}