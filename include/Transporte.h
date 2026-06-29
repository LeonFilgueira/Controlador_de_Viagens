//
// Created by leon on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_TRANSPORTE_H
#define CONTROLADOR_DE_VIAGENS_TRANSPORTE_H
#include <string>
#include "Cidade.h"

class Transporte {
private:
    std::string nome;
    char tipo;
    int capacidade;
    int velocidade;
    int distancia_entre_descansos;
    int tempo_de_descanso;
    int tempo_de_descanso_atual;
    Cidade* localAtual;
public:
    Transporte(const std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos,
        int tempo_de_descanso, int tempo_de_descanso_atual, Cidade *local_atual);
    std::string getNome();
    char getTipo();
    int getCapacidade();
    int getVelocidade();
    int getDistanciaEntreDescansos();
    int getTempoDescanso();
    int getTempoDescansoAtual();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
};


#endif //CONTROLADOR_DE_VIAGENS_TRANSPORTE_H
