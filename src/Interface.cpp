//
// Created by leon on 01/07/2026.
//
#include <iostream>
#include "../include/Interface.h"
#include "../include/ControladorDeTransito.h"

using namespace std;

ControladorDeTransito controlador;

void Interface::iniciar() {
    char entrada;
    controlador.carregarDados();
    do {
        cout << "=== Gestão de Viagens ===\n" << endl;
        cout << "1) Cadastros" << endl;
        cout << "2) Consultas e Relatórios" << endl;
        cout << "3) Gerenciar Viagens " << endl;
        cout << "\n0) Encerrar Programa" << endl;
        cin >> entrada;
        switch (entrada) {
            case '1':
                cadastros();
                break;
            case '2':
                consultas();
                break;
            case '3':
                gerenciarViagens();
                break;
            default:
                break;
        }
    } while (entrada != '0');
}

void Interface::cadastros() {
    char entrada;
    do {
        cout << "=== Página de cadastros ===\n" << endl;
        cout << "1) Cadastrar Cidade" << endl;
        cout << "2) Cadastrar Trajeto" << endl;
        cout << "3) Cadastrar Transporte" << endl;
        cout << "4) Cadastrar Passageiro" << endl;
        cout << "\n0) Voltar para menu inicial" << endl;
        cin >> entrada;

        switch (entrada) {
            case '1':
                cadastroCidade();
                break;
            case '2':
                cadastroTrajeto();
                break;
            case '3':
                cadastroTransporte();
                break;
            case '4':
                cadastroPassageiro();
                break;
            default:
                break;
        }
    } while (entrada != '0');
}

void Interface::consultas() {
    char entrada;
    do {
        cout << "=== Página de Consultas e Relatórios ===\n" << endl;
        cout << "1) Localizar passageiro" << endl;
        cout << "2) Localizar transporte" << endl;
        cout << "3) Listar todas as viagens" << endl;
        cout << "4) Listar viagens em andamento" << endl;
        cout << "5) Listar cidades mais visitadas" << endl;
        cout << "\n0) Voltar para menu inicial" << endl;
        cin >> entrada;

        switch (entrada) {
            case '1':
                localizarPassageiro();
                break;
            case '2':
                localizarTransporte();
                break;
            case '3':
                relatarEstado();
                break;
            case '4':
                viagensEmAndamento();
                break;
            case '5':
                maisVisitadas();
                break;
            default:
                break;
        }
    } while (entrada != '0');
}

void Interface::gerenciarViagens() {
    char entrada;
    do {
        cout << "=== Página Gerenciamento de Viagens ===\n" << endl;
        cout << "1) Iniciar Viagem" << endl;
        cout << "2) Avançar Horas" << endl;
        cout << "\n0) Voltar para menu inicial" << endl;
        cin >> entrada;

        switch (entrada) {
            case '1':
                iniciarViagem();
                break;
            case '2':
                avançarHoras();
                break;
            default:
                break;
        }
    } while (entrada != '0');

}



void Interface::cadastroCidade() {
    char entrada;
    cout << "== Cadastro de Cidade ==\n" << endl;
    do {
        string nome;
        cout << "Digite o nome da cidade: " << endl;
        getline(cin >> ws, nome);
        controlador.cadastrarCidade(nome);

        cout << "Deseja continuar o cadastro ? (1 - Sim | 0 - Não): " << endl;
        cin >> entrada;
    } while (entrada != '0');
}


void Interface::cadastroTrajeto() {
    char entrada;
    cout << "== Cadastro de Trajeto ==\n" << endl;
    do {
        string origem;
        string destino;
        char tipo;
        int distancia;

        cout << "Digite a cidade de origem: " << endl;
        getline(cin >> ws, origem);
        cout << "Digite a cidade destino: " << endl;
        getline(cin >> ws, destino);
        cout << "Informe o tipo de trajeto (T - Terrestre | A - Aquático)" << endl;
        cin >> tipo;
        cout << "Informe a distância em Km: " << endl;
        cin >> distancia;

        controlador.cadastrarTrajeto(origem, destino, tipo, distancia);

        cout << "Deseja continuar o cadastro ? (1 - Sim | 0 - Não): " << endl;
        cin >> entrada;
    } while (entrada != '0');
}

