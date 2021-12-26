#include <string>

#include "engine/uri.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(uri) {};

TEST(uri, crf1738_full)
{
	std::string uri = "dialect+driver://user:password@host.com:4321/service";
	engine::RFC1738 uri_p(uri);

	CHECK_EQUAL((std::string)"dialect", uri_p.dialect);
	CHECK_EQUAL((std::string)"driver", uri_p.driver);
	CHECK_EQUAL((std::string)"user", uri_p.user);
	CHECK_EQUAL((std::string)"password", uri_p.password);
	CHECK_EQUAL((std::string)"host.com", uri_p.host);
	CHECK_EQUAL(4321, uri_p.port);
	CHECK_EQUAL((std::string)"service", uri_p.resource);

}

TEST(uri, crf1738_short)
{
	std::string uri = "dialect+driver://user@host.com/service";
	engine::RFC1738 uri_p(uri);

	CHECK_EQUAL((std::string)"dialect", uri_p.dialect);
	CHECK_EQUAL((std::string)"driver", uri_p.driver);
	CHECK_EQUAL((std::string)"user", uri_p.user);
	CHECK_EQUAL((std::string)"host.com", uri_p.host);
	CHECK_EQUAL(0, uri_p.port);
	CHECK_EQUAL((std::string)"service", uri_p.resource);
}

TEST(uri, crf1738_no_credentials)
{
	std::string uri = "dialect+driver://host.com/service";
	engine::RFC1738 uri_p(uri);

	CHECK_EQUAL((std::string)"dialect", uri_p.dialect);
	CHECK_EQUAL((std::string)"driver", uri_p.driver);
	CHECK_EQUAL((std::string)"host.com", uri_p.host);
	CHECK_EQUAL(0, uri_p.port);
	CHECK_EQUAL((std::string)"service", uri_p.resource);
}

TEST(uri, crf1738_test_1)
{
	std::string uri = "dialect://host.com:1234/service";
	engine::RFC1738 uri_p(uri);

	CHECK_EQUAL((std::string)"dialect", uri_p.dialect);
	CHECK_EQUAL((std::string)"dialect", uri_p.driver);
	CHECK_EQUAL((std::string)"host.com", uri_p.host);
	CHECK_EQUAL(1234, uri_p.port);
	CHECK_EQUAL((std::string)"service", uri_p.resource);
}

TEST(uri, crf1738_test_2)
{
	std::string uri = "dialect:///service";
	engine::RFC1738 uri_p(uri);

	CHECK_EQUAL((std::string)"dialect", uri_p.dialect);
	CHECK_EQUAL((std::string)"dialect", uri_p.driver);
	CHECK_EQUAL(0, uri_p.port);
	CHECK_EQUAL((std::string)"service", uri_p.resource);
}
