CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
TARGET = higher_lower_game
OBJ = $(SRC:.cpp=.o)


SRC = src/core/Card.cpp \
      src/core/Deck.cpp \
      src/core/HigherLowerGame.cpp \
      src/ui/Renderer.cpp \
      src/ui/SDLApp.cpp \
      src/main.cpp


.PHONY: all build run clean

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
