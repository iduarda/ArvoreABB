#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Árvore Binária de Busca */

int lerNumero() { // Função para tratar erros do usuário
    int numero;
    while (scanf("%d", &numero) != 1) {
        printf("\nOpcao Invalida! Digite um numero: \n ");
        // Limpa o buffer de entrada
        while (getchar() != '\n');
    }
    return numero;
}

int main(int argc, char *argv[]) {
	
	int op;
	
	do{
	system("cls");
	printf("\n\tEDITOR DE ARVORE\n\n");
	printf("1 - Inserir\n");
	printf("2 - Remover um no\n");
	printf("3 - Pesquisar\n");
	printf("4 - Esvaziar a arvore\n");
	printf("5 - Exibir a arvore\n");
	printf("0 - Sair\n\n");
	printf("Digite sua opcao: ");
	op = lerNumero();
	
	switch(op){
		case 1:{
			printf("Inserir...\n");
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
			printf("Opcao invalida!\n");
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