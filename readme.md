

To install dependencies on Windows

conan install .. -s compiler="gcc" -s compiler.version=8.1 -s compiler.libcxx="libstdc++" --build imgui --build sqlite3