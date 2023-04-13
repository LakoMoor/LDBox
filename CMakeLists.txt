cmake_minimum_required(VERSION 3.0.0)
project(LDBox VERSION 0.1.0)

option(BUILD_SHARED_LIBS "Build Shared Libraries" ON) 

set(IMGUI_DIR src/imgui)


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

#assimp
add_subdirectory(vendor/assimp)
include_directories(vendor/assimp/include)
link_directories(vendor/assimp/lib)



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
        assimp
        glm
        #vulkan
        )