#include <string>

#include "engine.h"

#include "CppUTest/TestHarness.h"

TEST_GROUP(engine)
{
};

TEST(engine, create_engine_full)
{
	std::string uri = "dialect+driver://user:password@host.com:4321/service";
	Engine* engine = create_engine(uri.c_str());

	CHECK_EQUAL((std::string)"dialect", engine->dialect);
	CHECK_EQUAL((std::string)"driver", engine->driver);
	CHECK_EQUAL((std::string)"user", engine->user);
	CHECK_EQUAL((std::string)"password", engine->password);
	CHECK_EQUAL((std::string)"host.com", engine->host);
	CHECK_EQUAL(4321, engine->port);
	CHECK_EQUAL((std::string)"service", engine->resource);

	free_engine(engine);
}

TEST(engine, create_engine_short)
{
	std::string uri = "dialect+driver://user@host.com/service";
	Engine* engine = create_engine(uri.c_str());

	CHECK_EQUAL((std::string)"dialect", engine->dialect);
	CHECK_EQUAL((std::string)"driver", engine->driver);
	CHECK_EQUAL((std::string)"user", engine->user);
	CHECK_EQUAL((std::string)"host.com", engine->host);
	CHECK_EQUAL(0, engine->port);
	CHECK_EQUAL((std::string)"service", engine->resource);

	free_engine(engine);
}

TEST(engine, create_engine_no_credentials)
{
	std::string uri = "dialect+driver://host.com/service";
	Engine* engine = create_engine(uri.c_str());

	CHECK_EQUAL((std::string)"dialect", engine->dialect);
	CHECK_EQUAL((std::string)"driver", engine->driver);
	CHECK_EQUAL((std::string)"host.com", engine->host);
	CHECK_EQUAL(0, engine->port);
	CHECK_EQUAL((std::string)"service", engine->resource);

	free_engine(engine);
}
