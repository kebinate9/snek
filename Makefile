CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = $(shell pkg-config --libs raylib)
INCLUDES = $(shell pkg-config --cflags raylib)

TARGET = game
SRC = snek.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
