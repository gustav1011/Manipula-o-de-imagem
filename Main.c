#include <math.h>
#include <stdio.h>
#include <stdlib.h> // Para usar exit()

int linha, coluna, valor;

// Definindo a estrutura RGB!
typedef struct {
    int r;
    int g;
    int b;
} RGB;

// Funções para modificações de imagem, protótipos!
void imagemNegativa(char *nomeImagem, RGB **vetor, int linha, int coluna, int valor);
void imagemCinza(char *nomeImagem, RGB **vetor, int linha, int coluna, int valor);
void imagemRaioX(char *nomeImagem, RGB **vetor, int linha, int coluna, int valor);
void imagemEnvelhecida(char *nomeImagem, RGB **vetor, int linha, int coluna, int valor);
void imagemRotacionada90(char *nomeImagem, RGB **vetor, int linha, int coluna, int valor);



int main() {
    // Abertura do arquivo
    FILE *fp;
    char nomeImagem[50];

    // Solicita o nome da imagem
    printf("Escreva o nome da imagem colorida que deseja abrir (formato *.ppm):");
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
    int coluna, linha;
    fscanf(fp, "%d %d", &coluna, &linha);

    // Valida o tamanho da imagem
    if (linha < 300 || coluna < 300) {// imagem deve ter pelo menos 400x400(verificar essa verificação)
        fprintf(stderr, "Erro: A imagem deve ter pelo menos 400x400 pixels.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    printf("Tamanho: %d x %d\n", coluna, linha);

    // Leitura do valor máximo
    int valor;
    fscanf(fp, "%d", &valor);
    printf("Valor máximo: %d\n", valor);

    // Instanciação do array de struct RGB dinamicamente
    RGB **vetor = (RGB **)malloc(linha * sizeof(RGB *));
    for (int i = 0; i < linha; i++) {
        vetor[i] = (RGB *)malloc(coluna * sizeof(RGB));
    }

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
            imagemNegativa("imagem_negativa.ppm", vetor, linha, coluna, valor);//feita
            break;
        case '2':
            imagemCinza("imagem_cinza.ppm", vetor, linha, coluna, valor);//feita
            break;
        case '3':
            imagemRaioX("imagem_raioX.ppm", vetor, linha, coluna, valor);//feita
            break;
        case '4':
            imagemRotacionada90("imagem_rotacionada.ppm", vetor, linha, coluna, valor);//feita
            break;
        case '5':
            imagemEnvelhecida("Imagem_Envelhecida.ppm", vetor, linha, coluna, valor);//feita
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    // Liberação da memória
    for (int i = 0; i < linha; i++) {
        free(vetor[i]);
    }
    free(vetor);

    // Fechar o arquivo
    fclose(fp);
    return 0;
}

// Função para criar a imagem em tons de cinza:
void imagemCinza(char *nomeImagem, RGB **vetor, int linha, int coluna, int valor) {
    FILE *fp_Cinza = fopen(nomeImagem, "w");
    if (fp_Cinza == NULL) {
        perror("Erro ao criar o arquivo cinza");
        exit(EXIT_FAILURE);
    }
    fprintf(fp_Cinza, "P2\n");
    fprintf(fp_Cinza, "%d %d\n", coluna, linha);
    fprintf(fp_Cinza, "%d\n", valor);
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            int cinza = (int)((vetor[i][j].r * 0.299) + (vetor[i][j].g * 0.587) + (vetor[i][j].b * 0.114));
            // Escrever o valor de cinza para cada pixel
            fprintf(fp_Cinza, "%d\n ", cinza);
        }
        fprintf(fp_Cinza, "\n");
    }

    fclose(fp_Cinza);
    printf("Imagem em tons de cinza criada com sucesso.\n");
}// COMPLETA

// Função para criar a imagem negativa:
void imagemNegativa(char *nomeImagem, RGB **vetor, int linha, int coluna, int valor) {
    FILE *fp_Negativa = fopen(nomeImagem, "w");
    if (fp_Negativa == NULL) {
        perror("Erro ao criar o arquivo negativo");
        exit(EXIT_FAILURE);
    }
    fprintf(fp_Negativa, "P3\n");
    fprintf(fp_Negativa, "%d %d\n", coluna, linha);
    fprintf(fp_Negativa, "%d\n", valor);
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++){
            fprintf(fp_Negativa, "%d %d %d\n", 255 - vetor[i][j].r, 255 - vetor[i][j].g, 255 - vetor[i][j].b);
        }
    }

    fclose(fp_Negativa);
    printf("Imagem negativa criada com sucesso.\n");
}// COMPLETA

