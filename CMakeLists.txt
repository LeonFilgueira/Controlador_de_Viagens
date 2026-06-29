cmake_minimum_required(VERSION 4.2)
project(Controlador_de_Viagens)

set(CMAKE_CXX_STANDARD 20)

add_executable(Controlador_de_Viagens src/main.cpp
        src/Cidade.cpp
        include/Cidade.h
        src/Trajeto.cpp
        include/Trajeto.h
        src/Transporte.cpp
        include/Transporte.h
        src/Passageiro.cpp
        include/Passageiro.h
        src/Viagem.cpp
        include/Viagem.h
        src/ControladorDeTransito.cpp
        include/ControladorDeTransito.h)
