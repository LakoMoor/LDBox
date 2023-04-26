#ifndef RENDER_H
#define RENDER_H

// SDL2 and GLAD headers
#include <SDL.h>
#include <glad/glad.h>

class Render
{
public:
    Render();
    static bool Init();
    static void Fullscreen(SDL_Window* window);

};


#endif // RENDER_H