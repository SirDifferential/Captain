CC=g++
CFLAGS=-g -o0 2>&1
LDFLAGS=-std=c++0x -lGL -lGLU -lGLEW -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf
SOURCES=$(wildcard ./*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Kapteeni

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(LDFLAGS) -c -g -O0 -fno-threadsafe-statics -o $@ $<

clean:
	rm *.o

