CXX=g++
CFLAGS=
LIBS=-lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

SOURCES=src/main.cpp src/window.cpp

all:
	$(CXX) $(CFLAGS) -o game.exe $(SOURCES) $(LIBS)

.PHONY: run
run: all
	./game.exe

.PHONY: clean
clean:
	rm -f game.exe
