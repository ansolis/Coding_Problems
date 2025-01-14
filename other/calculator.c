#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// A + B + C + D/E
// A / B * C - D
// A + B * C - D / E + F

// SUM + OP1 * OP2

void process_token(char* token) {
    static char     last_operator  = ' ';
    static float    sum            = 0;
    static int      sign_mult      = 1; // 1 for +, -1 for -
    static uint32_t first_operand  = 0;
    static uint32_t second_operand = 0;

    if (isdigit(*token)) {
        if (last_operator == ' ') {
            // We're entering the first digit
            sum = (*token - '0');
        } else if ((last_operator == '+') || (last_operator == '-')) {
            // We're entering the second operand of the + or - operator
            first_operand = (*token - '0');
        } else if ((last_operator == '*') || (last_operator == '/')) {
            // We're entering the second operand of the * or / operator
            second_operand = (*token - '0');
        }
    }

    if ((*token == '+') || (*token == '-')) {
        if (last_operator == '+') {
            sum += first_operand;
            last_operator  = *token;
            first_operand  = 0;
            second_operand = 0;
        }

        if (last_operator == '-') {
            sum -= first_operand;
            last_operator  = *token;
            first_operand  = 0;
            second_operand = 0;
        }

        if (last_operator == ' ') {
            // We're entring the first +/- operator
            last_operator = *token;
        }

        if (last_operator == '*') {
            sum += first_operand * second_operand;
            last_operator  = *token;
            first_operand  = 0;
            second_operand = 0;
        }

        if (last_operator == '+') {
            sign_mult = 1;
        }

        if (last_operator == '-') {
            sign_mult = -1;
        }
    }

    if ((*token == '*') || (*token == '/')) {
        // TODO: Handle * and / operators
    }

    if (*token == '=') {
        if (last_operator == ' ') {
            // Nothing to do
        } else if (last_operator == '+') {
            //
            sum += first_operand;
        } else if (last_operator == '-') {
            //
            sum -= first_operand;
        } else if (last_operator == '*') {
            //
            sum += sign_mult * (float)first_operand * (float)second_operand;
        } else if (last_operator == '/') {
            //
            sum += sign_mult * (float)first_operand / (float)second_operand;
        }
    }

    printf("Sum: %f\n", sum);
}

int main(void) {
    char* token;
    // char  input[] = "1 + 2 * 3 - 4 / 2 + 5";
    char input[] = "1 + 2 * 3 - 4";

    token = strtok(input, " ");
    while (token != NULL) {
        printf(" % s\n", token);
        process_token(token);

        token = strtok(NULL, " ");
    }

    token = "=";
    process_token(token);

    return 0;
}
