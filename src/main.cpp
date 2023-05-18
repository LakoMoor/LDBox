// Config headers
#include "config.h"

// SDL2 and GLAD headers
#include <SDL.h>
#include <glad/glad.h>

// Logger
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>


// Render and UI headers
#include "core/render.h"
#include "ui/renderui.h"

// Other headers
#include <iostream>
#include <fstream>


int main(int argc, char* argv[])
{
    if(argc==2 && !strcmp(argv[1], "-dev"))
    {
        debugui = !debugui;
        spdlog::debug("DEV MODE");
    }
    // Initialize SDL2
    Render();
    //SDL_Init(SDL_INIT_VIDEO);
    

    // Create a window
    spdlog::info("Create SDL2 window");
    SDL_Window* window = SDL_CreateWindow("LDBox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_SetWindowResizable(window, SDL_TRUE);
    
    // Create an OpenGL context
    spdlog::info("Create OpenGL context");
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        spdlog::error("Failed to initialize GLAD");
        return -1;
    }
    
    // Setup ImGui context
    UI::InitImGui(window, glContext);

    // Set up the viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Create texture for rendering the SDL2 window
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // Wait for user to close the window
    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            // without it you won't have keyboard input and other things
            ImGui_ImplSDL2_ProcessEvent(&event);
            // you might also want to check io.WantCaptureMouse and io.WantCaptureKeyboard
            // before processing events
            switch (event.type)
            {

            //Check for quit   
            case SDL_QUIT:
                quit = true;
                break;

            // Keyboard stream
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_BACKQUOTE:
                    spdlog::debug("Debug console open case");
                    consoleui = !consoleui;
                    continue;
                case SDLK_F11:
                    spdlog::debug("Fullscreen case");
                    Render::Fullscreen(window);
                    continue;
                }
            }            
        }

        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        SDL_GetWindowSize(window, &GET_WIDTH, &GET_HEIGHT);

        //Clear OpenGL context
        glClearColor(R,G,B, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
         // Render the SDL2 window to a texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        UI::DrawImGui(window);

        // start the Dear ImGui frame
        UI::Launcher(&show_launcher, window, textureID);
        
        //ImGui::ShowStyleEditor();
        if(consoleui)
        {
            UI::Console();
        }
        UI::HeaderMenu(window, &debugui);

        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
    //Clean up ImGui
    spdlog::warn("Delete ImGui render...");
    UI::DestroyImGui();
    spdlog::debug("Delete successfully!");
    // Clean up OpenGL and SDL2
    spdlog::warn("Delete OpenGL context...");
    SDL_GL_DeleteContext(glContext);
    spdlog::debug("Delete successfully!");
    spdlog::warn("Destroy window...");
    SDL_DestroyWindow(window);
    spdlog::debug("Delete successfully!");
    spdlog::warn("Init SDL_Quit...");
    SDL_Quit();

    spdlog::debug("SDL_Quit successfully!");
    spdlog::info("Bye!");
    return 0;
}
