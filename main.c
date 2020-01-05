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
void calculaDistancias(int n)
{
    cidade c1, c2;
    float hipot;
    printf("---------------------------------------------------\n");
    for(int i = 0; i < numeroDeCidades ; i++)
    {
        for(int j = 0; j < numeroDeCidades; j++)
        {
            if(j == i)
                j++;
            if(n == 0)
                dEntreTodasCidades[i].feromonio = 0.1;

            dEntreTodasCidades[i].c1 = cidades[i].n;
            dEntreTodasCidades[i].c2 = cidades[j].n;
            float x1 = 0, y1 = 0;
            x1 = fabs(cidades[i].x - cidades[j].x);
            y1 = fabs(cidades[i].y - cidades[j].y);
            hipot = (x1 * x1) + (y1 * y1);
            dEntreTodasCidades[i].distancia = sqrt(hipot);
            dEntreTodasCidades[i].inverso =  1 / dEntreTodasCidades[i].distancia;
            dEntreTodasCidades[i].inv_ferom = dEntreTodasCidades[i].feromonio * dEntreTodasCidades[i].inverso;
            printf("%d\n", dEntreTodasCidades[i].c1);
            printf("%d\n", dEntreTodasCidades[i].c2);
            printf("%.3f\n", dEntreTodasCidades[i].distancia);
            printf("%.3f\n", dEntreTodasCidades[i].inverso);
            printf("%.3f\n", dEntreTodasCidades[i].inv_ferom);
        }
        printf("---------------------------------------------------\n");
    }
}
