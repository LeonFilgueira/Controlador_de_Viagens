//
// Created by leon on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_PASSAGEIRO_H
#define CONTROLADOR_DE_VIAGENS_PASSAGEIRO_H

#include <string>
#include "Cidade.h"

class Passageiro {
private:
    std::string nome;
    Cidade* localAtual;
public:
    Passageiro(std::string nome, Cidade* localAtual);
    std::string getNome();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
};


#endif //CONTROLADOR_DE_VIAGENS_PASSAGEIRO_H
