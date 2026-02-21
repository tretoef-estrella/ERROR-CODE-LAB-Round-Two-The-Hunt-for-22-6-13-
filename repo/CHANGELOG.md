# Changelog

## Round Two — 21 February 2026

### New Routes Eliminated

- **QT Hybrid f₁/f₂ (Conjugate Polynomials):** 46,126,047 rank-6 codes exhaustively searched across all 11 twist shifts. d_max = 12. This was the highest-priority unexplored route from Phase 2 — the only algebraic structure where no theoretical ceiling blocked d=13. Now closed.
- **Constacyclic QT (λ = ω, ω²):** 8,380,000 codes evaluated with both non-trivial lambda values. d_max = 12. Closed.

### New Methodology: La Púa del Jet

- Developed the "freeze base + search sixth row" extension attack strategy
- Built three C engines (V-FINAL-1, V-FINAL-2, V-FINAL-3) with 60-second hard cutoffs
- V-FINAL-1 achieved the campaign's best result: [22, 6, 12]₄ with A₁₂ = 78

### New Code Constructed

- **[22, 5, 13]₄** built by hill-climbing (2,401 attempts, 57 seconds). First known construction by this method.

### New Diagnostic Data

- Full weight distribution of best [22, 6, 12]₄ code
- Collision origin analysis: all 78 weight-12 words involve La Púa (g₆), base is clean
- 26+26+26 symmetry across GF(4) scalars (Collision Symmetry Theorem)
- Coordinate vulnerability map: all 22 coordinates covered, no puncture escape
- Complete coefficient vectors for all 78 weight-12 codewords

### New Theoretical Results

- **Collision Symmetry Theorem:** For any [22, 5, d≥13]₄ base, weight-12 collisions from a sixth row are always ≡ 0 (mod 3)
- Gemini killed Crack 5 (Trace GF(16)→GF(4)) and Crack 8 (condensation with non-trivial scalars) on theoretical grounds

### Infrastructure Improvements

- Anti-crash protocol ("Protocolo de Reinicio Táctico") for multi-session continuity
- "Silencio de Radio" — minimal logging in C engines to prevent timeout
- 60-second hard cutoff with emergency matrix dump
- Human quality control intervention (abort V-FINAL-3, demand transparency)

### Scale Update

| Metric | Phase 2 | Round Two | Combined |
|---|---|---|---|
| Routes eliminated | 12 | 2 + La Púa | 14+ |
| Evaluations | ~2M | ~58M | **~60M** |
| Best A₁₂ | (not tracked) | 78 | **78** |
| AI sessions | 4 systems × 1 | Claude × 4 | 8+ total |
| C engines built | 0 | 3 | 3 |

---

## Phase 2 — 20-21 February 2026

Initial 48-hour campaign. 12 routes eliminated. ~2M evaluations. 5 impossibility theorems proved. See [`results/gf4/phase2_final_report.md`](results/gf4/phase2_final_report.md).

## Phase 1 — 19-20 February 2026

GF(2) and GF(3) campaigns. Construction XX mastered. BCH and Belov codes constructed. See the [original repository](https://github.com/tretoef-estrella/ERROR-CODE-LAB).
