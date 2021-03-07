cmake_minimum_required(VERSION 3.17)
project(Projeto_CG)

set(CMAKE_CXX_STANDARD 14)

include_directories(Generate)

add_executable(Projeto_CG
        Engine/main.cpp
        Generate/box.cpp
        Generate/box.h
        Generate/cone.cpp
        Generate/cone.h
        Generate/generate.cpp
        Generate/plano.cpp
        Generate/plano.h
        Generate/sphere.cpp
        Generate/sphere.h)
