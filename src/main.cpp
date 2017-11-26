
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

