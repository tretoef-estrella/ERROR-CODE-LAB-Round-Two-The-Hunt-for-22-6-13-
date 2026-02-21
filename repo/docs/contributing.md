# How to Contribute

## The Problem Is Still Open

The code [22, 6, 13]₄ has not been found and has not been proved impossible. If you have ideas, computation, or mathematical insight, we want to hear from you.

## Three Highest-Priority Tasks

### 1. SAT/ILP Formulation (Definitive Resolution)

Encode the existence of [22, 6, 13]₄ as a satisfiability or integer linear programming problem:

- **Variables:** 96 entries of the parity matrix P (6×16 over GF(4) in systematic form)
- **Constraints:** All 4,095 nonzero codewords have Hamming weight ≥ 13
- **Tools:** Kissat, CaDiCaL, CPLEX, Gurobi, Minion, Chuffed

If UNSAT → computer-assisted proof of non-existence. If SAT → the solver gives us the matrix.

**Estimated difficulty:** Medium. The constraint space is large but structured.

### 2. Different Fuselages

Our best result used ONE specific [22, 5, 13]₄ base. Different bases have different weight distributions and different "holes" in the Hamming space.

- Construct 100+ different [22, 5, 13]₄ or [22, 5, 14]₄ bases
- For each, run intensive simulated annealing for the sixth row (La Púa)
- The base with the fewest weight-12 "trap directions" is most likely to admit d=13

### 3. Non-Standard Constructions

All our approaches started from known code families. The "Portrait Robot" tells us: if [22,6,13]₄ exists, it is asymmetric and unrelated to QR, BCH, QC, or QT families. Try:

- Algebraic geometry codes (Hermitian curves over GF(16))
- Z₄-linear codes via Gray/Lee map to GF(4)
- Codes from association schemes or strongly regular graphs

## What NOT to Do

These routes are exhausted. Please don't repeat them:

- QR(29) subcodes, puncturing [23,6,13] or [24,7,13], Construction X from [21,5,13]
- Random row extension from [22,5,14], condensation [23→22], random dual search
- Trace GF(16)→GF(4), additive GF(2)-linear, random/QC hill-climbing
- QT with common factor, QT hybrid f₁/f₂ (46M exhaustive), constacyclic λ=ω,ω²

## Assets Available

The [`results/gf4/round_two_report.md`](results/gf4/round_two_report.md) contains:
- The best known [22, 6, 12]₄ generator matrix (copy-paste ready)
- The clean [22, 5, 13]₄ base
- All 78 weight-12 coefficient vectors
- Coordinate vulnerability map
- GF(4) arithmetic tables

The `code/gf4/` directory contains C engines you can compile and modify.

## How to Submit

- **Open an Issue** with your approach and results
- **Fork and PR** if you have code or proofs to add
- **Email** the Architect via the Proyecto Estrella GitHub profile

## Rules

- **Truth over courtesy.** If the code doesn't exist, prove it.
- **Be specific.** Concrete algorithms and constructions, not vague suggestions.
- **Verify your results.** A [22, 6] code over GF(4) has only 4,096 codewords — verification takes milliseconds.
- **Credit all contributors.** This is open science.

---

*Proyecto Estrella — "The machine surrenders to logic. The human invents ways to bend it. Together, they make magic."*
