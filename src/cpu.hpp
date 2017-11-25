
#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <array>

namespace chip8 {

class Memory;

class CPU
{
public:
	CPU(Memory &memory);

	void reset();
	// execute single instruction
	void execute();
	void updateTimers();

private:
	Memory &memory;

	std::array<uint16_t, 16> stack;
	// general purpose registers
	std::array<uint8_t, 16> v;
	// I register
	uint16_t i;
	// program counter
	uint16_t pc;
	// delay timer
	uint8_t dt;
	// sound timer
	uint8_t st;
	// stack pointer
	uint8_t sp;
};

}

#endif /* CPU_HPP */

