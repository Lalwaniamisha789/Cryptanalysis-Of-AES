#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

// Function to swap the first differing word and return the modified text
void SimpleSWAP(char x0[][MAX_LENGTH], char x1[][MAX_LENGTH], char x00[][MAX_LENGTH], int numWords) {
    // Copy x1 to x00 initially
    for (int i = 0; i < numWords; i++) {
        strcpy(x00[i], x1[i]);
    }

    // Find the first differing word and swap it
    for (int i = 0; i < numWords; i++) {
        if (strcmp(x0[i], x1[i]) != 0) {
            // Swap the word from x0 to x00
            strcpy(x00[i], x0[i]);
            return;
        }
    }
}

int main() {
    // Example input texts with up to 4 words
    char x0[4][MAX_LENGTH] = {"Hello", "world", "from", "C"};
    char x1[4][MAX_LENGTH] = {"Hello", "everyone", "from", "C"};
    char x00[4][MAX_LENGTH];
    int numWords = 4;

    // Perform the SimpleSWAP operation
    SimpleSWAP(x0, x1, x00, numWords);

    // Output the result
    printf("Resulting text after SimpleSWAP:\n");
    for (int i = 0; i < numWords; i++) {
        printf("%s ", x00[i]);
    }
    printf("\n");

    return 0;
}
