#include <iostream>
#include <map>
#include <thread>
#include "socket.h"
#include "ISocket.h"

/*
Inspiration: http://www.techpowerup.com/forums/threads/c-c-sockets-faq-and-how-to-win-linux.56901/
http://www.codeproject.com/Articles/412511/Simple-client-server-network-using-Cplusplus-and-W
http://stackoverflow.com/questions/873978/c-simple-server-which-sends-simple-html-to-clients

https://code.google.com/p/mongoose/
*/
void ServerThread(MifuneCore::ISocket &sock, std::map<unsigned int, MifuneCore::ISocket&> sessions);

int main()
{
	auto x = R"(Hello world!)";
	std::cout << x;

	MifuneCore::Socket sock;
	sock.OpenSocket();

	sock.BindSocket(13374);
	std::map<unsigned int, MifuneCore::ISocket&> sessions;

	std::thread t1(ServerThread, sock, sessions);

	t1.join();
	sock.CloseSocket();
	return 0;
}

void ServerThread(MifuneCore::ISocket &sock, std::map<unsigned int, MifuneCore::ISocket&> sessions)
{
	unsigned int sessionNumber = 0;
	while (true)
	{
		sock.ListenSocket();
		sessions.insert(std::pair<unsigned int, MifuneCore::ISocket&>(sessionNumber++, sock.AcceptSocket()));
		auto x = R"(I got the session)";
		std::cout << x;
	}
}
