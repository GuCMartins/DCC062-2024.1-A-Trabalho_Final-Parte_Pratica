//FIFO com Segunda Chance
#include <iostream>
#include <cstdlib>
#include <unistd.h> // Para POSIX

using namespace std;

#ifdef WIN32
    #include <windows.h>
    #define clear_screen() system("cls")
    #define wait Sleep(3000)
#else
    #define clear_screen() system("/usr/bin/clear")
    #define wait sleep(3)
#endif

// Estrutura da lista que será criada
class Page {
    private:
        // Atributos
        int value;
        Page* next;
        int bitR;
    public:
        // Construtor
        Page(int val) {
            value = val;
            next = nullptr;
            bitR = 0;
        }
        // Destrutor
        ~Page() { //alterar para nao dar erro de memoria
            delete next;
        }
        Page* getNext() { return next; }
        void setNext(Page* prox) { next = prox; }
        int getValue() { return value; }
        void setBitR(int bit) { bitR = bit; }
        int getBitR() { return bitR; }
};

class Queue{
    private:
        Page* begin;
        Page* end;
        int max_pages;
        int num_pages;
    public:
        Queue(int max_pages){
            begin = nullptr;
            end = nullptr;
            max_pages = max_pages;
            num_pages = 0;
        }
        ~Queue() {
            while (begin != nullptr) {
                Page* temp = begin;
                begin = begin->getNext();
                delete temp;
            }
        }

        Page* getBegin(){
            return begin;
        }

        void insert(int val){
                if (num_pages >= max_pages) {
                cout << "Limite de páginas atingido. Executando exclusão para liberar espaço.\n";
                remove();
            }
            Page* atual = new Page(val);
            if (begin == nullptr) {
                begin = end = atual;
            } else {
                end->setNext(atual);
                end = atual;
            }
            num_pages++;
        }

        void remove(){
            if (begin == nullptr) return;

            if (begin->getBitR() == 1) {
                begin->setBitR(0);
                end->setNext(begin);
                end = begin;
                begin = begin->getNext();
                end->setNext(nullptr);
            } else {
                Page* temp = begin;
                begin = begin->getNext();
                delete temp;
                num_pages--;
            }
        }

        void show() {
            int position = 0;
            Page* actual = begin;
            while (actual != nullptr) {
                position++;
                cout << "Posição " << position << ", contém a página " << actual->getValue() << "\n";
                actual = actual->getNext();
            }
        }
};

void show_erro() {
    clear_screen();
    cout << "\nErro de Digitação: \n";
    cout << "--------------------------------------\n";
    cout << "\nDigite uma opção válida (pressione -Enter- p/ continuar)!\n\n";
    cout << "--------------------------------------";
    cin.ignore();
    cin.get();
}

int main() {
    // Variáveis
    int max_pages, value;
    cout << "Algoritmo de substituição de Páginas: Segunda Chance\n\n";
    cout <<" Insira o número máximo de páginas: ";
    cin >> max_pages;

    Queue queue(max_pages);

    char escolha;
    do {
        // Limpando a tela e showndo o menu
        clear_screen();
        cout << "\nAlgoritmo de substituição de Páginas: Segunda Chance\n\n";
        cout << "Escolha uma opção: \n";
        cout << "\t1 - Inserir Página\n";
        cout << "\t2 - Mostrar a Fila\n";
        cout << "\t9 - Sair\n\n";
        cout << "Resposta: ";
        cin >> escolha;

        switch (escolha) {
            case '1':
                cout<< "Insira o valor da página: ";
                cin>>value;
                queue.insert(value);
                break;
            case '2':
                if (queue.getBegin() != nullptr) {
                    queue.show();
                } else {
                    cout << "\n A Fila está vazia!\n";
                    cin.ignore();
                    cin.get();
                }
                break;
            case '9':
                cout << "\nObrigado por utilizar esse programa!\n";
                cout << "------>Terminal de Informação<------\n\n";
                wait;
                exit(0);
                break;
            default:
                show_erro();
                break;
        }
        // Limpar buffer de entrada
        cin.ignore();
    } while (escolha != '9');
    return 0;
}
