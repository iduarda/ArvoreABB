#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Função para tratar erros do usuário ao ler um número
int lerNumero() {
    int numero;
    
    while (scanf("%d", &numero) != 1) {
        printf("\nOp��o Inv�lida! Digite um n�mero: \n ");
        // Limpa o buffer de entrada
        while (getchar() != '\n');
    }
    return numero;
}

// Função para ler um texto da entrada padrão (stdin)
void lerTexto(char *texto, int tamanho) {
    fgets(texto, tamanho, stdin);
    // Remover o caractere de nova linha
    texto[strcspn(texto, "\n")] = '\0';
    
}

// Definição da estrutura de dados para um elemento da árvore
typedef struct elementos {
	int rgm;
	char nome[100];
}t_elemento;

// Definição da estrutura de um nó da árvore binária
typedef struct no {
	struct no *esq;
	t_elemento dado;
	struct no *dir;
}t_no;

// Definição do tipo abstrato de dados Árvore Binária
typedef t_no *t_arvore;

//exibir Pré-ordem (raiz - esquerda - direita)
void exibirPreOrdem(t_arvore tree) {
	if(tree!=NULL){
		printf("%s - %d\n", tree->dado.nome, tree->dado.rgm);
		exibirPreOrdem(tree->esq);
		exibirPreOrdem(tree->dir);
	}
}

//exibir In-ordem(esquerda - raiz - direita)
void exibirInOrdem(t_arvore tree) {
	if(tree!=NULL){
		exibirInOrdem(tree->esq);
		printf("%s - %d\n", tree->dado.nome, tree->dado.rgm);
		exibirInOrdem(tree->dir);
	}
}

//exibir Pós-ordem(esquerda - direita - raiz)
void exibirPosOrdem(t_arvore tree) {
	if(tree!=NULL){
		exibirPosOrdem(tree->esq);
		exibirPosOrdem(tree->dir);
		printf("%s - %d\n", tree->dado.nome, tree->dado.rgm);
	}
}

// Função para criar um nó vazio
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

// Função para comparar dois dados
int compara(t_elemento dado1, t_elemento dado2) {
    if (dado1.rgm < dado2.rgm) {
        return -1;
    } else if (dado1.rgm > dado2.rgm) {
        return 1;
    } else {
        return 0;
    }
}

// Função para buscar um elemento na árvore
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

// Função para inserir um elemento na árvore
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

// Função para esvaziar a árvore
void esvaziar(t_arvore *tree){
	if(*tree==NULL){
		return;
	}
	
	esvaziar(&(*tree)->esq);
	esvaziar(&(*tree)->dir);
	free(*tree);
	*tree = NULL;
}

// Função para buscar um elemento na árvore e seu pai
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

// Função para remover um elemento da árvore
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
	t_arvore tree = NULL;
	
	do{
	system("cls");
	printf("\nDisciplina: Estrutura de Dados 1\n");
	printf("Professor: Walace Bonfim\n");
	printf("\n\tEDITOR DE �RVORE\n\n");
	printf("1 - Inserir\n");
	printf("2 - Remover um n�\n");
	printf("3 - Pesquisar\n");
	printf("4 - Esvaziar a �rvore\n");
	printf("5 - Exibir a �rvore\n");
	printf("0 - Sair\n\n");
	printf("Digite sua op��o: ");
	op = lerNumero();
	
	switch(op){
		case 1:{ // Inserir um nó na árvore
			printf("\n----------------------------------------");
			printf("\nDigite o nome do aluno: \n");
			while (getchar() != '\n');
			lerTexto(aluno.nome, sizeof(aluno.nome));			
			printf("\nDigite o RGM do aluno: \n");
		    aluno.rgm = lerNumero();
		    
			if(inserir(&tree,aluno))
			printf("\nAluno inserido com sucesso!\n ");
			else
			printf("\nErro ao inserir aluno!\n");
			break;
		}
		case 2:{ // Remover um nó da árvore
		    printf("\n----------------------------------------");
			printf("\nDigite o RGM do aluno a remover: \n");
		    aluno.rgm = lerNumero();
		    if(remover(&tree,aluno))
			printf("\nAluno removido com sucesso!\n ");
			else
			printf("\nErro ao remover aluno!\n");
			break;
		}
		case 3:{ // Pesquisar um nó na árvore
			printf("\n----------------------------------------");
			printf("\Digite o RGM do aluno que deseja pesquisar: \n");
			aluno.rgm = lerNumero();
			
			t_no *resultado = busca(tree,aluno);
			
			if(resultado != NULL) {
				printf("\nAluno encontrado: %s - %d\n", resultado->dado.nome, resultado->dado.rgm);
			} else { 
				printf("\nAluno com o RGM %d n�o foi encontrado!\n", aluno.rgm);
			}
			break;
		}
		case 4:{ // Esvaziar a árvore
		    printf("\n----------------------------------------\n");
			printf("Tem certeza que deseja esvaziar a �rvore? \n 1 - Sim \n 2 - N�o \n\n");
			int op = lerNumero();
			if (1){
			    esvaziar(&tree);
			}
			break;
		}
		case 5:{ // Exibir a árvore
			int opExibir;
			
			printf("\n----------------------------------------");
			printf("\n\tEXIBI��O\n\n1 - Pr�-ordem \n2 - In-ordem \n3 - P�s-ordem\n");
			printf("\nDigite sua op��o: ");
			opExibir = lerNumero();
			
			if(opExibir == 1){
				exibirPreOrdem(tree);
				printf("\n");
			} else if(opExibir == 2){
				exibirInOrdem(tree);
				printf("\n");
			} else if(opExibir == 3){
				exibirPosOrdem(tree);
				printf("\n");
			} else {
				printf("Op��o inv�lida!");
			}
			
			break;
		}
		case 0:{ // Sair do programa
			printf("Saindo...\n");
			break;
		}
		default:{
			printf("Op��o inv�lida!\n");
			break;
		}
	}
	
	// Verificar se o usuário deseja continuar
	if (op != 0) {
		printf("\nDigite '1' para voltar ao menu ou '0' para encerrar o programa.\n");
		op = lerNumero();
		}
		
	}while(op != 0);
	
	return 0;
}
