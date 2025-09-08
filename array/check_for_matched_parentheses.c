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
    if (chr == '{' || chr == '(' || chr == '[') {
        return true;
    }

    return false;
}

static bool is_closing_paren(char chr) {
    if (chr == '}' || chr == ')' || chr == ']') {
        return true;
    }

    return false;
}

static bool is_matching_paren(char opening_paren, char closing_paren) {
    if (opening_paren == '{' && closing_paren == '}' ||
        opening_paren == '(' && closing_paren == ')' ||
        opening_paren == '[' && closing_paren == ']') {
        return true;
    }

    return false;
}

static bool is_matching_parens_only(char* str) {
    int len = strlen(str);

    if (len == 0) {
        return true;
    }

    char stack[len] = {};
    int stack_top_idx = -1;

    for (int i = 0; i < len; i++) {
        if (is_opening_paren(str[i])) {
            stack_top_idx++;
            stack[stack_top_idx] = str[i];
        } else if (is_closing_paren(str[i])) {
            if (stack_top_idx < 0 ) {
                return false;
            }
            if (!is_matching_paren(stack[stack_top_idx], str[i])) {
                return false;
            }

            // Remove the opening matched parenthesis from the stack
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

    char* str = "{a[b()]c}d";
    bool result = is_matching_parens_only(str);
    printf("%s, %s\n", str, result ? "TRUE" : "FALSE");

    str = "{a[b()]cd";
    result = is_matching_parens_only(str);
    printf("%s, %s\n", str, result ? "TRUE" : "FALSE");

    str = "a[b()]c}d";
    result = is_matching_parens_only(str);
    printf("%s, %s\n", str, result ? "TRUE" : "FALSE");

    str = "{a[b)]c}d";
    result = is_matching_parens_only(str);
    printf("%s, %s\n", str, result ? "TRUE" : "FALSE");

    str = "{a[b(]c}d";
    result = is_matching_parens_only(str);
    printf("%s, %s\n", str, result ? "TRUE" : "FALSE");

    str = "";
    result = is_matching_parens_only(str);
    printf("%s, %s\n", str, result ? "TRUE" : "FALSE");

    str = "a(b";
    result = is_matching_parens_only(str);
    printf("%s, %s\n", str, result ? "TRUE" : "FALSE");

    str = "]";
    result = is_matching_parens_only(str);
    printf("%s, %s\n", str, result ? "TRUE" : "FALSE");

    return 0;
}
