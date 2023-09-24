#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#define QE 4 // Quantidade de entradas (colunas)
#define QD 4 // Quantidade de dados (linhas)

 // Viari�veis Globais:

double inputs[QE][QD] = {{1, 2, 4, 8},
                           {2, 4, 8, 10},
                           {3, 8, 8, 9},
                           {5, 10, 15, 20}}; // Entradas da rede X Quantidade de dados

double output[QD] = {1, 1, 0, 1}; // sa�da da rede
double bias = 1; // por padr�o � considerado como 1
double learnRate = 0.3; // taxa de aprendizado
double moment = 1; // por padr�o � 1 para n�o influenciar no rec�lculo dos pesos
int epochs = 100; // quantidade de �pocas que a rede ir� rodar

 // Fun��es:

void init_weights(double *weights); // Fun��o para inicializa��o dos pesos
double calculate(double *weights, double *output_network); // Fun��o para c�lculos aritm�ticos necess�rios e aplica��o da fun��o de ativa��o
void recalculate(double delta, double *weights, int row); // Fun��o para recalcular pesos
void train_network(); // Fun��o para treinamento da rede


void main()
{
    setlocale(LC_ALL, "Portuguese");
    train_network();
}

void init_weights(double *weights){

    // Inicializa��o dos pesos com um intervalo entre -1 e 1

    int i;

    srand((unsigned)time(NULL));

    printf(" ==================================\n");
    for(i=0;i<QE;i++){
        weights[i] = rand()%101;
        weights[i] = (weights[i]/100) + (rand()%2)-1;
        printf(" -> Peso inicial %d: %lf\n", i+1, weights[i]);
    }

    printf(" * Bias: %.2lf\n", bias);
    printf(" ==================================\n\n");
}

double calculate(double *weights, double *output_network){

    double sum[QD];
    int i,j;

    for(i=0;i<QD;i++){
        for(j=0;j<QE;j++){
            sum[i] += (inputs[i][j] * weights[j]) + bias;
        }
    }

    // Fun��o Sigmoid:

    for(i=0;i<QD;i++){
        // printf(" -> Soma = %lf\n", sum[i]);
        output_network[i] = (1 / (1 + exp(-sum[i])));
    }

}

void recalculate(double delta, double *weights, int row){

    int i;

    for(i=0;i<QE;i++){
        weights[i] = (weights[i] * moment) + (inputs[row][i] * learnRate * delta);
        // printf(" -> Peso = %lf - Delta = %lf\n", weights[i], delta);
    }
}

void train_network(){

    double weights[QE], best_weights[QE], difference[QD], output_network[QD], mean_error, s_error, best_output[QD];
    int i, j, epoch = 0;

    init_weights(weights);

    while(epoch<epochs){

        for(i=0;i<QD;i++){
            difference[i] = 0;
        }

        mean_error = 0;
        calculate(weights, output_network);

        for(i=0;i<QD;i++){

        // printf(" -> Sa�da %d: %lf\n", i, output_network[i]);
            /*if(output_network[i]<=0.5){
                output_network[i] = 0;
            }
            else{
                output_network[i] = 1.0;
            }*/

            if(output_network[i] != output[i]){
                difference[i] = output[i] - output_network[i];
                mean_error += fabs(difference[i]);
                recalculate(difference[i], weights, i);
            }
        }

        mean_error /= QD;

        if(mean_error <= s_error || epoch == 0){
            s_error = mean_error;

            for(i=0;i<QE;i++){
                best_weights[i] = weights[i];
            }

            for(i=0;i<QD;i++){
                best_output[i] = output_network[i];
            }
        }

        printf(" - �poca: %d - Erro: %lf\n", epoch+1, mean_error);
        epoch++;
    }

    printf("\n ==================================");
    printf("\n O erro mais baixo foi: %lf\n", s_error);
    printf(" ==================================\n");
    printf("\n -> Melhores pesos:\n\n");

    for(i=0;i<QE;i++){
        printf(" * Peso %d: %lf\n", i+1, best_weights[i]);
    }
    printf(" ==================================\n\n");

    printf(" -> Sa�das rede:\n\n");
    for(i=0;i<QD;i++){
        printf(" * Sa�da %d: %lf\n", i+1, best_output[i]);
    }
}
