#include "ui.h"
#include <iostream>

static bool show_app_about = false;
static bool show_app_debug = false;
static bool show_app_launcher = false;

imgui_addons::ImGuiFileBrowser file_dialog;

bool launchGame(const char* gamePath) {
    // Code to launch game goes here
    return true; // Return true if game launched successfully, false otherwise
}

void UI::Launcher(bool* m_show)
{
    const char* games[] = { "Game 1", "Game 2", "Game 3" };
    int selectedGame = 0;
    char gamePath[256] = "";
    bool showGameDetails = false;
    
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);
    if(ImGui::Begin("Launcher", m_show, flags))
    {  
     // Add header text
        ImGui::StyleColorsDark();
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);


        ImGui::Text("GAMES");

        // Add list of games
        ImGui::BeginChild("GameList", ImVec2(350, 400), true, ImGuiWindowFlags_HorizontalScrollbar);
        for (int i = 0; i < IM_ARRAYSIZE(games); i++) {
            if (ImGui::Selectable(games[i], selectedGame == i, ImGuiSelectableFlags_AllowDoubleClick)) {
                if (ImGui::IsMouseDoubleClicked(0)) {
                    const char* pathToLaunch = games[i];
                    if (!launchGame(pathToLaunch)) {
                        ImGui::OpenPopup("Error");
                    }
                }
                else {
                    selectedGame = i;
                    showGameDetails = true;
                }
            }
        }
        ImGui::EndChild();

        // Add game details panel
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Spacing();
        ImGui::Text("Publisher: Example Publisher");
        ImGui::Text("Developer: Example Developer");
        ImGui::Text("Release Date: 01/01/2022");
        ImGui::Spacing();
        if (ImGui::Button("Play", ImVec2(150, 50))) {
            const char* pathToLaunch = games[selectedGame];
            if (!launchGame(pathToLaunch)) {
                ImGui::OpenPopup("Error");
            }
        }
        if (ImGui::Button("Exit", ImVec2(150, 50))) {
            return;
        }
        ImGui::EndGroup();

        // Add error popup if launch fails
        if (ImGui::BeginPopupModal("Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Failed to launch game!");
            if (ImGui::Button("OK", ImVec2(100, 30))) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        // End Dear ImGui window
        ImGui::End();
    }
}

void UI::DebugMenu(float* _R, float* _G, float* _B)
{
    
    if(ImGui::Begin("DebugMenu", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings))
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

        ImGui::Begin("About", m_show, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize );

        ImGui::Text("This program was developed by OpenAI");
        ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.");

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
                //open = true;
            }
            if(ImGui::MenuItem("Exit", NULL))
            {
                return;
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
        std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
    }
    if(show_app_about){
        UI::About(&show_app_about);
    }
    if(show_app_launcher){
        UI::Launcher(&show_app_launcher);
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