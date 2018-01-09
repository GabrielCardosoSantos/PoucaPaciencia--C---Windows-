#ifndef PACIENCIA_H_INCLUDED
#define PACIENCIA_H_INCLUDED

int numeros[40];

#define CORFUNDO 2
#define CORLETRA 15

enum {E = 1, P, C, O};

typedef struct{
    int valor;
    int cor;
    int visivel; // campo para definir se o elemento deve ficar visível ou não
    char naipe;
} st_elemento;

typedef struct {
    st_elemento carta;
    struct st_lista_circular *ant, *prox;
}st_lista_circular;

typedef struct {
    st_elemento carta;
    struct st_pilha *prox;
}st_pilha;

typedef struct{
    int n; // numero de elementos da lista
    st_lista_circular *prim, *ult;
} tipo_descritor_lista;

typedef struct{
    int n; // numero de elementos da pilha
    st_pilha *topo;
} tipo_descritor_pilha;

void gotoxy(int x,int y);
void cores(int ForgC, int BackC);
void gera_numeros ();
int valor_carta (int i);
char naipe_carta (int i);

tipo_descritor_pilha* criaPilha(int tam);
st_pilha* criaCarta(int tam);
tipo_descritor_lista* criaLista();
tipo_descritor_pilha* iniciaPilha (int *num);
tipo_descritor_lista* iniciaLista(int n);

void imprimirPilha (tipo_descritor_pilha *p);
void imprimirLista (tipo_descritor_lista* l);
void imprimirNaipe (tipo_descritor_pilha* p);
void risca (int x, int y, int i, int j, int k);
#endif // PACIENCIA_H_INCLUDED
