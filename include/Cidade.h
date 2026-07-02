//
// Created by leon on 29/06/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_CIDADE_H
#define CONTROLADOR_DE_VIAGENS_CIDADE_H
#include <string>

class Cidade {
private:
    std::string nome;
    int visitas;
public:
    Cidade(std::string nome);
    std::string getNome();
    int getVisitas();
    void setVisitas(int v);
};


#endif //CONTROLADOR_DE_VIAGENS_CIDADE_H
