#include <iostream>
#include <atomic>
#include <memory>
#include <map>
#include <thread>
#include "socket.h"
#include "ISocket.h"
#include "ThreadPool.h"
#include "httpstructs.h"
#include "CLFQueue.h"

/*
Inspiration: http://www.techpowerup.com/forums/threads/c-c-sockets-faq-and-how-to-win-linux.56901/
http://www.codeproject.com/Articles/412511/Simple-client-server-network-using-Cplusplus-and-W
http://stackoverflow.com/questions/873978/c-simple-server-which-sends-simple-html-to-clients

https://code.google.com/p/mongoose/
*/
using namespace MifuneCore;

void ServerThread(CancelationToken canceled);
void ConnectionHandler(CancelationToken canceled);

static LockFreeQueue<std::pair<unsigned int, ISocket*>> *RequestChannelQueue;
static ThreadPool *requestchannelThreadpool;

void initializeWebServer(int threadpoolsize) 
{
	requestchannelThreadpool = new ThreadPool(threadpoolsize);
	RequestChannelQueue = new LockFreeQueue<std::pair<unsigned int, ISocket*>>(1, threadpoolsize);
}

CancelationToken startWebServer()
{
	CancelationToken canceled;

	requestchannelThreadpool->enqueue([canceled]
	{
		ServerThread(canceled);
	});

	requestchannelThreadpool->enqueue([canceled]
	{
		ConnectionHandler(canceled);
	});
	return canceled;
}

void stopWebServer(CancelationToken canceled)
{
	canceled.Cancel();
}

void cleanUpWebServer() 
{
	delete requestchannelThreadpool;
	delete RequestChannelQueue;
}

int main()
{

	initializeWebServer(10);
	auto x = R"(Hello world!)";
	std::cout << x;

	CancelationToken canceled = startWebServer();

	std::cin.get();
	stopWebServer(canceled);
	cleanUpWebServer();

	return 0;
}

void ConnectionHandler(CancelationToken canceled)
{
	while (!canceled.IsCanceled())
	{
		auto item = RequestChannelQueue->pop();
		auto socket = item->second;
		auto x = R"(popped item)";
		std::cout << x;
		char recvbuff[8092];
		int bytes = socket->Recieve(recvbuff, 0, 8092);
		string str(recvbuff);
		httprequest req(str);
		std::cout << str;
		x = R"(Recieved)";
		std::cout << x;
		
	}
	auto x = R"(canceled con)";
	std::cout << x;
}




void ServerThread(CancelationToken canceled)
{
	Socket sock;
	sock.OpenSocket();
	auto x = R"(entered server)";
	std::cout << x;
	sock.BindSocket(13374);
	unsigned int sessionNumber = 0;
	while (!canceled.IsCanceled())
	{
		sock.ListenSocket();
		RequestChannelQueue->push(new std::pair<unsigned int, ISocket*>(sessionNumber++, sock.AcceptSocket()));
		auto x = R"(pushed item)";
		std::cout << x;
	}
	sock.CloseSocket();

	x = R"(canceled)";
	std::cout << x;
}
