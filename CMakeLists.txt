cmake_minimum_required(VERSION 3.0.1)
project(LDBox VERSION 0.1.1)

option(BUILD_SHARED_LIBS "Build Shared Libraries" ON) 

set(IMGUI_DIR src/imgui)

set (CMAKE_CXX_STANDARD 17)

file(GLOB LDBOX_SRC
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/ui/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/FileBrowser/*.cpp"
    "${IMGUI_DIR}/*.cpp"
)

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
        ${LDBOX_SRC}
)
target_link_libraries(
        LDBox PUBLIC 
        glfw 
        glad 
        glm
        cpr::cpr
        #vulkan
        )
