#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char out[1000];             /* output string */

int gettoken(void);

/* undcl: convert word description to C declaration */
int main(void)
{
    int type;
    char temp[1000];

    while (gettoken() != EOF) {
        strcpy(out, token);

        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                strcat(out, token);
            }
            else if (type == '*') {
                /* FIX for Exercise 5-19:
                   add parentheses ONLY when needed */
                if (out[0] == '(' || out[0] == '[')
                    sprintf(temp, "(*%s)", out);
                else
                    sprintf(temp, "*%s", out);
                strcpy(out, temp);
            }
            else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

/* gettoken: return next token */
int gettoken(void)
{
    int c;
    char *p = token;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            token[0] = '(';
            token[1] = '\0';
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        *p++ = '[';
        while ((*p++ = getchar()) != ']')
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        *p++ = c;
        while (isalnum(c = getchar()))
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
    }
    else {
        token[0] = c;
        token[1] = '\0';
        return tokentype = c;
    }
}
