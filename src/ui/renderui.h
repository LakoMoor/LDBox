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
    static void Launcher(bool* m_show, GLuint textureID);
    static void Profile();
    static void LauncherMobile(bool* m_show,  GLuint textureID);

    //Windows
    static void DebugMenu(float* _R, float* _G, float* _B, SDL_Window* window, GLuint textureID);
    static void About(bool* m_show);
    static void Settings(bool* m_show);
    static void Main();

    //Render
    static void InitImGui(SDL_Window* window, SDL_GLContext glContext);
    static void DrawImGui(SDL_Window* window);
    static void DestroyImGui();

    //tools
    static void openurl(const char* path)
    {
        #ifdef _WIN322
            ::ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWDEFAULT);
        #else
        #if __APPLE__
            const char* open_executable = "open";
        #else
            const char* open_executable = "xdg-open";
        #endif
            char command[256];
            snprintf(command, 256, "%s \"%s\"", open_executable, path);
            system(command);
        #endif
    }
private:
    int test;
};