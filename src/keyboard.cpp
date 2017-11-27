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

#include "keyboard.hpp"

namespace chip8 {

void Keyboard::setKeyPressed(uint8_t key, bool pressed)
{
	keys[key & 0xf] = pressed;
}

bool Keyboard::isKeyPressed(uint8_t key) const
{
	return keys[key & 0xf];
}

int Keyboard::getKeyPressed() const
{
	for (size_t i = 0; i < keys.size(); i++) {
		if (isKeyPressed(i)) {
			return i;
		}
	}

	return -1;
}

}

