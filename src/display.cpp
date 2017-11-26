
#include "display.hpp"
#include <algorithm>

namespace chip8 {

Display::Display() : display(width() * height())
{
}

void Display::clear()
{
	std::fill(display.begin(), display.end(), 0);
}

void Display::setPixel(uint8_t col, uint8_t row, uint8_t value)
{
	wrap(col, row);

	display[width() * row + col] = value;
}

uint8_t Display::getPixel(uint8_t col, uint8_t row) const
{
	wrap(col, row);

	return display[width() * row + col];
}

}

