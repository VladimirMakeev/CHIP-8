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

#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "memory.hpp"
#include "cpu.hpp"
#include "display.hpp"
#include "keyboard.hpp"
#include "sdlapp.hpp"
#include <string>
#include <memory>
#include <SDL.h>

namespace chip8 {

class Emulator : public SDLApplication
{
public:
	Emulator();

	bool loadRom(const std::string &file);
	void run();

private:
	void render();
	void updateTexture();
	void handleInput(const SDL_KeyboardEvent &event);

	Memory memory;
	Display display;
	Keyboard keyboard;
	CPU cpu;

	struct SDLDeleter
	{
		void operator()(SDL_Window *w) const { SDL_DestroyWindow(w); }
		void operator()(SDL_Renderer *r) const { SDL_DestroyRenderer(r); }
		void operator()(SDL_Texture *t) const { SDL_DestroyTexture(t); }
		void operator()(SDL_PixelFormat *f) const { SDL_FreeFormat(f); }
	};

	using WindowPtr = std::unique_ptr<SDL_Window, SDLDeleter>;
	using RendererPtr = std::unique_ptr<SDL_Renderer, SDLDeleter>;
	using TexturePtr = std::unique_ptr<SDL_Texture, SDLDeleter>;
	using FormatPtr = std::unique_ptr<SDL_PixelFormat, SDLDeleter>;

	WindowPtr window;
	RendererPtr renderer;
	TexturePtr texture;
	FormatPtr format;

	const size_t scale;
	const size_t width;
	const size_t height;
	// instructions per second
	const size_t ips;
	// timers frequency in Hz
	const size_t timers_freq;
	// instructions per timer update
	const size_t ipt;
};

}

#endif /* EMULATOR_HPP */

