#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define TAM 1000
#include <string.h>
void criar_cidade();
void calculaDistancias();
typedef struct
{
    int n;
    int x;
    int y;
} cidade;
cidade cidades[10];
typedef struct
{
    int c1;
    int c2;
    float distancia;
    float inverso;
    float feromonio;
    float inv_ferom;
    float probabilidade;
    float porcentagem;
} iteracoes;
int numeroDeCidades = 5; // Constante para definir a quantidade de cidades
iteracoes dEntreTodasCidades[TAM];

int main()
{
    criar_cidade();
    calculaDistancias(0);
    return 0;
}
void criar_cidade()
{
    FILE *file = fopen("arquivosTeste/st70.txt","r");
    if(!(file == NULL))
    {
        for(int i = 0; i < numeroDeCidades; i++)
        {
            fscanf(file,"%d %d %d\n", &cidades[i].n, &cidades[i].x, &cidades[i].y);
        }
    }
    else
    {
        printf("Arquivo nao encontrado!\n");
    }
}
void printTabela(){
    for(int i = 0; i < (numeroDeCidades * numeroDeCidades) - numeroDeCidades; i++){
            printf("---------------------------------------------------\n");
            printf("Cidade %d\n", dEntreTodasCidades[i].c1);
            printf("Cidade %d\n", dEntreTodasCidades[i].c2);
            printf("Distancia: %.3f\n", dEntreTodasCidades[i].distancia);
            printf("Inverso da distancia: %.3f\n", dEntreTodasCidades[i].inverso);
            printf("Inverso da distancia vezes feromonio: %.3f\n", dEntreTodasCidades[i].inv_ferom);
            printf("Probabilidade: %.3f\n", dEntreTodasCidades[i].probabilidade);
            printf("Porcentagem: %.2f %%\n", dEntreTodasCidades[i].porcentagem);
            printf("---------------------------------------------------\n");
    }
}
void calculaDistancias(int n){
    cidade c1, c2;
    float hipot;
    int i, j;
    int x= 0;
    printf("---------------------------------------------------\n");
    for(i = 0 ; i < numeroDeCidades ; i++){
        for(j = 0; j < numeroDeCidades; j++){
            if(j == i)
                j++;
            if(n == 0){
                dEntreTodasCidades[x].feromonio = 0.1;
                dEntreTodasCidades[x].probabilidade = 0;
            }
            dEntreTodasCidades[x].c1 = cidades[i].n;
            dEntreTodasCidades[x].c2 = cidades[j].n;
            float x1 = 0, y1 = 0;
            x1 = fabs(cidades[i].x - cidades[j].x);
            y1 = fabs(cidades[i].y - cidades[j].y);
            hipot = (x1 * x1) + (y1 * y1);
            dEntreTodasCidades[x].distancia = sqrt(hipot);
            dEntreTodasCidades[x].inverso =  1 / dEntreTodasCidades[x].distancia;
            dEntreTodasCidades[x].inv_ferom = dEntreTodasCidades[x].feromonio * dEntreTodasCidades[x].inverso;
            dEntreTodasCidades[x].probabilidade += dEntreTodasCidades[x].inv_ferom;
            printf("%d\n", dEntreTodasCidades[x].c1);
            printf("%d\n", dEntreTodasCidades[x].c2);
            printf("%.3f\n", dEntreTodasCidades[x].distancia);
            printf("%.3f\n", dEntreTodasCidades[x].inverso);
            printf("%.3f\n", dEntreTodasCidades[x].inv_ferom);
            printf("%.3f\n", dEntreTodasCidades[x].probabilidade);
            x++;
        }
        dEntreTodasCidades[x-1].probabilidade = dEntreTodasCidades[0].inv_ferom/dEntreTodasCidades[x-1].probabilidade;
        dEntreTodasCidades[x-1].porcentagem = dEntreTodasCidades[x-1].probabilidade * 100;
        printf("---------------------------------------------------\n");

    }
    printTabela();
}
