#include "arvore.h"
#include <iostream>
#include <stack>
#include <algorithm> // Para std::max

using namespace std;

// Cria um novo nó com o valor especificado
s_no* criaNo(int valor) {
    s_no* novoNo = new s_no;
    if (novoNo != nullptr) {
        novoNo->chave = valor;
        novoNo->esq = novoNo->dir = nullptr;
        novoNo->altura = 1; // Altura inicial
    }
    return novoNo;
}

// Retorna a altura de um nó
int altura(s_no* no) {
    if (no == nullptr)
        return 0;
    return no->altura;
}

// Atualiza a altura de um nó
void atualizaAltura(s_no* no) {
    if (no != nullptr)
        no->altura = 1 + max(altura(no->esq), altura(no->dir));
}

// Calcula o fator de balanceamento de um nó
int getBalance(s_no* no) {
    if (no == nullptr)
        return 0;
    return altura(no->esq) - altura(no->dir);
}

// Rotação à direita
s_no* rotacaoDireita(s_no* y) {
    s_no* x = y->esq;
    s_no* T2 = x->dir;

    // Realiza a rotação
    x->dir = y;
    y->esq = T2;

    // Atualiza alturas
    atualizaAltura(y);
    atualizaAltura(x);

    // Retorna a nova raiz
    return x;
}

// Rotação à esquerda
s_no* rotacaoEsquerda(s_no* x) {
    s_no* y = x->dir;
    s_no* T2 = y->esq;

    // Realiza a rotação
    y->esq = x;
    x->dir = T2;

    // Atualiza alturas
    atualizaAltura(x);
    atualizaAltura(y);

    // Retorna a nova raiz
    return y;
}

// Função para balancear um nó
s_no* balancear(s_no* no) {
    atualizaAltura(no);
    int balance = getBalance(no);

    // Caso 1: Desbalanceado à esquerda
    if (balance > 1) {
        // Caso 1.1: LL
        if (getBalance(no->esq) >= 0)
            return rotacaoDireita(no);
        // Caso 1.2: LR
        else {
            no->esq = rotacaoEsquerda(no->esq);
            return rotacaoDireita(no);
        }
    }

    // Caso 2: Desbalanceado à direita
    if (balance < -1) {
        // Caso 2.1: RR
        if (getBalance(no->dir) <= 0)
            return rotacaoEsquerda(no);
        // Caso 2.2: RL
        else {
            no->dir = rotacaoDireita(no->dir);
            return rotacaoEsquerda(no);
        }
    }

    // Sem desbalanceamento
    return no;
}

// Função auxiliar para inserção com balanceamento
s_no* inserirAVL(s_no* node, int valor, bool &result) {
    // Inserção padrão em BST
    if (node == nullptr) {
        node = criaNo(valor);
        if (node != nullptr)
            result = true;
        return node;
    }

    if (valor < node->chave)
        node->esq = inserirAVL(node->esq, valor, result);
    else if (valor > node->chave)
        node->dir = inserirAVL(node->dir, valor, result);
    else { // Valor já existe
        cout << "Valor já existe na árvore.\n";
        result = false;
        return node;
    }

    // Atualiza a altura do ancestral
    atualizaAltura(node);

    // Balanceia o nó
    node = balancear(node);

    return node;
}

// Função para inserir um valor na árvore AVL
bool inserir(t_arvore* raiz, int valor) {
    bool result = false;
    *raiz = inserirAVL(*raiz, valor, result);
    return result;
}

// Encontra o nó com o menor valor na subárvore
s_no* minValueNode(s_no* node) {
    s_no* current = node;
    while (current->esq != nullptr)
        current = current->esq;
    return current;
}

// Função auxiliar para remoção com balanceamento
s_no* removerAVL(s_no* root, int valor, bool &result) {
    // Remoção padrão em BST
    if (root == nullptr) {
        result = false;
        return root;
    }

    if (valor < root->chave)
        root->esq = removerAVL(root->esq, valor, result);
    else if (valor > root->chave)
        root->dir = removerAVL(root->dir, valor, result);
    else {
        // Nó encontrado
        result = true;
        if ((root->esq == nullptr) || (root->dir == nullptr)) {
            s_no* temp = root->esq ? root->esq : root->dir;

            // Caso 1: Sem filhos
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else // Caso 2: Com um filho
                *root = *temp; // Copia o conteúdo do filho

            delete temp;
        }
        else {
            // Caso 3: Nó com dois filhos
            s_no* temp = minValueNode(root->dir);
            root->chave = temp->chave;
            root->dir = removerAVL(root->dir, temp->chave, result);
        }
    }

    // Se a árvore tinha apenas um nó
    if (root == nullptr)
        return root;

    // Atualiza a altura
    atualizaAltura(root);

    // Balanceia o nó
    root = balancear(root);

    return root;
}

// Função para remover um valor da árvore AVL
bool remover(t_arvore* raiz, int valor) {
    bool result = false;
    *raiz = removerAVL(*raiz, valor, result);
    return result;
}

// Função para pesquisar um valor na árvore AVL
bool pesquisar(t_arvore raiz, int valor) {
    if (raiz == nullptr)
        return false;
    if (valor == raiz->chave)
        return true;
    else if (valor < raiz->chave)
        return pesquisar(raiz->esq, valor);
    else
        return pesquisar(raiz->dir, valor);
}

// Função para mostrar a árvore de forma balanceada
void mostrararvore(t_arvore raiz){
    if (raiz == nullptr) {
        cout << "--\n";
        return;
    }

    stack<s_no*> pilhaGlobal;
    pilhaGlobal.push(raiz);
    int nVazios = 32;
    bool linhaVazia = false;
    cout << endl;
    while(!linhaVazia){
        stack<s_no*> pilhaLocal;
        linhaVazia = true;

        for(int j=0; j<nVazios; j++)
            cout << ' ';

        int count = pilhaGlobal.size();

        while(!pilhaGlobal.empty()){
            s_no* temp = pilhaGlobal.top();
            pilhaGlobal.pop();
            if(temp != nullptr){
                cout << temp->chave;
                pilhaLocal.push(temp->esq);
                pilhaLocal.push(temp->dir);

                if(temp->esq != nullptr || temp->dir != nullptr)
                    linhaVazia = false;
            } else{
                cout << "--";
                pilhaLocal.push(nullptr);
                pilhaLocal.push(nullptr);
            }
            for(int j=0; j<nVazios*2-2; j++)
                cout << ' ';
        }
        cout << endl;
        nVazios = nVazios/2;
        while(!pilhaLocal.empty()){
            pilhaGlobal.push( pilhaLocal.top() );
            pilhaLocal.pop();
        }
    }  
    cout << endl;
}  
