//
// Created by leon on 29/06/2026.
//

#include "../include/ControladorDeTransito.h"
#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
#include <climits>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

//Algoritmo de Djikstra pra encontrar a melhor rota
vector<Trajeto *> ControladorDeTransito::calculcarMelhorRota(std::string nomeOrigem, std::string nomeDestino,
                                                             char tipo) {
    Cidade *origem = buscarCidade(nomeOrigem);
    Cidade *destino = buscarCidade(nomeDestino);

    if (!origem || !destino) return {};

    std::map<Cidade *, int> distancias;

    std::map<Cidade *, Trajeto *> trajetoAnterior;

    for (Cidade *cidade: cidades) {
        distancias[cidade] = INT_MAX;
        trajetoAnterior[cidade] = nullptr;
    }
    distancias[origem] = 0;

    priority_queue<std::pair<int, Cidade *>,
        std::vector<std::pair<int, Cidade *> >,
        std::greater<std::pair<int, Cidade *> > > fila;

    fila.push({0, origem});

    while (!fila.empty()) {
        Cidade *u = fila.top().second;
        int dist_u = fila.top().first;
        fila.pop();

        if (dist_u > distancias[u]) continue;
        if (u == destino) break;

        for (Trajeto *trajeto: trajetos) {
            if (trajeto->getOrigem() == u && trajeto->getTipo() == tipo) {
                Cidade *v = trajeto->getDestino();
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
        cout << "Nao ha rota disponivel entre " << nomeOrigem << " e " << nomeDestino << " para o tipo " << tipo <<
                endl;
        return {};
    }

    vector<Trajeto *> rotaDeTrajetos;
    Cidade *atual = destino;

    while (atual != origem) {
        Trajeto *t = trajetoAnterior[atual];
        if (!t) break;

        rotaDeTrajetos.push_back(t);
        atual = t->getOrigem();
    }

    std::reverse(rotaDeTrajetos.begin(), rotaDeTrajetos.end());

    return rotaDeTrajetos;
}


//Função para buscar uma cidade pelo nome
Cidade *ControladorDeTransito::buscarCidade(std::string nome) {
    for (Cidade *cidade: cidades) {
        if (cidade->getNome() == nome) {
            return cidade;
        }
    }
    return nullptr;
}

//Função para buscar um transporte pelo nome
Transporte *ControladorDeTransito::buscarTransporte(std::string nome) {
    for (Transporte *transporte: transportes) {
        if (transporte->getNome() == nome) {
            return transporte;
        }
    }
    cout << "Não existe um transporte cadastrado com o nome " << nome << endl;
    return nullptr;
}

//Função para buscar um passageiro pelo nome
Passageiro *ControladorDeTransito::buscarPassageiro(std::string nome) {
    for (Passageiro *passageiro: passageiros) {
        if (passageiro->getNome() == nome) {
            return passageiro;
        }
    }
    cout << "Não existe um passageiro cadastrado com o nome " << nome << endl;
    return nullptr;
}

//Função de cadastro de nova cidade
void ControladorDeTransito::cadastrarCidade(std::string nome) {
    if (!nome.empty()) {
        for (Cidade *cidade: cidades) {
            if (cidade->getNome() == nome) {
                cout << "Já existe uma cidade cadastrada com esse nome" << endl;
                return;
            }
        }
        //se a cidade ainda não foi cadastrada e o nome não está vazio, cria uma nova cidade e salva no txt
        Cidade *novaCidade = new Cidade(nome);
        this->cidades.push_back(novaCidade);
        salvarCidades();
        return;
    }
    cout << "O nome da cidade não pode estar vazio" << endl;
}

//Função de cadastro de novo trajeto
void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo,
                                             int distancia) {
    Cidade *origem = buscarCidade(nomeOrigem);
    Cidade *destino = buscarCidade(nomeDestino);

    //se ambos a cidadade e o destino existirem, cria o trajeto e salva no txt
    if (origem && destino) {
        this->trajetos.push_back(new Trajeto(origem, destino, tipo, distancia));
        cout << "Trajeto " << nomeOrigem << "->" << nomeDestino << " cadastrado com sucesso" << endl;
        salvarTrajetos();
    } else {
        cout << "Não foi possível cadastrar esse trajeto." << endl;
    }
}

//função de cadastro de novo transporte
void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade,
                                                int distancia_entre_descansos, int tempo_de_descanso,
                                                std::string localAtual) {
    Cidade *local = buscarCidade(localAtual);
    //se o local existe, cria o transporte naquele local
    if (local) {
        this->transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos,
                                                   tempo_de_descanso, local));
        cout << "Transporte " << nome << " cadastrado com sucesso." << endl;
        salvarTransportes();
    } else {
        cout << "Não foi possível cadastrar o transporte." << endl;
    }
}

