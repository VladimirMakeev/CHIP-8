
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

	Memory memory;
	Display display;
	Keyboard keyboard;
	CPU cpu;

	struct SDLDeleter
	{
		void operator()(SDL_Window *w) const { SDL_DestroyWindow(w); }
		void operator()(SDL_Renderer *r) const { SDL_DestroyRenderer(r); }
	};

	using WindowPtr = std::unique_ptr<SDL_Window, SDLDeleter>;
	using RendererPtr = std::unique_ptr<SDL_Renderer, SDLDeleter>;

	WindowPtr window;
	RendererPtr renderer;

	const size_t scale;
	const size_t width;
	const size_t height;
};

}

#endif /* EMULATOR_HPP */

