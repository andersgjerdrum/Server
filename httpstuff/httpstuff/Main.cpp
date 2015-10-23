#include <iostream>


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

	ListenSocket(thisSocket);
	struct sockaddr_in clientAddress;

	AcceptSocket(thisSocket,clientAddress);
	
	CloseSocket(thisSocket);
}
