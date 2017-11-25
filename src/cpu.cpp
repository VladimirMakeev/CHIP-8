
#include "cpu.hpp"
#include "memory.hpp"

namespace chip8 {

CPU::CPU(Memory &memory) : memory(memory)
{
}

void CPU::reset()
{
	stack.fill(0);
	v.fill(0);
	i = 0;
	pc = memory.prgStart();
	sp = 0;
	dt = 0;
	st = 0;
}

void CPU::execute()
{
}

void CPU::updateTimers()
{
	if (dt) {
		dt--;
	}

	if (st) {
		st--;
	}
}

}