// Função para criar a imagem em Raio X:
void imagemRaioX(char *nomeImagem, RGB **vetor, int linha, int coluna, int valor) {
    FILE *fp_RaioX = fopen(nomeImagem, "w");
    if (fp_RaioX == NULL) {
        perror("Erro ao criar o arquivo Raio X");
        exit(EXIT_FAILURE);
    }

    // Escreve o cabeçalho do arquivo no formato P2 (escala de cinza)
    fprintf(fp_RaioX, "P2\n");
    fprintf(fp_RaioX, "%d %d\n", coluna, linha);
    fprintf(fp_RaioX, "%d\n", valor);  // Valor máximo (255)

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            // Converte para escala de cinza usando ponderação RGB
            int cinza = (int)((vetor[i][j].r * 0.299) + (vetor[i][j].g * 0.587) + (vetor[i][j].b * 0.114));
            // Aplica a transformação raio X com um fator ajustado
            float raioX = pow((float)cinza, 1.1);
            // Normaliza para o intervalo 0-255
            if (raioX > valor) raioX = valor;  // Limita a 255
            if (raioX < 0) raioX = 0;          // Garante que não seja negativo

            // Escreve o valor resultante no arquivo
            fprintf(fp_RaioX, "%d\n", (int)raioX);
        }
        fprintf(fp_RaioX, "\n"); // Para manter o formato P2 correto
    }

    fclose(fp_RaioX);
    printf("Imagem em Raio X criada com sucesso.\n");
}// COMPLETA


// Função para criar a imagem Envelhecida:
void imagemEnvelhecida(char *nomeImagem, RGB **vetor, int linha, int coluna, int valor) {
    FILE *fp_Envelhecida = fopen(nomeImagem, "w");
    if (fp_Envelhecida == NULL) {
        perror("Erro ao criar o arquivo Envelhecida");
        exit(EXIT_FAILURE);
    }
    // Escreve o cabeçalho do arquivo no formato P3 (RGB)
    fprintf(fp_Envelhecida, "P3\n");
    fprintf(fp_Envelhecida, "%d %d\n", coluna, linha);
    fprintf(fp_Envelhecida, "%d\n", valor);  // Máximo valor de cor

    double fator = 0.1; 

    // Processa a imagem, aplicando o efeito de envelhecimento
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            // Aplica o fator de envelhecimento para cada componente RGB
            int r = (int)(vetor[i][j].r * (1 + fator));  // Aumenta o vermelho
            int g = (int)(vetor[i][j].g * (1 + fator));  // Aumenta o verde
            int b = (int)(vetor[i][j].b * (1 - fator));  // Diminui o azul

            r = r > 255 ? 255 : (r < 0 ? 0 : r);
            g = g > 255 ? 255 : (g < 0 ? 0 : g);
            b = b > 255 ? 255 : (b < 0 ? 0 : b);

            r = r + 10 > 255 ? 255 : r + 10;
            g = g + 10 > 255 ? 255 : g + 10;
            b = b - 10 < 0 ? 0 : b - 10;

            // Escreve os valores ajustados no arquivo
            fprintf(fp_Envelhecida, "%d %d %d\n", r, g, b);
        }
    }
    fclose(fp_Envelhecida);
    printf("Imagem Envelhecida criada com sucesso.\n");
}// COMPLETA


// Função para criar a imagem Rotacionada em 90°:
void imagemRotacionada90(char *nomeImagem, RGB **vetor, int linha, int coluna, int valor) {
    FILE *fp_Rotacionada = fopen(nomeImagem, "w");
    if (fp_Rotacionada == NULL) {
        perror("Erro ao criar o arquivo Rotacionado");
        exit(EXIT_FAILURE);
    }
    fprintf(fp_Rotacionada, "P3\n");
    fprintf(fp_Rotacionada, "%d %d\n", linha, coluna); // Inverte as dimensões
    fprintf(fp_Rotacionada, "%d\n", valor);

    // Rotaciona a imagem em 90 graus
    for (int j = 0; j < coluna; j++) {
        for (int i = linha - 1; i >= 0; i--) {
            fprintf(fp_Rotacionada, "%d %d %d\n", vetor[i][j].r, vetor[i][j].g, vetor[i][j].b);
        }
    }

    fclose(fp_Rotacionada);
    printf("Imagem Rotacionada em 90° criada com sucesso.\n");
}// COMPLETA JA