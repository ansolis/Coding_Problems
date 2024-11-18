// Find maximum subarray sum.
// This implementation is based on Kadane's algorithm, but
// with a slight modification. Instead of doing
//   for (int i = 1; i < size; i++) {
//     sum = (sum + arr[i] > arr[i]) ? sum + arr[i] : arr[i];
//     max_sum = (max_sum > sum) ? max_sum : sum;
//   }
// we do:
//   for (int i = 0; i < ARR_SIZE(arr); i++) {
//       sum += arr[i];
//       max_sum = MAX(max_sum, sum);
//       sum = (sum < 0) ? 0 : sum;
//   }

#include <stdio.h>

#define ARR_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int arr[] = {2, 3, -8, 7, -1, 2, 3};
    int max_sum = 0;
    int sum = 0;

    for (int i = 0; i < ARR_SIZE(arr); i++) {
        sum += arr[i];
        max_sum = MAX(max_sum, sum);
        sum = (sum < 0) ? 0 : sum;
    }

    printf("Maximum subarray sum: %i\n", max_sum);
}