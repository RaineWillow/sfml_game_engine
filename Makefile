CXX=g++
CFLAGS=
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

SOURCES=src/main.cpp
CORE=src/core/window.cpp
SCENE=src/scene/game.cpp src/scene/main_menu.cpp

all:
	$(CXX) $(CFLAGS) -o game.exe $(SOURCES) $(CORE) $(SCENE) $(LIBS)

.PHONY: run
run:
	./game.exe
.PHONY: crun
crun: all
	./game.exe
.PHONY: clean
clean:
	rm -f game.exe
