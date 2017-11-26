
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++11 -O3
LDFLAGS =

UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)
# Mac OS
CXXFLAGS += -I/Library/Frameworks/SDL2.framework/Headers/
LDFLAGS += -F/Library/Frameworks/ -framework SDL2
endif

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

