#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <iostream>
#include <SDL.h>
#include <glad/glad.h>

#define URL_API "https://api.github.com/repos/LakoMoor/LDBox"
#define URL "https://github.com/LakoMoor/LDBox"


class UI
{
public:
    //MenuBar
    static void HeaderMenu(SDL_Window* window, bool* debug);

    //Launcher
    static void Editor(bool* m_show, SDL_Window* window, GLuint textureID);

    //Windows
    static void About(bool* m_show);
    static void Console(int output);

    //Render
    static void InitImGui(SDL_Window* window, SDL_GLContext glContext);
    static void DrawImGui(SDL_Window* window);
    static void DestroyImGui();

private:
    int test;
};