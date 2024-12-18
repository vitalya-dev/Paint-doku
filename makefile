CXX = gcc
CXXFLAGS = -Dmain=SDL_main -Os -s
TARGET = Paint-doku

# Use pkg-config to retrieve the static linker flags
PKG_CONFIG_FLAGS = --static --libs-only-l SDL2 SDL2_ttf SDL2_mixer

# Platform-specific linker flags
ifeq ($(OS), Windows_NT)
	LDFLAGS = -static $(shell pkg-config $(PKG_CONFIG_FLAGS)) -mwindows 
	BINARY = $(TARGET).exe
else
	LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
	BINARY = $(TARGET)
endif

.PHONY: force

all: $(TARGET)
	./$(BINARY)

$(TARGET): main.o resources.o
	$(CXX) -o $(TARGET) main.o resources.o $(LDFLAGS)
	strip $(BINARY)

main.o: $(wildcard *.cpp) force
	$(CXX) -c main.cpp $(CXXFLAGS)

resources.o: resources.rc force
	windres resources.rc  -O coff -o resources.o

clean:
	rm -f $(TARGET) *.o

force: