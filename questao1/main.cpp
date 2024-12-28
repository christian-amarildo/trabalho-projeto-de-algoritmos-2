#include <iostream>
#include <cstdlib>
#include "arvore.h"

using namespace std;

int main(void){
    int op;
    int valor;
    bool ret = false;
    t_arvore raiz = nullptr;

    while(true){
        cout << "1 - Inserir valor\n";
        cout << "2 - Remover valor\n";
        cout << "3 - Consultar valor\n";
        cout << "4 - Mostrar a arvore\n";
        cout << "5 - Sair\n";
        cout << "Opcao? ";
        cin >> op;
        switch(op){
            case 1: // Inserir valor
                cout << "Qual o valor para ser inserido na arvore? ";
                cin >> valor;
                if (inserir(&raiz, valor)){
                    cout << "Valor inserido com sucesso: " << valor << endl << endl;
                }
                else
                    cout << "Valor nao inserido com sucesso.\n\n";
                break;
            case 2: // Remover valor
                cout << "Qual o valor para ser removido da arvore? ";
                cin >> valor;
                if (remover(&raiz, valor)){
                    cout << "Valor removido com sucesso: " << valor << endl << endl;
                }
                else
                    cout << "Valor nao encontrado na arvore.\n\n";
                break;
            case 3: // Consultar valor
                cout << "Qual o valor para consultar na arvore? ";
                cin >> valor;
                ret = pesquisar(raiz, valor);
                if (ret)
                    cout << "Valor " << valor << " encontrado na arvore.\n\n";
                else
                    cout << "Valor " << valor << " nao encontrado na arvore.\n\n";
                break;
            case 4: // Mostrar a arvore
                mostrararvore(raiz);
                break;
            case 5: // Abandonar o programa
                // Opcional: Implementar uma função para liberar a memória da árvore
                exit(0);
            default:
                cout << "Opcao invalida!\n\n";
        }
    }
}
