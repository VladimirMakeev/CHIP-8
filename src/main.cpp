
#include "emulator.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cerr << "Please, specify ROM file to load." << std::endl;
		return 1;
	}

	chip8::Emulator emulator;

	if (!emulator.loadRom(argv[1])) {
		std::cerr << "Failed to load ROM file." << std::endl;
		return 1;
	}

	emulator.run();
}

