#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Função para tratar erros do usuário
int lerNumero() {
    int numero;
    
    while (scanf("%d", &numero) != 1) {
        printf("\nOpção Inválida! Digite um número: \n ");
        // Limpa o buffer de entrada
        while (getchar() != '\n');
    }
    return numero;
}

void lerTexto(char *texto, int tamanho) {
    fgets(texto, tamanho, stdin);
    // Remover o caractere de nova linha
    texto[strcspn(texto, "\n")] = '\0';
    
}

typedef struct elementos {
	int rgm;
	char nome[100];
}t_elemento;

typedef struct no {
	struct no *esq;
	t_elemento dado;
	struct no *dir;
}t_no;

typedef t_no *t_arvore;

//exibir (raiz - esquerda - direita)
void exibirPreOrdem(t_arvore tree) {
	if(tree!=NULL){
		printf("%s - %d", tree->dado.nome, tree->dado.rgm);
		exibirPreOrdem(tree->esq);
		exibirPreOrdem(tree->dir);
	}
}

//exibir (esquerda - raiz - direita)
void exibirInOrdem(t_arvore tree) {
	if(tree!=NULL){
		exibirInOrdem(tree->esq);
		printf("%s - %d", tree->dado.nome, tree->dado.rgm);
		exibirInOrdem(tree->dir);
	}
}

//exibir (esquerda - direita - raiz)
void exibirPosOrdem(t_arvore tree) {
	if(tree!=NULL){
		exibirPosOrdem(tree->esq);
		exibirPosOrdem(tree->dir);
		printf("%s - %d", tree->dado.nome, tree->dado.rgm);
	}
}

// Cria um nó vazio
t_no *criar() {
	t_no *no = (t_no*) malloc(sizeof(t_no));
	
	if(no){
		no->esq = no->dir = NULL;
	}
	
	return no;
}

// Verifica se um nó está vazio
int isVazia(t_no *no){
	return (no == NULL);
}

// Compara dois dados
int compara(t_elemento dado1, t_elemento dado2) {
    if (dado1.rgm < dado2.rgm) {
        return -1;
    } else if (dado1.rgm > dado2.rgm) {
        return 1;
    } else {
        return 0;
    }
}

t_no *busca(t_arvore tree, t_elemento dado) {
	t_no *achou;
	
	if(tree==NULL){
		return NULL;
	}
	
	if(compara(tree->dado, dado) == 0){
		return tree;
	}
	
	achou = busca(tree->esq, dado);
	
	if(achou==NULL){
		achou = busca(tree->dir, dado);
	}
	
	return achou;
}

int inserir(t_arvore *tree, t_elemento item) {
    int ok;
	
    if(*tree==NULL){
    	*tree = criar();
    	
    	if(*tree==NULL){
    		return 0;
		}
		
	(*tree)->dado = item;
	
	return 1;	
	}
	
	if (compara((*tree)->dado, item) < 0) {
        ok = inserir(&((*tree)->dir), item);
    } else {
        if (compara((*tree)->dado, item) > 0) {
            ok = inserir(&((*tree)->esq), item);
        } else {
            ok = 0;
        }
    }
	
	return ok;
}

void esvaziar(t_arvore *tree){
	if(*tree==NULL){
		return;
	}
	
	esvaziar(&(*tree)->esq);
	esvaziar(&(*tree)->dir);
	free(*tree);
	*tree = NULL;
}

t_no *buscaSetPai(t_arvore tree, t_elemento dado, t_no **pai){
	if(tree==NULL){
		*pai = NULL;
		
		return NULL;
	}
	
	if(compara(tree->dado, dado) == 0){
		return tree;
	}
	
	if(compara(tree->dado, dado) > 	0){
		*pai = tree;
		
		return buscaSetPai(tree->esq, dado, pai);
	}else{
		*pai = tree;
		
		return buscaSetPai(tree->dir, dado, pai);
	}
}

int remover(t_arvore *tree, t_elemento item) {
	t_no *no, *pai, *sub, *paiSuce, *suce;
	no = *tree;
	pai = NULL;
	no = buscaSetPai(*tree, item, &pai);
	
	if(no==NULL){
		return 0;
	}
	
	if(no->esq==NULL){
		sub = no->dir;
	}else{
		if(no->dir==NULL){
			sub = no->esq;
		}else{	//////////////////
			paiSuce = no;
			sub = no->dir;
			suce = sub->esq;
			
			while(suce!=NULL){
				paiSuce = sub;
				sub = suce;
				suce = sub->esq;
			}
			
			if(paiSuce!=no){
				paiSuce->esq = sub->dir;
				sub->dir = no->dir;
			}
			
			sub->esq = no->esq;
		}
	}
	
	if(pai==NULL){
		*tree = sub;
	}else{
		if(no==pai->esq){
			pai->esq = sub;
		}else{
			pai->dir = sub;
		}
	}
	
	free(no);
	
	return 1;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	
	int op;
	t_elemento aluno;
	t_arvore tree;
	
	do{
	system("cls");
	printf("\nDisciplina: Estrutura de Dados 1\n");
	printf("Professor: Walace Bonfim\n");
	printf("\n\tEDITOR DE ÁRVORE\n\n");
	printf("1 - Inserir\n");
	printf("2 - Remover um nó\n");
	printf("3 - Pesquisar\n");
	printf("4 - Esvaziar a Árvore\n");
	printf("5 - Exibir a Árvore\n");
	printf("0 - Sair\n\n");
	printf("Digite sua opção: ");
	op = lerNumero();
	
	switch(op){
		case 1:{
			printf("\nDigite o nome do aluno: \n");
			lerTexto(aluno.nome, sizeof(aluno.nome));
			while (getchar() != '\n');
			printf("\nDigite o RGM do aluno: \n");
		    aluno.rgm = lerNumero();
		    
			if(inserir(&tree,aluno))
			printf("\nAluno inserido com sucesso!\n ");
			else
			printf("\nErro ao inserir aluno!\n");
			break;
		}
		case 2:{
			printf("Remover...\n");
			break;
		}
		case 3:{
			printf("Pesquisar...\n");
			break;
		}
		case 4:{
			printf("Esvaziar...\n");
			break;
		}
		case 5:{
			printf("Exibir...\n");
			break;
		}
		case 0:{
			printf("Saindo...\n");
			break;
		}
		default:{
			printf("Opção inválida!\n");
			break;
		}
	}
	
	if (op != 0) {
		printf("\nDigite '1' para voltar ao menu, ou '0' para encerrar o programa.\n");
		op = lerNumero();
		}
		
	}while(op != 0);
	
	return 0;
}
