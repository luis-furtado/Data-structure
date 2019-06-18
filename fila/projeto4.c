//############# Aluno : Luis Fernando Furtado de Araujo ##################
//############# Matricula : 180042661 ####################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//Estrutura da fila que será utilizada
struct Voo {
	char codigo[7];
	char modo;
	int combustivel;
	struct Voo *proximo;
} typedef Fila;

//Criando funções que serão utilizadas para manipulação na fila
Fila *criaFilaVazia();
Fila *montarFila(Fila *fila, char codigos[][7], int NVoos, int NAproximacoes, int NDecolagens, int *combustivel);
Fila *removeDaFila(Fila *fila, Fila *auxiliar);
Fila *colocaInicioDaFila(Fila *fila, Fila *auxiliar);

int main() {

	//vetor de strings que será armazenado os codigos
	char codigos[64][7];
	
	char aux;
	int i=0;

	//lendo codigos de voo disponiveis a partir do arquivo
	FILE *arquivo;

	arquivo = fopen("codigos.txt","r");

	while(!feof(arquivo)) {
		fscanf(arquivo,"%[^#]",codigos[i]);
		fscanf(arquivo,"%c",&aux);
		fscanf(arquivo,"%c",&aux);
		i++;
	}

	//Gerando aleatoriamente quantidade de voos, quantidade de aproximacoes, decolagens e combustivel

	srand( (unsigned)time(NULL));

	int NVoos = 20 + rand() % (65-20);
	int NAproximacoes = (rand() % NVoos)+1;
	int combustivel[NAproximacoes];
	for(i=0; i<NAproximacoes; i++) {
		combustivel[i] = rand() % 13;
	}
 	int NDecolagens = NVoos - NAproximacoes;

 	//Criando fila vazia
 	Fila *fila, *auxiliar, *auxiliar2;

 	auxiliar2 = fila;

 	fila = criaFilaVazia();

 	//Montando fila (já será montada com voos de combustivel = 0 com prioridade na fila)
	fila = montarFila(fila,codigos,NVoos,NAproximacoes,NDecolagens,combustivel);

	//execução do programa

	int tempoH=10, tempoMin=0;

	printf("---------------------------------------------------------------------------------\n“Aeroporto Internacional de Brasília”\nHora Inicial:\t%02d:%02d\n",tempoH,tempoMin);
	printf("Fila de Pedidos:\t");
	for(auxiliar = fila; auxiliar!=NULL; auxiliar = auxiliar->proximo) {
		//prioridade será = nivel de combustivel
		printf("%s/%d\t",auxiliar->codigo,auxiliar->combustivel);
	}
	printf("\nNVoos:\t%d\nNaproximações:\t%d\nNDecolagens:\t%d\n---------------------------------------------------------------------------------\n\n",NVoos,NAproximacoes,NDecolagens);

	int pista1=0, pista2=0, pista3=0, tempoPouso1=0, tempoDecolagem1=0, tempoPouso2=0, tempoDecolagem2=0, tempoPouso3=0, tempoDecolagem3=0;
	int diminuirCombustivel=0, combustivelZero=0, ativarDesvio=0;

	while(1) {
		//checando quantas aeronaves na frente da fila possuem nivel 0 de combustivel
		for(auxiliar = fila; auxiliar->combustivel==0; auxiliar = auxiliar->proximo) {
			combustivelZero++;
			if(combustivelZero==3) {
				//caso tenha 3 ou mais aeronaves zeradas, ativar desvio
				ativarDesvio=1;
			}
		}
		//se estiver alguma aeronave pousando na pista 1
		if(tempoPouso1>0) {
			tempoPouso1++;
			if(tempoPouso1==5) {
				tempoPouso1=0;
				pista1=0;
			}
		}
		//se estiver alguma aeronave decolando na pista 1
		if(tempoDecolagem1>0) {
			tempoDecolagem1++;
			if(tempoDecolagem1==3) {
				tempoDecolagem1=0;
				pista1=0;
			}
		}
		//se estiver alguma aeronave pousando na pista 2
		if(tempoPouso2>0) {
			tempoPouso2++;
			if(tempoPouso2==5) {
				tempoPouso2=0;
				pista2=0;
			}
		}
		//se estiver alguma aeronave decolando na pista 2
		if(tempoDecolagem2>0) {
			tempoDecolagem2++;
			if(tempoDecolagem2==3) {
				tempoDecolagem2=0;
				pista2=0;
			}
		}
		//se estiver alguma aeronave decolando na pista 3
		if(tempoDecolagem3>0) {
			tempoDecolagem3++;
			if(tempoDecolagem3==3) {
				tempoDecolagem3=0;
				pista3=0;
			}
		}
		//se estiver alguma aeronave sem gasolina pousando na pista 3
		if(tempoPouso3>0) {
			tempoPouso3++;
			if(tempoPouso3==5) {
				tempoPouso3=0;
				pista3=0;
				ativarDesvio=0;
			}
		}
		//se a pista 1 estiver desocupada
		if(pista1==0) {
			if(fila->modo=='A') {
				printf("Código do Voo:\t%s\n",fila->codigo);
				printf("Status:\tAeronave Pousou\n");
				printf("Horário do Início do Procedimento:\t%02d:%02d\n",tempoH,tempoMin);
				printf("Número da Pista:\t1\n\n");
				tempoPouso1++;
			}
			if(fila->modo=='D') {
				printf("Código do Voo:\t%s\n",fila->codigo);
				printf("Status:\tAeronave Decolou\n");
				printf("Horário do Início do Procedimento:\t%02d:%02d\n",tempoH,tempoMin);
				printf("Número da Pista:\t1\n\n");
				tempoDecolagem1++;
			}
			pista1++;
			fila = removeDaFila(fila,fila);
			//fila = fila->proximo;
			if(fila==NULL) {
				break;
			}
		}
		//se a pista 2 estiver desocupada
		if(pista2==0) {
			if(fila->modo=='A') {
				printf("Código do Voo:\t%s\n",fila->codigo);
				printf("Status:\tAeronave Pousou\n");
				printf("Horário do Início do Procedimento:\t%02d:%02d\n",tempoH,tempoMin);
				printf("Número da Pista:\t2\n\n");
				tempoPouso2++;
			}
			if(fila->modo=='D') {
				printf("Código do Voo:\t%s\n",fila->codigo);
				printf("Status:\tAeronave Decolou\n");
				printf("Horário do Início do Procedimento:\t%02d:%02d\n",tempoH,tempoMin);
				printf("Número da Pista:\t2\n\n");
				tempoDecolagem2++;
			}
			pista2++;
			fila = removeDaFila(fila,fila);
			//fila = fila->proximo;
			if(fila==NULL) {
				break;
			}
		}
		if(pista3==0) {
			if(fila->modo=='A'&&ativarDesvio==1) {
				printf("ALERTA GERAL DE DESVIO DE AERONAVE\n\n");
				//pousando aeronave sem combustivel
				printf("Código do Voo:\t%s\n",fila->codigo);
				printf("Status:\tAeronave Pousou\n");
				printf("Horário do Início do Procedimento:\t%02d:%02d\n",tempoH,tempoMin);
				printf("Número da Pista:\t3\n\n");
				tempoPouso3++;
				fila = removeDaFila(fila,fila);
				pista3++;
			}
			if(fila->modo=='D') {
				printf("Código do Voo:\t%s\n",fila->codigo);
				printf("Status:\tAeronave Decolou\n");
				printf("Horário do Início do Procedimento:\t%02d:%02d\n",tempoH,tempoMin);
				printf("Número da Pista:\t3\n\n");
				tempoDecolagem3++;
				fila = removeDaFila(fila,fila);
				pista3++;
			}
			//fila = fila->proximo;
			if(fila==NULL) {
				break;
			}
		}
		tempoMin+=5;
		if(tempoMin==60) {
			tempoMin=0;
			tempoH+=1;
		}
		diminuirCombustivel++;
		if(diminuirCombustivel==11) {
			//diminuindo 1 de combustivel a cada 10 unidades de tempmo
			for(auxiliar = fila; auxiliar!=NULL; auxiliar = auxiliar->proximo) {
				//caso o nivel de combustivel fique = 0, colocamos no inicio da fila
				if(auxiliar->combustivel==0) {
					fila = colocaInicioDaFila(fila, auxiliar);
				}
				//caso acabe o combustivel, removemos elemento da lista
				if(auxiliar->combustivel==-1) {
					printf("ALERTA CRÍTICO, AERONAVE DO VOO %s IRÁ CAIR\n\n",auxiliar->codigo);
					fila = removeDaFila(fila,auxiliar);
				}
				auxiliar->combustivel--;
			}
			diminuirCombustivel=0;
		}
	}



 }

