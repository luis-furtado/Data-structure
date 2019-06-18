//############# Aluno : Luis Fernando Furtado de Araujo ##################
//############# Matricula : 180042661 ####################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Criando struct Lista responsavel por cada Elemento
struct Listas{
	char nome[100];
	char telefone[15];
	char endereco[100];
	int cep;
	char nascimento[12];
	struct Listas *anterior;
	struct Listas *proximo;
}typedef Lista;

//Assinando os tipos de funções que serão utilizadas
Lista *criaListaVazia();
Lista *insereInicioDaLista(Lista *lista);
void imprimeLista(Lista *lista);
Lista *liberaLista(Lista *lista);
Lista *ordenaLista(Lista *lista);
Lista *removerRegistro(Lista *lista);
void escreverArquivo(Lista *lista);
void buscarRegistros(Lista *lista);
Lista *carregaDadosArquivo(Lista *lista);

int main() {

	system("clear");

	Lista *lista;

	lista = criaListaVazia(lista);

	//Carregando elementos já existentes no arquivo na lista
	lista = carregaDadosArquivo(lista);

	int opcao=-1;

	while(opcao!=0) {
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
		printf("1 - Inserir novo Registro\n");
		printf("2 - Remover registros que contenham certa string no nome\n");
		printf("3 - Visualizar registros que contenham certa string no nome\n");
		printf("4 - Visualizar todos os registros em ordem alfabética de acordo com o nome\n");
		printf("0 - Sair\n");
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
		scanf("%d",&opcao);
		if(opcao==1) {
			lista = insereInicioDaLista(lista);
			continue;
		}
		else if(opcao==2) {
			lista = removerRegistro(lista);
			continue;
		}
		else if(opcao==3) {
			buscarRegistros(lista);
			continue;
		}
		else if(opcao==4){
			if(lista!=NULL) {
				lista = ordenaLista(lista);
			}
			imprimeLista(lista);
			continue;
		}
	}

	escreverArquivo(lista);
	liberaLista(lista);

	return 0; 

}

Lista *criaListaVazia(Lista *l) {
	return NULL;
}

Lista *carregaDadosArquivo(Lista *lista) {
	//dados que serão lidos para o novo Lista
	char nome[100];
	int start = 0;
	char aux;

	FILE *arquivo;

	arquivo = fopen("contatos.txt","r");

	if(arquivo==NULL) {
		return NULL;
	}

	Lista *elem, *aux1;

	aux1 = NULL;

	while(!feof(arquivo)) {
		fscanf(arquivo,"%[^\n]", nome);
		if(feof(arquivo)) {
			//printf("start = %d\n", start);
			if(start == 0) {
				//printf("entrei 2");
				fclose(arquivo);
				return NULL;
			}
			break;
		}
		//printf("lendo arquivo\n");
		//Criando novo elemento
		start = 1;

		elem = (Lista*) malloc(sizeof(Lista));

		if(elem == NULL) {
			printf("Sem espaço na memória!\n");
			exit(1);
		}
		//Lendo dados da pessoa "n"
		strcpy(elem->nome,nome);
		//fscanf(arquivo,"%[^\n]",elem->nome);
		fscanf(arquivo,"%c",&aux);
		fscanf(arquivo,"%[^\n]",elem->telefone);
		fscanf(arquivo,"%c",&aux);
		fscanf(arquivo,"%[^\n]",elem->endereco);
		fscanf(arquivo,"%d",&elem->cep);
		fscanf(arquivo,"%c",&aux);
		fscanf(arquivo,"%[^\n]",elem->nascimento);
		fscanf(arquivo,"%c",&aux);
		fscanf(arquivo,"%c",&aux);
		fscanf(arquivo,"%c",&aux);
		//condicional para se for o primeiro elemento
		if(aux1==NULL) {
			elem->proximo = NULL;
			elem->anterior = NULL;
			//guarda o endereço do novo elemento
			aux1 = elem;
		}
		//Caso já exista, cada novo Elemento entra como primeiro elemento da lista
		else {
			elem->proximo = aux1;
			elem->anterior = NULL;
			elem->proximo->anterior = elem;
			aux1 = elem;
		}
	}

	fclose(arquivo);

	return elem;
}

Lista *insereInicioDaLista(Lista *lista) {
	
	char aux, nascimento[12];
	//Criando novo elemento da lista
	Lista *novoLista;

	//Alocando novo elemento da lista na memoria
	novoLista = (Lista*) malloc(sizeof(Lista));

	if(novoLista == NULL) {
		printf("Sem espaço na memória!\n");
		exit(1);
	}
	//Lendo dados arquivo e armazenando no novo elemento da lista
	scanf("%c",&aux);
	system("clear");
	printf("- - - - Inserindo novo registro - - - \n\n");
	printf("Insira o nome:\t");
	scanf("%[^\n]",novoLista->nome);
	scanf("%c",&aux);
	printf("Insira o telefone:\t");
	scanf("%[^\n]",novoLista->telefone);
	scanf("%c",&aux);
	printf("Insira o endereço:\t");
	scanf("%[^\n]",novoLista->endereco);
	scanf("%c",&aux);
	printf("Insira o cep:\t");
	scanf("%d",&novoLista->cep);
	scanf("%c",&aux);
	printf("Insira a data de nascimento:\t");
	scanf("%[^\n]",nascimento);
	while(nascimento[2]!='/'||nascimento[5]!='/') {
		printf("\nVocê deve escrever a data no formato 00/00/0000 !\n");
		printf("Insira a data de nascimento:\t");
		scanf("%c",&aux);
		scanf("%[^\n]",nascimento);
	}
	strcpy(novoLista->nascimento,nascimento);

	//Caso nao exista nenhum elemento na lista
	if(lista == NULL) {
		novoLista->proximo = NULL;
		novoLista->anterior = NULL;
		return novoLista;
	}
	//Caso já exista, o novo Lista entra como primeiro Lista da lista
	else {
		novoLista->proximo = lista;
		novoLista->anterior = NULL;
		lista->anterior = novoLista;
		return novoLista;
	}
}

