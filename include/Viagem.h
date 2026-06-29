//
// Created by leon on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_VIAGEM_H
#define CONTROLADOR_DE_VIAGENS_VIAGEM_H
#include <vector>
#include "Cidade.h"
#include "Passageiro.h"
#include "Transporte.h"

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    Viagem* proxima;
    int horasEmTransito;
    bool emAndamento;
public:
    Viagem(Transporte *transporte, const std::vector<Passageiro *> passageiros, Cidade *origem, Cidade *destino);
    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado();
    bool isEmAndamento();
};


#endif //CONTROLADOR_DE_VIAGENS_VIAGEM_H
