
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cstdint>
#include <array>

namespace chip8 {

class Keyboard
{
public:
	void setKeyPressed(uint8_t key, bool pressed);
	bool isKeyPressed(uint8_t key) const;
	int getKeyPressed() const;

private:
	std::array<bool, 16> keys;
};

}

#endif /* KEYBOARD_HPP */

