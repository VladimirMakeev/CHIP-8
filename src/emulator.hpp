
#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "memory.hpp"
#include "cpu.hpp"
#include "display.hpp"
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
	Display display;
	CPU cpu;
};

}

#endif /* EMULATOR_HPP */

