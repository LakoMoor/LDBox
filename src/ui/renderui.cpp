#include "renderui.h"
#include "../core/render.h"

#include <string>
#include <fstream>

#include <spdlog/spdlog.h>


static bool show_app_about = false;
static bool show_app_debug = false;
static bool show_app_launcher = false;

void UI::Launcher(bool* m_show)
{    
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;
   
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0,0,0,0));
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
}

void UI::DebugMenu(float* _R, float* _G, float* _B)
{
      
    if(ImGui::Begin("DebugMenu", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse))
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
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable docking

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