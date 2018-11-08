OPTFLAGS = \
  -O2

CXXFLAGS = \
  -std=c++11 \
  -pedantic \
  -Wall \
  -Wextra \
  -Wconversion \
  -Wsign-conversion \
  -Wshadow \
  $(OPTFLAGS)

TARGETS = \
  generate_normal_ziggurat

.PHONY: all clean

all: $(TARGETS)
	@:

clean:
	rm -f $(TARGETS)
