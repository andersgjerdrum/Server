#include <iostream>
#include <map>
#include <thread>
#include "socket.h"
#include "ISocket.h"
#include "ThreadPool.h"

/*
Inspiration: http://www.techpowerup.com/forums/threads/c-c-sockets-faq-and-how-to-win-linux.56901/
http://www.codeproject.com/Articles/412511/Simple-client-server-network-using-Cplusplus-and-W
http://stackoverflow.com/questions/873978/c-simple-server-which-sends-simple-html-to-clients

https://code.google.com/p/mongoose/
*/
using namespace MifuneCore;
void ServerThread();

int main()
{
	auto x = R"(Hello world!)";
	std::cout << x;
	ThreadPool threadpool(2);
	threadpool.enqueue([]
	{
		ServerThread();
	});

	std::cin.get();
	return 0;
}

void ServerThread(void)
{
	MifuneCore::Socket sock;
	sock.OpenSocket();
	auto x = R"(entered server)";
	std::cout << x;
	sock.BindSocket(13374);
	std::map<unsigned int, ISocket&> sessions;
	unsigned int sessionNumber = 0;
	while (true)
	{
		sock.ListenSocket();
		sessions.insert(std::pair<unsigned int, ISocket&>(sessionNumber++, sock.AcceptSocket()));
		auto x = R"(I got the session)";
		std::cout << x;
	}
	sock.CloseSocket();

}
