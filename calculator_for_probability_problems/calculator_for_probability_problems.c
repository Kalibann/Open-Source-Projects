/*
 ============================================================================
 Name         : Calculator for Probability Problems
 Author       : Ramon Soares Mendes Meneses Leite
 Version      : 0.25
 E-mail:      : ramnsores1000@gmail.com
 University   : Universidade Federal de Goiás - Catalão GO
 Objective    : Just for fun
 ============================================================================
 */

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <math.h>
#define E 2.7182818284590452353602874

void main_menu(int choice); // chama a função menu
long long int comb_arr(int n, int p, int opt); // função para cálculo de combinação e arranjo
void binomial(); // função para cálculo utilizando distribuição binomial
void poisson(); // função para cálculo utilizando distribuição de poisson
void geometric(); // função para cálculo utilizando distribuição geométrica
void hypergeometric(); // // função para cálculo utilizando distribuição hipergeométrica
void other_calculations(); // calcula a esperança, variância e desvio padrão
void summary(); // mostra o sumário para ajudar no entendimento dos cálculos
long long int factorial(int n); // calcula e retorna o fatorial de um número passado
void repeat(int choice); // função para fazer cálculo novamente ou ir ao menu
void quit(); //função para sair do programa

void main() {
    setlocale(LC_ALL, "Portuguese");
    main_menu(0);
}

void main_menu(int choice) {

    if(choice == 0) {

        printf("\n ===========================================");
        printf("\n *              MENU PRINCIPAL             *");
        printf("\n ===========================================");
        printf("\n * 1- Arranjo                              *");
        printf("\n * 2- Combinação                           *");
        printf("\n * 3- Distribuição Binomial                *");
        printf("\n * 4- Distribuição de Poisson              *");
        printf("\n * 5- Distribuição Geométrica              *");
        printf("\n * 6- Distribuição Hipergeométrica         *");
        printf("\n * 7- Esperança, Variância e Desvio Padrão *");
        printf("\n * 8- Sumário                              *");
        printf("\n * 9- Sair do Programa                     *");
        printf("\n ===========================================");

        while(true) {
            printf("\n\n > ");
            scanf("%d", &choice);
            if(choice >=1 && choice <=9) {
                break;
            }
        }
    }

    if(choice == 1 || choice == 2) {

        int n, p;
        long long int c;
        if(choice == 1) {
            printf("\n === ARRANJO ===");
            printf("\n\n > A(n,p)\n");
        } else {
            printf("\n === COMBINAÇÃO ===");
            printf("\n\n > C(n,p)\n");
        }

        while(true) {
            printf("\n Digite um N: ");
            scanf("%d", &n);
            printf(" Digite um P: ");
            scanf("%d", &p);
            if(n>=0 && p>=0 && n>=p) {
                break;
            } else {
                printf("\n # Inválido!\n");
            }
        }
        if(choice == 1) {
            c = comb_arr(n,p,0);
        } else {
            c = comb_arr(n,p,1);
        }
        printf("\n > Resultado: %lld\n", c);
        repeat(choice);
    }

    if(choice == 3) {
        binomial();
    }

    if(choice == 4) {
        poisson();
    }

    if(choice == 5) {
        geometric();
    }

    if(choice == 6) {
        hypergeometric();
    }

    if(choice == 7) {
        other_calculations();
    }

    if(choice == 8) {
        summary();
    }

    if(choice == 9) {
        quit();
    }
}

long long int comb_arr(n, p, opt) {

    long long int c, fact1, fact2, fact3;
    int x;

    x = n-p;

    fact1 = factorial(n);

    if(opt == 0) {
        fact2 = 1;
    }

    else {
        fact2 = factorial(p);

    }

    fact3 = factorial(x);

    c = fact1/(fact2*fact3);
    return c;
}

void binomial() {
    int n, k;
    long long int c;
    double p, q, X;
    printf("\n === DISTRIBUIÇÃO BINOMIAL ===\n");
    printf("\n > X~B(n,p)         > P(X = k)...\n");
    while(true) {
        printf("\n Digite um número para N: ");
        scanf("%d", &n);
        printf(" Digite um número para P: ");
        scanf("%lf", &p);
        printf(" Digite um número para K: ");
        scanf("%d", &k);
        if(n>=0 && p>=0 && p<=1 && k>=0 && n>=k) {
            break;
        } else {
            printf("\n # Inválido!\n");
        }
    }
    q = 1-p;
    c = comb_arr(n,k,1);
    X = c*(pow(p,k))*(pow(q,(n-k)));
    printf("\n > Resultado: %lf\n", X);
    repeat(3);
}

