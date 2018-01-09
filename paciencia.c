#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "paciencia.h"

#define VIRADA 254
#define TRACO 186


COORD coord={0,0};

//funcao de mover cursor na tela
void gotoxy(int x,int y) {
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
//funçao de mudar as cores da tela
void cores(int ForgC, int BackC) {
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

void gera_numeros (){
    int i,j, v[40];

    for (i = 0; i < 40; i++) v[i] = 0;
    srand( (unsigned)time(NULL) );
    for (i = 0; i < 40; i++) {
       j = rand() % 40;
       while (v[j] == 1 ) j = ( j + 1 ) % 40;
       numeros[i] = j;
       v[j] = 1;
    }
    return;
}

int valor_carta (int i){
    if  (i >= 0 && i <= 39)
        return numeros[i] % 10;
    else
        return -1;
}

char naipe_carta (int i){
    char naipe[8] = { 'E','P','O','C','P','E','C','O' };

    if (i >= 0 && i <= 39)
        return naipe[numeros[i] / 5];
    else
        return ' ';
}

tipo_descritor_pilha* criaPilha(int tam){
    int i;
    tipo_descritor_pilha* Pilha;
    Pilha = (tipo_descritor_pilha*) malloc(sizeof(tipo_descritor_pilha)* tam);
    for (i = 0; i < tam; i++){
        Pilha[i].n = 0;
        Pilha[i].topo = NULL;
    }
    return Pilha;
}

st_pilha* criaCarta(int tam){
    st_pilha* novaCarta;
    novaCarta = (st_pilha*) malloc(sizeof (st_pilha) * tam);
    novaCarta->prox = NULL;
    return novaCarta;
}

tipo_descritor_lista* criaLista(){
    tipo_descritor_lista* novaLista;
    novaLista = (tipo_descritor_lista*)malloc(sizeof(tipo_descritor_lista));
    novaLista->n = 0;
    novaLista->prim = NULL;
    novaLista->ult = NULL;
    return novaLista;
}

void imprimirPilha (tipo_descritor_pilha *p){
    int i, x = 1, y = 7;
    st_pilha* Mostrar;
    for (i = 0; i < 7; i++){
        Mostrar = p[i].topo;
        gotoxy(x, y);
        printf ("%c M%d %c", TRACO, i+1, TRACO);
        y += p[i].n;
        while (Mostrar != NULL){
            gotoxy(x, y);
            if (Mostrar->carta.visivel == 1){
                printf("%c", TRACO);
                cores(Mostrar->carta.cor, CORFUNDO);
                printf("% d%c ", Mostrar->carta.valor, Mostrar->carta.naipe);
                cores(CORLETRA, CORFUNDO);
                printf("%c", TRACO);
            }else {
                printf("%c  %c %c",TRACO, VIRADA, TRACO);
            }
            Mostrar = Mostrar->prox;
            y --;
        }
        x+= 7;
        y = 7;
    }
}

void imprimirLista (tipo_descritor_lista* l){
    int x = 10, y = 20;
    st_lista_circular *Mostrar;
    if (l != NULL){
        if (l->prim != NULL){
            Mostrar = l->prim;
            gotoxy(x, y);
            printf ("L: ");
            gotoxy (4, y+1);
            printf ("(Livres)");
            x = 15;
            do{
                gotoxy(x, y);
                if (Mostrar->carta.visivel == 1){
                    cores(Mostrar->carta.cor, CORFUNDO);
                    printf ("%d%c\t", Mostrar->carta.valor, Mostrar->carta.naipe);
                }else {
                    printf ("%c", VIRADA);
                }
                cores(CORLETRA, CORFUNDO);
                x+= 3;
                Mostrar = Mostrar->prox;
            }while (Mostrar != l->ult->prox);
        }
    }
}

void risca (int x, int y, int i, int j, int k){
    gotoxy(x, y);
    printf("%c%c%c%c", i, j, j, k);
}

void imprimirNaipe (tipo_descritor_pilha* p){
    int i, x = 10, y = 0;
    st_pilha* Mostrar;
    gotoxy(x, y);
    y++;
    printf("NAIPES  E         P         C         O");
    for (i = 0; i < 4; i++){
        risca(x+7, y, 201, 205, 187);
        y++;
        risca(x+7, y, 186, 186, 186);
        y++;
        risca(x+7, y, 200, 205, 188);
        y++;
        if (p != NULL){
            Mostrar = p[i].topo;
            gotoxy(x+8, 2);
            if (Mostrar != NULL){
                cores(Mostrar->carta.cor, CORFUNDO);
                printf("%d%c", Mostrar->carta.valor, Mostrar->carta.naipe);
                cores(CORLETRA, CORFUNDO);
            } else {
                printf ("  ");
            }
            cores(CORLETRA, CORFUNDO);
        }
        x += 10;
        y = 1;
    }
}

tipo_descritor_pilha* iniciaPilha (int *num){
    int i, j, tam = 7;
    st_pilha* novaCarta, *ant;
    tipo_descritor_pilha* Pilha;
    Pilha = criaPilha(tam);
    for(i = 0; i < 7; i++){
        novaCarta = criaCarta(i+1);
        for(j = 0; j <= i; j++){
            (novaCarta+j)->carta.naipe = naipe_carta(*num);
            (novaCarta+j)->carta.valor = valor_carta(*num);
            (novaCarta+j)->prox = NULL;
            if ((novaCarta+j)->carta.naipe == 'C' || (novaCarta+j)->carta.naipe == 'O'){
                (novaCarta+j)->carta.cor = 4;
            }else {
                (novaCarta+j)->carta.cor = 0;
            }
            if (Pilha[i].topo == NULL){
                Pilha[i].topo = (novaCarta+j);
                Pilha[i].n++;
            }else {
                ant = Pilha[i].topo;
                Pilha[i].topo = (novaCarta+j);
                Pilha[i].topo->prox = ant;
                Pilha[i].n++;
            }
             (*num)++;
        }
        Pilha[i].topo->carta.visivel = 1;
    }
    return Pilha;
}

tipo_descritor_lista* iniciaLista(int n){
    int i;
    st_lista_circular* Carta;
    tipo_descritor_lista* Lista;
    Lista = criaLista();
    Carta = (st_lista_circular*)malloc(sizeof(st_lista_circular)*(40 - n));
    for (i = 0; i < (40 - n); i++){
        (Carta+i)->carta.naipe = naipe_carta(n+i);
        (Carta+i)->carta.valor = valor_carta(n+i);
        if ((Carta+i)->carta.naipe == 'C' || (Carta+i)->carta.naipe == 'O'){
            (Carta+i)->carta.cor = 4;
        }else {
            (Carta+i)->carta.cor = 0;
        }
        (Carta+i)->carta.visivel = 0;
        (Carta+i)->ant = NULL;
        (Carta+i)->prox = NULL;
        if (Lista->prim == NULL){
            Lista->prim = (Carta+i);
            Lista->ult = (Carta+i);
            Lista->prim->carta.visivel = 1;
            Lista->prim->prox = Lista->ult;
            Lista->prim->ant = Lista->ult;
            Lista->ult->prox = Lista->prim;
            Lista->ult->ant = Lista->prim;
        } else {
            Lista->ult->prox = (Carta+i);
            Lista->ult = (Carta+i);
        }
    }

    return Lista;
}


st_elemento* busca(char *vet, tipo_descritor_pilha* Pilha, tipo_descritor_lista* Lista){
    st_elemento* carta;

    int i = 0;
    if (Pilha != NULL){
        i = *(vet+(i+1)) - '0';
        if (*(vet) == 'M' && Pilha[i-1].topo != NULL){
            if ((i-1) >= 0 && (i-1) < 7){
                carta = &Pilha[i-1].topo->carta;
                return carta;
            }
        }
    }

    if (Lista != NULL){
        if (*(vet) == 'L' && Lista->prim != NULL){
            carta = &Lista->prim->carta;
            return carta;
        }
    }
    return NULL;
}

int inserePilha (tipo_descritor_pilha* Pilha, st_elemento* carta){
    st_pilha* topo;
    if (Pilha != NULL){
        if (Pilha->topo != NULL){
            if ((Pilha->topo->carta.cor != carta->cor) && ((Pilha->topo->carta.valor-1) == carta->valor)){
                topo = criaCarta(1);
                topo->carta = *carta;
                topo->prox = Pilha->topo;
                Pilha->topo = topo;
                Pilha->n++;
                return 1;
            }
        }else {
            if (carta->valor == 9){
                topo = criaCarta(1);
                topo->carta = *carta;
                Pilha->topo = topo;
                return 1;
            }
        }
    }
    return 0;
}

int insereNaipe(tipo_descritor_pilha* Pilha, st_elemento* carta){
    st_pilha* topo;
    if (Pilha != NULL){
        if (Pilha->topo != NULL){
            if ((Pilha->topo->carta.cor == carta->cor) && ((Pilha->topo->carta.valor+1) == carta->valor)){
                topo = criaCarta(1);
                topo->carta = *carta;
                topo->prox = Pilha->topo;
                Pilha->topo = topo;
                Pilha->n++;
                return 1;
            }
        }else {
            if (carta->valor == 0){
                topo = criaCarta(1);
                topo->carta = *carta;
                Pilha->topo = topo;
                Pilha->n++;
                return 1;
            }
        }
    }
    return 0;
}

void removeLista(tipo_descritor_lista* lista){
    st_lista_circular *prim;
    if (lista != NULL){
        if (lista->prim != NULL){
            if (lista->prim == lista->ult){
                lista->prim = NULL;
            }else {
                prim = lista->prim;
                lista->prim = lista->prim->prox;
                lista->ult->prox = lista->prim;
                lista->prim->carta.visivel = 1;
            }
        }
    }
}

void removePilha(tipo_descritor_pilha* Pilha){
    st_pilha* remove;
    if (Pilha != NULL){
        if (Pilha->topo != NULL){
            remove = Pilha->topo;
            Pilha->topo = Pilha->topo->prox;
            if (Pilha->topo != NULL){
                Pilha->topo->carta.visivel = 1;
                Pilha->n--;
            }
            free(remove);
        }
    }
}

void rodaLista(tipo_descritor_lista *Lista){
    st_lista_circular *move;
    if (Lista != NULL){
        if (Lista->prim != NULL && Lista->ult != NULL){
            move = Lista->prim;
            Lista->prim = Lista->prim->prox;
            Lista->ult->prox = move;
            Lista->ult = move;
            move->carta.visivel = 0;
            if (Lista->prim != NULL)
                Lista->prim->carta.visivel = 1;
        }
    }
}

int fimjogo(tipo_descritor_pilha *Naipes){
    int i = 0, sair = 0;
    if (Naipes != NULL){
        for (i = 0; i < 4; i++){
            if (Naipes[i].topo != NULL){
                if (Naipes[i].topo->carta.valor == 9){
                    sair++;
                }
            }
        }
    }
    if (sair == 4){
        return 1;
    }else
        return 0;
}
