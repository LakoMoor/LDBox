#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_glfw.h"

//#include <stdio.h>

void HelloWorld()
{
    if(ImGui::Begin("HelloWorld", NULL, ImGuiWindowFlags_NoSavedSettings))
        {
            ImGui::Text("Hello World");
            if(ImGui::Button("Hi!"))
            std::cout<<'Hello'<<std::endl;
            ImGui::End(); 
        }
}