#include "render.h"

// SDL2 and GLAD headers
#include <SDL.h>
#include <glad/glad.h>

// Logger
#include <spdlog/spdlog.h>

// Other headers
#include <cstdio>

Render::Render()
{
    Render::Init();
}


bool Render::Init()
{
    spdlog::set_level(spdlog::level::debug);
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        spdlog::error("s\n",SDL_GetError());
        return false;
    }
    spdlog::info("Init SDL2");
    return true;
}

void Render::Fullscreen(SDL_Window*  window)
{
    Uint32 flags = SDL_GetWindowFlags(window);
    if(flags & SDL_WINDOW_FULLSCREEN_DESKTOP)
        SDL_SetWindowFullscreen(window, 0);
    else    
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}