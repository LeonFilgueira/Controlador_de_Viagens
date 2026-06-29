//
// Created by leon on 29/06/2026.
//

#include "../include/Passageiro.h"

Passageiro::Passageiro(std::string nome, Cidade *localAtual) {
    this->nome = nome;
    this->localAtual = localAtual;
}

void Passageiro::setLocalAtual(Cidade *local) {
    this->localAtual = local;
}

Cidade *Passageiro::getLocalAtual() {
    return this->localAtual;
}

std::string Passageiro::getNome() {
    return this->nome;
}
