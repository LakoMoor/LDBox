#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../FileBrowser/ImGuiFileBrowser.h"


class UI
{
public:
    //MenuBar
    static void HeaderMenu();

    //Windows
    static void DebugMenu(float* _R, float* _G, float* _B);
    static void About(bool* m_show);
    static void Launcher(bool* m_show);

    //Render
    static void InitImGui(GLFWwindow* window);
    static void DrawImGui();
    static void DestroyImGui();

private:
     
    int test;
};