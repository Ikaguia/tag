#include <stdio.h>//biblioteca de c
#include <stdlib.h>//biblioteca de c
#include <string.h>//biblioteca de c

#include "lista.hpp"//biblioteca propria

#define FNAME "amigos_tag20171.txt"
#define NALUNOS 39

typedef char string[100];

struct aluno{
	static int idCount;
	int id;
	int matricula;
	string nome;
	listInt amigos;
	aluno(){
		id=idCount++;
	}
	aluno(int matricula,string nome){
		id=idCount++;
		strcpy(this->nome,nome);
		this->matricula=matricula;
	}
};
int aluno::idCount = 1;

struct vetlist{
	aluno v[NALUNOS];
	aluno& operator[](int i){
		return v[i];
	}
};

listInt cliqueMax;

void encontraCliqueMaximo(const listInt l,vetlist &vetLista){
	listInt list;
	list.copy(l);

	int aluno;
	if(l.size==0)aluno=0;
	else aluno=l.last->val+1;//se a lista nao for vazia, tenta inserir apenas vertices de indice maior que o ultimo, para evitar repeticoes

	for(;aluno<NALUNOS;aluno++){
		if(list.find(aluno)!=nullptr){
			continue;//nao insere um vertice que ja esta no clique
		}
		//percorre a lista
		listIntNode *it = list.first;
		while(it!=nullptr){
			if(vetLista[aluno].amigos.find(it->val)==nullptr)break;//nao insere nenhum vertice que não é adjacente a todos os outros
			it=it->next;
		}
		if(it!=nullptr){
			continue;//se it nao for nullptr, significa que chamamos break e esse vertice nao deve ser inserido
		}
		//se o aluno forma um clique com a lista, insere ele
		list.push(aluno);
		if(list.size>cliqueMax.size){
			cliqueMax.copy(list);
		}
		encontraCliqueMaximo(list,vetLista);
		list.copy(l);
	}
}

void printaCliqueMaximo(vetlist &vetLista){
	auto it=cliqueMax.first;
	printf("Clique maximo = {\n\t%s",vetLista[it->val].nome);
	it=it->next;
	while(it!=nullptr){
		printf(",\n\t%s",vetLista[it->val].nome);
		it=it->next;
	}
	printf("\n}\n");
}

void printaVetLista(vetlist &vetLista){
	for(int i=0;i<NALUNOS;i++){
		printf("%9d - grau(%02d)\n",vetLista[i].matricula,vetLista[i].amigos.size);
	}
}

void ordena(vetlist &vetLista){

}

int findInstanceOf(char *string,char c,int instance){
	int instanceCount=0,i;
	for(i=0;instanceCount<instance;i++){
		if(string[i]==c){
			instanceCount++;
		}
	}
	return i-1;
}

void leArquivo(vetlist &vetLista){
	FILE* file=fopen(FNAME,"r");
	if(!file){
		printf("Erro ao ler o arquivo " FNAME "\n");
		exit(EXIT_FAILURE);
	}

	string line,nome;
	int matricula,x=-1;
	for(int aluno=0;aluno<NALUNOS;aluno++){
		//le para a variavel line a 'aluno'esima linha de file
		fgets(line, sizeof(line), file);
		//guarda o primeiro numero de line em matricula e o nome após o '|' em nome
		sscanf(line," %d | %[^|]s",&matricula,vetLista[aluno].nome);
		vetLista[aluno].matricula=matricula;
		//encontra o 2º '|' que delimita o nome e o usa para encontrar o inicio da lista de amigos
		char *line2part = line+findInstanceOf(line,'|',2)+1;
		//le todos os amigos após o '|'
		int amigo=0;
		while(sscanf(line2part," %d %[^\n]s",&x,line2part)==2){
			if(x!=-1){
				x--;//id dos amigos no arquivo é em base 1
				//e os insere na lista de adjacencia do aluno, caso nao esteja presente
				if(vetLista[aluno].amigos.find(x)==nullptr)vetLista[aluno].amigos.push(x);
				if(vetLista[x].amigos.find(aluno)==nullptr)vetLista[x].amigos.push(aluno);
			}
		}
		if(x!=-1){
			x--;//id dos amigos no arquivo é em base 1
			if(vetLista[aluno].amigos.find(x)==nullptr)vetLista[aluno].amigos.push(x);
			if(vetLista[x].amigos.find(aluno)==nullptr)vetLista[x].amigos.push(aluno);
		}
	}
	fclose(file);
}

int main(){
	vetlist vet;
	leArquivo(vet);

	ordena(vet);
	printaVetLista(vet);

	encontraCliqueMaximo(cliqueMax,vet);
	printaCliqueMaximo(vet);
}