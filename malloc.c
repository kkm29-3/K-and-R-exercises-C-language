// #include <stdlib.h>
// #include <stdio.h>  
// int main() {
// int *arr;
// arr = (int*) malloc(5 * sizeof(int));  // allocates space for 5 integers
// if (arr == NULL) {
//     printf("Memory allocation failed!");
// }
// }

// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     int n = 5;
//     int *ptr = (int*)malloc(n * sizeof(int));  // Allocates memory for 5 ints
//     if (ptr == NULL) {
//         printf("Memory allocation failed\n");
//         return 1;
//     }
//     // Use ptr as array: ptr[0] to ptr[4]
//     free(ptr);  // Always free to avoid leaks
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5;
    int *arr;

    // allocate memory for 5 integers
    arr = (int*) malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // assign values
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // print values
    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    // free memory
    free(arr);

    return 0;
}