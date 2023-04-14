#include "ui.h"

#include <string>
#include <fstream>

#include <cpr/cpr.h>


static bool show_app_about = false;
static bool show_app_debug = false;
static bool show_app_launcher = false;

imgui_addons::ImGuiFileBrowser file_dialog;

cpr::Response response = cpr::Get(cpr::Url{URL_API});
std::string json = response.text;
const char *jsonch = json.c_str();

void UI::Launcher(bool* m_show)
{    
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;
   
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);
    
    if(ImGui::Begin("Launcher", m_show, flags))
    {  
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);

        auto windowWidth = ImGui::GetWindowSize().x;
        auto windowHeight = ImGui::GetWindowSize().y;
        ImGui::SetCursorPosX((windowWidth) * 0.5f);
        ImGui::SetCursorPosY((windowHeight)*0.5f);
        
        if (ImGui::Button("Play")) 
        {
            
            std::cout<<json;
            std::ofstream jsapi("jsapi.json");
            jsapi<<json;
            jsapi.close();
            ImGui::OpenPopup("JSON");
        }

        ImGui::SetCursorPosX((windowWidth) * 0.5f);
        if (ImGui::Button("Exit")) 
        {
            UI::openurl(URL);
            exit(0);
        }

        //JSON Window
        if (ImGui::BeginPopupModal("JSON", NULL, ImGuiWindowFlags_NoResize| ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse)) 
        {
        // Draw popup contents.
        ImGui::Text("File created!");
        ImGui::BeginChild(1, ImVec2(420,228), true);
        ImGui::TextWrapped("%s",jsonch);
	    ImGui::EndChild();
        
        if (ImGui::Button("OK"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
        }
        ImGui::End();
    }
}

void UI::DebugMenu(float* _R, float* _G, float* _B)
{
    
    if(ImGui::Begin("DebugMenu", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse))
        {  
            static float col[3] = {0.1f,0.1f,0.1f}; 
            ImGui::Text("Hello World");
            if(ImGui::Button("Hi!"))
            std::cout<<"HelloWorld"<<std::endl;
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

        ImGui::Begin("About", m_show, ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Copyright (c) 2023 LakoMoor");
        ImGui::TextWrapped("MIT License\n\nCopyright (c) 2023 LakoMoor\n\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files (the 'Software'), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.");

        ImGui::Spacing();

        ImGui::Text("Licenses:");
        ImGui::Separator();

        ImGui::BulletText("License 1");
        ImGui::BulletText("License 2");
        ImGui::BulletText("License 3");

        ImGui::Spacing();

        ImGui::Text("TEST");
        ImGui::End();
}

void UI::HeaderMenu()
{
    bool open = false, save = false;
    
    if (ImGui::BeginMainMenuBar())
	{
        
		if (ImGui::BeginMenu("File"))
		{
			if(ImGui::MenuItem("Open", NULL))
            {
                open = true;
            }
            if(ImGui::MenuItem("Exit", NULL))
            {
                exit(0);
            }
			ImGui::EndMenu();
		}
        if (ImGui::BeginMenu("Tools"))
		{
            if (ImGui::MenuItem("Launcher"))
            {
                show_app_launcher = true;
            }
            ImGui::EndMenu();
        }            
        if (ImGui::BeginMenu("Help"))
		{
            if (ImGui::MenuItem("About"))
            {
                show_app_about = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar(); 
    }
    if(open)
        ImGui::OpenPopup("Open File");
    if(file_dialog.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".obj"))
    {
        std::cout << file_dialog.selected_fn << std::endl;     
        std::cout << file_dialog.selected_path << std::endl;    
    }
    if(show_app_about){
        UI::About(&show_app_about);
    }
    if(show_app_launcher){
    }
    
}

void UI::InitImGui(GLFWwindow* window)
{
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable keyboard controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable multi-viewports

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void UI::DrawImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UI::DestroyImGui()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}