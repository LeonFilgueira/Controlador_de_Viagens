//
// Created by leon on 29/06/2026.
//

#include "../include/Viagem.h"
#include <iostream>

#include "../include/ControladorDeTransito.h"
using namespace std;

Viagem::Viagem(Transporte *transporte, const std::vector<Passageiro *> passageiros, vector<Trajeto *> trajetosRota) {
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->horasEmTransito = 0;
    this->emAndamento = false;
    this->trajetoAtual = 0;
    this->horasDescansando = 0;
    this->kmDesdeDescanso = 0;
    this->emDescanso = false;
    this->trajetosRota = trajetosRota;
    this->origem = this->trajetosRota[0]->getOrigem();
    this->destino = this->trajetosRota[trajetosRota.size() - 1]->getDestino();
}

void Viagem::iniciarViagem() {
    this->emAndamento = true;
}

void Viagem::avancarHoras(int horas) {
    if (!this->emAndamento || this->trajetoAtual >= this->trajetosRota.size()) return;

    int velocidade = this->transporte->getVelocidade();
    int distanciaDescanso = this->transporte->getDistanciaEntreDescansos();
    int tempoDescanso = this->transporte->getTempoDescanso();

    for (int h = 0; h < horas; ++h) {
        if (this->trajetoAtual >= this->trajetosRota.size()) {
            this->emAndamento = false;
            break;
        }

        // Avança o tempo de descanso e pula esse loop
        if (this->emDescanso) {
            this->horasDescansando--;

            if (this->horasDescansando <= 0) {
                this->emDescanso = false;
            }

            continue;
        }

        // Aumenta o tempo de viagem
        this->horasEmTransito++;

        // O transporte e os passageiros ficam em trânsito
        this->transporte->setLocalAtual(nullptr);

        for (Passageiro *p: this->passageiros) {
            p->setLocalAtual(nullptr);
        }


        // Conta quantos km foram percorridos desde o último descanso
        this->kmDesdeDescanso += velocidade;


        // Verifica se precisa parar para descansar
        // e reseta a distância necessária pra descansar
        if (this->kmDesdeDescanso >= distanciaDescanso) {
            this->kmDesdeDescanso = 0;
            this->emDescanso = true;
            this->horasDescansando = tempoDescanso;
            continue;
        }


        // Calcula a distância total
        int kmTotal = this->horasEmTransito * velocidade;

        //Calcula a distância dos trajetos já percorridos
        int kmTrajetosAnteriores = 0;
        for (int i = 0; i < this->trajetoAtual; ++i) {
            kmTrajetosAnteriores += this->trajetosRota[i]->getDistancia();
        }

        // Distância dentro do trajeto atual
        int kmTrajetoAtual = kmTotal - kmTrajetosAnteriores;
        int distanciaTrajetoAtual = this->trajetosRota[this->trajetoAtual]->getDistancia();

        if (kmTrajetoAtual >= distanciaTrajetoAtual) {
            Cidade *cidadeChegada = this->trajetosRota[this->trajetoAtual]->getDestino();
            cidadeChegada->setVisitas(cidadeChegada->getVisitas() + 1);

            this->transporte->setLocalAtual(cidadeChegada);

            for (Passageiro *p: this->passageiros) {
                p->setLocalAtual(cidadeChegada);
            }


            this->trajetoAtual++;


            // Finaliza a viagem
            if (this->trajetoAtual >= this->trajetosRota.size()) {
                this->emAndamento = false;

                cout << "Viagem concluída!" << endl;
                this->relatarEstado();

                break;
            }
        }
    }
}

void Viagem::relatarEstado() {
    cout << "======================================" << endl;
    cout << "Estado da viagem " << origem->getNome() << "->" << destino->getNome() << endl;;
    if (isEmAndamento()) {
        cout << "Status: Em andamento" << endl;
    } else {
        if (this->trajetoAtual >= this->trajetosRota.size()) {
            cout << "Status: Finalizada" << endl;
        } else {
            cout << "Status: Não iniciada" << endl;
        }
    }
    cout << "Transporte: " << this->transporte->getNome() << endl;
    cout << "Tempo de viagem: " << this->horasEmTransito << endl;
    cout << "Passageiros: " << endl;
    for (Passageiro *p: passageiros) {
        cout << "   -" << p->getNome() << endl;
    }
    cout << "======================================" << endl;
}

bool Viagem::isEmAndamento() {
    return this->emAndamento;
}

Cidade *Viagem::getOrigem() {
    return this->origem;
}

Cidade *Viagem::getDestino() {
    return this->destino;
}

int Viagem::getHorasEmTransito() {
    return this->horasEmTransito;
}

int Viagem::getHorasDescansando() {
    return this->horasDescansando;
}

int Viagem::getKmDesdeDescanso() {
    return this->kmDesdeDescanso;
}

int Viagem::getTrajetoAtual() {
    return this->trajetoAtual;
}

Transporte *Viagem::getTransporte() {
    return this->transporte;
}

std::vector<Passageiro *> Viagem::getPassageiros() {
    return this->passageiros;
}

void Viagem::setTrajetoAtual(int trajetoAtual) {
    this->trajetoAtual = trajetoAtual;
}

void Viagem::setEmAndamento(bool emAndamento) {
    this->emAndamento = emAndamento;
}

void Viagem::setHorasEmTransito(int horasEmTransito) {
    this->horasEmTransito = horasEmTransito;
}
