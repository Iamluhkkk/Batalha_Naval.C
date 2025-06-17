#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Verifica se a posição está dentro do tabuleiro
int dentroDoTabuleiro(int linha, int coluna) {
    return (linha >= 0 && linha < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO);
}

// Verifica se já existe navio na posição (sobreposição)
int verificaSobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    return tabuleiro[linha][coluna] == 3;
}

// Posiciona navio horizontal ou vertical
// orientacao: 'H' para horizontal, 'V' para vertical
int posicionaNavioHV(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha;
        int c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else return 0;

        if (!dentroDoTabuleiro(l, c) || verificaSobreposicao(tabuleiro, l, c)) {
            return 0; // inválido
        }
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha;
        int c = coluna;
        if (orientacao == 'H') c += i;
        else l += i;
        tabuleiro[l][c] = 3;
    }
    return 1;
}

// Posiciona navio diagonal
// direcao: 'D' diagonal principal (linha e coluna aumentam), 'I' diagonal inversa (linha aumenta, coluna diminui)
int posicionaNavioDiagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i;
        int c = (direcao == 'D') ? coluna + i : coluna - i;

        if (!dentroDoTabuleiro(l, c) || verificaSobreposicao(tabuleiro, l, c)) {
            return 0; // inválido
        }
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i;
        int c = (direcao == 'D') ? coluna + i : coluna - i;
        tabuleiro[l][c] = 3;
    }
    return 1;
}

// Exibe o tabuleiro com '~' para água e 'N' para navio
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("    ");
    for (int c = 0; c < TAM_TABULEIRO; c++) {
        printf("%2d ", c);
    }
    printf("\n");

    for (int linha = 0; linha < TAM_TABULEIRO; linha++) {
        printf("%2d  ", linha);
        for (int coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            if (tabuleiro[linha][coluna] == 3) {
                printf(" N ");
            } else {
                printf(" ~ ");
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Posiciona dois navios horizontal/vertical
    if (!posicionaNavioHV(tabuleiro, 1, 1, 'H')) {
        printf("Erro ao posicionar navio horizontal em (1,1)\n");
        return 1;
    }
    if (!posicionaNavioHV(tabuleiro, 4, 7, 'V')) {
        printf("Erro ao posicionar navio vertical em (4,7)\n");
        return 1;
    }

    // Posiciona dois navios diagonais
    if (!posicionaNavioDiagonal(tabuleiro, 6, 2, 'D')) {
        printf("Erro ao posicionar navio diagonal principal em (6,2)\n");
        return 1;
    }
    if (!posicionaNavioDiagonal(tabuleiro, 0, 9, 'I')) {
        printf("Erro ao posicionar navio diagonal inversa em (0,9)\n");
        return 1;
    }

    printf("Tabuleiro com navios posicionados (N = navio, ~ = água):\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
