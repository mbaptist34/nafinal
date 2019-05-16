CC = g++
CFLAGS = -c -Wall -I/src
SOURCES = src/quat.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = quat_test

GTEST_DIR = googletest/goo
GTEST_FLAGS = -isystem $(GTEST_DIR)/include

libgtest.a:
	$(CC) $(GTEST_FLAGS) -I$(GTEST_DIR) \
		-pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o	


quat_test: $(SOURCES) $(OBJECTS) libgtest.a
	$(CC) $(GTEST_FLAGS) -pthread src/quat_test.cpp libgtest.a src/quat.o -o quat_test

runAllTests: quat_test
	./quat_test

clean:
	touch dummy.o
	rm *.o
	touch src/dummo.o
	rm src/*.o
	
	touch quat_test
	rm quat_test

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
