//
// Created by leon on 29/06/2026.
//

#include "../include/Cidade.h"

Cidade::Cidade(std::string nome) {
    this->nome = nome;
}

std::string Cidade::getNome() {
    return this->nome;
}