void poisson() {

    int k, auxk;
    long long int factk;
    double lambda, X;
    printf("\n === DISTRIBUIÇÃO DE POISSON ===\n");
    printf("\n > P(X = k) = [(E^-lambda)*(lambda^k)]/fact(k)\n");

    while(true) {
        printf("\n Digite um valor para K: ");
        scanf("%d", &k);
        printf(" Digite um valor para Lambda: ");
        scanf("%lf", &lambda);
        if(k>=0 && lambda>=0) {
            break;
        } else {
            printf("\n # Inválido!\n");
        }
    }

    auxk = k;
    factk = factorial(auxk);

    X = ((pow(E, -lambda))*(pow(lambda, k)))/factk;
    printf("\n > Resultado: %lf\n", X);
    repeat(4);
}

void geometric() {

    int n;
    double p, q, X;
    printf("\n === DISTRIBUIÇÃO GEOMÉTRICA ===\n");
    printf("\n P(X = n) = (q^(n-1))*p\n");

    while(true) {
        printf("\n Digite um N: ");
        scanf("%d", &n);
        printf(" Digite um P: ");
        scanf("%lf", &p);
        if(n>0 && p>=0 && p<=1) {
            break;
        } else {
            printf("\n # Inválido!\n");
        }
    }
    q = 1-p;

    X = pow(q,n-1)*p;
    printf("\n > Resultado: %lf\n", X);
    repeat(5);
}

void hypergeometric() {

    int n, k, r, t;
    long long int x0,x1,x2;
    double X;
    printf("\n === DISTRIBUIÇÃO HIPERGEOMÉTRICA ===\n");
    printf("\n > P(X = k) = (C(r,k) * C(t-r, n-k))/C(t,n)\n");

    while(true) {
        printf("\n Digite um T: ");
        scanf("%d", &t);
        printf(" Digite um N: ");
        scanf("%d", &n);
        printf(" Digite um K: ");
        scanf("%d", &k);
        printf(" Digite um R: ");
        scanf("%d", &r);
        if(t>=0 && n>=0 && k>=0 && r>=0 && n>=k && r>=k && t>=n) {
            break;
        } else {
            printf("\n # Inválido!\n");
        }
    }

    x0 = comb_arr(r,k,1);
    x1 = comb_arr(t-r,n-k,1);
    x2 = comb_arr(t,n,1);

    X = x0*x1;
    X = X/x2;

    printf("\n > Resultado: %lf\n", X);
    repeat(6);
}