//função de cadastro de novo passageiro
void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual) {
    Cidade *local = buscarCidade(localAtual);
    //não permite que o mesmo passageiro seja registrado mais de uma vez
    for (Passageiro* passageiro: passageiros) {
        if (passageiro->getNome() == nome) {
            cout << "Esse passageiro já foi cadastrado"<<endl;
            return;
        }
    }

    //se o local existir e o passageiro ainda não, cria o passageiro e salva no txt
    if (local) {
        this->passageiros.push_back(new Passageiro(nome, local));
        salvarPassageiros();
    } else {
        cout << "Não foi possivel cadastrar o passageiro" << endl;
    }
}

//Função de criar viagem
void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros,
                                          std::string nomeOrigem, std::string nomeDestino) {
    Cidade *origem = buscarCidade(nomeOrigem);
    Cidade *destino = buscarCidade(nomeDestino);
    Transporte *transporte = buscarTransporte(nomeTransporte);
    vector<Passageiro *> passageirosViagem;

    //Valida os passageiros e adiciona somente os válidos
    for (string nome: nomesPassageiros) {
        Passageiro *p = buscarPassageiro(nome);
        if (p) {
            passageirosViagem.push_back(p);
        }
    }

    //testa se existem origem, destino, transporte, e se o transporte e os passageiros estão no ponto de partida
    if (origem && destino && transporte && transporte->getLocalAtual() == origem && passageirosViagem.size() <=
        transporte->getCapacidade()) {
        for (Passageiro *passageiros: passageirosViagem) {
            if (passageiros->getLocalAtual() != origem) {
                cout << "Não foi possível iniciar a viagem, nem todos os passageiros estão no local de origem" << endl;
                return;
            }
        }
        //chama a função do algoritmo dijkstra pra calcular a melhor rota
        vector<Trajeto *> rotaIdeal = calculcarMelhorRota(nomeOrigem, nomeDestino, transporte->getTipo());
        if (!rotaIdeal.empty()) {
            //se a rota for possível, cria a viagem em andamento e salva no txt
            Viagem *novaViagem = new Viagem(transporte, passageirosViagem, rotaIdeal);
            novaViagem->iniciarViagem();
            this->viagens.push_back(novaViagem);
            cout << "Viagem iniciada com sucesso" << endl;
            salvarViagens();
        } else {
            cout << "Não foi possível iniciar a viagem, não existe uma rota para o percurso desejado" << endl;
        }
    } else {
        cout << "Não foi possível inciar a viagem" << endl;
    }
}

void ControladorDeTransito::avancarHoras(int horas) {
    for (Viagem *viagem: viagens) {
        viagem->avancarHoras(horas);
    }
    //após avançar a hora salva tudo que foi modificado
    salvarViagens();
    salvarCidades();
    salvarPassageiros();
    salvarTransportes();
}

void ControladorDeTransito::relatarEstado() {
    for (Viagem *viagem: viagens) {
        viagem->relatarEstado();
    }
}

//carrega os dados txt no programa
void ControladorDeTransito::carregarDados() {
    carregarCidades();
    carregarTrajetos();
    carregarTransportes();
    carregarPassageiros();
    carregarViagens();
}

void ControladorDeTransito::carregarCidades() {
    ifstream arquivo("../Data/Cidade.txt");

    if (!arquivo.is_open())
        return;

    string linha;

    while (getline(arquivo, linha)) {
        size_t pos = linha.find(';');

        if (pos == string::npos)
            continue;

        string nome = linha.substr(0, pos);
        int visitas = stoi(linha.substr(pos + 1));

        Cidade *cidade = new Cidade(nome);
        cidade->setVisitas(visitas);

        cidades.push_back(cidade);
    }
}

