#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../FileBrowser/ImGuiFileBrowser.h"
#include <iostream>
#include <GLFW/glfw3.h>
#define URL_API "https://api.github.com/repos/LakoMoor/LDBox"
#define URL "https://github.com/LakoMoor/LDBox"


class UI
{
public:
    //MenuBar
    static void HeaderMenu();

    //Windows
    static void DebugMenu(float* _R, float* _G, float* _B, GLuint my_image_texture);
    static void About(bool* m_show);
    static void Launcher(bool* m_show, GLuint my_image_texture);

    //Render
    static void InitImGui(GLFWwindow* window);
    static void DrawImGui();
    static void DestroyImGui();

    //tools
    static void openurl(const char* path)
    {
        #ifdef _WIN32
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