#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 100
#define MAX_KEY_LENGTH 20
#define NUM_INPUTS 12

void vigenere_encrypt_decrypt(char *input, char *key, int encrypt) {
    int keyLen = strlen(key);
    int keyIndex = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            char offset = isupper(input[i]) ? 'A' : 'a';
            int shift = (toupper(key[keyIndex % keyLen]) - 'A') * (encrypt ? 1 : -1);
            input[i] = (char)((((input[i] - offset) + shift + 26) % 26) + offset);
            keyIndex++;
        }
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char combinedInput[NUM_INPUTS * MAX_INPUT_LENGTH] = {0}; // Buffer to hold all inputs concatenated
    char key[MAX_KEY_LENGTH];
    int encrypt;

    // User prompt for encryption or decryption
    printf("Do you want to encrypt (1) or decrypt (0)? ");
    scanf("%d", &encrypt);
    getchar(); // to consume the newline character left by scanf

    if (encrypt) {
        // Taking multiple string inputs for encryption
        for (int i = 0; i < NUM_INPUTS; i++) {
            printf("Enter string %d: ", i + 1);
            fgets(input, MAX_INPUT_LENGTH, stdin);
            input[strcspn(input, "\n")] = 0; // Removing newline character
            strcat(combinedInput, input);
        }
    } else {
        // Taking one long string input for decryption
        printf("Enter the string to decrypt: ");
        fgets(combinedInput, sizeof(combinedInput), stdin);
        combinedInput[strcspn(combinedInput, "\n")] = 0; // Removing newline character
    }

    printf("Enter encryption key (up to 20 characters): ");
    fgets(key, MAX_KEY_LENGTH, stdin);
    key[strcspn(key, "\n")] = 0; // Removing newline character

    // Encrypting or Decrypting based on user choice
    vigenere_encrypt_decrypt(combinedInput, key, encrypt);
    if (encrypt) {
        printf("Encrypted String: %s\n", combinedInput);
    } else {
        printf("Decrypted String: %s\n", combinedInput);
    }

    return 0;
}
