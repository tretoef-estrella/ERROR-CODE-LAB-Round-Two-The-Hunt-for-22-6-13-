# Guide for Everyone

### What is this project and why should you care?

*Written for humans, not mathematicians.*

---

## The 30-Second Version

Every time you send a text, stream a video, or download a file, **error-correcting codes** protect your data from corruption. These codes are sequences of numbers designed so that even if some get damaged in transit, the original message can be recovered.

For 25 years, mathematicians have wondered: **can we build a specific code called [22, 6, 13]₄ that would offer better protection?** Nobody has built it. Nobody has proved it's impossible.

We — one human and four AI systems — spent 48+ hours and checked **60 million possibilities** trying to answer this question. We didn't find the code, but we created **the most detailed map of where it isn't** that has ever existed.

---

## The Metaphor: Babies and Bodyguards

Imagine you need to transport **6 babies** (your precious data) through dangerous territory. You hire **22 bodyguards** (code symbols) to protect them.

The **minimum distance** (d) is how many bodyguards an enemy must take out simultaneously to reach the babies:

- **d = 12** means the enemy needs to eliminate 12 bodyguards at once to cause harm. That's pretty good.
- **d = 13** means 13 bodyguards must fall simultaneously. That's even better — and it's what we're trying to achieve.

For 25 years, every formation of 22 bodyguards that mathematicians have tried leaves at least one angle where 12 can be taken out. We've now tried **60 million formations**. They all have the same weakness.

### La Púa del Jet (The Jet's Spike)

Our breakthrough strategy was inspired by a supersonic jet. These jets have a spike at their nose that creates a shockwave, clearing the air ahead so the body of the jet doesn't get crushed.

We applied this idea: instead of building the entire formation from scratch, we **froze 5 perfect rows** (the jet body) and searched for a **6th row** (the spike) that would "clear" the vulnerabilities. We tested 1.5 million spike candidates. The best one still had 78 weak angles. Close — but not zero.

---

## What We Actually Did

### The Team

| Who | Role |
|---|---|
| **Rafa** (human) | Strategy, creative metaphors, quality control |
| **Claude** (Anthropic) | Computation engine, C code, exhaustive searches |
| **Gemini** (Google) | Mathematical theory, algebraic ideas |
| **ChatGPT** (OpenAI) | Algebraic proofs, algorithm design |
| **Grok** (xAI) | Literature review, statistical assessment |

### The Numbers

- **60 million** code evaluations (like checking 60 million lock combinations)
- **14+** different methods tried (algebraic, random, structured, hybrid...)
- **48+ hours** of continuous work across 8 sessions
- **5 mathematical theorems proved** (things we can now say are definitely impossible)
- **0** codes with d=13 found

### What We Proved Is Impossible

We didn't just fail to find d=13 — we proved that several specific approaches **can never work**:

1. You can't get d=13 by taking a slice of the QR(29) code
2. You can't get d=13 by shortening the [23,6,13] code at any position
3. You can't get d=13 by shortening the [24,7,13] code at any position
4. You can't get d=13 using quasi-twisted codes with matching polynomials
5. The [22,7,13] code doesn't exist at all (one-step mathematical proof)

---

## Why This Matters

### For science
This is the most thorough investigation of this specific problem in 25 years. Future researchers start from our map, not from zero.

### For AI research
This is one of the first demonstrations of **distributed AI collaboration** on a genuine open mathematical problem — not a toy example, but a real unsolved question that has resisted human efforts for a quarter century.

### For the philosophy of knowledge
We didn't solve the problem. But we advanced human understanding. Sometimes science is about mapping the darkness, not finding the light.

---

## How to Read This Repository

| If you want... | Read this |
|---|---|
| The full technical story | [`results/gf4/round_two_report.md`](results/gf4/round_two_report.md) |
| What changed since Phase 2 | [`CHANGELOG.md`](CHANGELOG.md) |
| To help us find the code | [`docs/contributing.md`](docs/contributing.md) |
| The best matrix we found | [`results/gf4/round_two_report.md`](results/gf4/round_two_report.md) §6 |
| The original Phase 2 report | [`results/gf4/phase2_final_report.md`](results/gf4/phase2_final_report.md) |

---

## Glossary

| Term | Meaning |
|---|---|
| **GF(4)** | A number system with only 4 elements: {0, 1, ω, ω²}. Like normal arithmetic but everything wraps around. |
| **[22, 6, 13]₄** | A code with 22 symbols, 6 dimensions (can encode 4⁶ = 4096 messages), and minimum distance 13 (can survive 12 errors). Over GF(4). |
| **Minimum distance (d)** | The smallest number of positions where any two different codewords differ. Higher = more error protection. |
| **Griesmer bound** | A mathematical limit on how good a code can be. Says d ≤ 13 for our parameters. |
| **Generator matrix** | A compact representation of a code — 6 rows of 22 symbols that generate all 4,096 codewords through linear combinations. |
| **La Púa** | "The Spike" — the 6th row added to a 5-row base, designed to maintain high minimum distance. |
| **A₁₂** | The number of codewords with weight exactly 12. We want this to be zero (meaning d ≥ 13). |

---

*Proyecto Estrella — "Build bridges, not walls."*