void Interface::cadastroTransporte() {
    char entrada;
    cout << "== Cadastro de Transporte ==\n" << endl;
    do {
        string nome;
        char tipo;
        int capacidade;
        int velocidade;
        int distancia_entre_descansos;
        int tempo_de_descanso;
        string local_atual;

        cout << "Digite o nome do transporte: " << endl;
        getline(cin >> ws, nome);

        cout << "Informe o tipo de transporte (T - Terrestre | A - Aquático): " << endl;
        cin >> tipo;

        cout << "Informe a capacidade de passageiros: " << endl;
        cin >> capacidade;

        cout << "Informe a velocidade (Km/h): " << endl;
        cin >> velocidade;

        cout << "Informe a distância máxima entre descansos (Km): " << endl;
        cin >> distancia_entre_descansos;

        cout << "Informe o tempo de descanso (horas): " << endl;
        cin >> tempo_de_descanso;

        cout << "Digite o local/cidade atual do transporte: " << endl;
        getline(cin >> ws, local_atual);

        controlador.cadastrarTransporte(nome, tipo, capacidade, velocidade,
                                        distancia_entre_descansos, tempo_de_descanso, local_atual);

        cout << "\nDeseja continuar o cadastro ? (1 - Sim | 0 - Não): " << endl;
        cin >> entrada;
    } while (entrada != '0');
}

void Interface::cadastroPassageiro() {
    char entrada;
    cout << "== Cadastro de Passageiro ==\n" << endl;
    do {
        string nome;
        string local_atual;

        cout << "Digite o nome do passageiro: " << endl;
        getline(cin >> ws, nome);

        cout << "Digite o local/cidade atual do passageiro: " << endl;
        getline(cin >> ws, local_atual);

        controlador.cadastrarPassageiro(nome, local_atual);

        cout << "\nDeseja continuar o cadastro ? (1 - Sim | 0 - Não): " << endl;
        cin >> entrada;
    } while (entrada != '0');
}


void Interface::avançarHoras() {
    int horas;
    cout << "Digite a quantidade de horas que deseja avançar: " << endl;
    cin >> horas;
    controlador.avancarHoras(horas);
    cout << horas << " horas foram avançadas" << endl;
}

void Interface::relatarEstado() {
    controlador.relatarEstado();
}

void Interface::iniciarViagem() {
    char entrada;
    cout << "== Iniciar Viagem ==\n" << endl;
    do {
        string origem;
        string destino;
        string transporte;
        vector<string> passageiros;


        cout << "Digite o nome da cidade de origem: " << endl;
        getline(cin >> ws, origem);
        cout << "Digite o nome da cidade de destino: " << endl;
        getline(cin >> ws, destino);
        cout << "Digite o nome do transporte: " << endl;
        getline(cin >> ws, transporte);
        do {
            string nome;
            cout << "Digite o nome do passageiro: " << endl;
            getline(cin >> ws, nome);
            passageiros.push_back(nome);
            cout << "Deseja adicionar outro passageiro? (1 - Sim | 0 - Não): " << endl;
            cin >> entrada;
        } while (entrada != '0');
        controlador.iniciarViagem(transporte, passageiros, origem, destino);


        cout << "Deseja continuar o cadastro? (1 - Sim | 0 - Não): " << endl;
        cin >> entrada;
    } while (entrada != '0');
}

void Interface::viagensEmAndamento() {
    controlador.viagensEmAndamento();
}

void Interface::localizarPassageiro() {
    string nome;
    cout << "Digite o nome do passageiro: " << endl;
    getline(cin >> ws, nome);
    controlador.localizarPassageiro(nome);
}

void Interface::localizarTransporte() {
    string nome;
    cout << "Digite o nome do transporte: " << endl;
    getline(cin >> ws, nome);
    controlador.localizarTransporte(nome);
}

void Interface::maisVisitadas() {
    controlador.maisVisitadas();
}
