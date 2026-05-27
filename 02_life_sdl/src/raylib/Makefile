CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET = life_game

all: $(TARGET)

$(TARGET): life_game_raylib.c
	$(CC) $(CFLAGS) life_game_raylib.c $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
