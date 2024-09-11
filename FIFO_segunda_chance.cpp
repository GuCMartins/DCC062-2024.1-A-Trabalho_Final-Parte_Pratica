#include <iostream>
#include <random>
#include <list>
#include <vector>

//struct responsável por criar a página, cada página contém um item, sendo um número e seu bit R, sendo este iniciado com o valor "false".
struct Pagina {
    int numero;
    bool bitR;
    Pagina(int n){
        numero = n;
        bitR = false;
    }
};

void segundaChance(std::vector<int>& paginas, int n, int capacidade) {
    std::list<Pagina> fila;
    int pageFault = 0;
    int hit = 0;

    for (int i = 0; i < n; ++i) {
        int paginaAtual = paginas[i];

        if (fila.size() == capacidade) { //memória cheia
            //verificar se o item está na memória, dar o hit e modificar seu bit R para 1

            //percorrer a lista e verificar qual página será substituida e realizar a substituição

            //inserir paginaAtual na fila
        }

        else{
            //verificar se o item está na memória, dar o hit e modificar seu bit R para 1

            //dar page fault e inserir no final da fila
        }

    }       
}


void criando_paginas(std::vector<int>& paginas)
{
    std::random_device rd;
    std::mt19937 gerador(rd());
    std::uniform_int_distribution<int> dist(0, 9);

    for (int i = 0; i < paginas.size(); i++) {
        paginas[i] = dist(gerador);
    }

}


int main() {
    int n = 20;
    std::vector<int> paginas(n);

    criando_paginas(paginas);

    int frames = 3;  //Quantidade de frames na memória

    segundaChance(paginas, n, frames);

    return 0;
}
