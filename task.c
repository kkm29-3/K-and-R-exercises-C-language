// // "Write a recursive function to check enterd number is pelindrom or not. 
// // "


#include <stdio.h>
#include <math.h>

int reverse(int num) {
    if (num == 0) {
        return 0;
    }
    int digits = (int)log10(num);
    return (num % 10 * (int)pow(10, digits)) + reverse(num / 10);
}

int isPalindrome(int num) {
    return num == reverse(num);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (isPalindrome(num)) {
        printf("%d is a palindrome.\n", num);
    } else {
        printf("%d is not a palindrome.\n", num);
    }
    return 0;
}



























// #include <stdio.h>
// #include <ctype.h>      
// #include <string.h>
// #define MAXLEN 1000
// int is_palindrome(char s[], int i, int j);

// int main(void) {
//     char str[MAXLEN];
//     int len;

//     printf("Enter a string: ");
//     fgets(str, MAXLEN, stdin);

//     len = strlen(str);
//     if (str[len - 1] == '\n') {
//         str[len - 1] = '\0';
//         len--;
//     }

//     if (is_palindrome(str, 0, len - 1)) {
//         printf("The string is a palindrome.\n");
//     } else {
//         printf("The string is not a palindrome.\n");
//     }

//     return 0;
// }
// int is_palindrome(char s[], int i, int j) {
//     // Move i forward and j backward to skip non-alphanumeric characters
//     while (i < j && !isalnum((unsigned char)s[i])) {
//         i++;
//     }
//     while (i < j && !isalnum((unsigned char)s[j])) {
//         j--;
//     }

//     // Base case: If pointers have crossed, it's a palindrome
//     if (i >= j) {
//         return 1;
//     }

//     // Check characters at current pointers (case-insensitive)
//     if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j])) {
//         return 0; // Not a palindrome
//     }

//     // Recursive case: Move towards the center
//     return is_palindrome(s, i + 1, j - 1);
// }
// // NOTE: The function uses recursion to compare characters from the start and end
// // of the string, moving towards the center. It skips non-alphanumeric characters
// // and performs case-insensitive comparisons. If all corresponding characters
// // match, the function concludes that the string is a palindrome.   