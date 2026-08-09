CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude

MAIN_SOURCES = src/main.cpp src/inventory_report.cpp
TEST_SOURCES = tests/test_inventory_report.cpp src/inventory_report.cpp

main: $(MAIN_SOURCES)
	$(CXX) $(CXXFLAGS) $(MAIN_SOURCES) -o main

test: $(TEST_SOURCES)
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) -o test_runner
	./test_runner

clean:
	rm -f main test_runner
