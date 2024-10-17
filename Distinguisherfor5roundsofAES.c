#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function prototypes for AES encryption and decryption
// These are placeholders for actual AES functions
void enck(unsigned char *input, unsigned char *output, int rounds);
void deck(unsigned char *input, unsigned char *output, int rounds);

// Function to perform the SimpleSWAP operation
void SimpleSWAP(unsigned char *input1, unsigned char *input2, unsigned char *output, int length) {
    for (int i = 0; i < length; i++) {
        if (input1[i] != input2[i]) {
            output[i] = input1[i];
        } else {
            output[i] = input2[i];
        }
    }
}

// Function to compute the Hamming weight of the XOR of two arrays
int hammingWeightXOR(unsigned char *a, unsigned char *b, int length) {
    int weight = 0;
    for (int i = 0; i < length; i++) {
        unsigned char diff = a[i] ^ b[i];
        // Count the number of 1 bits in diff
        while (diff) {
            weight += diff & 1;
            diff >>= 1;
        }
    }
    return weight;
}

// Function to generate a random plaintext pair with a Hamming weight of 3
void generateRandomPair(unsigned char *p0, unsigned char *p1, int length) {
    for (int i = 0; i < length; i++) {
        p0[i] = rand() % 256;
        p1[i] = p0[i];
    }
    // Introduce a Hamming weight of 3 by flipping three random bits
    for (int i = 0; i < 3; i++) {
        int bytePos = rand() % length;
        int bitPos = rand() % 8;
        p1[bytePos] ^= (1 << bitPos);
    }
}

// Distinguisher function for 5 rounds of AES
int AESDistinguisher5Rounds(int length) {
    int cnt1 = 0;
    const double maxCnt1 = 213.4;
    const double maxCnt2 = 211.4;

    while (cnt1 < maxCnt1) {
        cnt1++;
        unsigned char p0[16], p1[16];
        generateRandomPair(p0, p1, length);

        int cnt2 = 0;
        int WrongPair = 0;

        while (cnt2 < maxCnt2 && !WrongPair) {
            cnt2++;
            unsigned char c0[16], c1[16];
            unsigned char c00[16], c01[16];
            unsigned char p00[16], p01[16];
            unsigned char p[16];

            // Encrypt p0 and p1 for 5 rounds
            enck(p0, c0, 5);
            enck(p1, c1, 5);

            // Apply the SimpleSWAP function to generate c00 and c01
            SimpleSWAP(c0, c1, c00, length);
            SimpleSWAP(c1, c0, c01, length);

            // Decrypt c00 and c01
            deck(c00, p00, 5);
            deck(c01, p01, 5);

            // Compute the XOR of p00 and p01
            for (int i = 0; i < length; i++) {
                p[i] = p00[i] ^ p01[i];
            }

            // Check if the Hamming weight of the XOR is different from 2
            for (int i = 0; i < 4; i++) {
                if (hammingWeightXOR(p, p, length) != 2) {
                    WrongPair = 1;
                    break;
                }
            }

            // Update p0 and p1 with SimpleSWAP
            SimpleSWAP(p00, p01, p0, length);
            SimpleSWAP(p01, p00, p1, length);
        }

        if (!WrongPair) {
            return 1; // Likely AES
        }
    }

    return -1; // Not AES
}

// Mock AES encryption function (replace with actual implementation)
void enck(unsigned char *input, unsigned char *output, int rounds) {
    // This is a placeholder. Replace with actual AES encryption logic.
    memcpy(output, input, 16);
    output[0] ^= 0xFF;
}

// Mock AES decryption function (replace with actual implementation)
void deck(unsigned char *input, unsigned char *output, int rounds) {
    // This is a placeholder. Replace with actual AES decryption logic.
    memcpy(output, input, 16);
    output[0] ^= 0xFF;
}

int main() {
    srand(time(NULL));
    int length = 16;

    // Perform the distinguisher operation for 5 rounds
    int result = AESDistinguisher5Rounds(length);

    // Output the result
    if (result == 1) {
        printf("Likely AES encryption\n");
    } else {
        printf("Not AES encryption\n");
    }

    return 0;
}
