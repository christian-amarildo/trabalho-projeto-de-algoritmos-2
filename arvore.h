typedef struct s_no t_no;

struct s_no{
	t_no *esq;
	int chave;
	t_no *dir;
};

typedef t_no* t_arvore;

///struct Arvore_str* CriaArvore ( ); 
t_no *criaNo ();
bool inserir (t_arvore *, int );
void mostrararvore(t_arvore *);
//void inserir(int , struct Arvore_str *);
/*int Vazia (TipoLista *);
void Insere (TipoItem , TipoLista *, Apontador); 
TipoItem RetiraIni (Celula*, TipoLista *); 
void Imprime (TipoLista* );
int Tamanho_lista(TipoLista* );
int Busca(int , TipoLista* );*/
