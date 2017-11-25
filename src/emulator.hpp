
#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include <string>

namespace chip8 {

class Emulator
{
public:
	Emulator();

	bool loadRom(const std::string &file);
	void run();
};

}

#endif /* EMULATOR_HPP */

