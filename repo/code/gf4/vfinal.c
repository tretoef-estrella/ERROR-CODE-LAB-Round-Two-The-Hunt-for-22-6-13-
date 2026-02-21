/*
 * LA PÚA DEL JET — V-FINAL (Unified Span Attack)
 * 60-second hard cutoff. Silent. Full 4095-word verification per step.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

static const uint8_t A[4][4] = {{0,1,2,3},{1,0,3,2},{2,3,0,1},{3,2,1,0}};
static const uint8_t M[4][4] = {{0,0,0,0},{0,1,2,3},{0,2,3,1},{0,3,1,2}};

/* Hardcoded [22,5,13]_4 base from previous run */
static uint8_t base[5][22] = {
    {1,0,0,0,0,2,3,2,2,3,3,2,1,0,1,1,3,0,2,0,0,1},
    {0,1,0,0,0,1,2,0,2,1,2,3,0,3,1,2,3,1,0,1,0,2},
    {0,0,1,0,0,3,3,2,2,1,2,3,2,1,3,0,1,3,1,2,1,2},
    {0,0,0,1,0,0,2,0,3,3,3,0,1,2,2,1,0,0,3,2,2,1},
    {0,0,0,0,1,1,3,3,0,1,0,3,1,1,2,2,3,0,0,3,2,1}
};

/* Precomputed 1024 base codewords */
static uint8_t bw[1024][22];
static int bwt[1024];

static void precomp(void) {
    for (int i = 0; i < 1024; i++) {
        memset(bw[i], 0, 22);
        int t = i;
        for (int r = 0; r < 5; r++) {
            uint8_t c = t%4; t/=4;
            if (c) for (int j = 0; j < 22; j++)
                bw[i][j] = A[bw[i][j]][M[c][base[r][j]]];
        }
        int w = 0;
        for (int j = 0; j < 22; j++) if (bw[i][j]) w++;
        bwt[i] = w;
    }
}

/* Full unified check: all 4095 codewords of [22,6,?] 
 * Returns: dmin of the full 6-dimensional code
 * Also sets *a12 = number of weight-12 codewords */
static int full_check(const uint8_t *row6, int *a12) {
    int dmin = 23;
    int cnt12 = 0;
    
    /* Base codewords (a6=0): already precomputed, skip idx=0 */
    for (int i = 1; i < 1024; i++) {
        if (bwt[i] < dmin) dmin = bwt[i];
    }
    
    /* New codewords (a6 = 1, 2, 3) */
    for (int a6 = 1; a6 < 4; a6++) {
        uint8_t sr[22];
        for (int j = 0; j < 22; j++) sr[j] = M[a6][row6[j]];
        
        for (int bi = 0; bi < 1024; bi++) {
            int w = 0;
            for (int j = 0; j < 22; j++)
                if (A[bw[bi][j]][sr[j]]) w++;
            if (w < dmin) dmin = w;
            if (w == 12) cnt12++;
            if (dmin < 10) { *a12 = 99999; return dmin; } /* hopeless abort */
        }
    }
    
    /* Also count base w=12 */
    for (int i = 1; i < 1024; i++) if (bwt[i] == 12) cnt12++;
    
    *a12 = cnt12;
    return dmin;
}

/* Rank check: does adding row6 give rank 6? */
static int rk6(const uint8_t *r6) {
    uint8_t m[6][22];
    for (int i = 0; i < 5; i++) memcpy(m[i], base[i], 22);
    memcpy(m[5], r6, 22);
    
    int rk = 0;
    for (int c = 0; c < 22 && rk < 6; c++) {
        int pr = -1;
        for (int r = rk; r < 6; r++) if (m[r][c]) { pr = r; break; }
        if (pr < 0) continue;
        if (pr != rk) { uint8_t t[22]; memcpy(t,m[rk],22); memcpy(m[rk],m[pr],22); memcpy(m[pr],t,22); }
        uint8_t inv = 0;
        for (uint8_t x = 1; x < 4; x++) if (M[m[rk][c]][x]==1) { inv=x; break; }
        for (int j = 0; j < 22; j++) m[rk][j] = M[m[rk][j]][inv];
        for (int r = 0; r < 6; r++) {
            if (r == rk) continue;
            uint8_t f = m[r][c];
            if (f) for (int j = 0; j < 22; j++)
                m[r][j] = A[m[r][j]][M[f][m[rk][j]]];
        }
        rk++;
    }
    return rk == 6;
}

