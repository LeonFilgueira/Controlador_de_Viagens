//
// Created by leon on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_CONTROLADORDETRANSITO_H
#define CONTROLADOR_DE_VIAGENS_CONTROLADORDETRANSITO_H
#include <vector>
#include <string>
#include "Cidade.h"
#include "Passageiro.h"
#include "Transporte.h"
#include "Trajeto.h"
#include "Viagem.h"

class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Trajeto*> trajetos;
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Viagem*> viagens;
public:
    Cidade* buscarCidade(std::string nome);
    Transporte* buscarTransporte(std::string nome);
    Passageiro* buscarPassageiro(std::string nome);
    void cadastrarCidade(std::string nome);
    void cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia);
    void cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual);
    void cadastrarPassageiro(std::string nome, std::string localAtual);
    void iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);
    void imprimirCidades();
    void imprimirPassageiros();
    void imprimirTrajetos();
    void relatarEstado();
};


#endif //CONTROLADOR_DE_VIAGENS_CONTROLADORDETRANSITO_H
