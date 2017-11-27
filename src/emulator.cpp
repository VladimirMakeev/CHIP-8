/*
 * This file is part of the CHIP-8 emulator (https://github.com/VladimirMakeev/CHIP-8).
 * Copyright (C) 2017 Vladimir Makeev.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
	height(Display::height()),
	ips(840),
	timers_freq(60),
	ipt(ips / timers_freq)
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

	const size_t timer_delta = 1000 / timers_freq;
	bool quit = false;
	SDL_Event event;

	while (!quit) {
		const uint32_t ticks = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
					break;
				}
				// fall through
			case SDL_KEYUP:
				handleInput(event.key);
				break;
			}
		}

		cpu.updateTimers();

		for (size_t i = 0; i < ipt; i++) {
			cpu.execute();
		}

		render();

		const uint32_t delta = SDL_GetTicks() - ticks;

		if (delta < timer_delta) {
			SDL_Delay(timer_delta - delta);
		}
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

void Emulator::handleInput(const SDL_KeyboardEvent &event)
{
	// map SDL keys to CHIP-8 keys
	static const SDL_Keycode keys[16] = {
		SDLK_x, // 0
		SDLK_1, // 1
		SDLK_2, // 2
		SDLK_3, // 3
		SDLK_q, // 4
		SDLK_w, // 5
		SDLK_e, // 6
		SDLK_a, // 7
		SDLK_s, // 8
		SDLK_d, // 9
		SDLK_z, // A
		SDLK_c, // B
		SDLK_4, // C
		SDLK_r, // D
		SDLK_f, // E
		SDLK_v  // F
	};

	const bool pressed = event.type == SDL_KEYDOWN;
	const SDL_Keycode code = event.keysym.sym;

	for (size_t i = 0; i < 16; i++) {
		if (code == keys[i]) {
			keyboard.setKeyPressed(i, pressed);
			break;
		}
	}
}

}

