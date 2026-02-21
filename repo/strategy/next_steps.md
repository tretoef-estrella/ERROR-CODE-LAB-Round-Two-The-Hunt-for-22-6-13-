# Next Steps — Open Attack Vectors

*Updated after Round Two, 21 February 2026*

## Status: The Gap Remains Open

d₄(22, 6) ∈ {12, 13}. After ~60 million evaluations across 14+ routes, d=12 is the best achieved. The conjecture is d₄(22, 6) = 12, but no proof exists.

## Priority 1: Definitive Resolution via SAT/ILP

**Goal:** Encode the existence of [22, 6, 13]₄ as a finite constraint satisfaction problem.

- 96 variables (6×16 parity matrix entries, each in {0,1,2,3})
- 4,095 constraints (each nonzero codeword must have weight ≥ 13)
- Modern SAT solvers (Kissat, CaDiCaL) or CSP solvers (Minion, Chuffed) could resolve this

**Why this is decisive:** SAT gives UNSAT (proof of non-existence) or SAT (the matrix). No ambiguity.

## Priority 2: Multi-Fuselage Púa Campaign

**Goal:** Test 100+ different [22, 5, 13]₄ bases with intensive SA per base.

The V-FINAL-1 result (A₁₂=78) used one specific base. Different bases have different weight-12 "trap directions." A base with fewer traps may admit a Púa with A₁₂=0.

**Concrete plan:**
1. Hill-climb for 100 distinct [22, 5, 13]₄ bases
2. For each, count the number of projective directions producing weight-12 words
3. Select the 10 bases with fewest trap directions
4. Run 10 minutes of SA per base (vs 58 seconds in V-FINAL-1)

## Priority 3: Algebraic Construction from Scratch

All previous approaches started from known code families. The "Portrait Robot" says [22,6,13]₄ (if it exists) is asymmetric and unstructured. Candidates:

- **AG codes** from Hermitian curve y⁴+y=x⁵ over GF(16), restricted to GF(4)
- **Z₄-linear codes** mapped to GF(4) via Gray/Lee map (Gemini's Crack 9)
- **Codes from strongly regular graphs** with appropriate parameters

## Priority 4: Extended Condensation

Gemini killed the scalar condensation approach, but there are non-linear condensation operations:

- Coordinate i ← f(coord_i, coord_j) for arbitrary functions f: GF(4)² → GF(4)
- There are 4^16 = ~4 billion such functions, but most are equivalent
- Up to GF(4)* symmetry, this reduces to a manageable search

## Priority 5: Formal Proof of Non-Existence

If d₄(22,6) = 12, a formal proof would be a significant contribution. Possible approaches:

- Weight enumerator constraints beyond LP bounds (Schrijver-type SDP)
- Matroid obstruction arguments
- Exhaustive computation (if SAT/ILP approach succeeds in proving UNSAT)

## Closed Routes (Do Not Revisit)

All routes documented in [`results/gf4/round_two_report.md`](../results/gf4/round_two_report.md) Section 10.

---

*Proyecto Estrella — Error Code Lab, February 2026*
