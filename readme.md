Componentes do Grupo: Davi Henrique, Josué William e Moisés Alcides

To compile this project you will need CMake, GCC and Conan

You will need bincrafters remote repository added on conan

To add Bincrafters repository run:
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

you will need OpenGL, GLFW and OpenGL ES3 installed to compile this code

To install OpenGL ES3 and GLFW on Ubuntu run on terminal:
sudo apt-get install libglfw3-dev libgles2-mesa-dev

To compile on GCC on Windows you can use:
conan install .. -s compiler="gcc" -s compiler.version=8.1 -s compiler.libcxx="libstdc++" --build imgui --build sqlite3