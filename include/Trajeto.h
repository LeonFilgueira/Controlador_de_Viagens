//
// Created by leon on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_TRAJETO_H
#define CONTROLADOR_DE_VIAGENS_TRAJETO_

#include "Cidade.h"

class Trajeto {
private:
    Cidade* origem;
    Cidade* destino;
    char tipo;
    int distancia;
public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);
    Cidade* getOrigem();
    Cidade* getDestino();
    char getTipo();
    int getDistancia();
};


#endif //CONTROLADOR_DE_VIAGENS_TRAJETO_H
