#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "paciencia.h"


int main(){
    cores(CORLETRA, CORFUNDO);
    system("cls");

    int i = 0, j = 0, n = 0, sair = 0, l = 0, ind, consegui = 0;
    char pegar, *str, *str2;

    st_elemento* carta = NULL;
    tipo_descritor_pilha* Pilha, *Naipes;
    tipo_descritor_lista* Lista;

    gera_numeros();
    Pilha = iniciaPilha(&n);
    Lista = iniciaLista(n);
    Naipes = criaPilha(4);
    str = (char*)malloc(sizeof(char)*2);
    str2 = (char*)malloc(sizeof(char)*2);
    while (sair == 0){
        system("cls");
        //DESENHA EM TELA
        imprimirNaipe(Naipes);
        imprimirPilha(Pilha);
        imprimirLista(Lista);
        cores(15, 2);
        gotoxy(54, 9);
        printf("%cComo fazer jogadas:", 176);
        gotoxy(54, 10);
        printf(" (ATIVAR CAPSLOCK)");
        gotoxy(54, 11);
        printf("%cDe:   Para:", 176);
        gotoxy(54, 12);
        printf("%cMNUM  MNUM", 176);
        gotoxy(54, 13);
        printf("%cMNUM  NAIPES", 176);
        gotoxy(54, 14);
        printf("%cL     L", 176);
        gotoxy(54, 15);
        printf("%cL     MNUM", 176);
        gotoxy(54, 16);
        printf("%cL     NAIPES", 176);
        gotoxy(54, 17);
        printf("%cS (Sair)", 176);
        gotoxy(35, 22);

        cores(CORLETRA, CORFUNDO);
        printf("De:   Para:");
        gotoxy(20, 23);

        cores(15, 0);
        printf("Sua jogada:");
        gotoxy(35, 23);
        printf ("    ");
        gotoxy(41, 23);
        printf ("    ");

        // JOGADA DE PARTIDA
        while (carta == NULL){
            i = 35;
            while (i < 37){
                gotoxy(i, 23);
                pegar = getche();
                if (pegar == 'S'){
                    exit(1);
                }
                if (pegar == 'L'){
                    *(str+l) = pegar;
                    l++;
                    break;
                }
                if (pegar == 'M'){
                    *(str+l) = pegar;
                    l++;
                    i++;
                } else {
                    if (i >= 36 && isdigit(pegar)){
                        *(str+l) = pegar;
                        l++;
                        i++;
                    }else if (i > 35 && pegar == '\b'){
                        gotoxy(i-1, 23);
                        i--;
                        l--;
                        printf(" ");
                    }else{
                        gotoxy(i, 23);
                        printf(" ");
                    }
                }
            }
            *(str+l) = '\0';
            carta = busca(str, Pilha, Lista);
        }

        // JOGADAS PARA ONDE VAI
        l = 0;
        i = 41;
        *(str2) = '\0';
        while (i < 43  && pegar != 'S'){
            gotoxy(i, 23);
            pegar = getche();
            if (pegar == 'S'){
                exit(1);
            }

            if (pegar == 'L'){
                rodaLista(Lista);
                carta = NULL;
                i = 35;
                break;
            }
            if (pegar == 'E' || pegar == 'P' || pegar == 'C' || pegar == 'O'){
                if (carta->naipe == pegar){
                    if (pegar == 'E'){
                        consegui = insereNaipe(&Naipes[0], carta);
                    }else if (pegar == 'P'){
                        consegui = insereNaipe(&Naipes[1], carta);
                    }else if (pegar == 'C'){
                        consegui = insereNaipe(&Naipes[2], carta);
                    }else if (pegar == 'O'){
                        consegui = insereNaipe(&Naipes[3], carta);
                    }
                    if (*str == 'M' && consegui == 1){
                        ind = *(str+1) - '0';
                        removePilha(&Pilha[ind-1]);
                        consegui = 0;
                    }else if (*str == 'L' && consegui == 1){
                        removeLista(Lista);
                        consegui = 0;
                    }
                } else {
                    gotoxy(1, 28);
                    printf ("JOGADA NAO PERMITIDA\n");
                    system("pause");
                }
                carta = NULL;
                break;
            }
            if (pegar == 'M'){
                *(str2+l) = pegar;
                l++;
                i++;
            } else {
                if (i >= 42 && isdigit(pegar)){
                    *(str2+l) = pegar;
                    l++;
                    i++;
                    *(str2+l) = '\0';

                    ind = *(str2+1) - '0';
                    consegui = inserePilha(&Pilha[ind-1], carta);
                    if (*str == 'M' && consegui == 1){
                        ind = *(str+1) - '0';
                        removePilha(&Pilha[ind-1]);
                        consegui = 0;
                    }else if (*str == 'L' && consegui == 1){
                        removeLista(Lista);
                        consegui = 0;
                    }

                    carta = NULL;
                    l = 0;
                }else if (i > 41 && pegar == '\b'){
                    gotoxy(i-1, 23);
                    i--;
                    l--;
                    printf(" ");
                }else {
                    gotoxy(i, 23);
                    printf(" ");
                }
            }
        }
        sair = fimjogo(Naipes);
        cores(CORLETRA, CORFUNDO);
    }
    free(str);
    free(str2);
    free(Pilha);
    free(Lista);
    free(Naipes);
    return 0;
}

