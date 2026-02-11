CC = g++
SRC = main.cpp algorithms.cpp
LIBS = -lsfml-graphics -lsfml-system -lsfml-window
OUT = sorting
CFLAGS = -Wall -Wpedantic -std=c++17 -I/opt/homebrew/Cellar/sfml/3.0.2/include -L/opt/homebrew/Cellar/sfml/3.0.2/lib

.PHONY: all clean

all: $(OUT)

$(OUT):
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LIBS)

clean:
	rm $(OUT)
