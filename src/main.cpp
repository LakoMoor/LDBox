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

// Include GLM
#include <glm/glm.hpp>

//Default
#include <stdio.h>
#include <vector>
#include <iostream>


const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

static bool show_launcher = true;
bool show_imgui = false;
bool show_debug = false;
bool button_pressed = false;
double button_timer = 0.0;
double button_delay = 0.2;

void processInput(GLFWwindow *window);

int main()
{   
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

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
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
        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Загрузка ИмГуи
        UI::DrawImGui();
        ImGui::ShowStyleEditor();
        if(show_imgui)
            UI::HeaderMenu();
        if(show_debug)
            UI::DebugMenu(&R, &G, &B);   
        //UI::Launcher(&show_launcher);
        

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Обновление экрана
        glfwSwapBuffers(window);

        // Обработка событий
        glfwPollEvents();
    }

    // Освобождение ресурсов GLFW и завершение программы
    UI::DestroyImGui();
     glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
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
