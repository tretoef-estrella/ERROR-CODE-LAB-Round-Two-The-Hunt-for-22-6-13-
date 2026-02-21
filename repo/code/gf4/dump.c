/*
 * DUMP: V-FINAL-1 best matrix [22, 6, 12]_4 with A12=78
 * Full weight analysis + coordinate coverage of w=12 words
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static const uint8_t AT[4][4] = {{0,1,2,3},{1,0,3,2},{2,3,0,1},{3,2,1,0}};
static const uint8_t MT[4][4] = {{0,0,0,0},{0,1,2,3},{0,2,3,1},{0,3,1,2}};

static uint8_t G[6][22] = {
    {1,0,0,0,0,2,3,2,2,3,3,2,1,0,1,1,3,0,2,0,0,1},
    {0,1,0,0,0,1,2,0,2,1,2,3,0,3,1,2,3,1,0,1,0,2},
    {0,0,1,0,0,3,3,2,2,1,2,3,2,1,3,0,1,3,1,2,1,2},
    {0,0,0,1,0,0,2,0,3,3,3,0,1,2,2,1,0,0,3,2,2,1},
    {0,0,0,0,1,1,3,3,0,1,0,3,1,1,2,2,3,0,0,3,2,1},
    {1,0,2,0,2,1,2,3,0,0,3,3,0,3,0,2,1,2,3,0,2,2}
};

int main() {
    printf("=== MATRIZ [22, 6, 12]_4 — V-FINAL-1 (A12=78) ===\n\n");
    
    printf("Generator G (0=0, 1=1, 2=w, 3=w²):\n");
    const char *lbl[] = {"base1","base2","base3","base4","base5","PÚA  "};
    for (int r = 0; r < 6; r++) {
        printf("  [%s] ", lbl[r]);
        for (int c = 0; c < 22; c++) printf("%d", G[r][c]);
        printf("\n");
    }
    
    printf("\n=== WEIGHT DISTRIBUTION ===\n");
    int aw[23] = {0};
    int w12_zero[22] = {0}; /* For each coord: how many w=12 words have ZERO there */
    int w12_count = 0;
    
    for (int idx = 1; idx < 4096; idx++) {
        uint8_t cw[22] = {0};
        int t = idx;
        for (int r = 0; r < 6; r++) {
            uint8_t c = t%4; t/=4;
            if (c) for (int j = 0; j < 22; j++)
                cw[j] = AT[cw[j]][MT[c][G[r][j]]];
        }
        int w = 0;
        for (int j = 0; j < 22; j++) if (cw[j]) w++;
        aw[w]++;
        
        if (w == 12) {
            w12_count++;
            /* Print first 20 weight-12 words */
            if (w12_count <= 20) {
                printf("  w12 #%02d: ", w12_count);
                for (int j = 0; j < 22; j++) printf("%d", cw[j]);
                printf("  zeros@{");
                int first = 1;
                for (int j = 0; j < 22; j++) {
                    if (cw[j] == 0) {
                        if (!first) printf(",");
                        printf("%d", j);
                        first = 0;
                    }
                }
                printf("}\n");
            }
            
            for (int j = 0; j < 22; j++) if (cw[j] == 0) w12_zero[j]++;
        }
    }
    
    printf("  ... (%d total weight-12 words)\n\n", w12_count);
    
    printf("Full distribution:\n");
    for (int w = 0; w <= 22; w++)
        if (aw[w]) printf("  A_%d = %d\n", w, aw[w]);
    
    printf("\n=== COORDINATE COVERAGE BY w=12 WORDS ===\n");
    printf("(How many w=12 words have a ZERO at each coordinate)\n");
    printf("Coord:  ");
    for (int j = 0; j < 22; j++) printf("%3d", j);
    printf("\nZeros:  ");
    for (int j = 0; j < 22; j++) printf("%3d", w12_zero[j]);
    printf("\n\nIf any coord has 0 zeros → that coord is a puncture candidate.\n");
    
    int min_z = 999, max_z = 0;
    for (int j = 0; j < 22; j++) {
        if (w12_zero[j] < min_z) min_z = w12_zero[j];
        if (w12_zero[j] > max_z) max_z = w12_zero[j];
    }
    printf("Min zeros per coord: %d, Max: %d\n", min_z, max_z);
    
    if (min_z > 0)
        printf("\nAll 22 coordinates are hit by w=12 zeros → no puncture to d=13 possible from THIS code.\n");
    else
        printf("\nSome coords have 0 zeros → PUNCTURE CANDIDATES exist!\n");
    
    /* Coefficients of the 78 w=12 words (which linear combos produce them) */
    printf("\n=== COEFFICIENT VECTORS OF w=12 WORDS (a1..a6 in GF4) ===\n");
    w12_count = 0;
    for (int idx = 1; idx < 4096; idx++) {
        uint8_t cw[22] = {0};
        int t = idx;
        uint8_t coeffs[6];
        for (int r = 0; r < 6; r++) {
            coeffs[r] = t%4; t/=4;
            if (coeffs[r]) for (int j = 0; j < 22; j++)
                cw[j] = AT[cw[j]][MT[coeffs[r]][G[r][j]]];
        }
        int w = 0;
        for (int j = 0; j < 22; j++) if (cw[j]) w++;
        if (w == 12) {
            w12_count++;
            printf("  #%02d coeffs=(%d%d%d%d%d%d) a6=%d\n", w12_count,
                   coeffs[0],coeffs[1],coeffs[2],coeffs[3],coeffs[4],coeffs[5],
                   coeffs[5]);
        }
    }
    
    /* How many w=12 words use a6 != 0 (i.e., involve La Púa) */
    int with_pua = 0, without_pua = 0;
    w12_count = 0;
    for (int idx = 1; idx < 4096; idx++) {
        uint8_t cw[22] = {0};
        int t = idx;
        uint8_t a6 = 0;
        for (int r = 0; r < 6; r++) {
            uint8_t c = t%4; t/=4;
            if (r == 5) a6 = c;
            if (c) for (int j = 0; j < 22; j++)
                cw[j] = AT[cw[j]][MT[c][G[r][j]]];
        }
        int w = 0;
        for (int j = 0; j < 22; j++) if (cw[j]) w++;
        if (w == 12) {
            if (a6) with_pua++; else without_pua++;
        }
    }
    printf("\nw=12 words using La Púa (a6!=0): %d\n", with_pua);
    printf("w=12 words from base only (a6=0): %d\n", without_pua);
    
    return 0;
}
