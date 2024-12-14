CXX = clang++ 
CXXFLAGS =  -IC:/msys64/ucrt64/include/SDL2 -Dmain=SDL_main -fuse-ld=lld -Wall
TARGET = paint_doku

# Platform-specific linker flags
ifeq ($(OS), Windows_NT)
	LDFLAGS = -LC:/msys64/ucrt64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -mwindows
	BINARY = $(TARGET).exe
else
	LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
	BINARY = $(TARGET)
endif

.PHONY: force

all: $(TARGET)
	./$(BINARY)

$(TARGET): main.o
	$(CXX) -o $(TARGET) main.o $(LDFLAGS)

main.o: $(wildcard *.cpp) force
	$(CXX) -c main.cpp $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o

force: