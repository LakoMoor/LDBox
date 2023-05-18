#define PROJECT_VER "0.1.0"

#include "renderui.h"
#include "../core/render.h"

#include <string>
#include <iostream>
#include <fstream>

// #include <cpr/cpr.h>

#include <nlohmann/json.hpp>

#include <spdlog/spdlog.h>

static bool show_app_about = false;

ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;

ImGuiWindowFlags CenterFlags = ImGuiWindowFlags_NoScrollbar;

void MainMenuButtons()
{
    using namespace ImGui;
    Button("Open");
    SameLine();
    Button("Save");
    SameLine();
    Button("Play");
    SameLine();
    Button("Help");
    SameLine();
}

void UI::Editor(bool *m_show, SDL_Window *window, GLuint textureID)
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Editor", m_show, window_flags);
    ImGui::PopStyleVar();

    ImGuiID dockspace_id = ImGui::GetID("editor");

    if (ImGui::DockBuilderGetNode(dockspace_id) == NULL)
    {
        ImGui::DockBuilderRemoveNode(dockspace_id);                                                                                           // Clear out existing layout
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_HiddenTabBar); // Add empty node
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImVec2(1280, 720));

        ImGuiID dock_main_id = dockspace_id;

        ImGuiID dock_id_n1 = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.05f, NULL, &dock_main_id);
        ImGuiID dock_id_n4 = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.25f, NULL, &dock_main_id);
        ImGuiID dock_id_n2 = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, NULL, &dock_main_id);
        ImGuiID dock_id_n3 = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, NULL, &dock_main_id);
        ImGuiID dock_id_n5 = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.0f, NULL, &dock_main_id);

        ImGui::DockBuilderDockWindow("MainMenu", dock_id_n1);
        ImGui::DockBuilderDockWindow("LeftUI", dock_id_n2);
        ImGui::DockBuilderDockWindow("RightUI", dock_id_n3);
        ImGui::DockBuilderDockWindow("CenterUI", dock_id_n5);
        ImGui::DockBuilderDockWindow("DownUI", dock_id_n4);
        ImGui::DockBuilderFinish(dockspace_id);
    }

    ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
    ImGui::PopStyleColor();
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(60, 70));

    ImGui::Begin("MainMenu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
    ImGui::PopStyleVar();
    if (ImGuiDockNode *dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
    {
        dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResize;
    }
    MainMenuButtons();
    ImGui::End();

    ImGui::Begin("LeftUI", nullptr, ImGuiWindowFlags_NoResize);
    if (ImGuiDockNode *dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
    {
        dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
    }
    ImGui::Text("");
    ImGui::End();

    ImGui::Begin("RightUI", nullptr, ImGuiWindowFlags_NoResize);
    if (ImGuiDockNode *dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
    {
        dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
    }
    ImGui::Text("");
    ImGui::End();

    ImGui::Begin("CenterUI", nullptr, CenterFlags);
    if (ImGuiDockNode *dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
    {
        dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
    }

    ImVec2 avail_size = ImGui::GetContentRegionAvail();
    ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(textureID)), avail_size, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();

    ImGui::Begin("DownUI", nullptr, ImGuiWindowFlags_NoResize);
    if (ImGuiDockNode *dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
    {
        dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
    }
    ImGui::Text("");
    ImGui::End();
}

void UI::Console()
{
    ImGui::Begin("Console", nullptr, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize);
    static char str[128] = "";
    ImGui::InputTextWithHint(" ", "command (use 'help' for show commands)", str, IM_ARRAYSIZE(str));
    ImGui::SameLine();
    if (ImGui::Button("Send") || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
    {
        std::string cmnd = str;
        if (cmnd == "debug")
        {
            spdlog::debug("Debug entry");
        }
        if (cmnd == "help")
        {
            spdlog::debug("help entry");
        }
        if (cmnd == "join")
        {

            /*using json = nlohmann::json;
            json j;
            j["user"] = "Habrahabr";
            cpr::Response r = cpr::Post(cpr::Url{"http://127.0.0.1:8080/api/v1/online"},
            cpr::Body{j.dump()},
            cpr::Header{ { "Content-Type", "application/json" } });
            std::cout << r.text << std::endl;*/
        }
        if (cmnd == "ping")
        {
            /* cpr::Response response = cpr::Get(cpr::Url{URL_API});
             std::string json = response.text;
             std::cout<<json;
             std::ofstream jsapi("jsapi.json");
             jsapi<<json;
             jsapi.close();
             //spdlog::debug(jsapi);*/
        }
        str[0] = '\0';
    }
    ImGui::End();
}

void UI::About(bool *m_show)
{

    ImGui::Begin("About", m_show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking);
    ImGui::Text("LDBox");
    ImGui::BeginChild(1, ImVec2(420, 228), true);
    ImGui::TextWrapped("MIT License\n\nCopyright (c) 2023 LakoMoor\n\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files (the 'Software'), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.");
    ImGui::EndChild();

    ImGui::Spacing();

    ImGui::Text("Licenses:");
    ImGui::Separator();

    ImGui::BulletText("SDL");
    ImGui::BulletText("GLAD");
    ImGui::BulletText("GLM");
    ImGui::BulletText("Dear ImGui");
    ImGui::BulletText("spdlog");

    ImGui::Spacing();

    ImGui::Text("t.me/LakoMoorDev");
    ImGui::Text("Version: %s", PROJECT_VER);
    ImGui::End();
}

void UI::HeaderMenu(SDL_Window *window, bool *debug)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open", "Ctrl + O"))
            {
                spdlog::warn("Empty item");
            }
            if (ImGui::MenuItem("Save", "Ctrl + S"))
            {
                spdlog::warn("Empty item");
            }
            if (ImGui::MenuItem("Save as", "Ctrl + Shift + S"))
            {
                spdlog::warn("Empty item");
            }
            if (ImGui::MenuItem("Exit", "Alt + F4"))
            {
                exit(0);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Debug menu"))
            {
                *debug = !*debug;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {
                show_app_about = true;
                spdlog::debug("About loaded!");
                // spdlog::warn("Empty item");
            }
            if (ImGui::MenuItem("Fullscreen", "(F11)"))
            {
                spdlog::debug("Fullscreen from Header");
                Render::Fullscreen(window);
            }
            if (ImGui::MenuItem("Hide", "(F1)"))
            {
                spdlog::warn("Empty item");
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    if (show_app_about)
    {
        UI::About(&show_app_about);
    }
}

void UI::InitImGui(SDL_Window *window, SDL_GLContext glContext)
{
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable docking
    io.ConfigViewportsNoDecoration = false;
#ifdef WIN32
// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable multi-viewports
#endif
    ImVec4 *colors = ImGui::GetStyle().Colors;

    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();
    spdlog::debug("Init ImGui");
}

void UI::DrawImGui(SDL_Window *window)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();
    ImGui::SetShortcutRouting(ImGuiMod_Ctrl | ImGuiKey_Tab, ImGuiKeyOwner_None);
}

void UI::DestroyImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
