#include <limits.h>
#include <stdio.h>

int atoi(char* str) {
    int value = 0;
    int sign  = 1;

    if (str == NULL) {
        return 0;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        sign = 1;
        str++;
    }

    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            break;
        }

        // Check for overflow
        if (value > INT_MAX / 10) {
            return 0;
        }

        value *= 10;
        value += *str - '0';
        str++;
    }

    return value * sign;
}

int main(void) {
    char* str[] = {"123", "-123", "+123", "123a", "a123"};

    for (int i = 0; i < 5; i++) {
        printf("%s => %d\n", str[i], atoi(str[i]));
    }

    return 0;
}
