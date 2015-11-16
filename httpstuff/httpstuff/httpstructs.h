#pragma once

#include <string>
#include <sstream>
#include <list>
using namespace std;
namespace MifuneCore
{
	
	enum HttpHeaderFieldPos {
			UserAgent,
			Host,
			Accept,
			AcceptLanguage,
			AcceptEncoding,
			AcceptCharset,
			KeepAlive,
			Connection,
			Cookie,
			Pragma,
			CacheControl,
			TransferEncoding,
			Date,
			Server,
			XPoweredBy,
			Expires,
			Etag,
			ContentType,
			LastModified,
			XPingback,
			Vary
		};
	namespace  HttpHeaderField 
	{
		 const string UserAgentFieldName("User-Agent");
		 const string HostFieldName("Host");
		 const string AcceptFieldName("Accept");
		 const string AcceptLanguageFieldName("Accept-Language");
		 const string AcceptEncodingFieldName("Accept-Encoding");
		 const string AcceptCharsetFieldName("Accept-Charset");
		 const string KeepAliveFieldName("Keep-Alive");
		 const string ConnectionFieldName("Connection");
		 const string CookieFieldName("Cookie");
		 const string PragmaFieldName("Pragma");
		 const string CacheControlFieldName("Cache-Control");
		 const string TransferEncodingFieldName("Transfer-Encoding");
		 const string DateFieldName("Date");
		 const string ServerFieldName("Server");
		 const string XPoweredByFieldName("X-Powered-By");
		 const string ExpiresFieldName("Expires");
		 const string EtagFieldName("Etag");
		 const string ContentTypeFieldName("Content-Type");
		 const string LastModifiedFieldName("Last-Modified");
		 const string XPingbackFieldName("X-Pingback");
		 const string VaryFieldName("Vary");


	};

	class httprequest 
	{	
	private:
		string Get;
		void parse(string buffer) 
		{
			std::stringstream stream(buffer);
			std::list<string> vector;
			string pch;
			std::getline(stream, pch);
			Get = pch;
			while (std::getline(stream, pch))
			{
				PutField(pch);
			}

		}
		void PutField(string buffer) 
		{
			stringstream stream(buffer);
			string Key;
			getline(stream, Key,':');
			if (Key.compare(HttpHeaderField::UserAgentFieldName)) {

			}
			else if (Key.compare(HttpHeaderField::UserAgentFieldName)) {
			}
			

		}
	public:
		string raw;
		map<int, string> HeaderFields;
		httprequest(string buffer) :raw(buffer)
		{
			parse(buffer);
		}

	};
}