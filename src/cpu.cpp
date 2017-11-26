
#include "cpu.hpp"
#include "memory.hpp"
#include "display.hpp"
#include "keyboard.hpp"

namespace chip8 {

CPU::CPU(Memory &memory, Display &display, Keyboard &keyboard) :
	dist(0, 255),
	memory(memory),
	display(display),
	keyboard(keyboard)
{
	std::random_device device;
	engine = std::mt19937(device());

	instructions = {{
		&CPU::ins_misc, &CPU::ins_1nnn, &CPU::ins_2nnn, &CPU::ins_3xnn,
		&CPU::ins_4xnn, &CPU::ins_5xy0, &CPU::ins_6xnn, &CPU::ins_7xnn,
		&CPU::ins_arith, &CPU::ins_9xy0, &CPU::ins_annn, &CPU::ins_bnnn,
		&CPU::ins_cxnn, &CPU::ins_dxyn, &CPU::ins_key, &CPU::ins_special
	}};

	arithmetic = {{
		&CPU::ins_8xy0, &CPU::ins_8xy1, &CPU::ins_8xy2, &CPU::ins_8xy3,
		&CPU::ins_8xy4, &CPU::ins_8xy5, &CPU::ins_8xy6, &CPU::ins_8xy7,
		&CPU::ins_8xye
	}};

	special = {
		{0x7, &CPU::ins_fx07}, {0xa, &CPU::ins_fx0a}, {0x15, &CPU::ins_fx15},
		{0x18, &CPU::ins_fx18}, {0x1e, &CPU::ins_fx1e}, {0x29, &CPU::ins_fx29},
		{0x33, &CPU::ins_fx33}, {0x55, &CPU::ins_fx55}, {0x65, &CPU::ins_fx65}
	};
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
	const uint16_t opcode = fetch();
	const uint8_t index = (opcode >> 12) & 0xf;

	(this->*instructions[index])(opcode);
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

uint16_t CPU::fetch()
{
	// opcodes are stored big-endian
	const uint16_t opcode = ((uint16_t)memory[pc] << 8) | memory[pc +1];

	pc += 2;

	return opcode;
}

uint8_t CPU::rand() const
{
	return dist(engine);
}

void CPU::ins_misc(uint16_t opcode)
{
	switch (opcodeGetNNN(opcode)) {
	case 0x0e0:
		ins_00e0(opcode);
		return;

	case 0x0ee:
		ins_00ee(opcode);
		return;
	}

	ins_0nnn(opcode);
}

void CPU::ins_arith(uint16_t opcode)
{
	const uint8_t nibble = opcodeGetN(opcode);
	const uint8_t index = nibble == 0xe ? 8 : nibble;

	(this->*arithmetic[index])(opcode);
}

void CPU::ins_key(uint16_t opcode)
{
	if (opcode & 0x1) {
		ins_exa1(opcode);
		return;
	}

	ins_ex9e(opcode);
}

void CPU::ins_special(uint16_t opcode)
{
	auto it = special.find(opcodeGetNN(opcode));

	if (it != special.end()) {
		auto handler = it->second;

		(this->*handler)(opcode);
	}
}

void CPU::ins_0nnn(uint16_t)
{
	// unsupported
}

void CPU::ins_00e0(uint16_t)
{
	display.clear();
}

void CPU::ins_00ee(uint16_t)
{
	pc = stack[sp--];
}

void CPU::ins_1nnn(uint16_t opcode)
{
	pc = opcodeGetNNN(opcode);
}

void CPU::ins_2nnn(uint16_t opcode)
{
	stack[++sp] = pc;

	pc = opcodeGetNNN(opcode);
}

void CPU::ins_3xnn(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t nn = opcodeGetNN(opcode);

	if (v[x] == nn) {
		pc += 2;
	}
}

void CPU::ins_4xnn(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t nn = opcodeGetNN(opcode);

	if (v[x] != nn) {
		pc += 2;
	}
}

void CPU::ins_5xy0(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t y = opcodeGetY(opcode);

	if (v[x] == v[y]) {
		pc += 2;
	}
}

void CPU::ins_6xnn(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t nn = opcodeGetNN(opcode);

	v[x] = nn;
}

void CPU::ins_7xnn(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t nn = opcodeGetNN(opcode);

	v[x] += nn;
}

void CPU::ins_8xy0(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t y = opcodeGetY(opcode);

	v[x] = v[y];
}

void CPU::ins_8xy1(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t y = opcodeGetY(opcode);

	v[x] |= v[y];
}

void CPU::ins_8xy2(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t y = opcodeGetY(opcode);

	v[x] &= v[y];
}

void CPU::ins_8xy3(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t y = opcodeGetY(opcode);

	v[x] ^= v[y];
}

void CPU::ins_8xy4(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t y = opcodeGetY(opcode);

	const uint16_t sum = (uint16_t)v[x] + v[y];

	v[x] = sum & 0xff;
	// set carry
	v[0xf] = sum > 0xff;
}

void CPU::ins_8xy5(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t y = opcodeGetY(opcode);

	// set !borrow
	v[0xf] = v[x] >= v[y];

	v[x] -= v[y];
}

void CPU::ins_8xy6(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);

	v[0xf] = v[x] & 0x1;

	v[x] >>= 1;
}

void CPU::ins_8xy7(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t y = opcodeGetY(opcode);

	// set !borrow
	v[0xf] = v[y] >= v[x];

	v[x] = v[y] - v[x];
}

void CPU::ins_8xye(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);

