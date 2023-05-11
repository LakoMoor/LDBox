#define PROJECT_VER "0.2.9"

#include "renderui.h"
#include "../core/render.h"

#include <string>
#include <iostream>
#include <fstream>

#include <spdlog/spdlog.h>

static bool show_app_about = false;
static bool hide_privew = false;
static bool show_app_debug = false;
static bool show_app_launcher = false;
const char* items[] = { "H1.5", "H2.0"};
const char* language[] = { "English"};
static bool show_app_widget = true;

static float progress = 0.0f;
const char* selectGame;

ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking |ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;

void UI::Profile()
{
     show_app_widget = false;
}

void Library()
{
    show_app_widget = true;
}

void UI::LogIn()
{
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;
   
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);
    //ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0,0,0,0));
    if(ImGui::Begin("Launcher", nullptr, flags))
    {  
        static bool button_disable = true;
        static char str1[128] = "";
        ImGui::InputTextWithHint(" ", "enter text here", str1, IM_ARRAYSIZE(str1));
        std::string usrname = str1;
        
        if(usrname == "") button_disable = true;
        else button_disable = false;
        static const char* current_item = language[0];
        if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < IM_ARRAYSIZE(language); n++)
            {
                bool is_selected = (current_item == language[n]); // You can store your selection however you want, outside or inside your objects
                if(ImGui::Selectable(language[n], is_selected))
                {
                        current_item = language[n];
                }
                if (is_selected)
                {
                     ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                }
                   
            }
            ImGui::EndCombo();
        }

        ImGui::BeginDisabled(button_disable);
        if(ImGui::Button("Apply"))
        {           
            ImGui::OpenPopup("Save");
        }
        ImGui::EndDisabled();

        if (ImGui::BeginPopupModal("Save", NULL, flags))
            {
            ImGui::Text("Restart LDBox");
            ImGui::Separator();

            if (ImGui::Button("OK", ImVec2(120, 0))) 
            { 
                spdlog::info(str1);
                std::ofstream accountCreate("acc.psi");
                accountCreate << str1;
                accountCreate.close();
                ImGui::CloseCurrentPopup(); 
                exit(0);
            }
            ImGui::SetItemDefaultFocus();
            ImGui::EndPopup();
        }
        ImGui::End();
    }
}

