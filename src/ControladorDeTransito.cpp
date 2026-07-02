//
// Created by leon on 29/06/2026.
//

#include "../include/ControladorDeTransito.h"
#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

//Algoritmo de Djikstra pra encontrar a melhor rota
vector<Trajeto *> ControladorDeTransito::calculcarMelhorRota(std::string nomeOrigem, std::string nomeDestino,
                                                             char tipo) {
    Cidade* origem = buscarCidade(nomeOrigem);
    Cidade* destino = buscarCidade(nomeDestino);

    if (!origem || !destino) return {};

    std::map<Cidade*, int> distancias;

    std::map<Cidade*, Trajeto*> trajetoAnterior;

    for (Cidade* cidade : cidades) {
        distancias[cidade] = INT_MAX;
        trajetoAnterior[cidade] = nullptr;
    }
    distancias[origem] = 0;

    priority_queue<std::pair<int, Cidade*>,
                        std::vector<std::pair<int, Cidade*>>,
                        std::greater<std::pair<int, Cidade*>>> fila;

    fila.push({0, origem});

    while (!fila.empty()) {
        Cidade* u = fila.top().second;
        int dist_u = fila.top().first;
        fila.pop();

        if (dist_u > distancias[u]) continue;
        if (u == destino) break;

        for (Trajeto* trajeto : trajetos) {

            if (trajeto->getOrigem() == u && trajeto->getTipo() == tipo) {
                Cidade* v = trajeto->getDestino();
                int peso = trajeto->getDistancia();

                if (distancias[u] != INT_MAX && distancias[u] + peso < distancias[v]) {
                    distancias[v] = distancias[u] + peso;
                    trajetoAnterior[v] = trajeto;
                    fila.push({distancias[v], v});
                }
            }
        }
    }

    if (distancias[destino] == INT_MAX) {
        cout << "Nao ha rota disponivel entre " << nomeOrigem << " e " << nomeDestino << " para o tipo " << tipo << endl;
        return {};
    }

    vector<Trajeto*> rotaDeTrajetos;
    Cidade* atual = destino;

    while (atual != origem) {
        Trajeto* t = trajetoAnterior[atual];
        if (!t) break;

        rotaDeTrajetos.push_back(t);
        atual = t->getOrigem();
    }

    std::reverse(rotaDeTrajetos.begin(), rotaDeTrajetos.end());

    return rotaDeTrajetos;

}

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

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo,
                                             int distancia) {
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
        Passageiro *p = buscarPassageiro(nome);
        if (p) {
            passageirosViagem.push_back(p);
        }
    }

    if (origem && destino && transporte && transporte->getLocalAtual() == origem) {
        vector<Trajeto*> rotaCalculada = calculcarMelhorRota(nomeOrigem, nomeDestino, transporte->getTipo());
        if (!rotaCalculada.empty()) {
            Viagem* novaViagem = new Viagem(transporte,passageirosViagem,rotaCalculada);
            novaViagem->iniciarViagem();
            this->viagens.push_back(novaViagem);
        }else {
            cout << "Não foi possível iniciar a viagem, não existe uma rota para o percurso desejado" << endl;
        }
    } else {
        cout << "Não foi possível inciar a viagem" << endl;
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
