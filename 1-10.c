// #include <stdio.h>

// int main() {
//     char c;
//     while ((c = getchar()) != EOF) {
//         if (c == '\t') {
//             putchar('\\');
//             putchar('t');
//         } else if (c == '\b') {
//             putchar('\\');
//             putchar('b');
//         } else if (c == '\\') {
//             putchar('\\');
//             putchar('\\');
//         } else {
//             putchar(c);
//         }
//     }

//     return 0;
// }

#include <stdio.h>

int main(void)
{
    int c;

    while ((c = getchar()) != EOF) {

        if (c == '\t') {
            putchar('\\');
            putchar('t');
        }
        else if (c == '\b') {
            putchar('\\');
            putchar('b');
        }
        else if (c == '\\') {
            putchar('\\');
            putchar('\\');
        }
        else {
            if (c!='\t'){
                if (c!='\b'){
                    if (c!='\\'){
                        putchar(c);
                    }
                }
            }
        
        }
    }
}
