#include <stdio.h>
#include <string.h>

// Function prototypes for AES encryption and decryption
// These are just placeholders for actual AES functions
void enck(unsigned char *input, unsigned char *output, int rounds);
void deck(unsigned char *input, unsigned char *output, int rounds);

// Function to perform the SimpleSWAP as described
void SimpleSWAP(unsigned char *input1, unsigned char *input2, unsigned char *output, int length) {
    for (int i = 0; i < length; i++) {
        if (input1[i] != input2[i]) {
            // Swap the differing byte
            output[i] = input1[i];
        } else {
            // Keep the same byte if they are identical
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

// Distinguisher function for 4 rounds of AES
int AESDistinguisher4Rounds(unsigned char *p0, unsigned char *p1, int length) {
    unsigned char c0[16], c1[16];
    unsigned char c00[16], c01[16];
    unsigned char p00[16], p01[16];

    // Encrypt p0 and p1 for 4 rounds
    enck(p0, c0, 4);
    enck(p1, c1, 4);

    // Apply the SimpleSWAP function to generate c00 and c01
    SimpleSWAP(c0, c1, c00, length);
    SimpleSWAP(c1, c0, c01, length);

    // Decrypt c00 and c01
    deck(c00, p00, 4);
    deck(c01, p01, 4);

    // Compute the Hamming weight of XOR of p00 and p01, and p0 and p1
    int wtOriginal = hammingWeightXOR(p0, p1, length);
    int wtDecrypted = hammingWeightXOR(p00, p01, length);

    // Check the distinguishing condition
    if (wtOriginal == wtDecrypted) {
        return 1; // Likely AES
    } else {
        return -1; // Not AES
    }
}

// Mock AES encryption function (replace with actual implementation)
void enck(unsigned char *input, unsigned char *output, int rounds) {
    // This is a placeholder. Replace with actual AES encryption logic.
    memcpy(output, input, 16);
    // Simulate some modification for demonstration purposes
    output[0] ^= 0xFF;
}

// Mock AES decryption function (replace with actual implementation)
void deck(unsigned char *input, unsigned char *output, int rounds) {
    // This is a placeholder. Replace with actual AES decryption logic.
    memcpy(output, input, 16);
    // Simulate some modification for demonstration purposes
    output[0] ^= 0xFF;
}

int main() {
    // Example inputs
    unsigned char p0[16] = {0x32, 0x88, 0x31, 0xE0, 0x43, 0x5A, 0x31, 0x37, 0xF6, 0x30, 0x98, 0x07, 0xA8, 0x8D, 0xA2, 0x34};
    unsigned char p1[16] = {0x32, 0x88, 0x31, 0xE1, 0x43, 0x5A, 0x31, 0x37, 0xF6, 0x30, 0x98, 0x07, 0xA8, 0x8D, 0xA2, 0x34};

    // Perform the distinguisher operation
    int result = AESDistinguisher4Rounds(p0, p1, 16);

    // Output the result
    if (result == 1) {
        printf("Likely AES encryption\n");
    } else {
        printf("Not AES encryption\n");
    }

    return 0;
}
