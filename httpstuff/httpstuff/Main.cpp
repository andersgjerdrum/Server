#include <iostream>
#include <atomic>
#include <memory>
#include <map>
#include <thread>
#include "socket.h"
#include "ISocket.h"
#include "ThreadPool.h"
#include "CLFQueue.h"

/*
Inspiration: http://www.techpowerup.com/forums/threads/c-c-sockets-faq-and-how-to-win-linux.56901/
http://www.codeproject.com/Articles/412511/Simple-client-server-network-using-Cplusplus-and-W
http://stackoverflow.com/questions/873978/c-simple-server-which-sends-simple-html-to-clients

https://code.google.com/p/mongoose/
*/
using namespace MifuneCore;

void ServerThread(std::shared_ptr<std::map<unsigned int, ISocket&>> sessions, CancelationToken canceled);
void ConnectionHandler(CancelationToken canceled);


int main()
{
	auto x = R"(Hello world!)";
	std::cout << x;
	ThreadPool threadpool(2);
	std::shared_ptr<std::map<unsigned int, ISocket&>> sessions(new std::map<unsigned int, ISocket&>);
	CancelationToken canceled;

	threadpool.enqueue([sessions, canceled]
	{
		ServerThread(sessions, canceled);
	});

	threadpool.enqueue([canceled]
	{
		ConnectionHandler(canceled);
	});

	std::cin.get();

	canceled.Cancel();
	return 0;
}

void ConnectionHandler(CancelationToken canceled)
{
	while (!canceled.IsCanceled())
	{
		
	}
	auto x = R"(canceled con)";
	std::cout << x;
}

void ServerThread(std::shared_ptr<std::map<unsigned int, ISocket&>> sessions, CancelationToken canceled)
{
	MifuneCore::Socket sock;
	sock.OpenSocket();
	auto x = R"(entered server)";
	std::cout << x;
	sock.BindSocket(13374);
	unsigned int sessionNumber = 0;
	while (!canceled.IsCanceled())
	{
		sock.ListenSocket();
		sessions->insert(std::pair<unsigned int, ISocket&>(sessionNumber++, sock.AcceptSocket()));
		auto x = R"(I got the session)";
		std::cout << x;
	}
	sock.CloseSocket();

	x = R"(canceled)";
	std::cout << x;
}
