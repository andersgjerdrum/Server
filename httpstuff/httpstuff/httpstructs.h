#pragma once

#include <string>
#include <sstream>
#include <list>
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
			string Value;
			getline(stream, Value, ':');
			if (Key.compare(HttpHeaderField::UserAgentFieldName)) {
				UserAgent = Value;
			}
			else if (Key.compare(HttpHeaderField::HostFieldName)) {
				Host = Value;
			}
			else if (Key.compare(HttpHeaderField::AcceptFieldName)) {
				Accept = Value;
			}
			else if (Key.compare(HttpHeaderField::AcceptLanguageFieldName)) {
				AcceptLanguage = Value;
			}
			else if (Key.compare(HttpHeaderField::AcceptEncodingFieldName)) {
				AcceptEncoding = Value;
			}
			else if (Key.compare(HttpHeaderField::AcceptCharsetFieldName)) {
				AcceptCharset = Value;
			}
			else if (Key.compare(HttpHeaderField::KeepAliveFieldName)) {
				KeepAlive = Value;
			}
			else if (Key.compare(HttpHeaderField::ConnectionFieldName)) {
				Connection = Value;
			}
			else if (Key.compare(HttpHeaderField::CookieFieldName)) {
				Cookie = Value;
			}
			else if (Key.compare(HttpHeaderField::PragmaFieldName)) {
				Pragma = Value;
			}
			else if (Key.compare(HttpHeaderField::CacheControlFieldName)) {
				CacheControl = Value;
			}
			else if (Key.compare(HttpHeaderField::TransferEncodingFieldName)) {
				TransferEncoding = Value;
			}
			else if (Key.compare(HttpHeaderField::DateFieldName)) {
				Date = Value;
			}
			else if (Key.compare(HttpHeaderField::ServerFieldName)) {
				Server = Value;
			}
			else if (Key.compare(HttpHeaderField::XPoweredByFieldName)) {
				XPoweredBy = Value;
			}
			else if (Key.compare(HttpHeaderField::ExpiresFieldName)) {
				Expires = Value;
			}
			else if (Key.compare(HttpHeaderField::EtagFieldName)) {
				Etag = Value;
			}
			else if (Key.compare(HttpHeaderField::ContentTypeFieldName)) {
				ContentType = Value;
			}
			else if (Key.compare(HttpHeaderField::LastModifiedFieldName)) {
				LastModified = Value;
			}
			else if (Key.compare(HttpHeaderField::XPingbackFieldName)) {
				XPingback = Value;
			}
			else if (Key.compare(HttpHeaderField::VaryFieldName)) {
				Vary = Value;
			}


		}
	public:
		string Raw;
		string UserAgent;
		string Host;
		string Accept;
		string AcceptLanguage;
		string AcceptEncoding;
		string AcceptCharset;
		string KeepAlive;
		string Connection;
		string Cookie;
		string Pragma;
		string CacheControl;
		string TransferEncoding;
		string Date;
		string Server;
		string XPoweredBy;
		string Expires;
		string Etag;
		string ContentType;
		string LastModified;
		string XPingback;
		string Vary;
		httprequest(string buffer) :Raw(buffer)
		{
			parse(buffer);
		}

	};
}