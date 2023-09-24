/*
 ====================================================================================
 Name         : Eigenvalues and Eigenvectors 2x2
 Author       : Lucas Elias de Andrade Cruvinel, Ramon Soares Mendes Meneses Leite
 Version      : 1.00
 E-mail:      : lucrilhasbr@gmail.com, ramnsores1000@gmail.com
 Description  : Program for calculating eigenvalues and eigenvectors of 2x2 matrices
 University   : Universidade Federal de Goi�s - Catal�o GO
 Objective    : Just for fun
 ====================================================================================
 */

//Bibliotecas utilizadas:

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include "colors.h" //Permite a utiliza��o de cores durante a execu��o do programa

void main() {
    setlocale(LC_ALL, "Portuguese"); //Permite a utiliza��o de acentos durante a execu��o do programa
    menu(0);
    }

void menu(int trat_error) { //Fun��o do menu principal
    system("cls");
    foreground(BLUE);
    style(BRIGHT);
    printf("\n++===============================++");
    printf("\n||                               ||");
    printf("\n||          AUTOVALORES          ||");
    printf("\n||               E               ||");
    printf("\n||          AUTOVETORES          ||");
    printf("\n||                               ||");
    printf("\n++===============================++");
    foreground(GREEN);
    printf("\n++===============================++");
    printf("\n||                               ||");
    printf("\n|| > Pressione 1 para Come�ar.   ||");
    printf("\n|| > Pressione 2 para Sair.      ||");
    printf("\n||                               ||");
    printf("\n++===============================++");
    if(trat_error) {
        foreground(RED);
        printf("\n++===============================++");
        printf("\n||                               ||");
        printf("\n||         ! Por Favor !         ||");
        printf("\n||   ! Pressione algo v�lido !   ||");
        printf("\n||                               ||");
        printf("\n++===============================++\n");
        }

    char escolha;
    escolha = getch();
    if(escolha == '1') {
        autovalores();
        }
    else if (escolha == '2') {
        saida();
        }
    else {
        menu(1);
        }
    }

void saida() { //Fun��o para finalizar o programa
    system("cls");
    style(NORMAL);
    foreground(YELLOW);
    printf("\n++=====================================++");
    printf("\n||   \"A Matem�tica � como um moinho de ||");
    printf("\n|| caf� que m�i admiravelmente o que se||");
    printf("\n|| lhe d� para moer, mas n�o devolve   ||");
    printf("\n|| outra coisa sen�o o que lhe deu.\"   ||");
    printf("\n||                         - Faraday   ||");
    printf("\n||                                     ||");
    printf("\n||~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||");
    printf("\n||                                     ||");
    printf("\n||          S2 S2 S2 S2 S2             ||");
    printf("\n||  -> Obrigado pela prefer�ncia <-    ||");
    printf("\n||          S2 S2 S2 S2 S2             ||");
    printf("\n||                                     ||");
    printf("\n++=====================================++\n");
    exit(1);
    }

