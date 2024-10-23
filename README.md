# Cryptanalysis of AES: Yoyo and Boomerang Attacks (C Implementation)

## Description:
This project provides C-based implementations of cryptanalytic attacks on the Advanced Encryption Standard (AES), focusing on two methods: the Yoyo attack and the Boomerang attack. These techniques exploit weaknesses in reduced-round AES to recover secret keys and distinguish AES from random permutations.

---

## Features:
- **Yoyo Attack** on 3- to 5-round AES: Implements key-independent distinguishers and key-recovery attacks with low computational complexity.
- **Boomerang Attack** on 6-round AES: Combines two short high-probability differentials into an effective distinguisher.

---

## Prerequisites:
- C compiler (e.g., GCC)
- Basic understanding of AES encryption
- Familiarity with cryptographic attacks

---

## How to Run:

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/cryptanalysis-of-aes.git

2. Navigate to the project directory:
   ```bash
   cd cryptanalysis-of-aes
3. Compile the project:
   ```bash
   gcc -o cryptanalysis main.c yoyo_attack.c boomerang_attack.c aes.c
4. Run the executable:
   ```bash
   ./cryptanalysis

---

## References:
1. Yoyo Tricks with AES by Sondre Rønjom et al.
2. Improved Boomerang Attacks on 6-Round AES by Augustin Bariant et al.

---
