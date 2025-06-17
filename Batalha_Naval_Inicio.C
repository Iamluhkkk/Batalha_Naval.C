#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    int navioHorizontalLinha = 2;
    int navioHorizontalColuna = 4;

    int navioVerticalLinha = 5;
    int navioVerticalColuna = 7;

    // Validações simplificadas
    if (navioHorizontalColuna + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: Navio horizontal ultrapassa os limites do tabuleiro.\n");
        return 1;
    }
    if (navioVerticalLinha + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: Navio vertical ultrapassa os limites do tabuleiro.\n");
        return 1;
    }

    // Verifica sobreposição
    int sobreposicao = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        int hLinha = navioHorizontalLinha;
        int hColuna = navioHorizontalColuna + i;
        for (int j = 0; j < TAM_NAVIO; j++) {
            int vLinha = navioVerticalLinha + j;
            int vColuna = navioVerticalColuna;
            if (hLinha == vLinha && hColuna == vColuna) {
                sobreposicao = 1;
                break;
            }
        }
        if (sobreposicao) break;
    }
    if (sobreposicao) {
        printf("Erro: Os navios se sobrepõem.\n");
        return 1;
    }

    // Posiciona navios
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[navioHorizontalLinha][navioHorizontalColuna + i] = 3;
        tabuleiro[navioVerticalLinha + i][navioVerticalColuna] = 3;
    }

    // Exibe o tabuleiro com formatação melhorada
    printf("   "); // Espaço para o cabeçalho das colunas
    for (int c = 0; c < TAM_TABULEIRO; c++) {
        printf(" %d ", c);
    }
    printf("\n");

    for (int linha = 0; linha < TAM_TABULEIRO; linha++) {
        printf("%2d ", linha); // Cabeçalho da linha
        for (int coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            if (tabuleiro[linha][coluna] == 3) {
                printf(" N ");  // N para navio
            } else {
                printf(" ~ ");  // ~ para água
            }
        }
        printf("\n");
    }

    return 0;
}