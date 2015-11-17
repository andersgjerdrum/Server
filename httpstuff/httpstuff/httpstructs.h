#pragma once

#include <string>
#include <sstream>
#include <map>
using namespace std;
namespace MifuneCore
{
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
		 const string XForwardForFieldName("X-Forwarded-For");


	};

	class httprequest 
	{	
	private:
		string Get;
		void parse(string buffer) 
		{
			std::stringstream stream(buffer);
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
			string Value;
			getline(stream, Value);
			RawHeaderFields.insert(std::pair<string,string>(Key, Value.substr(Value.find_first_not_of(' '), Value.length())));
		}

	public:
		std::map<string, string> RawHeaderFields;
		httprequest(string buffer) :Raw(buffer)
		{
			parse(buffer);
		}

	};
}