void autovalores() { //Fun��o para calcular os autovalores de uma matriz 2x2

    /*
          Matriz: [a    b]
                        [c    d]
    */

    system("cls");
    int i, j;
    double trace, deter; //trace = a+d ; deter = a*d-b*c
    double lambda1, lambda2; //lambda = raizes da equa��o formada pelo c�lculo do determinante
    double matriz[2][2];

    printf("===============================================================\n");
    for(i=0; i<2; i++) {
        for(j=0; j<2; j++) {
            printf(" > Digite um numero para a matriz na posicao [%d][%d]: ", i+1, j+1); //preenchimento da matriz
            scanf(" %lf", &matriz[i][j]);
            }
        }
    printf("===============================================================\n");

    trace = matriz[0][0] + matriz[1][1];
    deter = ( matriz[0][0] * matriz[1][1] ) - ( matriz[0][1] * matriz[1][0] );
    lambda1 = (trace/2) + sqrt( ( (trace*trace)/4 ) - deter );
    lambda2 = (trace/2) - sqrt( ( (trace*trace)/4 ) - deter );


    if( 4*deter > trace * trace ) {
        printf("\n > O discriminante � negativo! \n > N�o existem autovalores e autovetores reais!\n\n");
        printf(" > ");
        system("pause");
        menu(0);
        }

    else if(4*deter == trace * trace) {
        system("cls");
        printf("===============================================================\n\n");
        printf(" -> AUTOVALOR:\n");
        printf("   > Lambda �nico: [%.2lf]\n\n", lambda1);
        printf("===============================================================\n\n");
        autovetores(matriz, lambda1, lambda2);
        }

    else {
        system("cls");
        printf("===============================================================\n\n");
        printf(" -> AUTOVALORES:\n");
        printf("   > Lambda 1: [%.2lf]\n", lambda1);
        printf("   > Lambda 2: [%.2lf]\n\n", lambda2);
        printf("===============================================================\n\n");
        autovetores(matriz, lambda1, lambda2); //Chama fun��o para c�lculo dos autovetores
        }
    }

void autovetores(double matriz[2][2], double lambda1, double lambda2) { //Fun��o para calcular os autovetores
    int i, j;
    double vet1, vet2;

    if(lambda1 == lambda2) { //Para lambda �nico:
        vet1 = -( ( matriz[0][0] - lambda1 ) + matriz[0][1] );
        vet2 = matriz[0][1] + ( matriz[1][1] - lambda1 );
        printf(" -> AUTOVETORES:\n");
        if(matriz[1][0]!=0) {
            vet1 = lambda1 - matriz[1][1];
            vet2 = matriz[1][0];
            printf("   >  Para Lambda �nico = [%.2lf ; %.2lf]\n", vet1, vet2);
            }
        else if(matriz[0][1]!=0) {
            vet1 = matriz[0][1];
            vet2 = lambda1 - matriz[0][0];
            printf("   >  Para Lambda �nico = [%.2lf ; %.2lf]\n", vet1, vet2);
            }
        else if(matriz[1][0]== 0 && matriz[0][1] == 0) {
            vet1 = 1;
            vet2 = 0;
            printf("   >  Para Lambda �nico = [%.2lf ; %.2lf]\n\n", vet1, vet2);
            }
        printf("===============================================================\n");
        printf(" > ");
        system("pause");
        menu(0);
        }

    else { //Para dois lambdas:
        printf(" -> AUTOVETORES:\n");
        if(matriz[1][0]!=0) {
            vet1 = lambda1 - matriz[1][1];
            vet2 = matriz[1][0];
            printf("   >  Para Lambda 1 = [%.2lf ; %.2lf]\n", vet1, vet2);
            vet1 = lambda2 - matriz[1][1];
            vet2 = matriz[1][0];
            printf("   >  Para Lambda 2 = [%.2lf ; %.2lf]\n", vet1, vet2);
            }
        else if(matriz[0][1]!=0) {
            vet1 = matriz[0][1];
            vet2 = lambda1 - matriz[0][0];
            printf("   >  Para Lambda 1 = [%.2lf ; %.2lf]\n", vet1, vet2);
            vet1 = matriz[0][1];
            vet2 = lambda2 - matriz[0][0];
            printf("   >  Para Lambda 2 = [%.2lf ; %.2lf]\n", vet1, vet2);
            }
        else if(matriz[1][0]== 0 && matriz[0][1] == 0) {
            vet1 = 1;
            vet2 = 0;
            printf("   >  Para Lambda 1 = [%.2lf ; %.2lf]\n", vet1, vet2);
            vet1 = 0;
            vet2 = 1;
            printf("   >  Para Lambda 2 = [%.2lf ; %.2lf]\n", vet1, vet2);
            }
        printf("\n===============================================================\n\n");
        printf(" > ");
        system("pause");
        menu(0);
        }
    }
