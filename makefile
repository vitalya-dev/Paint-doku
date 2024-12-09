CXX = g++
CXXFLAGS =  -std=c++17 -Wall
TARGET = paint_doku

# Platform-specific linker flags
ifeq ($(OS), Windows_NT)
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer
	BINARY = $(TARGET).exe
else
	LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
	BINARY = $(TARGET)
endif

all: $(TARGET)
	./$(BINARY)

$(TARGET): main.o
	$(CXX) -o $(TARGET) main.o $(LDFLAGS)

main.o: $(wildcard *.cpp)
	$(CXX) -c main.cpp $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o
