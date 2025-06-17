#include <stdio.h>
#include <stdlib.h>  // para abs()
#include <ctype.h>   // para toupper()

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5  // tamanho fixo das matrizes de habilidade (5x5)
#define TAM_NAVIO 3

// Protótipos das funções
void inicializaTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
int posicionaNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao);
void criaMatrizCone(int cone[TAM_HABILIDADE][TAM_HABILIDADE]);
void criaMatrizCruz(int cruz[TAM_HABILIDADE][TAM_HABILIDADE]);
void criaMatrizOctaedro(int octaedro[TAM_HABILIDADE][TAM_HABILIDADE]);
void sobreporHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int pontoOrigemLinha, int pontoOrigemColuna);
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);

// Inicializa o tabuleiro com água (0)
void inicializaTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Posiciona navio horizontal ('H') ou vertical ('V') no tabuleiro
int posicionaNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    orientacao = toupper(orientacao);
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha;
        int c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else return 0;

        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO) return 0;
        if (tabuleiro[l][c] == 3) return 0; // sobreposição
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

// Cria matriz da habilidade Cone (5x5) com formato de cone apontando para baixo
void criaMatrizCone(int cone[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= meio - i && j <= meio + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Cria matriz da habilidade Cruz (5x5) com ponto de origem no centro
void criaMatrizCruz(int cruz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == meio || j == meio)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Cria matriz da habilidade Octaedro (5x5) com formato de losango centrado
void criaMatrizOctaedro(int octaedro[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Sobrepõe a matriz da habilidade ao tabuleiro, marcando área afetada com 5
void sobreporHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int pontoOrigemLinha, int pontoOrigemColuna) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = pontoOrigemLinha - meio + i;
                int colTab = pontoOrigemColuna - meio + j;
                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO && colTab >= 0 && colTab < TAM_TABULEIRO) {
                    if (tabuleiro[linhaTab][colTab] != 3) {
                        tabuleiro[linhaTab][colTab] = 5;
                    }
                }
            }
        }
    }
}

// Exibe o tabuleiro com símbolos: ~ para água, N para navio, * para área afetada
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("    ");
    for (int c = 0; c < TAM_TABULEIRO; c++) {
        printf("%2d ", c);
    }
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d  ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) printf(" ~ ");
            else if (tabuleiro[i][j] == 3) printf(" N ");
            else if (tabuleiro[i][j] == 5) printf(" * ");
            else printf(" ? ");
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializaTabuleiro(tabuleiro);

    // Posiciona navios fixos (exemplo)
    if (!posicionaNavio(tabuleiro, 1, 1, 'H')) {
        printf("Erro ao posicionar navio horizontal em (1,1)\n");
        return 1;
    }
    if (!posicionaNavio(tabuleiro, 4, 7, 'V')) {
        printf("Erro ao posicionar navio vertical em (4,7)\n");
        return 1;
    }

    // Cria matrizes de habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criaMatrizCone(cone);
    criaMatrizCruz(cruz);
    criaMatrizOctaedro(octaedro);

    // Define pontos de origem para as habilidades no tabuleiro
    int origemConeLinha = 2, origemConeColuna = 3;
    int origemCruzLinha = 6, origemCruzColuna = 5;
    int origemOctaedroLinha = 7, origemOctaedroColuna = 8;

    // Sobrepõe as áreas de efeito das habilidades no tabuleiro
    sobreporHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    sobreporHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    sobreporHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Exibe o tabuleiro final com navios e áreas afetadas
    printf("Tabuleiro com navios (N), água (~) e áreas de efeito das habilidades (*):\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}