#include <stdio.h>
#include <string.h>

// Function prototypes for AES encryption and decryption
// These are just placeholders for actual AES functions
void enck(unsigned char *input, unsigned char *output, int rounds);
void deck(unsigned char *input, unsigned char *output, int rounds);

// Function to perform the SimpleSWAP as described earlier
void SimpleSWAP(unsigned char *c0, unsigned char *c1, int length) {
    for (int i = 0; i < length; i++) {
        if (c0[i] != c1[i]) {
            c0[i] = c1[i];
            return;
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

// Distinguisher function for 3 rounds of AES
int AESDistinguisher(unsigned char *p0, unsigned char *p1, int length) {
    unsigned char c0[16], c1[16];
    unsigned char temp[16];

    // Encrypt p0 and p1 for 3 rounds
    enck(p0, c0, 3);
    enck(p1, c1, 3);

    // Apply the SimpleSWAP function to c0 and c1
    SimpleSWAP(c0, c1, length);

    // Decrypt c0 after swap
    deck(c0, temp, 3);

    // Compute the Hamming weight of XOR of p0 and p1, and temp and p1
    int wt1 = hammingWeightXOR(p0, p1, length);
    int wt2 = hammingWeightXOR(temp, p1, length);

    // Check the distinguishing condition
    if (wt1 == wt2) {
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
    int result = AESDistinguisher(p0, p1, 16);

    // Output the result
    if (result == 1) {
        printf("Likely AES encryption\n");
    } else {
        printf("Not AES encryption\n");
    }

    return 0;
}
