#include <stdexcept>
#include <system_error>
#include <string>

#include "engine.h"
#include "driver/oracle.hpp"
#include "driver/oracle/cursor.hpp"
#include "connection.h"
#include "inner_driver_oracle.h"

#define CHECK_OUTPUT_SNPRINTF(LEN, OUT) \
	do {\
		if (LEN < 0) { \
			throw std::system_error(errno, std::generic_category(), "snprintf");\
		}\
		if( (size_t)LEN >= OUT ) {\
			throw std::length_error("Not enought buffer passed for allocate the values");\
		}\
	}while(0)

driver::Oracle::Oracle(Engine* engine) : Connection(engine) {
	int length;
	// \todo mutext ward this
	static int counter = 0;

	length = snprintf((char*)data.user, sizeof data.user, "%s", engine->user.c_str());
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.user);

	length = snprintf((char*)data.password, sizeof data.password, "%s", engine->password.c_str());
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.password);

	length = snprintf((char*)data.connect_string, sizeof data.connect_string, "%s", engine->host.c_str());
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.connect_string);

	snprintf((char*)data.dbname, sizeof data.dbname, "dbname_%i", counter);
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.dbname);

	snprintf((char*)data.input_descriptor, sizeof data.input_descriptor, "input_descriptor_%i", counter);
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.input_descriptor);

	snprintf((char*)data.output_descriptor, sizeof data.output_descriptor, "output_descriptor_%i", counter);
	CHECK_OUTPUT_SNPRINTF(length, sizeof data.output_descriptor);

	data.cursor_open = 0;

	counter++;
}
#undef CHECK_OUTPUT

/** The desctructor close the connection */
driver::Oracle::~Oracle() {
	this->close();
}

struct connection_state driver::Oracle::open(void) {
	struct connection_state state = INIT_CONNECTION_STATE;
	state = driver_ora_connect(&data);
	return state;
}

struct connection_state driver::Oracle::close(void) {
	struct connection_state state = INIT_CONNECTION_STATE;
	state = driver_ora_close(&data);
	return state;
}

struct connection_state driver::Oracle::begin(void) {
	struct connection_state state = INIT_CONNECTION_STATE;
	state.error = NO_IMPLEMENTED;
	return state;
}

struct connection_state driver::Oracle::commit(void) {
	struct connection_state state = INIT_CONNECTION_STATE;
	state = driver_ora_commit(&data);
	return state;
}

struct connection_state driver::Oracle::rollback(void) {
	struct connection_state state = INIT_CONNECTION_STATE;
	state.error = NO_IMPLEMENTED;
	return state;
}

struct connection_state driver::Oracle::execute_many(const char* stmt, void* params) {
	struct connection_state state = INIT_CONNECTION_STATE;
	struct connection_state cstate = INIT_CONNECTION_STATE;
	state = driver_ora_execute_many(&data, stmt, params);
	if(state.error) {
		return state;
	}
	driver::oracle::Cursor* c = new driver::oracle::Cursor(&data);
	state.cursor = c;
	if(state.tuples_ok) {
		cstate = c->open();
		if(cstate.error) {
			state.tuples_ok = false;
			state = cstate;
			delete c;
		}
	}
	c->_changes = state.changes;;
	return state;
}

struct connection_state driver::Oracle::execute(const char* stmt) {
	struct connection_state state = INIT_CONNECTION_STATE;
	state = execute_many(stmt, nullptr);
	return state;
}

