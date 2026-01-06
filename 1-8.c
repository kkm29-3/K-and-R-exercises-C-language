// #include <stdio.h>

// int main() {
//     int blanks = 0;
//     int tabs = 0;
//     int newlines = 0;

//     char c;
//     while ((c = getchar()) != EOF) {
//         if (c == ' ') {
//             ++blanks;
//         } else if (c == '\t') {
//             ++tabs;
//         } else if (c == '\n') {
//             ++newlines;
//         }
//     }

//     printf("blanks_nr: %d\ntabs_nr: %d\nnewlines_nr: %d\n", blanks, tabs,
//            newlines);

//     return 0;
// }

#include <stdio.h>

int main(void)
{
    int c;
    long blanks = 0, tabs = 0, newlines = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++blanks;
        else if (c == '\t')
            ++tabs;
        else if (c == '\n')
            ++newlines;
    }

    printf("blanks = %ld, tabs = %ld, newlines = %ld\n",
           blanks, tabs, newlines);

    return 0;
}
