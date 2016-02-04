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
	
#define HTTP_GET  1
#define HTTP_POST  2
#define HTTP_PUT  3

	std::map<string, int> RequestMethods = { 
		{"GET", HTTP_GET },
		{"POST", HTTP_POST },
		{"PUT",	HTTP_PUT } 
	};

	class httprequest 
	{	
	public:
		void parse(string buffer) 
		{
			std::stringstream stream(buffer);
			ExtractRequestLine(stream);
			string pch;
			int CurrentByte = 0;

			//read headers
			//TODO: support content length and transfer encoding
			while (std::getline(stream, pch))
			{
				//if not header read the rest to body
				if (pch.find(":") == string::npos) {
					body = buffer.substr(CurrentByte);
					break;
				}
				PutField(pch);
				CurrentByte = stream.tellg();
			}
		}
	private:
		void ExtractRequestLine(std::stringstream &stream) {
			string pch;
			std::getline(stream, pch);
			int first_separator = pch.find_first_of(' ');
			int second_separator = pch.find(' ', first_separator);

			method = RequestMethods[pch.substr(0, first_separator)];

			path = pch.substr(first_separator, second_separator);
			version = pch.substr(second_separator);
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
		int method;
		std::string path;
		std::string version;
		std::map<string, string> RawHeaderFields;
		std::string body;
		httprequest()
		{
		}
	};
}