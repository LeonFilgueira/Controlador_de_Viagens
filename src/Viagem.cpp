//
// Created by leon on 29/06/2026.
//

#include "../include/Viagem.h"

Viagem::Viagem(Transporte* transporte, const std::vector<Passageiro*> passageiros, Cidade *origem, Cidade *destino) {
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;
    this->horasEmTransito = 0;
    this->emAndamento = false;
}

void Viagem::iniciarViagem() {
    this->emAndamento = true;
}

void Viagem::avancarHoras(int horas) {
    this->horasEmTransito = this->horasEmTransito + horas;
}

void Viagem::relatarEstado() {
}

bool Viagem::isEmAndamento() {
    return this->emAndamento;
}
