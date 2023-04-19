cmake_minimum_required(VERSION 3.12)
project(LDBox VERSION 0.1.1)

option(BUILD_SHARED_LIBS "Build Shared Libraries" ON) 

set(IMGUI_DIR src/imgui)

set (CMAKE_CXX_STANDARD 17)



#glfw
add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)
link_directories(vendor/glfw/lib)

#glad
add_subdirectory(vendor/glad/)
link_directories(vendor/glad)
include_directories(vendor/glad/include)

#glm
add_subdirectory(vendor/glm)
link_directories(vendor/glm)
include_directories(vendor/glm)

#cpr
add_subdirectory(vendor/cpr)
include_directories(vendor/cpr/include)
link_directories(vendor/cpr/lib)

#assimp
#add_subdirectory(vendor/assimp)
#include_directories(vendor/assimp/include)
#link_directories(vendor/assimp/lib)



add_executable(
        LDBox
        src/main.cpp 
        src/ui/ui.cpp
        src/FileBrowser/ImGuiFileBrowser.cpp
        ${IMGUI_DIR}/imgui_impl_opengl3.cpp 
        ${IMGUI_DIR}/imgui_impl_glfw.cpp 
        ${IMGUI_DIR}/imgui.cpp 
        ${IMGUI_DIR}/imgui_draw.cpp 
        ${IMGUI_DIR}/imgui_demo.cpp 
        ${IMGUI_DIR}/imgui_tables.cpp 
        ${IMGUI_DIR}/imgui_widgets.cpp
)
target_link_libraries(
        LDBox PUBLIC 
        glfw 
        glad 
        glm
        cpr::cpr
        #vulkan
        )
