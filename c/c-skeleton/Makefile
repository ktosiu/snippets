#Should set your lib name here
LIB_NAME=YOUR_LIBRARY

# OPTFLAGS lets people augment the build options as needed
CFLAGS=-g -o2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
# Used when linking a library. OPTLIBS enables the user to augment needed options.
LIBS=-ldl $(OPTLIBS)
# ?= means if not set then use this one as default.
PREFIX?=/usr/local

# wildcard search the .c files in src and below src.
SOURCES=$(wildcard src/**/*.c src/*.c)
# Tell patsubst to change all the %.c extension to %.o and then
# those are assigned to OBJECTS
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c, %, $(TEST_SRC))

# the "YOUR_LIBRARY" should be the actual name your library is.
TARGET=build/lib$(LIB_NAME).a
SO_TARGET=$(patsubst %.a, %.so, $(TARGET))

# The Target build
all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Test
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name ".gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# THe installer
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The checker
BADFUNCS='[^_.>A-Za-z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially danderous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