void ControladorDeTransito::carregarTrajetos() {
    ifstream arquivo("../Data/Trajeto.txt");

    if (!arquivo.is_open())
        return;

    string linha;

    while (getline(arquivo, linha)) {
        stringstream ss(linha);

        string origemNome;
        string destinoNome;
        string distanciaStr;
        char tipo;

        getline(ss, origemNome, ';');
        getline(ss, destinoNome, ';');

        ss >> tipo;
        ss.ignore();

        getline(ss, distanciaStr);

        Cidade *origem = buscarCidade(origemNome);
        Cidade *destino = buscarCidade(destinoNome);

        if (origem && destino) {
            trajetos.push_back(
                new Trajeto(
                    origem,
                    destino,
                    tipo,
                    stoi(distanciaStr)
                )
            );
        }
    }
}


void ControladorDeTransito::carregarTransportes() {
    ifstream arquivo("../Data/Transporte.txt");

    if (!arquivo.is_open())
        return;

    string linha;

    while (getline(arquivo, linha)) {
        stringstream ss(linha);

        string nome;
        string capacidadeStr;
        string velocidadeStr;
        string distanciaStr;
        string descansoStr;
        string cidadeNome;

        char tipo;

        getline(ss, nome, ';');

        ss >> tipo;
        ss.ignore();

        getline(ss, capacidadeStr, ';');
        getline(ss, velocidadeStr, ';');
        getline(ss, distanciaStr, ';');
        getline(ss, descansoStr, ';');
        getline(ss, cidadeNome);

        Cidade *cidade = buscarCidade(cidadeNome);

        if (cidade) {
            transportes.push_back(
                new Transporte(
                    nome,
                    tipo,
                    stoi(capacidadeStr),
                    stoi(velocidadeStr),
                    stoi(distanciaStr),
                    stoi(descansoStr),
                    cidade
                )
            );
        }
    }
}


void ControladorDeTransito::carregarPassageiros() {
    ifstream arquivo("../Data/Passageiro.txt");

    if (!arquivo.is_open())
        return;

    string linha;

    while (getline(arquivo, linha)) {
        stringstream ss(linha);

        string nome;
        string cidadeNome;

        getline(ss, nome, ';');
        getline(ss, cidadeNome);

        Cidade *cidade = buscarCidade(cidadeNome);

        if (cidade) {
            passageiros.push_back(
                new Passageiro(nome, cidade)
            );
        }
    }
}


void ControladorDeTransito::carregarViagens() {
    ifstream arquivo("../Data/Viagem.txt");

    if (!arquivo.is_open())
        return;

    string linha;

    while (getline(arquivo, linha)) {
        stringstream ss(linha);

        string nomeTransporte;
        string nomeOrigem;
        string nomeDestino;
        string horas;
        string andamento;
        string trajetoAtual;
        string listaPassageiros;

        getline(ss, nomeTransporte, ';');
        getline(ss, nomeOrigem, ';');
        getline(ss, nomeDestino, ';');
        getline(ss, horas, ';');
        getline(ss, andamento, ';');
        getline(ss, trajetoAtual, ';');
        getline(ss, listaPassageiros);

        Transporte *transporte = buscarTransporte(nomeTransporte);
        Cidade *origem = buscarCidade(nomeOrigem);
        Cidade *destino = buscarCidade(nomeDestino);

        if (!transporte || !origem || !destino)
            continue;

        vector<Passageiro *> passageiros;

        stringstream sp(listaPassageiros);
        string nomePassageiro;

        while (getline(sp, nomePassageiro, ',')) {
            Passageiro *p = buscarPassageiro(nomePassageiro);

            if (p)
                passageiros.push_back(p);
        }

        vector<Trajeto *> rota = calculcarMelhorRota(
            nomeOrigem,
            nomeDestino,
            transporte->getTipo()
        );

        if (rota.empty())
            continue;

        Viagem *viagem = new Viagem(transporte, passageiros, rota);

        viagem->setHorasEmTransito(stoi(horas));
        viagem->setTrajetoAtual(stoi(trajetoAtual));
        viagem->setEmAndamento(stoi(andamento));

        viagens.push_back(viagem);
    }
}

