#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */

int error = 0;              /* error flag */

int gettoken(void);
void dcl(void);
void dirdcl(void);
void skip_to_eol(void);

/* main: read declarations */
int main(void)
{
    while (gettoken() != EOF) {
        error = 0;
        strcpy(out, "");
        if (tokentype != NAME) {
            printf("error: missing datatype\n");
            skip_to_eol();
            continue;
        }
        strcpy(datatype, token);
        dcl();
        if (!error) {
            if (tokentype != '\n')
                printf("syntax error\n");
            else
                printf("%s: %s %s\n", name, out, datatype);
        }
        skip_to_eol();
    }
    return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns = 0;

    while (tokentype == '*') {
        ns++;
        gettoken();
    }
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    if (tokentype == '(') {
        gettoken();
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            error = 1;
        } else
            gettoken();
    }
    else if (tokentype == NAME) {
        strcpy(name, token);
        gettoken();
    }
    else {
        printf("error: expected name or (dcl)\n");
        error = 1;
    }

    while (!error && (tokentype == PARENS || tokentype == BRACKETS)) {
        if (tokentype == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
        gettoken();
    }
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
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = getchar()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

/* skip_to_eol: discard input until newline */
void skip_to_eol(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
