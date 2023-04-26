#include "renderui.h"
#include "../core/render.h"

#include <string>
#include <fstream>

#include <spdlog/spdlog.h>


static bool show_app_about = false;
static bool show_app_debug = false;
static bool show_app_launcher = false;

void UI::Main()
{
    /*
    if(ImGui::Begin("Launcher", m_show, flags))
    {  
        //ImVec4* colors = ImGui::GetStyle().Colors;
        //colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        auto windowWidth = ImGui::GetWindowSize().x;
        auto windowHeight = ImGui::GetWindowSize().y;
        ImGui::SetCursorPosY((windowHeight) * 0.5f);
        ImGui::SetCursorPosX((windowWidth) * 0.5f);
        if (ImGui::Button("Play")) 
        {
            spdlog::debug("Button Play pressed");
            std::ofstream jsapi("jsapi.json");
            jsapi<<"{json:'test'}";
            jsapi.close();
            ImGui::OpenPopup("JSON");
            spdlog::info("JSON saved!");
        }

        ImGui::SetCursorPosX((windowWidth) * 0.5f);
        if (ImGui::Button("About")) 
        {
            spdlog::info("Load about...");
            show_app_about = true;
        }

        ImGui::SetCursorPosX((windowWidth) * 0.5f);
        if (ImGui::Button("Exit")) 
        {
            spdlog::info("Load browser...");
            UI::openurl(URL);
            spdlog::info("Browser load! Good bye!");
            exit(0);
        }


        ImGui::PopStyleColor();
        ImGui::SetNextWindowBgAlpha(1.0f);
        //JSON Window
        if (ImGui::BeginPopupModal("JSON", NULL, ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse)) 
        {
        // Draw popup contents.
        ImGui::Text("File created!");
        ImGui::BeginChild(1, ImVec2(420,228), true);
        ImGui::TextWrapped("%s","TEST");
	    ImGui::EndChild();
        
        if (ImGui::Button("OK"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
        }
        ImGui::End();
    }
    if(show_app_about){
        UI::About(&show_app_about);
    }
    */

}

void UI::Launcher(bool* m_show)
{    
        bool open = true;
        
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);

        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus ;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Launcher", &open, window_flags);
        ImGui::PopStyleVar();

        ImGuiID dockspace_id = ImGui::GetID("my_dockspace");

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
            
            
            ImGui::DockBuilderDockWindow("MainMenu", dock_id_n1);
            ImGui::DockBuilderDockWindow("GameList", dock_id_n2);
            ImGui::DockBuilderDockWindow("Preview", dock_id_n3);
            ImGui::DockBuilderDockWindow("Status", dock_id_n4);
            ImGui::DockBuilderFinish(dockspace_id);
        }
   
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
        ImGui::PopStyleColor();
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(60, 70));
        ImGui::Begin("MainMenu", nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoScrollbar);
        if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
        {
            dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar |  ImGuiDockNodeFlags_NoResize;
        }
        static ImGuiTableFlags flags1 = ImGuiTableFlags_BordersV;
        static bool show_headers = false;
        if (ImGui::BeginTable("table_padding", 3, flags1))
        {
            if (show_headers)
            {
                ImGui::TableSetupColumn("One");
                ImGui::TableSetupColumn("Two");
                ImGui::TableSetupColumn("Three");
                ImGui::TableHeadersRow();
            }
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Button("Store",ImVec2(-FLT_MIN, -FLT_MIN));
            ImGui::TableSetColumnIndex(1);
            ImGui::Button("Library",ImVec2(-FLT_MIN, -FLT_MIN));
            ImGui::TableSetColumnIndex(2);
            ImGui::Button("Profile",ImVec2(-FLT_MIN, -FLT_MIN));
            
            ImGui::EndTable();
        }        
        ImGui::End();
        
        ImGui::Begin("GameList", nullptr, ImGuiWindowFlags_NoResize);
        if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
        {
            dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
        }
        ImGui::Text("GameList");
        ImGui::End();

        ImGui::Begin("Preview", nullptr, ImGuiWindowFlags_NoResize);
        if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
        {
            dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar;
        }
        ImGui::Text("Preview");
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(10, 10));
        ImGui::Begin("Status", nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoScrollbar);
        if (ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(ImGui::GetWindowDockID()))
        {
            dockNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoTabBar |  ImGuiDockNodeFlags_NoResize;
        }
        ImGui::Text("Status");
        ImGui::End();
}

void UI::DebugMenu(float* _R, float* _G, float* _B)
{
      
    if(ImGui::Begin("DebugMenu", NULL, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse))
        {   
            static float col[3] = {0.1f,0.1f,0.1f}; 
            ImGui::Text("Hello World");
            if(ImGui::Button("Hi!"))
            spdlog::info("Hello logger :)");
            ImGui::SeparatorText("Background Color");
            if(ImGui::ColorEdit3("Background", col))
                std::cout << _R << _G << _B <<std::endl;
            ImGui::SliderFloat("R",_R,0.0f, 1.0f);
            ImGui::SliderFloat("G",_G,0.0f, 1.0f);
            ImGui::SliderFloat("B",_B,0.0f, 1.0f);
            ImGui::End(); 
        }
}

void UI::About(bool* m_show)
{
            
        ImGui::Begin("About", m_show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings);
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
        ImGui::End();   
}

void UI::HeaderMenu(SDL_Window* window)
{  
       
    if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if(ImGui::MenuItem("Open", NULL))
            {
                spdlog::warn("Empty item");
            }
            if(ImGui::MenuItem("Exit", NULL))
            {
                exit(0);
            }
			ImGui::EndMenu();
		}
        if (ImGui::BeginMenu("Tools"))
		{
            if (ImGui::MenuItem("Style editor"))
            {            
                spdlog::warn("Empty item");
            }
            ImGui::EndMenu();
        }            
        if (ImGui::BeginMenu("Help"))
		{
            if (ImGui::MenuItem("About"))
            {
                //show_app_about = true;
                spdlog::debug("About loaded!");
                spdlog::warn("Empty item");
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
    /*if(show_app_about){
        UI::About(&show_app_about);
    }*/
    
}

void UI::InitImGui(SDL_Window* window, SDL_GLContext glContext)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable keyboard controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable docking
    io.ConfigViewportsNoDecoration = false;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable multi-viewports
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
    
}

void UI::DestroyImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}