CC=gcc
CFLAGS=-c -g -I.
LDFLAGS=
SOURCES=main.c hello.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=hello
all:$(SOURCES) $(EXECUTABLE)
$(EXECUTABLE):$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf hello *.o

