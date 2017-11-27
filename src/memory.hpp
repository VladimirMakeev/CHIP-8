/*
 * This file is part of the CHIP-8 emulator (https://github.com/VladimirMakeev/CHIP-8).
 * Copyright (C) 2017 Vladimir Makeev.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <vector>
#include <array>

namespace chip8 {

class Memory
{
public:
	Memory();

	// program start address
	static constexpr uint16_t prgStart() { return 0x200; }
	// font start address
	static constexpr uint16_t fontStart() { return 0x50; }

	bool loadRom(const std::vector<uint8_t> &rom);

	uint8_t& operator[](uint16_t address)
	{
		return memory[address & 0xfff];
	}

private:
	void loadFont();

	std::array<uint8_t, 4 * 1024> memory;
};

}

#endif /* MEMORY_HPP */

