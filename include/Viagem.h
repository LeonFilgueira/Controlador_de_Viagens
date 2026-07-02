//
// Created by leon on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_VIAGEM_H
#define CONTROLADOR_DE_VIAGENS_VIAGEM_H

#include <vector>
#include "Cidade.h"
#include "Passageiro.h"
#include "Trajeto.h"
#include "Transporte.h"

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    std::vector<Trajeto*> trajetosRota;
    Cidade* origem;
    Cidade* destino;
    int horasEmTransito;
    int horasDescansando;
    int kmDesdeDescanso;
    int trajetoAtual;
    bool emAndamento;
    bool emDescanso;


public:
    Viagem(Transporte *transporte, std::vector<Passageiro *> passageiros, std::vector<Trajeto*> trajetosRota);
    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado();
    bool isEmAndamento();
    Cidade* getOrigem();
    Cidade* getDestino();
    int getHorasEmTransito();
    int getHorasDescansando();
    int getKmDesdeDescanso();
    int getTrajetoAtual();
    void setTrajetoAtual(int trajetoAtual);
    void setEmAndamento(bool emAndamento);
    void setHorasEmTransito(int horasEmTransito);
    Transporte* getTransporte();
    std::vector<Passageiro*> getPassageiros();
};


#endif //CONTROLADOR_DE_VIAGENS_VIAGEM_H
