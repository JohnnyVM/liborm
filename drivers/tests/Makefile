TEST_SOURCES := $(wildcard src/*.cpp)
TEST_OBJECTS := $(patsubst %.cpp,%.o,${TEST_SOURCES})
TEST_DEPENDENCIES := $(patsubst %.cpp,%.d,${TEST_SOURCES})

TEST_C_SOURCES := $(wildcard src/*.c)
TEST_C_OBJECTS := $(patsubst %.c,%.o,${TEST_C_SOURCES})
TEST_C_DEPENDENCIES := $(patsubst %.c,%.d,${TEST_C_SOURCES})

OBJECTS := $(patsubst %,../${TEST_DRIVER}/%,${OBJECTS}) ${TEST_OBJECTS} ${TEST_C_OBJECTS}

INCLUDE_FLAGS := -I../${TEST_DRIVER}/include -I$(CPPUTEST_HOME)/include -I${LIBDICT_HOME}/include -I${LIBARRAY_HOME}/include
LD_FLAGS += -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt -lsqlite3
CPPFLAGS += ${INCLUDE_FLAGS} ${COMMON_FLAGS}
CFLAGS += ${INCLUDE_FLAGS} ${COMMON_FLAGS}
DEFINES := -DTEST_DRIVER=${TEST_DRIVER}

tests: ${TEST_OBJECTS} ${TEST_C_OBJECTS}
	${CXX} ${DEFINES} ${CPPFLAGS} -MMD -o $@ ${OBJECTS} ${LD_FLAGS}

${TEST_OBJECTS}: %.o: %.cpp
	${CXX} ${DEFINES} ${CPPFLAGS} -MMD -c $< -o $@

${TEST_C_OBJECTS}: %.o: %.c
	${CC} ${DEFINES} ${CFLAGS} -MMD -c $< -o $@

-include $(TEST_DEPENDENCIES)

clean:
	-rm ${TEST_OBJECTS} ${TEST_DEPENDENCIES} ${TEST_C_OBJECTS} ${TEST_C_DEPENDENCIES} tests
