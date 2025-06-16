// Remove any duplicate characters from the string.
// Example: Given "abacbddxxyyzzabcd", should return "abcdxyz"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_ASCII_CODE  128

int main(void) {
    char str[] = "abacbddxxyyzzabcd";
    printf("%s => ", str);

    bool character_found[MAX_ASCII_CODE] = {0};

    if (strlen(str) < 2) {
        printf("%s\n", str);
        return 0;
    }

    // Remove duplicates in place
    int i = 1; // Indexes every character in the original string; finds the next unique character.
    int j = 0; // Marks the position where the first unique character will be moved to.
    character_found[str[j]] = true;

    while (str[i] != '\0') {
        // Find the first character that's different than str[j]
        while (str[i] != '\0') {
            if (character_found[str[i]]) {
                i++;
            } else {
                break;
            }
        }

        if (str[i] == '\0') {
            break;
        }

        // Log the new character as encountered
        character_found[str[i]] = true;

        // i is now pointing at the first character that's different from the previous character.
        // Copy the character at i to the character after j.
        j++;
        str[j] = str[i];

        i++;
    }

    str[j + 1] = '\0';
    printf("%s\n", str);

    return 0;
}
