//
// Created by leon on 29/06/2026.
//

#include "../include/Cidade.h"

Cidade::Cidade(std::string nome) {
    this->nome = nome;
    this->visitas = 0;
}

std::string Cidade::getNome() {
    return this->nome;
}

int Cidade::getVisitas() {
    return this->visitas;
}

void Cidade::setVisitas(int visitas) {
    this->visitas = visitas;
}