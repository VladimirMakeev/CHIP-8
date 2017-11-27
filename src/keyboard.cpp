
#include "keyboard.hpp"

namespace chip8 {

void Keyboard::setKeyPressed(uint8_t key, bool pressed)
{
	keys[key & 0xf] = pressed;
}

bool Keyboard::isKeyPressed(uint8_t key) const
{
	return keys[key & 0xf];
}

int Keyboard::getKeyPressed() const
{
	for (size_t i = 0; i < keys.size(); i++) {
		if (isKeyPressed(i)) {
			return i;
		}
	}

	return -1;
}

}

