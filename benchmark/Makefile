OPTFLAGS = \
  -mtune=native \
  -funsafe-math-optimizations \
  -O2

INCLUDES = \
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
  $(INCLUDES)

TARGETS = \
  bench_normal_distribution

.PHONY: all clean

all: $(TARGETS)
	@:

clean:
	rm -f $(TARGETS)
