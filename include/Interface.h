//
// Created by leon on 01/07/2026.
//

#ifndef CONTROLADOR_DE_VIAGENS_INTERFACE_H
#define CONTROLADOR_DE_VIAGENS_INTERFACE_H


class Interface {
public:
    void iniciar();
    void cadastros();
    void consultas();
    void gerenciarViagens();
    void cadastroCidade();
    void cadastroTrajeto();
    void cadastroTransporte();
    void cadastroPassageiro();
    void avançarHoras();
    void relatarEstado();
    void iniciarViagem();
    void viagensEmAndamento();
    void localizarPassageiro();
    void localizarTransporte();
    void maisVisitadas();

};


#endif //CONTROLADOR_DE_VIAGENS_INTERFACE_H
