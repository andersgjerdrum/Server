#pragma once

namespace MifuneCore 
{
	class ISocket
	{
	public:
		virtual void CloseSocket() = 0;
		virtual void BindSocket(unsigned int port) = 0;
		virtual void Connect(wchar_t ipAddr, int port) = 0;
		virtual void Send(char * buffer, int startaddr, int buffersize) = 0;
		virtual void Recieve(char * buffer, int startaddr, int buffersize) = 0;
		virtual void OpenSocket() = 0;
		virtual void ListenSocket() = 0;
		virtual ISocket& AcceptSocket() = 0;
	};
}