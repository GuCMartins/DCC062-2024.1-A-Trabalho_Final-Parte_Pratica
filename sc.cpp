#include <iostream>
#include <sys/ioctl.h>
#include <random>
#include <unistd.h>
#include <list>
#include <vector>


/* Estrutura responsável por simbolizar a página, cada página contém um item,
   sendo um número e seu bit R, sendo este iniciado com o valor "false". */

struct Pagina {
    int numero;
    bool bitR;
    Pagina(int n) : numero(n), bitR(false) {}
};


// Variável global para armazenar a largura do terminal
int largura = 0;

// Função para inicializar a largura do terminal
void calculando_largura_terminal() {
    struct winsize w;
    // Obter a largura do terminal
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    largura = w.ws_col;  // Armazena a largura na variável global
}

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
        std::cout << "\nPaginas na memoria: ";
    for (std::list<Pagina>::iterator it = fila.begin(); it != fila.end(); it++){
        if (it == --fila.end()){   
            std::cout << "|" << it->numero  << "(" << it->bitR << ")|";
        }
        else
            std::cout << "|" << it->numero << "(" << it->bitR << ")| --- ";
    }
    std::cout << std::endl;
    }

    else
        std::cout << "\nMemoria Vazia!" << std::endl;  
}

void segundaChance(std::vector<int>& paginas, int capacidade) {
    std::list<Pagina> fila;
    int pageFault = 0;
    int hit = 0;

    imprime_fila(fila);

    for (int i = 0; i < paginas.size(); i++) {

        int paginaAtual = paginas[i];
        std::cout << "\nInserindo a pagina de valor: " << paginaAtual << std::endl;
     
        if (presente_na_fila(paginaAtual, fila)) {
            std::cout << "\nPagina encontrada na memoria!" << std::endl;
            hit++;
        } 
        
        else {
            pageFault++;
            std::cout << "\nPagina nao esta presente na memoria!" << std::endl;
            if (fila.size() == capacidade){
                std::cout << "Memoria cheia!!!" << std::endl;
                while (fila.front().bitR == true) {
                    Pagina p = fila.front();
                    fila.pop_front();
                    p.bitR = false;
                    fila.push_back(p);
                    std::cout << "Pagina de valor " << p.numero << " possui bit R = 1, logo vai para fim da fila!" << std::endl;
                    imprime_fila(fila);  
                }
                if (!fila.empty()) {
                    Pagina p = fila.front();
                    std::cout << "\nRetirando pagina de valor: " << p.numero << std::endl; 
                    fila.pop_front();
                }
            }
            fila.push_back(Pagina(paginaAtual));  // Cria uma nova página com o número atual
        }
        imprime_fila(fila);
        std::cout << std::string(largura, '-') << std::endl;

    }
    std::cout << "\nPageFaults: " << pageFault << std::endl;
    std::cout << "Hits: " << hit << std::endl;
}

void criando_paginas(std::vector<int>& paginas, int n) {
    std::random_device rd;
    std::mt19937 gerador(rd());
    std::uniform_int_distribution<int> dist(0, 2 * n);
    
    std::cout << "Paginas a serem inseridas na memoria: ";

    for (int i = 0; i < paginas.size(); i++) {
        paginas[i] = dist(gerador);
        
        if (i == paginas.size() - 1)
            std::cout << "|" << paginas[i] << "|" << std::endl;
        else
            std::cout << "|" << paginas[i] << "| --- ";
    }

    std::cout << std::string(largura, '-') << std::endl;

}

int main() {
    int n = 20;

    std::vector<int> paginas(n);

    calculando_largura_terminal();
    
    criando_paginas(paginas, n);

    int frames = n / 1.5;  // Quantidade de frames na memória

    segundaChance(paginas, frames);

    return 0;
}
