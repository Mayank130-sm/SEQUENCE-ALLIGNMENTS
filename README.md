# DNA Sequence Alignment Tool

A C++ implementation of the **Needleman-Wunsch (Global)** and **Smith-Waterman (Local)** alignment algorithms using dynamic programming.

## 🧬 Overview

This tool identifies the similarity between two DNA sequences. It calculates an optimal alignment score based on user-defined parameters for matches, mismatches, and gaps, then performs a traceback to visualize the alignment.

---

## 🧪 Algorithms Explained

### 1. Global Alignment (Needleman-Wunsch)
The Global Alignment algorithm attempts to align every character in both sequences from start to finish. It is best used for sequences of similar length that are expected to be related across their entire span.

* **Initialization:** The first row and column represent alignment against gaps, initialized as `index * gap_penalty`.
* **Traceback:** Starts at the very bottom-right of the matrix and moves to the top-left.



### 2. Local Alignment (Smith-Waterman)
The Local Alignment algorithm finds the most similar "sub-region" between two sequences. It ignores areas of high divergence and focuses on highly conserved motifs.

* **Logic:** If a score becomes negative, it is reset to **0**. This allows the alignment to "restart" anywhere in the sequence.
* **Initialization:** The first row and column are initialized to 0.
* **Traceback:** Starts at the **highest value** found anywhere in the matrix and ends when it hits a cell with a value of 0.

---

## 📊 Scoring System

The program calculates the score for each cell $(i, j)$ using the following logic:

| Move | Source Cell | Calculation |
| :--- | :--- | :--- |
| **Diagonal** | $(i-1, j-1)$ | $Score = Prev + (Match \text{ or } Mismatch)$ |
| **Up (Gap)** | $(i-1, j)$ | $Score = Prev + Gap Penalty$ |
| **Left (Gap)** | $(i, j-1)$ | $Score = Prev + Gap Penalty$ |

For **Global**, the cell takes the maximum of these three.  
For **Local**, the cell takes the maximum of these three **OR** zero.

---

## 🚀 Getting Started

### Prerequisites
* A C++ compiler (GCC/Clang/MSVC).

### Compilation
Use the following command to compile the code:
```bash
g++ -o alignment_tool main.cpp
