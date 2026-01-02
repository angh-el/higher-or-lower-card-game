CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET = higher_lower_game
SRC = src/core/Card.cpp src/core/Deck.cpp src/core/HigherLowerGame.cpp src/main.cpp
OBJ = $(SRC:.cpp=.o)

.PHONY: all build run clean

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