Fila *criaFilaVazia() {
	return NULL;
}

Fila *montarFila(Fila *fila, char codigos[][7], int NVoos, int NAproximacoes, int NDecolagens, int *combustivel) {

	int sorteado, i=0, j=0;

	while(NVoos>0) {
		//criando novo elemento da fila
		Fila *novoElem, *aux, *anterior;
		anterior = NULL;

		novoElem = (Fila*) malloc(sizeof(Fila));

		if(novoElem==NULL) {
			printf("Deu ruim!");
			exit(1);
		}

		//sorteando se será do tipo aproximação ou decolagem
		if(NAproximacoes>0&&NDecolagens>0){
			sorteado = rand() % 2;
			//sorteado==0 teremos aproximação
			if(sorteado==0) {
				strcpy(novoElem->codigo,codigos[i]);
				novoElem->modo = 'A';
				novoElem->combustivel = combustivel[j];
				j++;
				NAproximacoes--;
			}
			if(sorteado==1) {
				strcpy(novoElem->codigo,codigos[i]);
				novoElem->modo = 'D';
				//Numero deve ser maior que 12, pois é do tipo Decolagem
				novoElem->combustivel = 100;
				NDecolagens--;
			}
		}
		//Caso já tenha selecionado todos os tipos Decolagem
		else if(NAproximacoes>0) {
			strcpy(novoElem->codigo,codigos[i]);
			novoElem->modo = 'A';
			novoElem->combustivel = combustivel[j];
			j++;
			NAproximacoes--;
		}
		//Caso já tenha selecionado todos os tipos Aproximação
		else if(NDecolagens>0) {
			strcpy(novoElem->codigo,codigos[i]);
			novoElem->modo = 'D';
			//Numero deve ser maior que 12, pois é do tipo Decolagem
			novoElem->combustivel = 15;
			NDecolagens--;
		}

		//se não existir nenhum elemento na fila, o novo elem sera o primeiro da fila
		if(fila==NULL) {
			novoElem->proximo = NULL;
			fila = novoElem;
		}
		//caso já exista, inserir de forma que com combustivel = 0 fique na frente da fila
		else {
			aux = fila;
			//inserindo no ultimo elemento da fila caso combustivel seja > 0
			if(novoElem->combustivel>0) {
				while(aux->proximo!=NULL) {
					aux = aux->proximo;
				}
				aux->proximo = novoElem;
				novoElem->proximo = NULL;
			}
			//inserindo no primeiro elemento da fila caso combustivel seja = 0
			if(novoElem->combustivel==0) {
				novoElem->proximo = aux;
				fila = novoElem;
			}
		}

		NVoos--;
		i++;
	}

	//Retornando o primeiro elemento da fila
	return fila;
}

Fila *removeDaFila(Fila *f, Fila *aux) {

	Fila *fila;
	fila = f;

	//se for o primeiro elemento da fila
	if(aux==fila) {
		fila = fila->proximo;
		free(aux);
		return fila;
	}
	//se for o ultimo elemento da fila
	else if(aux->proximo==NULL) {
		while(fila->proximo!=aux) {
			fila = fila->proximo;
		}
		fila->proximo = NULL;
		free(aux);
		return f;
	}
	//se for elemento do meio da fila
	else {
		while(fila->proximo!=aux) {
			fila = fila->proximo;
		}
		fila->proximo = aux->proximo;
		free(aux);
		return f;
	}
}

Fila *colocaInicioDaFila(Fila *fila, Fila *auxiliar) {

	Fila *aux;
	aux = fila;

	//caso ja esteja no inicio da fila (não faça nada)
	if (fila==auxiliar) {
		return fila;
	}
	//caso seja outro elemento da fila
	else{
		while(aux->proximo!=auxiliar) {
			aux = aux->proximo;
		}
		aux->proximo = auxiliar->proximo;
		auxiliar->proximo = fila;
		return auxiliar;
	}
}