void ControladorDeTransito::salvarCidades() {
    fstream arquivo("../Data/Cidade.txt");

    if (!arquivo.is_open()) return;

    for (Cidade *cidade: cidades) {
        arquivo << cidade->getNome() << ";" << cidade->getVisitas() << endl;
    }
}

void ControladorDeTransito::salvarTransportes() {
    fstream arquivo("../Data/Transporte.txt");
    if (!arquivo.is_open()) return;
    for (Transporte *transporte: transportes) {
        arquivo << transporte->getNome() << ";" << transporte->getTipo() << ";" << transporte->getCapacidade() << ";" <<
                transporte->getVelocidade() << ";" << transporte->getDistanciaEntreDescansos() << ";" << transporte->
                getTempoDescanso() << ";";

        if (transporte->getLocalAtual()) {
            arquivo << transporte->getLocalAtual()->getNome();
        }
        arquivo << endl;
    }
}

void ControladorDeTransito::salvarPassageiros() {
    fstream arquivo("../Data/Passageiro.txt");
    if (!arquivo.is_open()) return;
    for (Passageiro *passageiro: passageiros) {
        arquivo << passageiro->getNome() << ";";

        if (passageiro->getLocalAtual())
            arquivo << passageiro->getLocalAtual()->getNome();

        arquivo << endl;
    }
}

void ControladorDeTransito::salvarViagens() {
    fstream arquivo("../Data/Viagem.txt");
    if (!arquivo.is_open()) return;
    for (Viagem *viagem: viagens) {
        arquivo << viagem->getTransporte()->getNome() << ";" << viagem->getOrigem()->getNome() << ";" << viagem->
                getDestino()->getNome() << ";" << viagem->getHorasEmTransito() << ";" << viagem->isEmAndamento() << ";"
                << viagem->getTrajetoAtual() << ";";

        vector<Passageiro *> passageiros = viagem->getPassageiros();

        for (int i = 0; i < passageiros.size(); i++) {
            arquivo << passageiros[i]->getNome();

            if (i + 1 < passageiros.size())
                arquivo << ",";
        }

        arquivo << endl;
    }
}

void ControladorDeTransito::salvarTrajetos() {
    ofstream arquivo("../Data/Trajeto.txt");

    if (!arquivo.is_open())
        return;

    for (Trajeto *trajeto: trajetos) {
        arquivo << trajeto->getOrigem()->getNome() << ";" << trajeto->getDestino()->getNome() << ";" << trajeto->
                getTipo() << ";" << trajeto->getDistancia() << endl;
    }

    arquivo.close();
}

void ControladorDeTransito::localizarPassageiro(std::string nome) {
    Passageiro *passageiro = buscarPassageiro(nome);
    if (passageiro) {
        Cidade *local = passageiro->getLocalAtual();
        if (local) {
            cout << "o Passageiro " << nome << " está em " << local->getNome() << endl;
        } else {
            cout << "o Passageiro " << nome << " está em " << "trânsito" << endl;
        }
    }
}

void ControladorDeTransito::localizarTransporte(std::string nome) {
    Transporte *transporte = buscarTransporte(nome);
    if (transporte) {
        Cidade *local = transporte->getLocalAtual();
        if (local) {
            cout << "o Transporte " << nome << " está em " << local->getNome() << endl;
        } else {
            cout << "o Transporte " << nome << " está em trânsito" << endl;
        }
    }
}

void ControladorDeTransito::viagensEmAndamento() {
    for (Viagem *viagem: viagens) {
        if (viagem->isEmAndamento()) {
            viagem->relatarEstado();
        }
    }
}

void ControladorDeTransito::maisVisitadas() {
    vector<Cidade *> ordem = cidades;

    sort(ordem.begin(), ordem.end(), [](Cidade *a, Cidade *b) {
        return a->getVisitas() > b->getVisitas();
    });

    cout << "Cidades mais visitadas:" << endl;
    for (Cidade *cidade: ordem) {
        cout << cidade->getNome() << ": " << cidade->getVisitas() << endl;
    }
}
