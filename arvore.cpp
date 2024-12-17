#include "arvore.h"
#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;

typedef struct t_no {
  int chave;
  struct t_no *esq;
  struct t_no *dir;
  int altura;  // Altura do nó na árvore AVL
} t_no, *t_arvore;

// Função para criar um nó
t_no *criaNo(void) {
  t_no *novoNo = (t_no *)malloc(sizeof(t_no));
  if (novoNo != NULL) {
    novoNo->esq = novoNo->dir = NULL;
    novoNo->chave = 0;
    novoNo->altura = 1;  // Inicializa com altura 1
  }
  return novoNo;
}

// Função para calcular a altura de um nó
int altura(t_no *n) {
  if (n == NULL) return 0;
  return n->altura;
}

// Função para calcular o fator de balanceamento de um nó
int balanceamento(t_no *n) {
  if (n == NULL) return 0;
  return altura(n->esq) - altura(n->dir);
}

// Função para atualizar a altura de um nó
void atualizarAltura(t_no *n) {
  if (n != NULL) {
    n->altura = 1 + max(altura(n->esq), altura(n->dir));
  }
}

// Função para fazer uma rotação à esquerda
t_no* rotacaoEsquerda(t_no *x) {
  t_no *y = x->dir;
  t_no *T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  atualizarAltura(x);
  atualizarAltura(y);

  return y;
}

// Função para fazer uma rotação à direita
t_no* rotacaoDireita(t_no *y) {
  t_no *x = y->esq;
  t_no *T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  atualizarAltura(y);
  atualizarAltura(x);

  return x;
}

// Função para balancear um nó
t_no* balancear(t_no *n) {
  if (n == NULL) return n;

  int fator = balanceamento(n);

  // Caso de rotação à esquerda
  if (fator > 1 && balanceamento(n->esq) >= 0) {
    return rotacaoDireita(n);
  }

  // Caso de rotação à direita
  if (fator < -1 && balanceamento(n->dir) <= 0) {
    return rotacaoEsquerda(n);
  }

  // Caso de rotação dupla (esquerda-direita)
  if (fator > 1 && balanceamento(n->esq) < 0) {
    n->esq = rotacaoEsquerda(n->esq);
    return rotacaoDireita(n);
  }

  // Caso de rotação dupla (direita-esquerda)
  if (fator < -1 && balanceamento(n->dir) > 0) {
    n->dir = rotacaoDireita(n->dir);
    return rotacaoEsquerda(n);
  }

  return n;
}

// Função para inserir um valor na árvore AVL
t_no* inserir(t_no* n, int chave) {
  if (n == NULL) return criaNo();

  if (chave < n->chave) {
    n->esq = inserir(n->esq, chave);
  } else if (chave > n->chave) {
    n->dir = inserir(n->dir, chave);
  } else {
    return n;  // Não permite duplicatas
  }

  atualizarAltura(n);
  return balancear(n);
}

// Função para pesquisar um valor na árvore AVL
t_no* pesquisar(t_no* n, int chave) {
  if (n == NULL || n->chave == chave) {
    return n;
  }

  if (chave < n->chave) {
    return pesquisar(n->esq, chave);
  } else {
    return pesquisar(n->dir, chave);
  }
}

// Função para exibir a árvore de forma visual
void mostrararvore(t_arvore raiz) {
  if (raiz == NULL) return;
  stack<t_no*> pilhaGlobal;
  pilhaGlobal.push(raiz);
  int nVazios = 32;
  bool linhaVazia = false;
  cout << endl;
  while (!linhaVazia) {
    stack<t_no*> pilhaLocal;
    linhaVazia = true;

    for (int j = 0; j < nVazios; j++) cout << ' ';

    while (!pilhaGlobal.empty()) {
      t_no* temp = pilhaGlobal.top();
      pilhaGlobal.pop();
      if (temp != NULL) {
        cout << temp->chave;
        pilhaLocal.push(temp->esq);
        pilhaLocal.push(temp->dir);

        if (temp->esq != NULL || temp->dir != NULL) linhaVazia = false;
      } else {
        cout << "--";
        pilhaLocal.push(NULL);
        pilhaLocal.push(NULL);
      }

      for (int j = 0; j < nVazios * 2 - 2; j++) cout << ' ';
    }
    cout << endl;
    nVazios /= 2;
    while (!pilhaLocal.empty()) {
      pilhaGlobal.push(pilhaLocal.top());
      pilhaLocal.pop();
    }
  }
  cout << endl;
}

// Função para remover um nó
t_no* remover(t_no* raiz, int chave) {
  if (raiz == NULL) return raiz;

  if (chave < raiz->chave) {
    raiz->esq = remover(raiz->esq, chave);
  } else if (chave > raiz->chave) {
    raiz->dir = remover(raiz->dir, chave);
  } else {
    // Caso 1: Nó a ser removido tem um filho ou nenhum filho
    if (raiz->esq == NULL) {
      t_no* temp = raiz->dir;
      free(raiz);
      return temp;
    } else if (raiz->dir == NULL) {
      t_no* temp = raiz->esq;
      free(raiz);
      return temp;
    }

    // Caso 2: Nó a ser removido tem dois filhos
    t_no* temp = raiz->dir;
    while (temp && temp->esq != NULL) temp = temp->esq;

    raiz->chave = temp->chave;

    raiz->dir = remover(raiz->dir, temp->chave);
  }

  if (raiz == NULL) return raiz;

  atualizarAltura(raiz);
  return balancear(raiz);
}
