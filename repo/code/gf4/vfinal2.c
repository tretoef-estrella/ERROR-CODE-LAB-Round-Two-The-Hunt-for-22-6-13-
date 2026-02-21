/*
 * LA PÚA DEL JET — V-FINAL-2 (Multi-Base Attack)
 * Try different [22,5,13+] bases. For each, SA for row 6.
 * 60s hard cutoff total.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

static const uint8_t AT[4][4] = {{0,1,2,3},{1,0,3,2},{2,3,0,1},{3,2,1,0}};
static const uint8_t MT[4][4] = {{0,0,0,0},{0,1,2,3},{0,2,3,1},{0,3,1,2}};

static uint8_t base[5][22];
static uint8_t bw[1024][22];
static int bwt[1024];

static void precomp(void) {
    for (int i = 0; i < 1024; i++) {
        memset(bw[i], 0, 22);
        int t = i;
        for (int r = 0; r < 5; r++) {
            uint8_t c = t%4; t/=4;
            if (c) for (int j = 0; j < 22; j++)
                bw[i][j] = AT[bw[i][j]][MT[c][base[r][j]]];
        }
        int w = 0;
        for (int j = 0; j < 22; j++) if (bw[i][j]) w++;
        bwt[i] = w;
    }
}

static int base_dmin(void) {
    int d = 99;
    for (int i = 1; i < 1024; i++) if (bwt[i] < d) d = bwt[i];
    return d;
}

static int full_check(const uint8_t *row6, int *a12) {
    int dmin = 23, cnt = 0;
    for (int i = 1; i < 1024; i++) { if (bwt[i] < dmin) dmin = bwt[i]; }
    for (int a6 = 1; a6 < 4; a6++) {
        uint8_t sr[22];
        for (int j = 0; j < 22; j++) sr[j] = MT[a6][row6[j]];
        for (int bi = 0; bi < 1024; bi++) {
            int w = 0;
            for (int j = 0; j < 22; j++) if (AT[bw[bi][j]][sr[j]]) w++;
            if (w < dmin) dmin = w;
            if (w == 12) cnt++;
            if (dmin < 10) { *a12 = 99999; return dmin; }
        }
    }
    for (int i = 1; i < 1024; i++) if (bwt[i] == 12) cnt++;
    *a12 = cnt;
    return dmin;
}

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
        for (uint8_t x = 1; x < 4; x++) if (MT[m[rk][c]][x]==1) { inv=x; break; }
        for (int j = 0; j < 22; j++) m[rk][j] = MT[m[rk][j]][inv];
        for (int r = 0; r < 6; r++) {
            if (r == rk) continue;
            uint8_t f = m[r][c];
            if (f) for (int j = 0; j < 22; j++)
                m[r][j] = AT[m[r][j]][MT[f][m[rk][j]]];
        }
        rk++;
    }
    return rk == 6;
}

/* Build random [22,5,>=13] by hill-climbing */
static int build_base(unsigned int seed) {
    srand(seed);
    int best_d = 0;
    uint8_t best[5][22];
    
    for (int att = 0; att < 50000; att++) {
        uint8_t g[5][22];
        memset(g, 0, sizeof(g));
        for (int r = 0; r < 5; r++) {
            g[r][r] = 1;
            for (int c = 5; c < 22; c++) g[r][c] = rand()%4;
        }
        
        /* Quick check via sampling: compute a few codewords */
        memcpy(base, g, sizeof(g));
        precomp();
        int d = base_dmin();
        
        /* Hill climb */
        for (int hc = 0; hc < 3000 && d < 14; hc++) {
            int r = rand()%5, c = 5+rand()%17;
            uint8_t old = g[r][c];
            g[r][c] = (old+1+rand()%3)%4;
            memcpy(base, g, sizeof(g));
            precomp();
            int nd = base_dmin();
            if (nd >= d) { d = nd; } else { g[r][c] = old; }
            if (d >= 14) break;
        }
        
        if (d > best_d) {
            best_d = d;
            memcpy(best, g, sizeof(g));
            if (d >= 13) break;
        }
    }
    
    memcpy(base, best, sizeof(best));
    precomp();
    return best_d;
}

static double now_sec(struct timespec *t0) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (t.tv_sec - t0->tv_sec) + (t.tv_nsec - t0->tv_nsec)/1e9;
}

