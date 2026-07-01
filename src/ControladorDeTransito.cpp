//
// Created by leon on 29/06/2026.
//

#include "../include/ControladorDeTransito.h"
#include <iostream>
using namespace std;

Cidade *ControladorDeTransito::buscarCidade(std::string nome) {
    for (Cidade *cidade: cidades) {
        if (cidade->getNome() == nome) {
            return cidade;
        }
    }
    cout << "Não existe uma cidade cadastrada com o nome " << nome << endl;
    return nullptr;
}

Transporte *ControladorDeTransito::buscarTransporte(std::string nome) {
    for (Transporte *transporte: transportes) {
        if (transporte->getNome() == nome) {
            return transporte;
        }
    }
    cout << "Não existe um transporte cadastrado com o nome " << nome << endl;
    return nullptr;
}

Passageiro *ControladorDeTransito::buscarPassageiro(std::string nome) {
    for (Passageiro *passageiro: passageiros) {
        if (passageiro->getNome() == nome) {
            return passageiro;
        }
    }
    cout << "Não existe um passageiro cadastrado com o nome " << nome << endl;
    return nullptr;
}

void ControladorDeTransito::cadastrarCidade(std::string nome) {
    if (!nome.empty()) {
        for (Cidade *cidade: cidades) {
            if (cidade->getNome() == nome) {
                cout << "Já existe uma cidade cadastrada com esse nome" << endl;
                return;
            }
        }
        this->cidades.push_back(new Cidade(nome));
        cout << "Cidade de nome " << nome << " cadastrada com sucesso" << endl;
        return;
    }
    cout << "O nome da cidade não pode estar vazio";
}

void ControladorDeTransito::
cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia) {
    Cidade *origem = buscarCidade(nomeOrigem);
    Cidade *destino = buscarCidade(nomeDestino);
    if (origem && destino) {
        this->trajetos.push_back(new Trajeto(origem, destino, tipo, distancia));
        cout << "Trajeto " << nomeOrigem << "->" << nomeDestino << " cadastrado com sucesso" << endl;
    } else {
        cout << "Não foi possível cadastrar esse trajeto." << endl;
    }
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade,
                                                int distancia_entre_descansos, int tempo_de_descanso,
                                                std::string localAtual) {
    Cidade *local = buscarCidade(localAtual);
    if (local) {
        this->transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos,
                                                   tempo_de_descanso, local));
        cout << "Transporte " << nome << " cadastrado com sucesso." << endl;
    } else {
        cout << "Não foi possível cadastrar o transporte." << endl;
    }
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual) {
    Cidade *local = buscarCidade(localAtual);
    if (local) {
        this->passageiros.push_back(new Passageiro(nome, local));
    } else {
        cout << "Não foi possivel cadastrar o passageiro" << endl;
    }
}

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros,
                                          std::string nomeOrigem, std::string nomeDestino) {
    Cidade *origem = buscarCidade(nomeOrigem);
    Cidade *destino = buscarCidade(nomeDestino);
    Transporte *transporte = buscarTransporte(nomeTransporte);
    vector<Passageiro *> passageirosViagem;

    for (string nome: nomesPassageiros) {
        Passageiro *passageiro = buscarPassageiro(nome);
        if (passageiro) {
            passageirosViagem.push_back(passageiro);
        }
    }

    if (origem && destino) {
        this->viagens.push_back(new Viagem(transporte, passageirosViagem, origem, destino));
    }
}

void ControladorDeTransito::avancarHoras(int horas) {
}

void ControladorDeTransito::relatarEstado() {
}

void ControladorDeTransito::imprimirCidades() {
    cout << "Cidades cadastradas: \n" << endl;
    for (Cidade *cidade: cidades) {
        cout << cidade->getNome() << endl;
    }
    cout << "\n\n";
}

void ControladorDeTransito::imprimirPassageiros() {
}

void ControladorDeTransito::imprimirTrajetos() {
}
