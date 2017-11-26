
#include "sdlapp.hpp"
#include <stdexcept>
#include <SDL.h>

SDLApplication::SDLApplication() : NonCopyable()
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		throw std::runtime_error("Failed to initialize SDL");
	}
}

SDLApplication::~SDLApplication()
{
	SDL_Quit();
}

