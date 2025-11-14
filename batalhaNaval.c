#include <stdlib.h>
#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define HAB 5
#define TAM_HAB 7   // tamanho das matrizes de habilidade 7x7

//---------------------------------------------------------
// Funções auxiliares
//---------------------------------------------------------
int dentroDoTabuleiro(int l, int c) {
    return (l >= 0 && l < TAM && c >= 0 && c < TAM);
}

// Aplica uma matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tab[TAM][TAM], int hab[TAM_HAB][TAM_HAB], int origemL, int origemC) {

    int centro = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {

            // Deslocamento da matriz de habilidade em relação ao centro
            int lTab = origemL + (i - centro);
            int cTab = origemC + (j - centro);

            // 1 = área afetada
            if (hab[i][j] == 1 && dentroDoTabuleiro(lTab, cTab)) {

                // Marca com 5 sem sobrescrever navio
                if (tab[lTab][cTab] == 0)
                    tab[lTab][cTab] = HAB;
            }
        }
    }
}

//---------------------------------------------------------
// CONSTRUÇÃO DINÂMICA DAS MATRIZES DE HABILIDADE
//---------------------------------------------------------
void construirCone(int cone[TAM_HAB][TAM_HAB]) {

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {

            // O cone começa estreito e abre conforme desce
            int centro = TAM_HAB / 2;
            int largura = i; // aumenta conforme desce

            if (j >= centro - largura && j <= centro + largura)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

void construirCruz(int cruz[TAM_HAB][TAM_HAB]) {

    int centro = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {

            if (i == centro || j == centro)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

void construirOctaedro(int oct[TAM_HAB][TAM_HAB]) {

    int centro = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {

            int dist = abs(i - centro) + abs(j - centro);

            if (dist <= centro)
                oct[i][j] = 1;
            else
                oct[i][j] = 0;
        }
    }
}


//---------------------------------------------------------
// PROGRAMA PRINCIPAL
//---------------------------------------------------------
int main() {

    int tabuleiro[TAM][TAM];

    // Inicializa tudo com água
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;

    //-----------------------------------------------------
    // Aqui você pode inserir a lógica dos navios
    // (copiada e resumida do nível anterior)
    //-----------------------------------------------------

    // Para simplificar, posicionaremos 1 navio horizontal
    // e 1 vertical apenas para efeito visual.

    // Navio horizontal
    for (int i = 0; i < 3; i++)
        tabuleiro[2][3 + i] = NAVIO;

    // Navio vertical
    for (int i = 0; i < 3; i++)
        tabuleiro[5 + i][6] = NAVIO;

    //-----------------------------------------------------
    // MATRIZES DE HABILIDADE
    //-----------------------------------------------------

    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    //-----------------------------------------------------
    // APLICAR HABILIDADES NO TABULEIRO
    // (definindo um ponto de origem para cada uma)
    //-----------------------------------------------------

    aplicarHabilidade(tabuleiro, cone, 1, 1);
    aplicarHabilidade(tabuleiro, cruz, 5, 4);
    aplicarHabilidade(tabuleiro, octaedro, 7, 8);

    //-----------------------------------------------------
    // EXIBIR TABULEIRO FINAL
    //-----------------------------------------------------
    printf("\n===== TABULEIRO FINAL COM HABILIDADES =====\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {

            if (tabuleiro[i][j] == 0)
                printf(". "); // água
            else if (tabuleiro[i][j] == NAVIO)
                printf("N "); // navio
            else if (tabuleiro[i][j] == HAB)
                printf("* "); // habilidade

        }
        printf("\n");
    }

    printf("\nLegenda: . = água | N = navio | * = habilidade\n");

    return 0;
}
