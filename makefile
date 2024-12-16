CXX = clang++ 
CXXFLAGS =  -IC:/msys64/clang64/include/SDL2 -Dmain=SDL_main -Wall -Oz -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-stack-protector  
TARGET = Paint-doku

# Use pkg-config to retrieve the static linker flags
PKG_CONFIG_FLAGS = --static --libs SDL2 SDL2_ttf SDL2_mixer

# Platform-specific linker flags
ifeq ($(OS), Windows_NT)
	LDFLAGS = -static $(shell pkg-config $(PKG_CONFIG_FLAGS))  -Wl,--gc-sections -s
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

main.o: $(wildcard *.cpp) force
	$(CXX) -c main.cpp $(CXXFLAGS)

resources.o: resources.rc force
	windres resources.rc -O coff -o resources.o

clean:
	rm -f $(TARGET) *.o

force: