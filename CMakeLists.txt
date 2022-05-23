cmake_minimum_required(VERSION 3.23.1)
project(Editer CXX)
add_executable(Editer main.cpp io.cpp window.cpp command.cpp)
set_property(TARGET Editer PROPERTY CXX_STANDARD 17)
