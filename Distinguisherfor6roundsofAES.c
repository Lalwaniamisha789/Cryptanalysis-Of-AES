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

// Function to generate a set of random plaintext pairs with a specified size
void generateRandomPairs(unsigned char pairs[][2][16], int numPairs, int length) {
    for (int i = 0; i < numPairs; i++) {
        for (int j = 0; j < length; j++) {
            pairs[i][0][j] = rand() % 256; // Random bytes for p0
            pairs[i][1][j] = pairs[i][0][j]; // Start p1 as a copy of p0
        }
        // Introduce a Hamming weight of 3 by flipping three random bits in p1
        for (int k = 0; k < 3; k++) {
            int bytePos = rand() % length;
            int bitPos = rand() % 8;
            pairs[i][1][bytePos] ^= (1 << bitPos);
        }
    }
}

// Distinguisher function for 6 rounds of AES
int AESDistinguisher6Rounds(unsigned char pairs[][2][16], int numPairs, int length) {
    for (int i = 0; i < numPairs; i++) {
        unsigned char p0[16], p1[16];
        memcpy(p0, pairs[i][0], length);
        memcpy(p1, pairs[i][1], length);

        int WrongPair = 0;
        int counter = 0;
        const double maxCounter = 260.4;

        while (counter < maxCounter && !WrongPair) {
            // Check if the Hamming weight of the XOR is different from 2
            if (hammingWeightXOR(p0, p1, length) < 2) {
                WrongPair = 1; // Too many zeros in the difference
                break;
            }

            unsigned char c0[16], c1[16];
            unsigned char c00[16], c01[16];
            unsigned char p00[16], p01[16];

            // Encrypt p0 and p1 for 6 rounds
            enck(p0, c0, 6);
            enck(p1, c1, 6);

            // Check if the Hamming weight of the XOR of c0 and c1 is different from 2
            if (hammingWeightXOR(c0, c1, length) < 2) {
                WrongPair = 1; // Too many zeros in the difference
                break;
            }

            // Apply the SimpleSWAP function to generate c00 and c01
            SimpleSWAP(c0, c1, c00, length);
            SimpleSWAP(c1, c0, c01, length);

            // Decrypt c00 and c01
            deck(c00, p00, 6);
            deck(c01, p01, 6);

            // Update p0 and p1 with SimpleSWAP
            SimpleSWAP(p00, p01, p0, length);
            SimpleSWAP(p01, p00, p1, length);

            counter++;
        }

        // If no "WrongPair" was found during the process, return 1 indicating likely AES
        if (!WrongPair) {
            return 1;
        }
    }

    // If no pair passed the distinguishing test, return -1 indicating not AES
    return -1;
}

// Mock AES encryption function (replace with actual implementation)
void enck(unsigned char *input, unsigned char *output, int rounds) {
    // This is a placeholder. Replace with actual AES encryption logic.
    memcpy(output, input, 16);
    output[0] ^= 0xFF; // Modify to simulate encryption
}

// Mock AES decryption function (replace with actual implementation)
void deck(unsigned char *input, unsigned char *output, int rounds) {
    // This is a placeholder. Replace with actual AES decryption logic.
    memcpy(output, input, 16);
    output[0] ^= 0xFF; // Modify to simulate decryption
}

int main() {
    srand(time(NULL));
    int numPairs = 261; // Number of plaintext pairs, approximating 2^61.4
    int length = 16;
    unsigned char pairs[261][2][16];

    // Generate random plaintext pairs
    generateRandomPairs(pairs, numPairs, length);

    // Perform the distinguisher operation for 6 rounds
    int result = AESDistinguisher6Rounds(pairs, numPairs, length);

    // Output the result
    if (result == 1) {
        printf("Likely AES encryption\n");
    } else {
        printf("Not AES encryption\n");
    }

    return 0;
}
