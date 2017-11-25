
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++11 -O3

SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,%.o,$(SRC))
DEP := $(OBJ:%.o=%.d)

TARGET := chip8emu

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

.PHONY: c,clean

c clean:
	$(RM) $(TARGET) $(OBJ) $(DEP)

-include $(DEP)

