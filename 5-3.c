#include <stdio.h>

void strcat_ptr(char *s, char *t);

int main(void) {
    char s[100], t[100];
    
    // Method 1: printf/scanf (easier for full strings)
    printf("Enter first string: ");
    scanf("%99s", s);  // 99 leaves room for null terminator
    printf("Enter second string: ");
    scanf("%99s", t);
    
    strcat_ptr(s, t);
    puts(s);
    
    return 0;
}

void strcat_ptr(char *s, char *t) {
    // Step 1: Find end of s (null terminator '\0')
    while (*s)  // Loop until *s == '\0'
        ++s;    // Move pointer forward
    
    // Step 2: Copy t to end of s
    while ((*s++ = *t++))  // Copy char, advance both pointers
        ;                  // Empty body - assignment acts as condition
}
