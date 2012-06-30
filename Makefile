CXX=g++
CXXFLAGS=-Wall -Wextra -g

all: range_tree_tests range_tree_c_api.o

range_tree_tests: range_tree.hh tests.cc Makefile
	$(CXX) -o range_tree_tests tests.cc $(CXXFLAGS)

range_tree_c_api.o: range_tree_c_api.cc range_tree_c_api.h range_tree.hh Makefile
	$(CXX) -o range_tree_c_api.o -c range_tree_c_api.cc $(CXXFLAGS)
