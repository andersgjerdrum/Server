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

/*
Inspiration: http://www.techpowerup.com/forums/threads/c-c-sockets-faq-and-how-to-win-linux.56901/

*/
void CloseSocket(int thisSocket);
int BindSocket(int thisSocket);
int OpenSocket();

int main()
{
	auto x = R"(Hello world!)";
	std::cout << x;

	int thisSocket = OpenSocket();

	BindSocket(thisSocket);

	CloseSocket(thisSocket);
}

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

int Listen(int thisSocket)
{
	printf("\nListening on 13374...");
	if (listen(thisSocket, 5) < 0)
	{
		printf("\nListening on Socket FAILED!\n");
		if (thisSocket)
		{ 
			CloseSocket(thisSocket); 
		}
		return 0;
	}
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
	if (bind(thisSocket, (struct sockaddr *)&destination, sizeof(destination))<0)
	{
		printf("\nBinding Socket FAILED!\n");
		if (thisSocket)
		{
			CloseSocket(thisSocket);
		}
			return 0;
	}
	return 1;
}