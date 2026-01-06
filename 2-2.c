//alternate of i < lim-1 && (c=getchar()) != '\n' && c != EOF  without using && or ||. 
#include <stdio.h>

#define MAXLINE 1000

int main(void) {
    int c;
    int i = 0;
    int lim = MAXLINE;
    char s[MAXLINE];

    while (i < lim-1) {
        c = getchar();
        if (c == '\n')
            break;
        if (c == EOF)
            break;
        s[i] = c; //store character
        ++i;
    }

    s[i] = '\0'; //null terminate the string
    printf("%s\n", s);

    return 0;
}

// #include <stdio.h>
// #define MAXLINE 1000

// enum boolean { NO, YES };
// enum boolean check =  YES;

// int main(){

//     int i=0;
//     int lim = MAXLINE;
//     char s[MAXLINE];
//     int c;
//     while (check == YES){
//         if (i >= lim-1){
//             check= NO;
//         } else if ((c=getchar()) == '\n'){
//             check= NO;
//         } else if (c == EOF){
//             check= NO;
//         } else {
//             s[i]= c;
//             ++i;
//         }
//     }
//     s[i] = '\0';
//     printf("%s\n", s);

//     return 0;
// }
