CC = g++
CFLAGS = -Wall -Wpedantic -std=c++17 -I/opt/homebrew/Cellar/sfml/3.0.2/include -L/opt/homebrew/Cellar/sfml/3.0.2/lib
SRC = main.cpp algorithms.cpp
LIBS = -lsfml-graphics -lsfml-system -lsfml-window
OUT = sorting

sorting:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LIBS)

clean:
	rm $(OUT)