void other_calculations() {

    int oc_choice;
    double H, V, SD;
    printf("\n ========================================");
    printf("\n * ESPERANÇA, VARIÂNCIA E DESVIO PADRÃO *");
    printf("\n ========================================");
    printf("\n * > Calcular para:                     *");
    printf("\n *                                      *");
    printf("\n * 1- Distribuição Binomial             *");
    printf("\n * 2- Distribuição de Poisson           *");
    printf("\n * 3- Distribuição Geométrica           *");
    printf("\n * 4- Distribuição Hipergeométrica      *");
    printf("\n * 5- Voltar ao menu principal          *");
    printf("\n ========================================");

    while(true) {
        printf("\n\n > ");
        scanf("%d", &oc_choice);
        if(oc_choice >=1 && oc_choice <=5) {
            break;
        }
    }

    if(oc_choice == 1) {
        int n;
        double p, q;
        printf("\n >> Para Distribuição Binomial <<\n");
        while(true) {
            printf("\n Digite um N: ");
            scanf("%d", &n);
            printf(" Digite um P: ");
            scanf("%lf", &p);
            if(n>=0 && p>=0 && p<=1) {
                break;
            } else {
                printf("\n # Inválido!\n");
            }
        }
        q = 1-p;

        H = n*p;
        V = n*p*q;
        SD = sqrt(V);

        printf("\n > Esperança: %lf\n", H);
        printf(" > Variância: %lf\n", V);
        printf(" > Desvio Padrão: %lf\n\n", SD);
        repeat(7);
    }

    else  if(oc_choice == 2) {
        double lambda;
        printf("\n >> Para Distribuição de Poisson <<\n");
        while(true) {
            printf("\n Digite um Lambda: ");
            scanf("%lf", &lambda);
            if(lambda>=0) {
                break;
            } else {
                printf("\n # Inválido!\n");
            }
        }

        H = lambda;
        V = lambda;
        SD = sqrt(V);

        printf("\n > Esperança: %lf\n", H);
        printf(" > Variância: %lf\n", V);
        printf(" > Desvio Padrão: %lf\n\n", SD);
        repeat(7);
    }

    else  if(oc_choice == 3) {
        double p, q;
        printf("\n >> Para Distribuição Geométrica <<\n");
        while(true) {
            printf("\n Digite um P: ");
            scanf("%lf", &p);
            if(p>=0 && p<=1) {
                break;
            } else {
                printf("\n # Inválido!\n");
            }
        }
        q = 1-p;

        H = 1/p;
        V = q/(pow(p,2));
        SD = sqrt(V);

        printf("\n > Esperança: %lf\n", H);
        printf(" > Variância: %lf\n", V);
        printf(" > Desvio Padrão: %lf\n\n", SD);
        repeat(7);
    }

    else  if(oc_choice == 4) {
        double p, q, t, n, r;
        printf("\n >> Para Distribuição Hipergeométrica <<\n");
        while(true) {
            printf("\n Digite um T: ");
            scanf("%lf", &t);
            printf(" Digite um N: ");
            scanf("%lf", &n);
            printf(" Digite um R: ");
            scanf("%lf", &r);
            if(t>=0 && n>=0 && r>=0 && t>=n) {
                break;
            } else {
                printf("\n # Inválido!\n");
            }
        }
        p = r/t;
        q = 1-p;

        H = n*p;
        V = (n*p*q)*((t-n)/(t-1));
        SD = sqrt(V);

        printf("\n > Esperança: %lf\n", H);
        printf(" > Variância: %lf\n", V);
        printf(" > Desvio Padrão: %lf\n\n", SD);
        repeat(7);
    }

    else  if(oc_choice == 5) {
        main_menu(0);
    }

}

void summary() {

    printf("\n =====================================");
    printf("\n *              SUMÁRIO              *");
    printf("\n =====================================\n");

    printf("\n >> Arranjo e Combinação <<\n\n");
    printf(" n = Quantidade total de elementos no conjunto;\n");
    printf(" p = Quantidade de elementos por arranjo.\n");

    printf("\n >> Distribuição Binomial <<\n\n");
    printf(" n = Tentativas independentes;\n");
    printf(" p = Probabilidade de sucesso;\n");
    printf(" k = Número de sucessos em 'n'.\n");

    printf("\n >> Distribuição de Poisson <<\n\n");
    printf(" k = Número de ocorrências de um determinado evento (sucesso) em um certo intervalo;\n");
    printf(" lambda = Média de ocorrência do sucesso.\n");

    printf("\n >> Distribuição Geométrica <<\n\n");
    printf(" n = Número de tentativas sucessivas e independentes necessárias ao aparecimento do primeiro sucesso;\n");
    printf(" p = Probabilidade de sucesso.\n");

    printf("\n >> Distribuição Hipergeométrica <<\n\n");
    printf(" t = Tamanho da população;\n");
    printf(" n = Tamanho da amostra;\n");
    printf(" k = Número de sucessos na amostra;\n");
    printf(" r = Característica determinada.\n\n");

    main_menu(0);

}

long long int factorial(int n) {

    long long int fact=1;
    while(n>0) {
        fact *= n--;
    }
    return fact;
}

void repeat(int choice) {

    int conf;
    while(true) {
        printf(" > Deseja fazer outro cálculo? [0-Não|1-Sim]: ");
        scanf("%d", &conf);
        if(conf == 0) {
            main_menu(0);
        } else if(conf == 1) {
            main_menu(choice);
        } else {
            printf("\n # Opção inválida!\n\n");
        }
    }
}

void quit() {
    printf("\n >>> Adios!!! <<<\n");
    exit(0);
}
