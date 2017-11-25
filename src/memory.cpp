
#include "memory.hpp"
#include <algorithm>

namespace chip8 {

bool Memory::loadRom(const std::vector<uint8_t> &rom)
{
	auto rom_start = std::begin(memory) + prgStart();

	std::copy(std::begin(rom), std::end(rom), rom_start);

	return true;
}

}

