cmake_minimum_required(VERSION 3.0.1)
project(LDBox VERSION 0.1.1)

option(BUILD_SHARED_LIBS "Build Shared Libraries" ON) 

set(IMGUI_DIR src/imgui)

set (CMAKE_CXX_STANDARD 17)

file(GLOB LDBOX_SRC
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
    "${IMGUI_DIR}/*.cpp"
)

#SDL2
add_subdirectory(vendor/SDL)
include_directories(vendor/SDL/include)
link_directories(vendor/SDL/lib)

#glad
add_subdirectory(vendor/glad/)
link_directories(vendor/glad)
include_directories(vendor/glad/include)

#glm
#add_subdirectory(vendor/glm)
#link_directories(vendor/glm)
#include_directories(vendor/glm)


add_executable(
        LDBox
        ${LDBOX_SRC}
)
target_link_libraries(
        LDBox PUBLIC
        SDL2 
        SDL2main 
        glad 
#        glm
        )