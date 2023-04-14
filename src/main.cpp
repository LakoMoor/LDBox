//define
//#define GLFW_INCLUDE_VULKAN

//OpenGL
//#include <vulkan/vulkan.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

//ImGui
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

//User include
#include "ui/ui.h"

//Default
#include <cstdio>
#include <iostream>

static bool show_launcher = true;
bool show_imgui = false;
bool show_debug = false;
bool button_pressed = false;
double button_timer = 0.0;
double button_delay = 0.2;
std::string word;

void processInput(GLFWwindow *window);

int main(int argc, char *argv[])
{   
    
    if(argv[1] == NULL){
        word  = " ";
    }else{
        word  = argv[1];
    }
    
    // Инициализация GLFW
    if (!glfwInit())
    {
        std::cerr << "Ошибка инициализации GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создание окна
    GLFWwindow* window = glfwCreateWindow(1280, 720, "LDBox", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Ошибка создания GLFW окна" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Установка текущего контекста OpenGL в окно GLFW
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Ошибка создания  GLAD" << std::endl;
        return -1;
    } 
    //////////////////////////////////////////////////////////////////////////////

    //IMGUI Init
    UI::InitImGui(window);

    glfwSwapInterval(1);
    static float R,G,B;

    //////////////////////////////////////////////////////////////////////////////
    // Главный цикл приложения
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        double current_time = glfwGetTime();
    glfwPollEvents();

    if (button_pressed && current_time > button_timer) {
        button_pressed = false;
    }   
        
        // Очистка буфера цвета
        glClearColor(R,G,B, 1.0f);
        //std::cout << R << G << B <<std::endl;
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Отрисовка

        //Загрузка ИмГуи
        UI::DrawImGui();
        ImGui::ShowStyleEditor();
        if(show_imgui)
            UI::HeaderMenu();
        if(show_debug)
            UI::DebugMenu(&R, &G, &B); 
        if(word == "--dev")
        {
            // ???
        } 
        else
        {
            UI::Launcher(&show_launcher);
        }
        ImGui::ShowUserGuide();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Обновление экрана
        glfwSwapBuffers(window);

        // Обработка событий
        glfwPollEvents();
    }
    // Освобождение ресурсов GLFW и завершение программы
    UI::DestroyImGui();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}



void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_F1)  == GLFW_PRESS && !button_pressed) {
        button_pressed = true;
        button_timer = glfwGetTime() + button_delay;
        show_imgui = !show_imgui;
    }
    if (glfwGetKey(window, GLFW_KEY_F5)  == GLFW_PRESS && !button_pressed) {
        button_pressed = true;
        button_timer = glfwGetTime() + button_delay;
        show_debug = !show_debug;
    }
}
