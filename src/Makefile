CC=g++
CFLAGS=-lGL -lGLU -lGLEW -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf -g -O0 2>&1
SOURCES=main.cpp sprite.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Captain

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	$(CC) -c -g -O0 -fno-threadsafe-statics -o $@ $<

clean:
	rm *.o
