#
# This file is part of the CHIP-8 emulator (https://github.com/VladimirMakeev/CHIP-8).
# Copyright (C) 2017 Vladimir Makeev.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

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

