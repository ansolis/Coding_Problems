// Remove duplicate characters from the string.
// Example: Given "aabbccdd", return "abcd".

#include <stdio.h>
#include <string.h>

int main(void) {
    char str[] = "aaabbccccdd";
    printf("%s => ", str);

    if (strlen(str) < 2) {
        printf("%s\n", str);
        return 0;
    }

    // Remove duplicates in place
    int i = 1; // Indexes every character in the original string; finds the next unique character.
    int j = 0; // Marks the position of the first repeating character.
    while (str[i] != '\0') {
        // Find the first character that's different than str[j]
        while ((str[i] != '\0') && (str[i] == str[j])) {
            i++;
        }

        if (str[i] == '\0') {
            break;
        }

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
