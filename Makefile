CC = gcc
CFLAGS = -Wall -g -Iinclude -I/usr/include/json-c
SRC = src/main.c src/tree.c src/artist.c src/music.c
OBJ = $(SRC:.c=.o)
TARGET = build/music_db

all: build_dir $(TARGET)

build_dir:
	mkdir -p build

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -ljson-c

clean:
	rm -rf build
	rm -f $(OBJ)