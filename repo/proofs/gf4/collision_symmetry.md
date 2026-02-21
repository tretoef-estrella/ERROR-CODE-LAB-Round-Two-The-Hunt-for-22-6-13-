# Collision Symmetry Theorem

## Statement

**Theorem (Error Code Lab, Round Two, February 2026):** Let C₀ be a [22, 5, d₀]₄ code with d₀ ≥ 13, and let g₆ ∈ GF(4)²² be any vector not in the span of C₀ (so that C = ⟨C₀, g₆⟩ has dimension 6). Then the number of codewords in C with Hamming weight exactly 12 is divisible by 3.

More precisely: if we define A₁₂(a₆) as the number of codewords c₀ + a₆·g₆ (with c₀ ∈ C₀) having weight 12, then A₁₂(1) = A₁₂(ω) = A₁₂(ω²).

## Proof

The codewords of C with a₆ ≠ 0 partition into orbits under GF(4)* scalar multiplication of the a₆ component.

For any fixed coefficient vector (a₁, ..., a₅, 1), the codeword is:

c = a₁g₁ + ... + a₅g₅ + g₆

Its weight is wt(c). Now consider the codeword with the same base coefficients but a₆ = ω:

c' = a₁g₁ + ... + a₅g₅ + ωg₆ = (a₁g₁ + ... + a₅g₅ + g₆) + (ω-1)g₆ = c + ω²g₆

since ω - 1 = ω² in GF(4).

**Key observation:** The map φ: (a₁,...,a₅,a₆) → (a₁,...,a₅, ω·a₆) is a bijection on the set of coefficient vectors with a₆ ≠ 0. It permutes the set {a₆=1} → {a₆=ω} → {a₆=ω²} → {a₆=1}.

However, φ does NOT preserve weight in general. The weight of c' = c₀ + ωg₆ is different from wt(c₀ + g₆) at every coordinate j where g₆[j] ≠ 0.

**What IS true:** The three sets of codewords {c₀ + 1·g₆}, {c₀ + ω·g₆}, {c₀ + ω²·g₆} have the same SIZE (each has |C₀| = 4⁵ = 1024 elements). The question is whether the weight-12 counts are equal.

## Empirical Observation

In V-FINAL-1 (1,548,008 full evaluations with simulated annealing), the best Púa consistently produced exactly A₁₂(1) = A₁₂(ω) = A₁₂(ω²) = 26, giving total A₁₂ = 78.

This perfect symmetry was observed across ALL candidate sixth rows examined, not just the best one. When A₁₂ changed during SA, it always changed in multiples of 3.

## Structural Explanation

The symmetry arises because the base code C₀ is over GF(4), which has the property that scalar multiplication by ω permutes the nonzero elements {1, ω, ω²} cyclically. For a codeword c₀ + a₆g₆, the support (set of nonzero coordinates) depends on the interaction between c₀ and a₆g₆ at each coordinate. The GF(4) addition table is symmetric under the action of GF(4)*, meaning that the probability that c₀[j] + a₆g₆[j] = 0 is the same for a₆ = 1, ω, ω² when averaged over all c₀ ∈ C₀.

**Precise statement of the mechanism:** For a random c₀ drawn uniformly from C₀ and fixed g₆, the random variables wt(c₀ + g₆), wt(c₀ + ωg₆), wt(c₀ + ω²g₆) have the same distribution. This follows from the fact that multiplication by ω is an automorphism of (GF(4), +).

## Consequence

The minimum achievable A₁₂ is always 0 (mod 3). To reach d=13, we need A₁₂ = 0 exactly — a jump from 78 to 0. There is no "gradual descent" to 1 or 2 collisions; the symmetry forces a discrete jump.

## Status

This theorem was discovered empirically during Round Two and has a solid structural explanation. A fully rigorous proof requires showing that the weight distribution of {c₀ + αg₆ : c₀ ∈ C₀} is identical for all α ∈ GF(4)*, which follows from the GF(4)* action on the coordinate-wise nonzero patterns.

---

*Error Code Lab — Proyecto Estrella, February 2026*
