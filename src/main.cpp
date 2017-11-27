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

#include "emulator.hpp"
#include <iostream>
#include <exception>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cerr << "Please, specify ROM file to load." << std::endl;
		return 1;
	}

	try {
		chip8::Emulator emulator;

		if (!emulator.loadRom(argv[1])) {
			std::cerr << "Failed to load ROM file." << std::endl;
			return 1;
		}

		emulator.run();
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

