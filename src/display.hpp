
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <cstdint>
#include <vector>

namespace chip8 {

class Display
{
public:
	Display();

	static constexpr size_t width() { return 64; }
	static constexpr size_t height() { return 32; }

	void clear();

	void setPixel(uint8_t col, uint8_t row, uint8_t value);
	uint8_t getPixel(uint8_t col, uint8_t row) const;

private:
	void wrap(uint8_t &col, uint8_t &row) const
	{
		col %= width();
		row %= height();
	}

	std::vector<uint8_t> display;
};

}

#endif /* DISPLAY_HPP */

