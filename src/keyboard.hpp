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

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cstdint>
#include <array>

namespace chip8 {

class Keyboard
{
public:
	void setKeyPressed(uint8_t key, bool pressed);
	bool isKeyPressed(uint8_t key) const;
	int getKeyPressed() const;

private:
	std::array<bool, 16> keys;
};

}

#endif /* KEYBOARD_HPP */

