
#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <array>

namespace chip8 {

class Memory;
class Display;

class CPU
{
public:
	CPU(Memory &memory, Display &display);

	void reset();
	// execute single instruction
	void execute();
	void updateTimers();

private:
	// instruction handlers
	// jump to machine code routine at nnn
	void ins_0nnn(uint16_t opcode);
	// clear the display
	void ins_00e0(uint16_t opcode);
	// return from a subroutine
	void ins_00ee(uint16_t opcode);
	// jump to nnn
	void ins_1nnn(uint16_t opcode);
	// call subroutine at nnn
	void ins_2nnn(uint16_t opcode);
	// skip next instruction if vx == nn
	void ins_3xnn(uint16_t opcode);
	// skip next instruction if vx != nn
	void ins_4xnn(uint16_t opcode);
	// skip next instruction if vx == vy
	void ins_5xy0(uint16_t opcode);
	// set vx = nn
	void ins_6xnn(uint16_t opcode);
	// set vx = vx + nn
	void ins_7xnn(uint16_t opcode);
	// set vx = vy
	void ins_8xy0(uint16_t opcode);
	// set vx = vx | vy
	void ins_8xy1(uint16_t opcode);
	// set vx = vx & vy
	void ins_8xy2(uint16_t opcode);
	// set vx = vx ^ vy
	void ins_8xy3(uint16_t opcode);
	// set vx = vx + vy, set vf = carry
	void ins_8xy4(uint16_t opcode);
	// set vx = vx - vy, set vf = !borrow
	void ins_8xy5(uint16_t opcode);
	// set vx = vx >> 1
	void ins_8xy6(uint16_t opcode);
	// set vx = vy - vx, set vf = !borrow
	void ins_8xy7(uint16_t opcode);
	// set vx = vx << 1
	void ins_8xye(uint16_t opcode);
	// skip next instruction if vx != vy
	void ins_9xy0(uint16_t opcode);
	// set i = nnn
	void ins_annn(uint16_t opcode);
	// jump to nnn + v0
	void ins_bnnn(uint16_t opcode);
	// set vx = rand() & nn
	void ins_cxnn(uint16_t opcode);
	// display n-byte sprite starting at memory location i
	void ins_dxyn(uint16_t opcode);
	// skip next instruction if key with the value of vx is pressed
	void ins_ex9e(uint16_t opcode);
	// skip next instruction if key with the value of vx is not pressed
	void ins_exa1(uint16_t opcode);
	// set vx = dt
	void ins_fx07(uint16_t opcode);
	// wait for a key press, store the value of the key in vx
	void ins_fx0a(uint16_t opcode);
	// set dt = vx
	void ins_fx15(uint16_t opcode);
	// set st = vx
	void ins_fx18(uint16_t opcode);
	// set i = i + vx
	void ins_fx1e(uint16_t opcode);
	// set i = memory location of sprite for digit vx
	void ins_fx29(uint16_t opcode);
	// store BCD representation of vx in memory
	void ins_fx33(uint16_t opcode);
	// store registers v0 through vx in memory starting at i
	void ins_fx55(uint16_t opcode);
	// read registers v0 through vx from memory starting at i
	void ins_fx65(uint16_t opcode);
	
	uint16_t opcodeGetNNN(uint16_t opcode) const
	{
		return opcode & 0xfff;
	}

	uint8_t opcodeGetNN(uint16_t opcode) const
	{
		return opcode & 0xff;
	}

	uint8_t opcodeGetN(uint16_t opcode) const
	{
		return opcode & 0xf;
	}

	uint8_t opcodeGetX(uint16_t opcode) const
	{
		return (opcode >> 8) & 0xf;
	}

	uint8_t opcodeGetY(uint16_t opcode) const
	{
		return (opcode >> 4) & 0xf;
	}


	Memory &memory;
	Display &display;

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

