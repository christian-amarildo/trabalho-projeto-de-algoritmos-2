#ifndef ARVORE_H
#define ARVORE_H

// Estrutura do nó da árvore AVL
struct s_no {
    s_no *esq;     // Ponteiro para a subárvore esquerda
    s_no *dir;     // Ponteiro para a subárvore direita
    int chave;     // Valor armazenado no nó
    int altura;    // Altura do nó para balanceamento
};

typedef s_no* t_arvore;

// Declaração das funções principais
s_no* criaNo(int valor);
bool inserir(t_arvore* raiz, int valor);
bool remover(t_arvore* raiz, int valor);
bool pesquisar(t_arvore raiz, int valor);
void mostrararvore(t_arvore raiz);

#endif // ARVORE_H
