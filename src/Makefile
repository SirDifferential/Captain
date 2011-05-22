CC=g++
CFLAGS=-lGL -lGLU -lGLEW -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf -g -O0 2>&1
SOURCES=main.cpp programManager.cpp objectManager.cpp inputManager.cpp timedFunctions.cpp toolbox.cpp objLoader.cpp object3d.cpp renderer.cpp sprite.cpp text.cpp arena.cpp stars.cpp ship.cpp pcharacter.cpp square.cpp component.cpp menu.cpp planet.cpp sun.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Captain

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	$(CC) -c -g -O0 -fno-threadsafe-statics -o $@ $<

clean:
	rm *.o
