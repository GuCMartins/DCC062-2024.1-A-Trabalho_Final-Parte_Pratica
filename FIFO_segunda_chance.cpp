#include <iostream>
#include <random>
#include <list>
#include <vector>

/* Estrutura responsável por simbolizar a página, cada página contém um item,
   sendo um número e seu bit R, sendo este iniciado com o valor "false". */

struct Pagina {
    int numero;
    bool bitR;
    Pagina(int n) : numero(n), bitR(false) {}
};

// Função para verificar se a página atual está na fila
bool presente_na_fila(int paginaAtual, std::list<Pagina>& fila) {

    for (std::list<Pagina>::iterator it = fila.begin(); it != fila.end(); it++) {
        if (it->numero == paginaAtual) {
            it->bitR = true;  // Modifica o bitR da página encontrada
            return true;
        }
    }
    return false;
}

void imprime_fila(std::list<Pagina>& fila){
    if (fila.size() != 0){
    for (std::list<Pagina>::iterator it = fila.begin(); it != fila.end(); it++)
        std::cout << it->numero << "(" << it->bitR << "), ";
    std::cout << std::endl;
    }

    else
        std::cout << "Memória Vazia" << std::endl;  
}

void segundaChance(std::vector<int>& paginas, int n, int capacidade) {
    std::list<Pagina> fila;
    int pageFault = 0;
    int hit = 0;

    for (int i = 0; i < n; i++) {
        imprime_fila(fila);

        int paginaAtual = paginas[i];
        std::cout << "Inserindo a página de valor: " << paginaAtual << std::endl;
     
        if (presente_na_fila(paginaAtual, fila)) {
            std::cout << "Página encontrada na memória!" << std::endl;
            hit++;
        } 
        
        else {
            pageFault++;
            if (fila.size() == capacidade){
                while (!fila.empty() && fila.front().bitR == true) {
                    Pagina p = fila.front();
                    fila.pop_front();
                    p.bitR = false;
                    fila.push_back(p);
                }
                if (!fila.empty()) {
                    fila.pop_front();
                }
            }
            fila.push_back(Pagina(paginaAtual));  // Cria uma nova página com o número atual
        }
    }

    std::cout << "PageFaults: " << pageFault << std::endl;
    std::cout << "Hits: " << hit << std::endl;
}

void criando_paginas(std::vector<int>& paginas) {
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

    int frames = 3;  // Quantidade de frames na memória

    segundaChance(paginas, n, frames);

    return 0;
}
