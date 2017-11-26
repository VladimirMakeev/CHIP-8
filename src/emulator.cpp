
#include "emulator.hpp"
#include <cstdint>
#include <fstream>
#include <vector>

namespace chip8 {

Emulator::Emulator() : cpu(memory, display)
{
}

bool Emulator::loadRom(const std::string &file)
{
	std::ifstream in(file, std::ios_base::binary);

	if (!in) {
		return false;
	}

	in.seekg(0, in.end);

	const size_t length = in.tellg();

	in.seekg(0, in.beg);

	std::vector<uint8_t> rom(length);

	in.read((char*)&rom[0], length);

	return memory.loadRom(rom);
}

void Emulator::run()
{
	cpu.reset();

	while (true) {
		cpu.execute();
		cpu.updateTimers();
	}
}

}

