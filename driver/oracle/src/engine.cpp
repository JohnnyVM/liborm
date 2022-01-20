#include <stdexcept>
#include <system_error>
#include <mutex>
#include <memory>

#include "engine/engine.h"
#include "connection/connection.h"
#include "driver/oracle/engine.hpp"
#include "inner_driver_oracle.h"

static std::once_flag enable_threads;

#define CHECK_OUTPUT_SNPRINTF(LEN, OUT) \
	do {\
		if (LEN < 0) { \
			throw std::system_error(errno, std::generic_category(), "snprintf");\
		}\
		if( (size_t)LEN >= OUT ) {\
			throw std::length_error("Not enought buffer passed for allocate the values");\
		}\
	}while(0)

struct oracle_connection_data driver::oracle::Engine::params_to_conn() {
	int length;
	struct oracle_connection_data data;
	// \todo mutext ward this
	static int counter = 0;

	length = snprintf((char*)data.user, sizeof data.user, "%s", this->params.user.c_str());
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.user);

	length = snprintf((char*)data.password, sizeof data.password, "%s", this->params.password.c_str());
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.password);

	length = snprintf((char*)data.connect_string, sizeof data.connect_string, "%s", this->params.host.c_str());
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.connect_string);

	length = snprintf((char*)data.dbname, sizeof data.dbname, "dbname_%i", counter);
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.dbname);

	length = snprintf((char*)data.input_descriptor, sizeof data.input_descriptor, "input_descriptor_%i", counter);
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.input_descriptor);

	length = snprintf((char*)data.output_descriptor, sizeof data.output_descriptor, "output_descriptor_%i", counter);
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.output_descriptor);

	data.ctx = nullptr;

	counter++;

	return data;
}
#undef CHECK_OUTPUT

std::unique_ptr<PConnection> driver::oracle::Engine::connect() {
	struct oracle_connection_data conn = params_to_conn();

	std::call_once(enable_threads, driver_ora_enable_threads);
	conn_state state = driver_ora_connect(&conn);
	if(state) {
		assert(!"Could not open connection to the database");
		throw std::runtime_error("Could not open connection to the database"); // TODO move to custom exception
	}
	std::unique_ptr<PConnection>connection = std::make_unique<driver::oracle::Connection>(conn);
	return connection;
}