int main() {
    struct timespec t0;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    
    /* Global best */
    uint8_t gbest_base[5][22];
    uint8_t gbest_pua[22];
    int gbest_dmin = 0, gbest_a12 = 999999;
    long total_evals = 0;
    int bases_tried = 0;
    
    /* Try multiple bases with different seeds */
    unsigned int seeds[] = {42, 137, 271, 314, 577, 691, 853, 997, 1123, 1291,
                            1447, 1597, 1741, 1889, 2003, 2111, 2237, 2399, 2521, 2657};
    int nseeds = 20;
    
    for (int si = 0; si < nseeds; si++) {
        if (now_sec(&t0) > 55.0) break;
        
        int bd = build_base(seeds[si]);
        if (bd < 13) continue;
        bases_tried++;
        
        /* Count base A_12 */
        int base_a12 = 0;
        for (int i = 1; i < 1024; i++) if (bwt[i] == 12) base_a12++;
        
        /* SA for La Púa on this base */
        uint8_t curr[22], best_pua[22];
        int best_dmin_here = 0, best_a12_here = 999999;
        
        /* Init */
        srand(seeds[si] * 31 + 7);
        do { for (int j = 0; j < 22; j++) curr[j] = rand()%4; } while (!rk6(curr));
        int ca12;
        int cdm = full_check(curr, &ca12);
        total_evals++;
        best_dmin_here = cdm;
        best_a12_here = ca12;
        memcpy(best_pua, curr, 22);
        
        double time_per_base = (si < 3) ? 12.0 : 4.0; /* More time for first bases */
        double base_start = now_sec(&t0);
        
        for (int rs = 0; rs < 20; rs++) {
            if (now_sec(&t0) > 55.0) break;
            if (now_sec(&t0) - base_start > time_per_base) break;
            
            if (rs > 0) {
                do { for (int j = 0; j < 22; j++) curr[j] = rand()%4; } while (!rk6(curr));
                cdm = full_check(curr, &ca12);
                total_evals++;
            }
            
            for (long it = 0; it < 100000; it++) {
                if (it % 500 == 0 && now_sec(&t0) > 55.0) goto next_base;
                
                int pos = rand()%22;
                uint8_t old = curr[pos];
                curr[pos] = (old+1+rand()%3)%4;
                if (!rk6(curr)) { curr[pos] = old; continue; }
                
                int a12;
                int dm = full_check(curr, &a12);
                total_evals++;
                
                int accept = 0;
                if (dm > cdm) accept = 1;
                else if (dm == cdm && a12 < ca12) accept = 1;
                else if (dm == cdm && a12 == ca12) accept = (rand()%2);
                else {
                    double temp = 1.5 * (1.0 - (double)it/100000.0);
                    if (dm >= cdm-1 && temp > 0.01 && (rand()%100) < (int)(25*temp))
                        accept = 1;
                }
                
                if (accept) {
                    cdm = dm; ca12 = a12;
                    if (dm > best_dmin_here || (dm == best_dmin_here && a12 < best_a12_here)) {
                        best_dmin_here = dm;
                        best_a12_here = a12;
                        memcpy(best_pua, curr, 22);
                        if (dm >= 13) goto eureka;
                    }
                } else { curr[pos] = old; }
            }
        }
        
        next_base:
        /* Update global best */
        if (best_dmin_here > gbest_dmin || 
            (best_dmin_here == gbest_dmin && best_a12_here < gbest_a12)) {
            gbest_dmin = best_dmin_here;
            gbest_a12 = best_a12_here;
            memcpy(gbest_base, base, sizeof(base));
            memcpy(gbest_pua, best_pua, 22);
        }
        
        fprintf(stderr, "[%.0fs] Base #%d (seed=%u): bd=%d, best d=%d A12=%d\n",
                now_sec(&t0), bases_tried, seeds[si], bd, best_dmin_here, best_a12_here);
        continue;
        
        eureka:
        gbest_dmin = best_dmin_here;
        gbest_a12 = best_a12_here;
        memcpy(gbest_base, base, sizeof(base));
        memcpy(gbest_pua, best_pua, 22);
        fprintf(stderr, "*** EUREKA ***\n");
        goto done;
    }
    
done:;
    double total_time = now_sec(&t0);
    
    /* Reload best base for final verification */
    memcpy(base, gbest_base, sizeof(base));
    precomp();
    int fa12;
    int fdmin = full_check(gbest_pua, &fa12);
    
    printf("========================================\n");
    if (fdmin >= 13)
        printf("=    ¡¡¡ E U R E K A !!!              =\n=    [22, 6, %d]_4 FOUND               =\n", fdmin);
    else
        printf("=  BEST: [22, 6, %d]_4                 =\n=  A_12 = %d                           =\n", fdmin, fa12);
    printf("========================================\n");
    printf("Bases tried: %d | Evals: %ld | Time: %.1fs\n\n", bases_tried, total_evals, total_time);
    
    printf("Generator (0=0,1=1,2=w,3=w²):\n");
    for (int r = 0; r < 5; r++) {
        printf("  ");
        for (int c = 0; c < 22; c++) printf("%d", gbest_base[r][c]);
        printf("  [base]\n");
    }
    printf("  ");
    for (int c = 0; c < 22; c++) printf("%d", gbest_pua[c]);
    printf("  [PÚA]\n");
    
    /* Weight distribution */
    printf("\nWeight distribution:\n");
    int aw[23] = {0};
    for (int idx = 1; idx < 4096; idx++) {
        uint8_t cw[22] = {0};
        int t = idx;
        for (int r = 0; r < 5; r++) {
            uint8_t c = t%4; t/=4;
            if (c) for (int j = 0; j < 22; j++)
                cw[j] = AT[cw[j]][MT[c][gbest_base[r][j]]];
        }
        uint8_t c6 = t%4;
        if (c6) for (int j = 0; j < 22; j++)
            cw[j] = AT[cw[j]][MT[c6][gbest_pua[j]]];
        int w = 0;
        for (int j = 0; j < 22; j++) if (cw[j]) w++;
        aw[w]++;
    }
    for (int w = 0; w <= 22; w++)
        if (aw[w]) printf("  A_%d = %d\n", w, aw[w]);
    
    return 0;
}
