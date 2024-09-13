#include <math.h>
#include <stdio.h>
#include <stdlib.h> // Para usar exit()

// Definindo variáveis globais
int linha, coluna, valor;

// Definindo a estrutura RGB
typedef struct {
    int r;
    int g;
    int b;
} RGB; 

// Funções para modificações de imagem
void imagemNegativa(char *nomeImagem, RGB vetor[linha][coluna]);
void imagemCinza(char *nomeImagem, RGB vetor[linha][coluna]);
void imagemRaioX(char *nomeImagem, RGB vetor[linha][coluna]);

int main() {
    // Abertura do arquivo
    FILE *fp;
    char nomeImagem[50];

    printf("Escreva o nome da imagem colorida que deseja abrir (formato *.ppm): ");
    scanf("%s", nomeImagem);

    fp = fopen(nomeImagem, "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo, tente novamente!");
        exit(EXIT_FAILURE);
    }

    // Leitura do formato
    char formato[3];
    fscanf(fp, "%s", formato);
    printf("Formato: %s\n", formato);

    // Leitura do tamanho da imagem
    fscanf(fp, "%d %d", &coluna, &linha);
    printf("Tamanho: %d x %d\n", coluna, linha);

    // Leitura do valor máximo
    fscanf(fp, "%d", &valor);
    printf("Valor máximo: %d\n", valor);

    // Instanciação do array de struct RGB
    RGB vetor[700][700];

    // Leitura dos valores de cada pixel da imagem
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            fscanf(fp, "%d %d %d", &vetor[i][j].r, &vetor[i][j].g, &vetor[i][j].b);
        }
    }
    printf("Leitura completa do arquivo.\n");

    // Menu para escolher a operação:
    char operacao;
    printf("Escolha a opção de modificação:\n");
    printf("1 - Imagem Negativa\n");
    printf("2 - Imagem Cinza\n");
    printf("3 - Imagem em Raio X\n");
    printf("4 - Rotacionar Imagem 90 graus\n");
    printf("5 - Envelhecer Imagem\n");
    scanf(" %c", &operacao);

    switch (operacao) {
        case '1':
            imagemNegativa("imagem_negativa.ppm", vetor);
            break;
        case '2':
            imagemCinza("imagem_cinza.ppm", vetor);
            break;
        case '3':
            imagemRaioX("imagem_raioX.ppm", vetor);
            break;
        //case '4':
            // Implementar imagemRotacionada();
            //break;
        //case '5':
            // Implementar imagemEnvelhecida();
            //break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    // Fechar o arquivo
    fclose(fp);
    return 0;
}

// Função para criar a imagem em tons de cinza
void imagemCinza(char *nomeImagem, RGB vetor[linha][coluna]) {
    FILE *fp_Cinza = fopen(nomeImagem, "w");
    if (fp_Cinza == NULL) {
        perror("Erro ao criar o arquivo cinza");
        exit(EXIT_FAILURE);
    }
    fprintf(fp_Cinza, "P2\n");
    fprintf(fp_Cinza, "%d %d\n", coluna, linha);
    fprintf (fp_Cinza, "%d\n", valor);
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            int cinza = (vetor[i][j].r * 0.299) + (vetor[i][j].g * 0.587) + (vetor[i][j].b * 0.114);
            // Escrever o valor de cinza para cada pixel
            fprintf(fp_Cinza, "%d ", cinza);
        }
        fprintf(fp_Cinza, "\n");
    }

    fclose(fp_Cinza);
    printf("Imagem em tons de cinza criada com sucesso.\n");
}


// Função para criar a imagem negativa
void imagemNegativa(char *nomeImagem, RGB vetor[linha][coluna]) {
    FILE *fp_Negativa = fopen(nomeImagem, "w");
    if (fp_Negativa == NULL) {
        perror("Erro ao criar o arquivo negativo");
        exit(EXIT_FAILURE);
    }
    fprintf(fp_Negativa, "P2\n");
    fprintf(fp_Negativa, "%d %d\n", coluna, linha);
    fprintf(fp_Negativa, "%d\n", valor);
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            vetor[i][j].r = 255 - vetor[i][j].r;
            vetor[i][j].g = 255 - vetor[i][j].g;
            vetor[i][j].b = 255 - vetor[i][j].b;
            fprintf(fp_Negativa, "%d %d %d\n", vetor[i][j].r, vetor[i][j].g, vetor[i][j].b);
        }
    }

    fclose(fp_Negativa);
    printf("Imagem negativa criada com sucesso.\n");
}

// Função para criar a imagem em Raio X
void imagemRaioX(char *nomeImagem, RGB vetor[linha][coluna]) {
    FILE *fp_RaioX = fopen(nomeImagem, "w");
    if (fp_RaioX == NULL) {
        perror("Erro ao criar o arquivo Raio X");
        exit(EXIT_FAILURE);
    }

    fprintf(fp_RaioX, "P2\n%d %d\n%d\n", coluna, linha, valor);
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            int cinza = (vetor[i][j].r * 0.299) + (vetor[i][j].g * 0.587) + (vetor[i][j].b * 0.114);
            float raioX = pow(cinza, 0.5); // Aplicar transformação de Raio X
            fprintf(fp_RaioX, "%d ", (int)raioX);
        }
        fprintf(fp_RaioX, "\n");
    }
    fclose(fp_RaioX);
    printf("Imagem em Raio X criada com sucesso.\n");
}

//void imagemEnvelhecida(char*nomeImagem) {}; ////a fazer

//void imagemRotacionada(char*nomeImagem){}; // a fazer



