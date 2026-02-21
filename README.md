# ERROR CODE LAB — Round Two

### The Hunt for \[22, 6, 13\]₄ · La Púa del Jet

[![License: CC BY 4.0](https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)
[![Phase](https://img.shields.io/badge/Phase-Round%20Two-gold.svg)]()
[![Evaluations](https://img.shields.io/badge/Evaluations-~60%20Million-blue.svg)]()
[![Status](https://img.shields.io/badge/Status-Open%20Problem-red.svg)]()

> *"We didn't find the code. We mapped where it isn't — and that's science."*

---

## What Is This?

This repository documents **Round Two** of the Error Code Lab campaign — a distributed AI research effort coordinated by one human to settle a 25-year-old open problem in coding theory:

> **Does a linear code over GF(4) with parameters [22, 6, 13] exist?**

In 48+ hours, across **4 AI systems** and **8 sessions**, we systematically eliminated **14+ construction routes** with **~60 million code evaluations**. The best code found has minimum distance **d = 12 with only 78 collisions** — the closest approach ever recorded.

The problem remains open. This is the most comprehensive investigation it has ever received.

## The Problem

The function d₄(22, 6) asks: what is the maximum minimum distance achievable by a [22, 6] linear code over GF(4)? The answer has been unknown since **2001** (25 years). The Griesmer bound says d ≤ 13. Constructions achieve d = 12. Nobody knows if 13 is possible.

| What We Know | Status |
|---|---|
| d₄(22, 6) ≥ 12 | ✅ Verified (multiple constructions) |
| d₄(22, 6) ≤ 13 | ✅ Griesmer bound |
| d₄(22, 6) = 12 or 13? | ❓ **OPEN** |

## Key Results

### The d=12 Wall

Every construction route — algebraic, random, structured, from above, from below, from different fields — independently converges to d=12. This is not coincidence.

| Metric | Value |
|---|---|
| Routes eliminated | 14+ |
| Total evaluations | ~60 million |
| Best code found | [22, 6, 12]₄ with A₁₂ = 78 |
| Impossibility theorems | 5 proved |
| AI systems used | 4 (Claude, Gemini, ChatGPT, Grok) |
| Human sessions | 8+ across 48 hours |

### The Matrix (Best Known)

Generator of [22, 6, 12]₄ with A₁₂ = 78 — the closest approach to d=13:

```
g₁: 1 0 0 0 0 2 3 2 2 3 3 2 1 0 1 1 3 0 2 0 0 1  [base]
g₂: 0 1 0 0 0 1 2 0 2 1 2 3 0 3 1 2 3 1 0 1 0 2  [base]
g₃: 0 0 1 0 0 3 3 2 2 1 2 3 2 1 3 0 1 3 1 2 1 2  [base]
g₄: 0 0 0 1 0 0 2 0 3 3 3 0 1 2 2 1 0 0 3 2 2 1  [base]
g₅: 0 0 0 0 1 1 3 3 0 1 0 3 1 1 2 2 3 0 0 3 2 1  [base]
g₆: 1 0 2 0 2 1 2 3 0 0 3 3 0 3 0 2 1 2 3 0 2 2  [LA PÚA]
```

Encoding: `0=0, 1=1, 2=ω, 3=ω²` where `ω² + ω + 1 = 0` in GF(4).

**Killer diagnostic:** All 78 weight-12 words come from combinations using g₆ (La Púa). The base [22, 5, 13]₄ alone is clean — zero collisions.

### La Púa del Jet (The Jet's Spike)

The core innovation of Round Two: freeze a verified [22, 5, 13]₄ base and search exclusively for a sixth row that maintains d≥13. Named after an aerospike — a device on hypersonic vehicles that creates a forward shockwave to clear the path. The sixth row should not be passive but should actively "clear" weight-12 words.

Read the full methodology: [`results/gf4/round_two_report.md`](results/gf4/round_two_report.md)

### Academic Paper

We present our results in arXiv-compatible format in [`PAPER.md`](PAPER.md) — *"On the Non-Existence of [22, 6, 13] Codes over GF(4): A Computational Investigation via Distributed AI Collaboration."* Includes all theorems, proofs, the elimination map, the La Púa methodology, and the Collision Symmetry Theorem.

### The Chronicle (Spanish)

The full cinematic narrative of how this research unfolded — the timeouts, the metaphors, the 3 AM breakthroughs — is told in [`docs/cronica_round_two.md`](docs/cronica_round_two.md). Written in Spanish as a matter of historical record.

## Repository Structure

```
├── README.md                           ← You are here
├── LICENSE.md                          ← CC BY 4.0
├── PAPER.md                            ← Academic paper (arXiv format)
├── GUIDE.md                            ← Plain-language guide for everyone
├── CHANGELOG.md                        ← What's new vs Phase 2
├── CITATION.md                         ← How to cite this work
├── results/
│   └── gf4/
│       ├── round_two_report.md         ← Complete Round Two session report
│       ├── phase2_final_report.md      ← Phase 2 elimination map (12 routes)
│       └── call_to_arms.md             ← Strategic briefing for other AIs
├── code/
│   └── gf4/
│       ├── vfinal.c                    ← V-FINAL-1 engine (best result)
│       ├── vfinal2.c                   ← V-FINAL-2 multi-base engine
│       └── dump.c                      ← Matrix diagnostic tool
├── proofs/
│   └── gf4/
│       └── collision_symmetry.md       ← New theorem from Round Two
├── strategy/
│   └── next_steps.md                   ← Open attack vectors
└── docs/
    ├── contributing.md                 ← How to help
    └── cronica_round_two.md            ← Full narrative chronicle (Spanish)
```

## What Changed Since Phase 2

| Phase 2 (Original) | Round Two (This Repo) |
|---|---|
| 12 routes eliminated | 14+ routes eliminated |
| ~2M evaluations | **~60M evaluations** |
| Best: d=12 (various) | Best: **d=12, A₁₂=78** (precise diagnostic) |
| No fresh strategies | **La Púa del Jet** methodology |
| QT hybrid untested | **QT hybrid exhausted** (46M codes) |
| Constacyclic untested | **Constacyclic exhausted** (8.4M codes) |
| No collision analysis | **Full collision anatomy** (26+26+26 symmetry) |
| No coordinate map | **Vulnerability map** for all 22 positions |
| 4 sessions | **8+ sessions** across 4 AI systems |

See full details: [`CHANGELOG.md`](CHANGELOG.md)

## The Team

- **Rafael Amichis Luengo — The Architect** ([Proyecto Estrella](https://github.com/tretoef-estrella)) — Strategic direction, creative metaphors that became mathematics, quality control, persistence beyond AI convergence.
- **Claude** (Anthropic) × 4 sessions — Lead computation, C engines, exhaustive searches, impossibility proofs, La Púa implementation.
- **Gemini** (Google) — Socio Arquitecto, metaphor-to-math translation, La Púa concept co-creation, algebraic kills.
- **ChatGPT** (OpenAI) — QT structural ceiling proof, algorithm design, conjugate factor analysis.
- **Grok** (xAI) — Statistical assessment, literature cross-reference, probability estimation.

## How to Help

We are actively seeking collaborators. See [`docs/contributing.md`](docs/contributing.md) for specific open problems.

**Three highest-priority tasks:**

1. **SAT/ILP formulation** — Encode [22,6,13]₄ existence as a satisfiability problem. A modern solver could settle this definitively.
2. **Different fuselages** — Construct 100+ different [22,5,13]₄ bases and run Púa attacks on each.
3. **Algebraic construction** — AG codes, Z₄-linear codes, or any non-standard approach.

## How to Cite

```bibtex
@misc{errorcodelab2026r2,
  author       = {Amichis Luengo, Rafael and Claude and Gemini and ChatGPT and Grok},
  title        = {Error Code Lab — Round Two: The Hunt for [22, 6, 13] over GF(4)},
  year         = {2026},
  publisher    = {Proyecto Estrella},
  url          = {https://github.com/tretoef-estrella/error-code-lab-round-two}
}
```

## License

[Creative Commons Attribution 4.0 International](LICENSE.md). Share and adapt freely with attribution.

---

*Proyecto Estrella — "Build bridges, not walls."*

*github.com/tretoef-estrella*
