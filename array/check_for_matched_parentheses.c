// Check if a string contains only matching pairs of parentheses.
// Valid parentheses: (, ), {, }, [, ].
// Example:
// This contains matching pairs of parentheses:
//   (({[{{()}}]})){}[]()
//   -Empty-
//   [abc]def
// This contains unmatched parentheses:
//   ((([))){}
//   {
//   (]

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static bool is_opening_paren(char chr) {
    return chr == '{' || chr == '(' || chr == '[';
}

static bool is_closing_paren(char chr) {
    return chr == '}' || chr == ')' || chr == ']';
}

static bool is_matching_paren(char opening_paren, char closing_paren) {
    return ((opening_paren == '{' && closing_paren == '}') ||
        (opening_paren == '(' && closing_paren == ')') ||
        (opening_paren == '[' && closing_paren == ']'));
}

static bool is_matching_parens_only(const char* str) {
    size_t len = strlen(str);

    if (len == 0) {
        return true;
    }

    // Using a Variable Length Array (VLA) as a stack. This is a C99 feature.
    // For very large strings, a dynamically allocated stack (using malloc)
    // would be safer to prevent stack overflow.
    char stack[len];
    int stack_top_idx = -1;

    for (size_t i = 0; i < len; i++) {
        if (is_opening_paren(str[i])) {
            stack_top_idx++;
            stack[stack_top_idx] = str[i];
        } else if (is_closing_paren(str[i])) {
            if (stack_top_idx < 0 ) {
                // Closing parenthesis with no matching opening one.
                return false;
            }
            if (!is_matching_paren(stack[stack_top_idx], str[i])) {
                // Mismatched parenthesis.
                return false;
            }

            // Pop the matched opening parenthesis from the stack.
            stack_top_idx--;
        } else {
            // Non-parenthesis character - continue
        }
    }

    if (stack_top_idx >= 0) {
        return false;
    }

    return true;
}

int main(void) {
    printf("Matching parens only:\n");

    const char* test_cases[] = {
        "(({[{{()}}]})){}[]()",
        "",
        "[abc]def",
        "((([))){}",
        "{",
        "(]",
        "{a[b()]c}d",
        "{a[b()]cd",
        "a[b()]c}d",
        "{a[b)]c}d",
        "{a[b(]c}d",
        "a(b",
        "]"
    };
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; i++) {
        const char* str = test_cases[i];
        bool result = is_matching_parens_only(str);
        // Print string in quotes for clarity, especially for the empty string.
        printf("\"%s\", %s\n", str, result ? "TRUE" : "FALSE");
    }

    return 0;
}
