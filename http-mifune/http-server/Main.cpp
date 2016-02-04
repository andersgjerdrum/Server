#include <iostream>
#include <atomic>
#include <memory>
#include <map>
#include <thread>
#include "socket.h"
#include "httpstructs.h"
#include "threadpool.h"
#include "queue.h"

/*
Inspiration: http://www.techpowerup.com/forums/threads/c-c-sockets-faq-and-how-to-win-linux.56901/
http://www.codeproject.com/Articles/412511/Simple-client-server-network-using-Cplusplus-and-W
http://stackoverflow.com/questions/873978/c-simple-server-which-sends-simple-html-to-clients

https://code.google.com/p/mongoose/
*/
using namespace MifuneCore;

void ServerThread(CancelationToken canceled);
void ConnectionHandler(CancelationToken canceled);
void RetrieveRequest(httprequest& req, Socket *socket);
void RequestHandler(httprequest &req, Socket *socket);


static Queue<std::pair<unsigned int, Socket*>> *RequestChannelQueue;
static ThreadPool *requestchannelThreadpool;

void initializeWebServer(int threadpoolsize) 
{
	requestchannelThreadpool = new ThreadPool(threadpoolsize);
	RequestChannelQueue = new Queue<std::pair<unsigned int, Socket*>>(1, threadpoolsize);
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
		auto socket = item.second;
		auto x = R"(popped item)";
		std::cout << x;
		httprequest req;
		RetrieveRequest(req, socket);
		RequestHandler(req,socket);
	}

	auto x = R"(canceled connection)";
	std::cout << x;
}

void RequestHandler(httprequest &req, Socket *socket)
{
	switch (req.method) 
	{
		case HTTP_GET: 
		{
			
		}
	}
}



#define MAX_TCP_CHUNKBUFFER 8092
void RetrieveRequest(httprequest& req, Socket *socket)
{
	char recvbuff[MAX_TCP_CHUNKBUFFER];
	int bytes = 0;
	int total = 0;
	do {

		bytes = socket->Recieve(recvbuff, total, MAX_TCP_CHUNKBUFFER);
		total += bytes;
	} while (bytes < 0 && total < MAX_TCP_CHUNKBUFFER);
	
	if (total <= 0) 
	{
		return;
	}
	assert(total < MAX_TCP_CHUNKBUFFER);
	
	string str(recvbuff);
	str.resize(total);

	req.parse(str);
	std::cout << str;
	auto x = R"(Recieved)";
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
		RequestChannelQueue->push(std::pair<unsigned int, Socket*>(sessionNumber++, sock.AcceptSocket()));
		auto x = R"(pushed item)";
		std::cout << x;
	}
	sock.CloseSocket();

	x = R"(canceled)";
	std::cout << x;
}
