#include <iostream>
#include <cstdlib>
#include "arvore.h"

using namespace std;

int main(void) {
  int op;
  int valor;
  t_arvore raiz = NULL;

  while (1) {
    cout << "1 - Inserir valor\n";
    cout << "2 - Remover valor\n";
    cout << "3 - Consultar valor\n";
    cout << "4 - Mostrar a arvore\n";
    cout << "5 - Sair\n";
    cout << "Opcao? ";
    cin >> op;

    switch (op) {
      case 1: // Inserir valor
        cout << "Qual o valor para ser inserido na arvore? ";
        cin >> valor;
        raiz = inserir(raiz, valor);
        cout << "Valor inserido com sucesso!" << endl;
        break;

      case 2: // Remover valor
        cout << "Qual o valor para ser removido da arvore? ";
        cin >> valor;
        raiz = remover(raiz, valor);
        cout << "Valor removido com sucesso!" << endl;
        break;

      case 3: // Consultar valor
        cout << "Qual o valor para pesquisar na arvore? ";
        cin >> valor;
        if (pesquisar(raiz, valor)) {
          cout << "Valor encontrado!" << endl;
        } else {
          cout << "Valor nao encontrado!" << endl;
        }
        break;

      case 4: // Mostrar a árvore
        mostrararvore(raiz);
        break;

      case 5: // Sair
        exit(0);
        break;
    }
  }
}
