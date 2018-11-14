OPTFLAGS = \
  -O2

DBGFLAGS = \
  -g \
  -fsanitize=address

INCLUDES = \
  -isystem include \
  -I ../include

CXXFLAGS = \
  -std=c++11 \
  -pedantic \
  -Wall \
  -Wextra \
  -Wconversion \
  -Wsign-conversion \
  -Wshadow \
  $(OPTFLAGS) \
  $(DBGFLAGS) \
  $(INCLUDES)

OBJECTS = \
  main.o \
  test_ziggurat_normal_distribution.o

ARTIFACTS = \
  $(OBJECTS) \
  main.dSYM \
  main

.PHONY: test clean

test: main
	@./main

clean:
	rm -f $(ARTIFACTS)

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

test_ziggurat_normal_distribution.o: ../include/ziggurat.hpp
