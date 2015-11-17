#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\httpstuff\httpstructs.h"
#include "..\httpstuff\ThreadPool.h"
#include <atomic>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace MifuneCore;
namespace httpstuffunittests
{		
	static std::atomic<int> cnt = ATOMIC_VAR_INIT(0);

	TEST_CLASS(MifuneCoreTests)
	{
	public:
		
		TEST_METHOD(httpstructs)
		{
			httprequest req(R"foo(GET /tutorials/other/top-20-mysql-best-practices/ HTTP/1.1
Host: net.tutsplus.com
User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.5) Gecko/20091102 Firefox/3.5.5 (.NET CLR 3.5.30729)
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip,deflate
Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
Keep-Alive: 300
Connection: keep-alive
Cookie: PHPSESSID=r2t5uvjq435r4q7ib3vtdjq120
Pragma: no-cache
Cache-Control: no-cache
X-Forwarded-For: 192.168.10.1
)foo");

			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::HostFieldName].compare("net.tutsplus.com") == 0,L"HostFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::UserAgentFieldName].compare("Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.5) Gecko/20091102 Firefox/3.5.5 (.NET CLR 3.5.30729)") == 0,L"UserAgentFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::AcceptFieldName].compare("text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8") == 0, L"AcceptFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::AcceptLanguageFieldName].compare("en-us,en;q=0.5") == 0, L"AcceptLanguageFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::AcceptEncodingFieldName].compare("gzip,deflate") == 0, L"AcceptEncodingFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::AcceptCharsetFieldName].compare("ISO-8859-1,utf-8;q=0.7,*;q=0.7") == 0, L"AcceptCharsetFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::KeepAliveFieldName].compare("300") == 0, L"KeepAliveFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::ConnectionFieldName].compare("keep-alive") == 0, L"ConnectionFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::CookieFieldName].compare("PHPSESSID=r2t5uvjq435r4q7ib3vtdjq120") == 0, L"CookieFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::PragmaFieldName].compare("no-cache") == 0, L"PragmaFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::CacheControlFieldName].compare("no-cache") == 0, L"CacheControlFieldName should be equal");
			Assert::IsTrue(req.RawHeaderFields[HttpHeaderField::XForwardForFieldName].compare("192.168.10.1") == 0, L"XForwardForFieldName should be equal");
		}

		TEST_METHOD(threadpooltest) 
		{

			ThreadPool *thrdpl = new ThreadPool(10);
			for (int i = 0; i < 100; i++) 
			{
				thrdpl->enqueue([]
				{
					std::atomic_fetch_add(&cnt, 1);
				});
			}
			delete thrdpl;

			Assert::AreEqual(cnt.load(), 100);

		}
	};
}