void UI::LauncherMobile(bool* m_show,  GLuint textureID)
{    
        bool open = true;
        
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
        ImGui::SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);
        ImGui::PopStyleVar();

        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus ;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Launcher", &open, window_flags);
        ImGui::PopStyleVar();

        ImGuiID dockspace_idMobile = ImGui::GetID("MainDockerMobile");

       if (ImGui::DockBuilderGetNode(dockspace_idMobile) == NULL)
        {
            ImGui::DockBuilderRemoveNode(dockspace_idMobile); // Clear out existing layout
            ImGui::DockBuilderAddNode(dockspace_idMobile, ImGuiDockNodeFlags_NoTabBar| ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_HiddenTabBar); // Add empty node
            ImGui::DockBuilderSetNodeSize(dockspace_idMobile, ImVec2(720, 1280));

            ImGuiID dock_main_idMobile = dockspace_idMobile;

            ImGuiID dock_id_n1 = ImGui::DockBuilderSplitNode(dock_main_idMobile, ImGuiDir_Down, 0.1f, NULL, &dock_main_idMobile);
            ImGuiID dock_id_n2 = ImGui::DockBuilderSplitNode(dock_main_idMobile, ImGuiDir_Down, 0.15f, NULL, &dock_main_idMobile);
            ImGuiID dock_id_n3 = ImGui::DockBuilderSplitNode(dock_main_idMobile, ImGuiDir_Down, 0.5f, NULL, &dock_main_idMobile);
            ImGuiID dock_id_n5 = ImGui::DockBuilderSplitNode(dock_main_idMobile, ImGuiDir_Right, 0.5f, NULL, &dock_main_idMobile);
            
            ImGui::DockBuilderDockWindow("MainMenuMobile", dock_id_n1);
            ImGui::DockBuilderDockWindow("GameListMobile", dock_id_n2);
            ImGui::DockBuilderDockWindow("PreviewMobile", dock_id_n3);
            ImGui::DockBuilderDockWindow("Profile", dock_id_n5);
            
            ImGui::DockBuilderFinish(dockspace_idMobile);
        }
   
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        ImGui::DockSpace(dockspace_idMobile, ImVec2(0.0f, 0.0f));
        ImGui::PopStyleColor();
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(60, 70));
        ImGui::Begin("MainMenuMobile", nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoScrollbar);
        ImGui::PopStyleVar();
        if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
        {
            dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar |  ImGuiDockNodeFlags_NoResize;
        }
        static bool show_headers = false;
        if (ImGui::BeginTable("table_padding", 3, ImGuiTableFlags_BordersV))
        {
            if (show_headers)
            {
                ImGui::TableSetupColumn("OneMobile");
                ImGui::TableSetupColumn("TwoMobile");
                ImGui::TableSetupColumn("ThreeMobile");
                ImGui::TableHeadersRow();
            }
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            if(ImGui::Button("Store",ImVec2(-FLT_MIN, -FLT_MIN))) UI::Profile();
            ImGui::TableSetColumnIndex(1);
            if(ImGui::Button("Library",ImVec2(-FLT_MIN, -FLT_MIN))) Library();
            ImGui::TableSetColumnIndex(2);
            if(ImGui::Button("Profile",ImVec2(-FLT_MIN, -FLT_MIN))) UI::Profile();

            
            ImGui::EndTable();
        }        
        ImGui::End();
        
        if(show_app_widget)
        {
          ImGui::Begin("GameListMobile", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
        if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
        {
            dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
        }
        const char* items[] = { "H1.5", "H2.0"};
        
        static int item_current_idx = 0; // Here we store our selection data as an index.
        if (ImGui::BeginListBox("GameListMobile", ImVec2(-FLT_MIN, -FLT_MIN)))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_current_idx == n);
                if (ImGui::Selectable(items[n], is_selected))
                {
                    
                    item_current_idx = n;
                    //spdlog::debug(items[n]);
                    selectGame = items[n];
                    hide_privew = true;
                    spdlog::debug(selectGame);

                }
                if (ImGui::BeginPopupContextItem())
                {
                    ImGui::Button("Install");
                    ImGui::Separator();
                    //ImGui::Text(items[n], NULL);
                    if(ImGui::BeginMenu("Settings"))
                    {
                        spdlog::warn("Empty item");
                        ImGui::MenuItem("Directory", NULL);
                        ImGui::MenuItem("Delete", NULL);
                        ImGui::MenuItem("Update", NULL);
                        ImGui::EndMenu();
                    }
                    ImGui::Separator();
                    if(ImGui::MenuItem("Propirtes", NULL))
                    {
                            exit(0);
                    }
                    ImGui::EndPopup();
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::End();
        //spdlog::debug(select);
        if(selectGame == items[1])
        {
            ImGui::Begin("PreviewMobile", &hide_privew, ImGuiWindowFlags_NoResize);
            if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
            {
                dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
            }
            ImGui::SetWindowFontScale(3.0f);
            ImGui::Text("HOLODILNIK 2.0");
            ImGui::SetWindowFontScale(1.0f);
            ImGui::Separator();
            ImGui::Text("");
            ImGui::Button("Install",ImVec2(125.0f, 45.0f));
            ImGui::Text("");
            ImGui::SeparatorText("News");
            ImGui::End();
        }
        if(selectGame == items[0])
        {
            ImGui::Begin("PreviewMobile", nullptr, ImGuiWindowFlags_NoResize);
            if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
            {
                dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
            }
            ImGui::SetWindowFontScale(3.0f);
            ImGui::Text("HOLODILNIK 1.5");
            ImGui::SetWindowFontScale(1.0f);
            ImGui::Separator();
            ImGui::Text("");
            ImGui::Button("Install",ImVec2(125.0f, 45.0f));
            ImGui::Text("");
            ImGui::SeparatorText("News");
            ImGui::End();
        }
        
        if(!hide_privew)
        {
            ImGui::Begin("PreviewMobile", nullptr, ImGuiWindowFlags_NoResize| ImGuiWindowFlags_NoScrollbar);
            if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
            {
                dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
            }
            ImGui::Spacing();
            {
                ImGui::BeginChild("ChildR2Mobile", ImVec2(-FLT_MIN, 260), true, window_flags);
            
                if (ImGui::BeginTable("split2Mobile", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
                {
                    ImGui::TableNextColumn();
                    ImGui::SetWindowFontScale(3.0f);
                    ImGui::Text("%s", items[0]);
                    ImGui::SetWindowFontScale(1.0f);
                    ImGui::Separator();
                    ImGui::Text("");
                    ImGui::Button("Install",ImVec2(125.0f, 45.0f));
                    ImGui::EndTable();
                }
                
                ImGui::EndChild();
            }
            {
                ImGui::BeginChild("ChildR1Mobile", ImVec2(-FLT_MIN, 260), true, window_flags);
            
                if (ImGui::BeginTable("split1Mobile", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
                {
                    ImGui::TableNextColumn();
                    ImGui::SetWindowFontScale(3.0f);
                    ImGui::Text("%s", items[1]);
                    ImGui::SetWindowFontScale(1.0f);
                    ImGui::Separator();
                    ImGui::Text("");
                    ImGui::Button("Install",ImVec2(125.0f, 45.0f));
                    ImGui::EndTable();
                }
                
                ImGui::EndChild();
            }       
            ImGui::End();
        }  
        }
    if(!show_app_widget)
        {
            ImGui::Begin("Profile",  nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoScrollbar);
            if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
            {
                dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar |  ImGuiDockNodeFlags_NoResize;
            }
            ImGui::SeparatorText("Profile");
            {
            ImVec2 window_size = ImGui::GetWindowSize();
            ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(textureID)), window_size, ImVec2(0, 1), ImVec2(1, 0));
            }
            ImGui::End();
        }
}

void UI::Launcher(bool* m_show, GLuint textureID)
{    
        bool open = true;
        
       
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
        ImGui::SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);
        ImGui::PopStyleVar();
        

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Launcher", &open, window_flags);
        ImGui::PopStyleVar();

        ImGuiID dockspace_id = ImGui::GetID("MainDocker");

        if (ImGui::DockBuilderGetNode(dockspace_id) == NULL)
        {
            ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_NoTabBar| ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_HiddenTabBar); // Add empty node
            ImGui::DockBuilderSetNodeSize(dockspace_id, ImVec2(1280, 720));

            ImGuiID dock_main_id = dockspace_id;

            ImGuiID dock_id_n1 = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.1f, NULL, &dock_main_id);
            ImGuiID dock_id_n4 = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.1f, NULL, &dock_main_id);
            ImGuiID dock_id_n2 = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.15f, NULL, &dock_main_id);
            ImGuiID dock_id_n3 = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.5f, NULL, &dock_main_id);
            ImGuiID dock_id_n5 = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.5f, NULL, &dock_main_id);
            
            
            ImGui::DockBuilderDockWindow("MainMenu", dock_id_n1);
            ImGui::DockBuilderDockWindow("GameList", dock_id_n2);
            ImGui::DockBuilderDockWindow("Preview", dock_id_n3);
            ImGui::DockBuilderDockWindow("Status", dock_id_n4);
            ImGui::DockBuilderDockWindow("Profile", dock_id_n5);
            ImGui::DockBuilderFinish(dockspace_id);
        }
   
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
        ImGui::PopStyleColor();
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(60, 70));
        ImGui::Begin("MainMenu", nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoScrollbar);
        ImGui::PopStyleVar();
        if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
        {
            dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar |  ImGuiDockNodeFlags_NoResize;
        }
        static bool show_headers = false;
        if (ImGui::BeginTable("table_padding", 4, ImGuiTableFlags_BordersV))
        {
            if (show_headers)
            {
                ImGui::TableSetupColumn("One");
                ImGui::TableSetupColumn("Two");
                ImGui::TableSetupColumn("Three");
                ImGui::TableSetupColumn("Four");
                ImGui::TableHeadersRow();
            }
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            if(ImGui::Button("Store",ImVec2(-FLT_MIN, -FLT_MIN))) UI::Profile();
            ImGui::TableSetColumnIndex(1);
            if(ImGui::Button("Library",ImVec2(-FLT_MIN, -FLT_MIN))) Library();
            ImGui::TableSetColumnIndex(2);
            if(ImGui::Button("Profile",ImVec2(-FLT_MIN, -FLT_MIN))) UI::Profile();
            ImGui::TableSetColumnIndex(3);
            if(ImGui::Button("Exit",ImVec2(-FLT_MIN, -FLT_MIN)))exit(0);
            
            ImGui::EndTable();
        }        
        ImGui::End();
        
        if(show_app_widget)
        {
            ImGui::Begin("GameList", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
        {
            dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
        }
        const char* items[] = { "H1.5", "H2.0"};
        
        static int item_current_idx = 0; // Here we store our selection data as an index.
        if (ImGui::BeginListBox("GameList", ImVec2(-FLT_MIN, -FLT_MIN)))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_current_idx == n);
                if (ImGui::Selectable(items[n], is_selected))
                {
                    
                    item_current_idx = n;
                    //spdlog::debug(items[n]);
                    selectGame = items[n];
                    hide_privew = true;
                    spdlog::debug(selectGame);

                }
                if (ImGui::BeginPopupContextItem())
                {
                    ImGui::Button("Install");
                    ImGui::Separator();
                    //ImGui::Text(items[n], NULL);
                    if(ImGui::BeginMenu("Settings"))
                    {
                        spdlog::warn("Empty item");
                        ImGui::MenuItem("Directory", NULL);
                        ImGui::MenuItem("Delete", NULL);
                        ImGui::MenuItem("Update", NULL);
                        ImGui::EndMenu();
                    }
                    ImGui::Separator();
                    if(ImGui::MenuItem("Propirtes", NULL))
                    {
                            exit(0);
                    }
                    ImGui::EndPopup();
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::End();
        //spdlog::debug(select);
        if(selectGame == items[1])
        {
            ImGui::Begin("Preview", &hide_privew, ImGuiWindowFlags_NoResize);
            if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
            {
                dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
            }
            ImGui::SetWindowFontScale(3.0f);
            ImGui::Text("HOLODILNIK 2.0");
            ImGui::SetWindowFontScale(1.0f);
            ImGui::Separator();
            ImGui::Text("");
            ImGui::Button("Install",ImVec2(125.0f, 45.0f));
            ImGui::Text("");
            ImGui::SeparatorText("News");
            ImGui::End();
        }
        if(selectGame == items[0])
        {
            ImGui::Begin("Preview", nullptr, ImGuiWindowFlags_NoResize);
            if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
            {
                dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
            }
            ImGui::SetWindowFontScale(3.0f);
            ImGui::Text("HOLODILNIK 1.5");
            ImGui::SetWindowFontScale(1.0f);
            ImGui::Separator();
            ImGui::Text("");
            ImGui::Button("Install",ImVec2(125.0f, 45.0f));
            ImGui::Text("");
            ImGui::SeparatorText("News");
            ImGui::End();
        }
        if(!hide_privew)
        {
            ImGui::Begin("Preview", nullptr, ImGuiWindowFlags_NoResize);
            if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
            {
                dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
            }
            {
                ImGui::BeginChild("ChildR2", ImVec2(250, 260), true, window_flags);
            
                if (ImGui::BeginTable("split2", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
                {
                    ImGui::TableNextColumn();
                    ImGui::SetWindowFontScale(3.0f);
                    ImGui::Text("%s", items[0]);
                    ImGui::SetWindowFontScale(1.0f);
                    ImGui::Separator();
                    ImGui::Text("");
                    ImGui::Button("Install",ImVec2(125.0f, 45.0f));
                    ImGui::EndTable();
                }
                
                ImGui::EndChild();
            }
            ImGui::SameLine();
            {
                ImGui::BeginChild("ChildR1", ImVec2(250, 260), true, window_flags);
            
                if (ImGui::BeginTable("split1", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
                {
                    ImGui::TableNextColumn();
                    ImGui::SetWindowFontScale(3.0f);
                    ImGui::Text("%s", items[1]);
                    ImGui::SetWindowFontScale(1.0f);
                    ImGui::Separator();
                    ImGui::Text("");
                    ImGui::Button("Install",ImVec2(125.0f, 45.0f));
                    ImGui::EndTable();
                }
                ImGui::EndChild();
            }           
            ImGui::End();
            ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(10, 10));
            ImGui::Begin("Status", nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoScrollbar);
            ImGui::PopStyleVar();
            if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
            {
                dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar |  ImGuiDockNodeFlags_NoResize;
            }
        ImGui::End();
        }
        }
        if(!show_app_widget)
        {
            ImGui::Begin("Profile",  nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoScrollbar);
            if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
            {
                dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar |  ImGuiDockNodeFlags_NoResize;
            }
            ImGui::SeparatorText("Profile");
            {
            ImVec2 window_size = ImGui::GetWindowSize();
            ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(textureID)), window_size, ImVec2(0, 1), ImVec2(1, 0));
            }
            ImGui::End();
        }
}

void UI::Console()
{
    ImGui::Begin("Console",nullptr, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize);
    static char str[128] = "";
    static char log[128] = "";
    ImGui::InputTextMultiline("##source", log, IM_ARRAYSIZE(log), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_ReadOnly);
    ImGui::InputTextWithHint(" ", "command (use 'help' for show commands)", str, IM_ARRAYSIZE(str));
    ImGui::SameLine();
    if(ImGui::Button("Send") || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
    {
        std::string cmnd = str;
        if(cmnd == "debug")
        {
            spdlog::debug("Debug entry");
        }
        str[0] = '\0';
    }
    ImGui::End();
}

void UI::DebugMenu(float* _R, float* _G, float* _B, SDL_Window* window, GLuint textureID, bool* triangle)
{
    if(ImGui::Begin("DebugMenu", NULL, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse))
        {   
            static float col[3] = {0.1f,0.1f,0.1f}; 
            ImGui::Text("Hello World");
            if(ImGui::Button("Hi!"))
            spdlog::info("Hello logger :)");
            ImGui::SeparatorText("Background Color");
            ImGui::SliderFloat("R",_R,0.0f, 1.0f);
            ImGui::SliderFloat("G",_G,0.0f, 1.0f);
            ImGui::SliderFloat("B",_B,0.0f, 1.0f);
            ImGui::SeparatorText("OpenGL");
            {
                ImGui::Checkbox("Show/Hide Triangle", triangle);
                ImVec2 window_size = ImGui::GetWindowSize();
                ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(textureID)), ImVec2(256,128), ImVec2(0, 1), ImVec2(1, 0));
            }
            ImGui::SeparatorText("Mobile mode");
            if(ImGui::Button("Mobile"))
            {
                spdlog::warn("Mobile");
                SDL_SetWindowSize(window, 360, 640);
            }
            ImGui::SameLine();
            if(ImGui::Button("PC"))
            {
                spdlog::warn("PC");
                SDL_SetWindowSize(window, 1280, 720);
            }
            ImGui::End(); 
        }
}

void UI::About(bool* m_show)
{
            
        ImGui::Begin("About", m_show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking);
        ImGui::Text("LDBox");
        ImGui::BeginChild(1, ImVec2(420,228), true);
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

void UI::HeaderMenu(SDL_Window* window, bool* debug)
{  
    if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if(ImGui::MenuItem("Open", NULL))
            {
                spdlog::warn("Empty item");
            }
            if(ImGui::MenuItem("Logout", NULL))
            {
                std::remove("acc.psi");
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
                //spdlog::warn("Empty item");
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
    if(show_app_about){
        UI::About(&show_app_about);
    }
    
}

void UI::InitImGui(SDL_Window* window, SDL_GLContext glContext)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable keyboard controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;    // Enable docking
    io.ConfigViewportsNoDecoration = false;
    #ifdef WIN32
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable multi-viewports
    #endif
    ImVec4* colors = ImGui::GetStyle().Colors;


    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();
    spdlog::debug("Init ImGui");
}

void UI::DrawImGui(SDL_Window* window)
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