	v[0xf] = (v[x] & 0x80) != 0;

	v[x] <<= 1;
}

void CPU::ins_9xy0(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t y = opcodeGetY(opcode);

	if (v[x] != v[y]) {
		pc += 2;
	}
}

void CPU::ins_annn(uint16_t opcode)
{
	i = opcodeGetNNN(opcode);
}

void CPU::ins_bnnn(uint16_t opcode)
{
	pc = opcodeGetNNN(opcode) + v[0];
}

void CPU::ins_cxnn(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t nn = opcodeGetNN(opcode);

	v[x] = rand() & nn;
}

void CPU::ins_dxyn(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t y = opcodeGetY(opcode);
	const uint8_t n = opcodeGetN(opcode);

	const uint8_t vx = v[x];
	const uint8_t vy = v[y];

	v[0xf] = 0;

	for (uint8_t line = 0; line < n; line++) {
		const uint8_t sprite = memory[i + line];

		for (uint8_t column = 0; column < 8; column++) {
			// pixel position on screen
			const uint8_t px = vx + column;
			const uint8_t py = vy + line;

			const uint8_t bit = (sprite >> (7 - column)) & 0x1;
			const uint8_t pixel = display.getPixel(px, py);
			const uint8_t result = pixel ^ bit;

			v[0xf] |= pixel & bit;
			display.setPixel(px, py, result);
		}
	}
}

void CPU::ins_ex9e(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);

	if (keyboard.isKeyPressed(v[x] & 0xf)) {
		pc += 2;
	}
}

void CPU::ins_exa1(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);

	if (!keyboard.isKeyPressed(v[x] & 0xf)) {
		pc += 2;
	}
}

void CPU::ins_fx07(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	
	v[x] = dt;
}

void CPU::ins_fx0a(uint16_t)
{
}

void CPU::ins_fx15(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);

	dt = v[x];
}

void CPU::ins_fx18(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);

	st = v[x];
}

void CPU::ins_fx1e(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);

	i += v[x];
}

void CPU::ins_fx29(uint16_t)
{
}

void CPU::ins_fx33(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);
	const uint8_t vx = v[x];
	const uint8_t hundreds = vx / 100;
	const uint8_t tens = (vx / 10) % 10;
	const uint8_t ones = vx % 10;

	memory[i] = hundreds;
	memory[i + 1] = tens;
	memory[i + 2] = ones;
}

void CPU::ins_fx55(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);

	for (uint8_t reg = 0; reg <= x; reg++) {
		memory[i + reg] = v[reg];
	}
}

void CPU::ins_fx65(uint16_t opcode)
{
	const uint8_t x = opcodeGetX(opcode);

	for (uint8_t reg = 0; reg <= x; reg++) {
		v[reg] = memory[i + reg];
	}
}

}

