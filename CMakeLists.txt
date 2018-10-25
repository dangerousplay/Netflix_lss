cmake_minimum_required(VERSION 3.10)
project(Netflix_lss)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")

include(build/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME}
        "src" "src/main.cpp"
        src/models/cliente.cpp
        src/models/cliente.h
        src/models/Filme.cpp
        src/models/Filme.h
        src/models/Alocacao.cpp
        src/models/Alocacao.h
        src/db/init.h
        src/services/alocacao.cpp
        src/services/alocacao.h
        src/imgui/imgui_impl_glfw.cpp
        src/imgui/imgui_impl_glfw.h
        src/imgui/imgui_impl_opengl3.cpp
        src/imgui/imgui_impl_opengl3.h
        src/menus/filme.cpp
        src/menus/filme.h
        src/menus/IMenu.h
        src/menus/cliente.cpp
        src/menus/cliente.h
        src/menus/alocacao.cpp
        src/menus/alocacao.h
        src/utils/stringUtils.h src/db/init.cpp src/utils/stringUtils.cpp)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
