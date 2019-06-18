//############ ALUNO: LUIS FERNANDO FURTADO DE ARAUJO #############
// # # # # # # MATRICULA: 180042661 # # # # # # # # # # # # # # # # 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct No {
	int numero;
	int altura;
	struct No *esquerda;
	struct No *direita;
} typedef No;

No *newTree(No *raiz, int valor) {
	raiz->numero = valor;
	raiz->altura = 0;
	raiz->esquerda = NULL;
	raiz->direita = NULL;
	return raiz;
}

No *insereNo(No *arvore, int numero, int altura) {

	if(arvore==NULL) {
		No *novo;
		novo = (No*) malloc(sizeof(No));
		novo->numero = numero;
		novo->altura = altura;
		novo->esquerda = NULL;
		novo->direita = NULL;
		return novo;
	}
	else {
		altura++;
		if(numero>arvore->numero) {
			arvore->direita = insereNo(arvore->direita, numero, altura);
		}
		else {
			arvore->esquerda = insereNo(arvore->esquerda, numero, altura);
		}
		return arvore;
	}
}

No *loadTreeFromFile(char *caminho, No *arvore) {

	int valor[10];
	char aux;
	No *raiz;
	
	FILE *arquivo = fopen(caminho,"r");

	for(int i=0; i<10; i++) {
		fscanf(arquivo,"%d",&valor[i]);
		fscanf(arquivo,"%c",&aux);
		if(i==0) {
			raiz = newTree(arvore,valor[i]);
			arvore = raiz;
		}
		else {
			arvore = insereNo(arvore,valor[i],0);
		}
	}

	return arvore;
}

int print_arvore(No *arvore, int is_esquerda, int fora, int profundidade, char s[20][255]) {
    
    char b[20];
    int largura = 5;

    if(!arvore) {
    	return 0;
    }

    sprintf(b, "(%03d)", arvore->numero);

    int esquerda  = print_arvore(arvore->esquerda,  1, fora, profundidade + 1, s);
    int direita = print_arvore(arvore->direita, 0, fora + esquerda + largura, profundidade + 1, s);

#ifdef COMPACT
    for (int i = 0; i < largura; i++)
        s[profundidade][fora + esquerda + i] = b[i];

    if (profundidade && is_esquerda) {

        for (int i = 0; i < largura + direita; i++)
            s[profundidade - 1][fora + esquerda + largura/2 + i] = '-';

        s[profundidade - 1][fora + esquerda + largura/2] = '.';

    } else if (profundidade && !is_esquerda) {

        for (int i = 0; i < esquerda + largura; i++)
            s[profundidade - 1][fora - largura/2 + i] = '-';

        s[profundidade - 1][fora + esquerda + largura/2] = '.';
    }
#else
    for (int i = 0; i < largura; i++)
        s[2 * profundidade][fora + esquerda + i] = b[i];

    if (profundidade && is_esquerda) {

        for (int i = 0; i < largura + direita; i++)
            s[2 * profundidade - 1][fora + esquerda + largura/2 + i] = '-';

        s[2 * profundidade - 1][fora + esquerda + largura/2] = '+';
        s[2 * profundidade - 1][fora + esquerda + largura + direita + largura/2] = '+';

    } else if (profundidade && !is_esquerda) {

        for (int i = 0; i < esquerda + largura; i++)
            s[2 * profundidade - 1][fora - largura/2 + i] = '-';

        s[2 * profundidade - 1][fora + esquerda + largura/2] = '+';
        s[2 * profundidade - 1][fora - largura/2 - 1] = '+';
    }
#endif

    return esquerda + largura + direita;
}

void showTree(No *arvore) {
    
    char s[20][255];

    for (int i = 0; i < 20; i++) {
        sprintf(s[i], "%80s", " ");
    }

    print_arvore(arvore, 0, 0, 0, s);

    for (int i = 0; i < 20; i++) {
        printf("%s\n", s[i]);
    }

}

int isFull(No *arvore, int retorno) {

	if(arvore!=NULL) {
		isFull(arvore->esquerda,retorno);
    	isFull(arvore->direita,retorno);
    	if((arvore->esquerda!=NULL&&arvore->direita==NULL)||(arvore->esquerda==NULL&&arvore->direita!=NULL)) {
			return 0;
		}
	}
}

