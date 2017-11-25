
#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "memory.hpp"
#include "cpu.hpp"
#include <string>

namespace chip8 {

class Emulator
{
public:
	Emulator();

	bool loadRom(const std::string &file);
	void run();

private:
	Memory memory;
	CPU cpu;
};

}

#endif /* EMULATOR_HPP */

