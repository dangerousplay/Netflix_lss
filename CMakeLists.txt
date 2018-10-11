cmake_minimum_required(VERSION 3.12)
project(Netflix_lss)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include(build/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(${PROJECT_NAME} "src" "src/main.cpp" src/models/cliente.cpp src/models/cliente.h src/models/Filme.cpp src/models/Filme.h src/models/Alocacao.cpp src/models/Alocacao.h src/db/init.h src/services/alocacao.cpp src/services/alocacao.h)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