void searchValue(No *arvore, No *pai, int num, int cont, char *direcao) {

	if(arvore==NULL) {
		printf("\nNão existe esse número na àrvore!\n\n");
		return;
	}

	if(arvore->numero==num) {
		printf("\nEste número pertence ao nível:\t%d\n",cont-1);
		if(pai!=NULL) {
			printf("Valor de seu pai:\t%d\n",pai->numero);
			if(strcmp(direcao,"esquerda")==0) {
				if(pai->direita!=NULL) {
					printf("Valor de seu seu irmão:\t%d\n",pai->direita->numero);
				}
				else {
					printf("Este número não possui irmão\n");
				}
			}
			else {
				if(pai->esquerda!=NULL) {
					printf("Valor de seu seu irmão:\t%d\n",pai->esquerda->numero);
				}
				else {
					printf("Este número não possui irmão\n");
				}
			}
		}
		else {
			printf("Este numero pertence a raiz da àrvore\n");
		}
		printf("\n");
	}

	if(arvore->numero!=num) {
		if(num>arvore->numero) {
			searchValue(arvore->direita,arvore,num,cont+1,"direita");
		}
		else {
			searchValue(arvore->esquerda,arvore,num,cont+1,"esquerda");
		}
	}
}

int maior(int esquerda, int direita) {
	if(esquerda>direita) {
        return esquerda;
	}
    else {
        return direita;
    }
}

int getHeight(No *arvore) {

	if(arvore==NULL||(arvore->esquerda==NULL&&arvore->direita==NULL)) {
		return 0;
	}
	else {
		return 1 + maior(getHeight(arvore->esquerda), getHeight(arvore->direita));
	}
}

No *remove_atual(No *atual) {
	No *no1, *no2;
	if(atual->esquerda==NULL) {
		no2 = atual->direita;
		free(atual);
		return no2;
	}
	no1 = atual;
	no2 = atual->esquerda;
	while(no2->direita != NULL) {
		no1 = no2;
		no2 = no2->direita;
	}

	if(no1 !=atual) {
		no1->direita = no2->esquerda;
		no2->esquerda = atual->esquerda;
	}
	no2->direita = atual->direita;
	free(atual);
	return no2;
}

int removeValue(No *arvore, int valor) {
	if(arvore==NULL) {
		return 0;
	}
	No *ant = NULL;
	No *atual;
	atual = arvore;

	while(atual!=NULL) {
		if(valor == atual->numero) {
			if(atual == arvore) {
				//atual = remove_atual(atual);
			}
			else {
				if(ant->direita == atual) {
					ant->direita = remove_atual(atual);
				}
				else {
					ant->esquerda = remove_atual(atual);
				}
			}
			return 1;
		}
		ant = atual;
		if(valor > atual->numero) {
			atual = atual->direita;
		}
		else {
			atual = atual->esquerda;
		}
	}
}

void printInOrder(No *arvore){
    if(arvore != NULL) {
        printInOrder(arvore->esquerda);
        printf("%d, ", arvore->numero);
        printInOrder(arvore->direita);
    }
}

void printPreOrder(No *arvore){
    if(arvore != NULL) {
        printf("%d, ", arvore->numero);
        printPreOrder(arvore->esquerda);
        printPreOrder(arvore->direita);
    }
}