void imprimeLista(Lista *lista) {
	system("clear");
    Lista *elem;

    for(elem = lista; elem != NULL; elem = elem->proximo) {
    	if(strlen(elem->nome)==0) {
    		continue;
    	}
    	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
    	printf("Nome: %s\n",elem->nome);
        printf("Telefone: %s\n",elem->telefone);
        printf("Endereco: %s\n",elem->endereco);
        printf("Cep: %d\n",elem->cep);
        printf("nascimento: %s\n\n",elem->nascimento);
    }
    
}

Lista *ordenaLista(Lista *l) {

	Lista *elem, *outroElem, *aux1, *aux2, *listaRetorno;
	listaRetorno = l;
	int i=0,j=0;

	for(elem = listaRetorno->proximo; elem != NULL; elem = elem->proximo) {
		i=0;
		for(elem = listaRetorno->proximo; i<j; elem = elem->proximo) {
			i++;
			if(elem==NULL) {
				break;
			}
		}
		if(elem==NULL) {
			break;
		}

		for(outroElem = elem->anterior; outroElem !=NULL; outroElem = outroElem->anterior) {
			if(strcasecmp(outroElem->nome,elem->nome)>0) {
				if(outroElem->anterior==NULL&&elem->proximo==NULL) {
					listaRetorno = elem;
				}
				else if(outroElem->anterior==NULL) {
					elem->proximo->anterior = outroElem;
					listaRetorno = elem;
				}
				else if(elem->proximo==NULL) {
					outroElem->anterior->proximo = elem;
				}
				else {
					outroElem->anterior->proximo = elem;
					elem->proximo->anterior = outroElem;
				}
				aux2 = elem->proximo;
				//Trocando para onde aponta cada elemento da lista
				elem->anterior = outroElem->anterior;
				elem->proximo = outroElem;
				outroElem->anterior = elem;
				outroElem->proximo = aux2;
		}
	}
	j++;
}

		return listaRetorno;
	
}

Lista *removerRegistro(Lista *lista) {
	system("clear");
	Lista *elem, *l;
	l = lista;

	char nome[100], aux;
	printf("Digite a palavra chave para o que quer que seja excluido:\t");
	scanf("%c",&aux);
	scanf("%[^\n]",nome);

	if(lista->anterior==NULL&&lista->proximo==NULL) {
        return NULL;
    }

    for(elem = lista; elem != NULL; elem = elem->proximo) {
        if(strncmp(nome, elem->nome, strlen(nome))==0) {
        	if(elem->anterior==NULL) {
        		 elem = elem->proximo;
        		 free(elem->anterior);
        		 elem->anterior = NULL;
        	}
        	else if(elem->proximo == NULL) {
        		elem = elem->anterior;
        		free(elem->proximo);
        		elem->proximo = NULL;
        	}
        	else {
        		elem->anterior->proximo = elem->proximo;
        		elem->proximo->anterior = elem->anterior;
        		free(elem);
        	}
        }
    }
    return lista;

}

void escreverArquivo(Lista *lista) {
	FILE *arquivo;

	arquivo = fopen("contatos.txt","w");

	if(arquivo==NULL) {
		printf("Deu ruim!");
		exit(1);
	}

	if(lista==NULL) {
		exit(2);
	}

	Lista *elem;

	for(elem = lista; elem != NULL; elem = elem->proximo) {
		if(strlen(elem->nome)<3) {
			continue;
		}
			fprintf(arquivo,"%s\n",elem->nome);
        	fprintf(arquivo,"%s\n",elem->telefone);
        	fprintf(arquivo,"%s\n",elem->endereco);
        	fprintf(arquivo,"%d\n",elem->cep);
        	fprintf(arquivo,"%s\n",elem->nascimento);
        	fprintf(arquivo,"$\n");
    }

	fclose(arquivo);
}

void buscarRegistros(Lista *lista) {
	system("clear");
	Lista *elem;

	char nome[100], aux;

	printf("Digite um nome que esteja procurando:\t");
	scanf("%c",&aux);
	scanf("%[^\n]",nome);

	for(elem = lista; elem != NULL; elem = elem->proximo) {
        if(strncmp(nome, elem->nome, strlen(nome))==0) {
        	if(strlen(elem->nome)==0) {
        		continue;
        	}
        	else {
        		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
        		printf("Nome: %s\n",elem->nome);
        		printf("Telefone: %s\n",elem->telefone);
        		printf("Endereço: %s\n",elem->endereco);
        		printf("Cep: %d\n",elem->cep);
        		printf("Nascimento: %s\n\n",elem->nascimento);
        	}
        }
    }
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
}

Lista *liberaLista(Lista *lista) {

	Lista *aux;

	for( aux=lista->proximo; aux!=NULL; aux = aux->proximo) {
		free(aux->anterior);
	}

	return NULL;
}
