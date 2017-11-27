
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
};

}

#endif /* EMULATOR_HPP */