void printPosOrder(No *arvore){
    if(arvore != NULL){
        printPosOrder(arvore->esquerda);
        printPosOrder(arvore->direita);
        printf("%d, ", arvore->numero);
    }
}
/*
int alturaNo(No *no) {
	if(no==NULL) {
		return -1;
	}
	else {
		return no->altura;
	}
}

void rotacaoRR(No *arvore) {
	No *no;
	no = arvore->direita;
	arvore->direita = no->esquerda;
	no->esquerda = arvore;
	arvore->altura = maior(alturaNo(arvore->esquerda),alturaNo(arvore->direita))+1;
	arvore->altura = maior(alturaNo(no->direita),arvore->altura)+1;
	arvore = no;
}

void rotacaoLL(No *arvore) {
	No *no;
	no = arvore->esquerda;
	arvore->esquerda = no->direita;
	no->direita = arvore;
	arvore->altura = maior(alturaNo(arvore->esquerda),alturaNo(arvore->direita))+1;
	arvore->altura = maior(alturaNo(no->esquerda),arvore->altura)+1;
	arvore = no;
}

void rotacaoLR(No *arvore) {
	rotacaoRR(arvore->esquerda);
	rotacaoLL(arvore);
}

void rotacaoRL(No *arvore) {
	rotacaoRR(arvore->direita);
	rotacaoLL(arvore);
}

int fatorBalanceamento(No *no) {
	return labs(alturaNo(no->esquerda) - alturaNo(no->direita));
}

No *insereNoBalanceada(No *arvore, int numero, int altura, int res) {

	if(arvore==NULL) {
		No *novo;
		novo = (No*) malloc(sizeof(No));
		novo->numero = numero;
		novo->altura = altura;
		novo->esquerda = NULL;
		novo->direita = NULL;
		res = 1;
		return novo;
	}

	No *atual;
	atual = arvore;

	if(numero < atual->numero) {
		if(res == 1) {
			if(fatorBalanceamento(atual) >= 2) {
				if(numero < arvore->esquerda->numero) {
					rotacaoLL(arvore);
				}
				else {
					rotacaoLR(arvore);
				}
			}
		}
		else {
			insereNoBalanceada(atual->esquerda,numero,altura,res);
		}
	}
	else {
		if(numero > atual->numero) {
			if(res == 1) {
				if(fatorBalanceamento(atual) >= 2) {
					if(arvore->direita->numero < numero) {
						rotacaoRR(arvore);
					}
					else {
						rotacaoRL(arvore);
					}
				}
			}
			else {
				insereNoBalanceada(atual->esquerda,numero,altura,res);
			}
		}
	}

	atual->altura = maior(alturaNo(atual->esquerda),alturaNo(atual->direita))+1;
	
}

No *loadTreeFromFileBalance(char *caminho, No *arvore) {

	int valor[10];
	char aux;
	No *raiz;
	
	FILE *arquivo = fopen(caminho,"r");

	for(int i=0; i<10; i++) {
		fscanf(arquivo,"%d",&valor[i]);
		fscanf(arquivo,"%c",&aux);
		if(i==0) {
			raiz = newTree(arvore,valor[i]);
			arvore = raiz;
		}
		else {
			arvore = insereNoBalanceada(arvore,valor[i],0,0);
		}
	}

	return arvore;
}*/


int main() {

	No *arvore;

	int opcao = -1, numeroArvore, altura=0, remocao=0, cheia=0;

	while(opcao!=0) {
		printf("1 - Load tree from file\n");
		printf("2 - Show tree\n");
		printf("3 - Is full\n");
		printf("4 - Search Value\n");
		printf("5 - Get Height\n");
		printf("6 - Remove Value\n");
		printf("7 - Print in order\n");
		printf("8 - Print pre order\n");
		printf("9 - Print post order\n");
		printf("10 - Balance tree\n");
		printf("0 - Sair\n");
		scanf("%d",&opcao);
		if(opcao==0) {
			exit(1);
		}
		if(opcao==1) {
			printf("Digite o número da árvore desejada:\t");
			scanf("%d",&numeroArvore);
			if(numeroArvore==1) {
				arvore = loadTreeFromFile("./BSTs/bst1.txt",arvore);
			}
			if(numeroArvore==2) {
				arvore = loadTreeFromFile("./BSTs/bst2.txt",arvore);
			}
			if(numeroArvore==3) {
				arvore = loadTreeFromFile("./BSTs/bst3.txt",arvore);
			}
			if(numeroArvore==4) {
				arvore = loadTreeFromFile("./BSTs/bst4.txt",arvore);
			}
			if(numeroArvore==5) {
				arvore = loadTreeFromFile("./BSTs/bst5.txt",arvore);
			}
			if(numeroArvore==6) {
				arvore = loadTreeFromFile("./BSTs/bst6.txt",arvore);
			}
		}
		if(opcao==2) {
			showTree(arvore);
		}
		if(opcao==3) {
			cheia = isFull(arvore,cheia);
			if(cheia==1) {
				printf("\nArvore é cheia!\n\n");
			}
			else {
				printf("\nArvore não é cheia!\n\n");
				cheia=1;
			}
		}
		if(opcao==4) {
			printf("Digite o número para procurar na árvore:\t");
			scanf("%d",&numeroArvore);
			searchValue(arvore,NULL,numeroArvore,1,"nada");
		}
		if(opcao==5) {
			altura = getHeight(arvore);
			printf("\nA altura da àrvore é:\t%d\n\n",altura);
		}
		if(opcao==6) {
			printf("Digite o número para remover da árvore:\t");
			scanf("%d",&numeroArvore);
			remocao = removeValue(arvore,numeroArvore);
			if(remocao==1) {
				printf("Número removido com sucesso!\n");
			}
		}
		if(opcao==7) {
			printInOrder(arvore);
			printf("\n\n");
		}
		if(opcao==8) {
			printPreOrder(arvore);
			printf("\n\n");
		}
		if(opcao==9) {
			printPosOrder(arvore);
			printf("\n\n");
		}
		if(opcao==10) {
			//arvore = loadTreeFromFileBalance("./BSTs/bst1.txt",arvore);
		}
		opcao=-1;	
	}
}