#include <stdio.h>
#include <stdlib.h>

// Estrutura para o nó da árvore
struct Tree {
    int info;
    Tree *esq, *dir;
};
typedef struct Tree tree;

// Estrutura para a pilha
typedef struct Pilha {
    tree *arvoreNode; // Ponteiro para o nó da árvore
    struct Pilha *prox;
} Pilha;

// Função para criar um novo nó na pilha
Pilha* novoNo(tree *arvoreNode) {
    Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
    novo->arvoreNode = arvoreNode;
    novo->prox = NULL;
    return novo;
}

// Função para empilhar um nó da árvore
void Push(Pilha **topo, tree *arvoreNode) {
    Pilha *novo = novoNo(arvoreNode);
    novo->prox = *topo;
    *topo = novo;
}

// Função para desempilhar um nó da árvore
tree* Pop(Pilha **topo) {
    if (*topo == NULL) {
        printf("Pilha vazia!\n");
        return NULL;
    }
    Pilha *temp = *topo;
    tree *arvoreNode = temp->arvoreNode;
    *topo = (*topo)->prox;
    free(temp);
    return arvoreNode;
}

// Função para verificar se a pilha está vazia
int isEmpty(Pilha *topo) {
    return topo == NULL;
}

// Função para criar um novo nó na árvore
tree *CriaNo(int info) {
    tree *no = (tree*)malloc(sizeof(tree));
    no->info = info;
    no->esq = no->dir = NULL;
    return no;
}

tree* insereABB(tree **raiz, int valor) {
    // Se a raiz é nula, criamos um novo nó
    if (*raiz == NULL) {
        *raiz = CriaNo(valor);
        return *raiz;  // Retorna o novo nó inserido
    }

    // Se o valor for menor, vamos para a subárvore esquerda
    if (valor < (*raiz)->info) {
        return insereABB(&((*raiz)->esq), valor);
    }
    // Se o valor for maior, vamos para a subárvore direita
    else if (valor > (*raiz)->info) {
        return insereABB(&((*raiz)->dir), valor);
    }

    // Se o valor já existe, não fazemos nada (nada é inserido)
    return NULL;
}


// Percurso em ordem (in-ordem)
void in_ordem(tree *raiz) {
    if (raiz != NULL) {
        in_ordem(raiz->esq);
        printf("%d ", raiz->info);
        in_ordem(raiz->dir);
    }
}

// Percurso pré-ordem
void pre_ordem(tree *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->info);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }
}

// Percurso pós-ordem
void pos_ordem(tree *raiz) {
    if (raiz != NULL) {
        pos_ordem(raiz->esq);
        pos_ordem(raiz->dir);
        printf("%d ", raiz->info);
    }
}

// Função de percurso não recursiva em pré-ordem
void INPre_ordem(tree *raiz) {
    Pilha *p = NULL;
    Push(&p, raiz);
    while (!isEmpty(p)) {
        if (raiz != NULL) {
            raiz = Pop(&p);
            while (raiz != NULL) {
                printf("%d ", raiz->info);
                Push(&p, raiz);
                raiz = raiz->esq;
            }
            raiz = Pop(&p);
            raiz = raiz->dir;
            if (raiz != NULL) {
                Push(&p, raiz);
            }
        }
    }
}

// Percurso pós-ordem não recursivo
void InPos_ordem(tree *raiz) {
    Pilha *p1 = NULL, *p2 = NULL;
    Push(&p1, raiz);
    while (!isEmpty(p1)) {
        if (raiz != NULL) {
            raiz = Pop(&p1);
            while (raiz != NULL) {
                Push(&p2, raiz);
                Push(&p1, raiz);
                raiz = raiz->dir;
            }
            raiz = Pop(&p1);
            raiz = raiz->esq;
            if (raiz != NULL) {
                Push(&p1, raiz);
            }
        }
    }
    while (!isEmpty(p2)) {
        raiz = Pop(&p2);
        printf("%d ", raiz->info);  // Aqui seria um free para deletar
    }
}

//Quantidades de itens na arvore
void contNo(tree *raiz, int *contador) {
    if (raiz != NULL) {
        (*contador)++; // Incrementa o contador para cada nó visitado
        contNo(raiz->esq, contador); // Percorre a subárvore esquerda
        contNo(raiz->dir, contador); // Percorre a subárvore direita
    }
}

