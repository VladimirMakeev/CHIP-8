
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

void CPU::ins_0nnn(uint16_t)
{
}

void CPU::ins_00e0(uint16_t)
{
}

void CPU::ins_00ee(uint16_t)
{
}

void CPU::ins_1nnn(uint16_t)
{
}

void CPU::ins_2nnn(uint16_t)
{
}

void CPU::ins_3xnn(uint16_t)
{
}

void CPU::ins_4xnn(uint16_t)
{
}

void CPU::ins_5xy0(uint16_t)
{
}

void CPU::ins_6xnn(uint16_t)
{
}

void CPU::ins_7xnn(uint16_t)
{
}

void CPU::ins_8xy0(uint16_t)
{
}

void CPU::ins_8xy1(uint16_t)
{
}

void CPU::ins_8xy2(uint16_t)
{
}

void CPU::ins_8xy3(uint16_t)
{
}

void CPU::ins_8xy4(uint16_t)
{
}

void CPU::ins_8xy5(uint16_t)
{
}

void CPU::ins_8xy6(uint16_t)
{
}

void CPU::ins_8xy7(uint16_t)
{
}

void CPU::ins_8xye(uint16_t)
{
}

void CPU::ins_9xy0(uint16_t)
{
}

void CPU::ins_annn(uint16_t)
{
}

void CPU::ins_bnnn(uint16_t)
{
}

void CPU::ins_cxnn(uint16_t)
{
}

void CPU::ins_dxyn(uint16_t)
{
}

void CPU::ins_ex9e(uint16_t)
{
}

void CPU::ins_exa1(uint16_t)
{
}

void CPU::ins_fx07(uint16_t)
{
}

void CPU::ins_fx0a(uint16_t)
{
}

void CPU::ins_fx15(uint16_t)
{
}

void CPU::ins_fx18(uint16_t)
{
}

void CPU::ins_fx1e(uint16_t)
{
}

void CPU::ins_fx29(uint16_t)
{
}

void CPU::ins_fx33(uint16_t)
{
}

void CPU::ins_fx55(uint16_t)
{
}

void CPU::ins_fx65(uint16_t)
{
}

}

