//
// Created by leon on 29/06/2026.
//

#include "../include/ControladorDeTransito.h"

void ControladorDeTransito::cadastrarCidade(std::string nome) {
    this->cidades.push_back(new Cidade(nome));
}

void ControladorDeTransito::
cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia) {
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade,
    int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual) {
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual) {
}

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros,
    std::string nomeOrigem, std::string nomeDestino) {
}

void ControladorDeTransito::avancarHoras(int horas) {
}

void ControladorDeTransito::relatarEstado() {
}