void busca(tree *raiz, int valor, tree **noEncontrado, tree **pai) {
    *noEncontrado = NULL;
    *pai = NULL;

    tree *atual = raiz;
    tree *anterior = NULL;

    // Percorre a árvore até encontrar o valor ou chegar ao final
    while (atual != NULL) {
        if (valor == atual->info) {
            *noEncontrado = atual; // Valor encontrado
            *pai = anterior; // Guarda o pai do nó encontrado
            return;
        }
        anterior = atual; // Atualiza o pai
        if (valor < atual->info) {
            atual = atual->esq; // Vai para a subárvore esquerda
        } else {
            atual = atual->dir; // Vai para a subárvore direita
        }
    }
}


/* exclusao não completa
void Exclusao(tree **raiz , tree *e,tree *pai)
{
	if(e->esq == NULL  && e->dir == NULL)
	{
		if(e!=pai)
		{
			if(e->info>pai->info)
				pai->dir=NULL;
			else
				pai->esq=NULL
		}
		else
			*raiz=NULL;
		free(e);
	}
	else
	{
		if(e->esq==NULL || e->dir == NULL)
		{
			
		}
		else
		{
			 
		}
	}
}

*/
void Exclusao(tree **raiz, tree *e, tree *pai)
{
    // Caso 1: Nó folha (sem filhos)
    if(e->esq == NULL && e->dir == NULL)
    {
        if(e != pai)
        {
            if(e->info > pai->info)
                pai->dir = NULL;
            else
                pai->esq = NULL;
        }
        else
            *raiz = NULL;  // Caso onde estamos removendo a raiz
        free(e);
    }
    // Caso 2: Nó com um filho
    else if(e->esq == NULL || e->dir == NULL)
    {
        tree *filho;
        
        // Determinando o filho (se existir)
        if(e->esq != NULL)
            filho = e->esq;
        else
            filho = e->dir;
        
        if(e != pai)
        {
            if(e->info > pai->info)
                pai->dir = filho;
            else
                pai->esq = filho;
        }
        else
            *raiz = filho;  // Se estamos removendo a raiz, o filho vira a nova raiz
        
        free(e);
    }
    // Caso 3: Nó com dois filhos
    else
    {
        // Encontrar o menor valor da subárvore direita (ou pode usar o máximo da subárvore esquerda)
        tree *menor = e->dir;
        tree *paiMenor = e;
        
        while(menor->esq != NULL)
        {
            paiMenor = menor;
            menor = menor->esq;
        }
        
        // Substituir o valor de 'e' pelo valor de 'menor'
        e->info = menor->info;
        
        // Remover o nó 'menor' (que será um caso de nó folha ou nó com um único filho)
        Exclusao(raiz, menor, paiMenor);
    }
}

// Função de balanceamento (correções simples)
void Balanceamento(tree **raiz, tree **e, tree *pai, char lado) {
    tree *no;
    int quantD, quantE, fb;
    quantD = quantE = 0;
    
    contNo((*raiz)->dir, &quantD);
    contNo((*raiz)->esq, &quantE);
    fb = quantD - quantE;

    Pilha *f = NULL;
    Push(&f, *raiz);

    while (!isEmpty(f)) {
        no = Pop(&f);
        do {
            if (fb < -1 || fb > 1) {  // Ou abs(fb) > 1
                int aux = no->info;
                if (no->esq == NULL) {
                    no = no->dir;
                }
                if (no->dir == NULL) {
                    no = no->esq;
                }
                // Função de busca não implementada
                busca(*raiz, aux, e, &pai);
                if (fb > 0)
                    Exclusao(raiz, *e, pai);
                else
                    Exclusao(raiz, *e, pai);
                // Função de inserção não implementada
                insereABB(raiz, aux);
            }
        } while (fb < -1 || fb > 1);

        if (no->esq != NULL) {
            Push(&f, no->esq);
        }
        if (no->dir != NULL) {
            Push(&f, no->dir);
        }
    }
}

int main() {
    // O código de teste pode ser implementado aqui
    return 0;
}

