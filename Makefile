CXXFLAGS += -Wall -g

SRC_DIR = ./src
BIN_DIR = ./bin
SOURCES=$(wildcard *.cpp)

all: directories task1 task2

directories:
	mkdir -p $(BIN_DIR)

%: $(SRC_DIR)/%.cpp directories
	$(CXX) $(CXXFLAGS) $< -o $(BIN_DIR)/$@

clean:
	rm -rvf $(BIN_DIR)
