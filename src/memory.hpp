
#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <vector>
#include <array>

namespace chip8 {

class Memory
{
public:
	Memory() = default;

	// program start address
	static constexpr uint16_t prgStart() { return 0x200; }

	bool loadRom(const std::vector<uint8_t> &rom);

	uint8_t& operator[](uint16_t address)
	{
		return memory[address & 0xfff];
	}

private:
	std::array<uint8_t, 4 * 1024> memory;
};

}

#endif /* MEMORY_HPP */

