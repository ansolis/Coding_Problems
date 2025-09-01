// Trapping rain water
// See https://www.geeksforgeeks.org/trapping-rain-water/
//
//         X
// X       X
// X       X   X
// X   X   X X X
// = = = = = = =
// 3 0 1 0 4 1 2
//
// Expected answer: 9 (the 9 dashes below represent the trapped water):
//
//         X
// X - - - X
// X - - - X - X
// X - X - X X X
// = = = = = = =
// 3 0 1 0 4 1 2

#include <stdio.h>

#define ARR_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int rainwater_trap[] = {3, 0, 1, 0, 4, 1, 2};

    int l = 0;
    int r = ARR_SIZE(rainwater_trap) - 1;
    int l_max_trap_level = rainwater_trap[l];
    int r_max_trap_level = rainwater_trap[r];
    int water_trapped = 0;

    while (l < r) {
        if (rainwater_trap[l] < rainwater_trap[r]) {
            // l_max_trap_level = MAX(l_max_trap_level, rainwater_trap[l]);
            water_trapped += MIN(l_max_trap_level, r_max_trap_level) - rainwater_trap[l];
            l++;
            l_max_trap_level = MAX(l_max_trap_level, rainwater_trap[l]);
        } else {
            // r_max_trap_level = MAX(r_max_trap_level, rainwater_trap[r]);
            water_trapped += MIN(l_max_trap_level, r_max_trap_level) - rainwater_trap[r];
            r--;
            r_max_trap_level = MAX(r_max_trap_level, rainwater_trap[r]);
        }
    }

    printf("Water trapped: %i\n", water_trapped);
}