int main() {
    struct timespec ts0, ts_now;
    clock_gettime(CLOCK_MONOTONIC, &ts0);
    srand(12345);
    
    precomp();
    
    /* Verify base */
    int bd = 99;
    for (int i = 1; i < 1024; i++) if (bwt[i] < bd) bd = bwt[i];
    fprintf(stderr, "Base d=%d\n", bd);
    
    /* Best result tracking */
    uint8_t best_pua[22] = {0};
    int best_dmin = 0;
    int best_a12 = 999999;
    long total_evals = 0;
    
    /* SA state */
    uint8_t curr[22];
    int curr_dmin, curr_a12;
    
    /* Initialize: random row6 with rank 6 */
    do { for (int j = 0; j < 22; j++) curr[j] = rand()%4; } while (!rk6(curr));
    curr_dmin = full_check(curr, &curr_a12);
    total_evals++;
    best_dmin = curr_dmin;
    best_a12 = curr_a12;
    memcpy(best_pua, curr, 22);
    
    /* Multi-restart SA loop with 60s hard cutoff */
    int restart = 0;
    for (;;) {
        /* Time check */
        clock_gettime(CLOCK_MONOTONIC, &ts_now);
        double elapsed = (ts_now.tv_sec - ts0.tv_sec) + (ts_now.tv_nsec - ts0.tv_nsec)/1e9;
        if (elapsed > 58.0) break;
        
        /* New random start every 500K iterations or first time */
        if (restart > 0) {
            do { for (int j = 0; j < 22; j++) curr[j] = rand()%4; } while (!rk6(curr));
            curr_dmin = full_check(curr, &curr_a12);
            total_evals++;
        }
        restart++;
        
        for (long it = 0; it < 200000; it++) {
            /* Time check every 1000 iterations */
            if (it % 1000 == 0) {
                clock_gettime(CLOCK_MONOTONIC, &ts_now);
                double el = (ts_now.tv_sec - ts0.tv_sec) + (ts_now.tv_nsec - ts0.tv_nsec)/1e9;
                if (el > 58.0) goto done;
            }
            
            /* Mutate 1 position */
            int pos = rand() % 22;
            uint8_t old = curr[pos];
            uint8_t nv = (old + 1 + rand()%3) % 4;
            curr[pos] = nv;
            
            if (!rk6(curr)) { curr[pos] = old; continue; }
            
            int a12;
            int dm = full_check(curr, &a12);
            total_evals++;
            
            /* Accept if better (prefer higher dmin, then lower a12) */
            int accept = 0;
            if (dm > curr_dmin) accept = 1;
            else if (dm == curr_dmin && a12 < curr_a12) accept = 1;
            else if (dm == curr_dmin && a12 == curr_a12) accept = (rand()%2);
            else {
                /* SA: accept worse with decreasing prob */
                double temp = 1.5 * (1.0 - (double)it / 200000.0);
                if (dm >= curr_dmin - 1 && temp > 0.01 && (rand()%100) < (int)(30*temp))
                    accept = 1;
            }
            
            if (accept) {
                curr_dmin = dm;
                curr_a12 = a12;
                
                /* Global best? */
                if (dm > best_dmin || (dm == best_dmin && a12 < best_a12)) {
                    best_dmin = dm;
                    best_a12 = a12;
                    memcpy(best_pua, curr, 22);
                    
                    if (dm >= 13) {
                        fprintf(stderr, "*** EUREKA at eval %ld ***\n", total_evals);
                        goto done;
                    }
                }
            } else {
                curr[pos] = old;
            }
        }
    }
    
done:
    /* ===== FINAL DUMP ===== */
    clock_gettime(CLOCK_MONOTONIC, &ts_now);
    double total_time = (ts_now.tv_sec - ts0.tv_sec) + (ts_now.tv_nsec - ts0.tv_nsec)/1e9;
    
    /* Recompute final answer cleanly */
    int fa12;
    int fdmin = full_check(best_pua, &fa12);
    
    printf("========================================\n");
    if (fdmin >= 13) {
        printf("=    ¡¡¡ E U R E K A !!!              =\n");
        printf("=    [22, 6, %d]_4 FOUND               =\n", fdmin);
    } else {
        printf("=  BEST: [22, 6, %d]_4                 =\n", fdmin);
        printf("=  A_12 = %d                           =\n", fa12);
    }
    printf("========================================\n");
    printf("Evals: %ld | Restarts: %d | Time: %.1fs\n\n", total_evals, restart, total_time);
    
    printf("Generator (0=0,1=1,2=w,3=w²):\n");
    for (int r = 0; r < 5; r++) {
        printf("  ");
        for (int c = 0; c < 22; c++) printf("%d", base[r][c]);
        printf("  [base]\n");
    }
    printf("  ");
    for (int c = 0; c < 22; c++) printf("%d", best_pua[c]);
    printf("  [PÚA]\n");
    
    /* Full weight distribution */
    printf("\nWeight distribution of [22,6,%d]_4:\n", fdmin);
    int aw[23] = {0};
    for (int idx = 1; idx < 4096; idx++) {
        uint8_t cw[22] = {0};
        int t = idx;
        for (int r = 0; r < 5; r++) {
            uint8_t c = t%4; t/=4;
            if (c) for (int j = 0; j < 22; j++)
                cw[j] = A[cw[j]][M[c][base[r][j]]];
        }
        uint8_t c6 = t%4;
        if (c6) for (int j = 0; j < 22; j++)
            cw[j] = A[cw[j]][M[c6][best_pua[j]]];
        int w = 0;
        for (int j = 0; j < 22; j++) if (cw[j]) w++;
        aw[w]++;
    }
    for (int w = 0; w <= 22; w++)
        if (aw[w]) printf("  A_%d = %d\n", w, aw[w]);
    
    return 0;
}
