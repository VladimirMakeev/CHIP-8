
#include "emulator.hpp"
#include <cstdint>
#include <fstream>
#include <vector>
#include <stdexcept>

namespace chip8 {

Emulator::Emulator() :
	cpu(memory, display, keyboard),
	scale(10),
	width(Display::width()),
	height(Display::height())
{
	window = WindowPtr(SDL_CreateWindow("CHIP-8 Emulator",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width * scale, height * scale, SDL_WINDOW_SHOWN));

	if (!window) {
		throw std::runtime_error("Failed to create SDL window");
	}

	renderer = RendererPtr(SDL_CreateRenderer(window.get(), -1,
			SDL_RENDERER_ACCELERATED));

	if (!renderer) {
		throw std::runtime_error("Failed to create SDL renderer");
	}

	texture = TexturePtr(SDL_CreateTexture(renderer.get(),
			SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING,
			width, height));

	if (!texture) {
		throw std::runtime_error("Failed to create SDL texture");
	}

	format = FormatPtr(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888));

	if (!format) {
		throw std::runtime_error("Failed to create SDL pixel format");
	}

	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
}

bool Emulator::loadRom(const std::string &file)
{
	std::ifstream in(file, std::ios_base::binary);

	if (!in) {
		return false;
	}

	in.seekg(0, in.end);

	const size_t length = in.tellg();

	in.seekg(0, in.beg);

	std::vector<uint8_t> rom(length);

	in.read((char*)&rom[0], length);

	return memory.loadRom(rom);
}

void Emulator::run()
{
	cpu.reset();

	bool quit = false;
	SDL_Event event;

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		cpu.execute();
		cpu.updateTimers();

		render();

		SDL_Delay(1);
	}
}

void Emulator::render()
{
	updateTexture();

	SDL_Renderer *r = renderer.get();

	SDL_RenderClear(r);

	SDL_RenderCopy(r, texture.get(), nullptr, nullptr);

	SDL_RenderPresent(r);
}

void Emulator::updateTexture()
{
	uint32_t *pixels;
	int pitch = 0;

	SDL_LockTexture(texture.get(), nullptr, (void**)&pixels, &pitch);

	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			const uint8_t color = display.getPixel(x, y) ? 255 : 0;

			pixels[width * y + x] = SDL_MapRGB(format.get(), color, color, color);
		}
	}

	SDL_UnlockTexture(texture.get());
}

}

