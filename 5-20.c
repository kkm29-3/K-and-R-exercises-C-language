#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUT   1000

enum { NAME, PARENS, BRACKETS, QUALIFIER };

int  tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXOUT];

int gettoken(void);
void dcl(void);
void dirdcl(void);

/* main: read a declaration and translate it */
int main(void)
{
    while (gettoken() != EOF) {
        strcpy(datatype, token);   /* first token is the data type */
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns = 0;

    while (tokentype == '*' || tokentype == QUALIFIER) {
        if (tokentype == '*')
            ns++;
        else {
            strcat(out, " ");
            strcat(out, token);
        }
        gettoken();
    }

    dirdcl();

    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;

    if (tokentype == '(') {
        // gettoken();
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME) {
        strcpy(name, token);
    } else {
        printf("error: expected name or (dcl)\n");
    }

    while ((type = gettoken()) == PARENS ||
           type == BRACKETS ||
           type == '(') {

        if (type == PARENS) {
            strcat(out, " function returning");
        }
        else if (type == BRACKETS) {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
        else if (type == '(') {
            strcat(out, " function expecting");

            gettoken();
            if (tokentype != ')') {
                while (1) {
                    dcl();
                    if (tokentype == ')')
                        break;
                    strcat(out, ",");
                    gettoken();
                }
            }
            strcat(out, " returning");
        }
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
            token[0] = '(';
            token[1] = '\0';
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

        if (!strcmp(token, "const") ||
            !strcmp(token, "volatile") ||
            !strcmp(token, "unsigned") ||
            !strcmp(token, "signed") ||
            !strcmp(token, "short") ||
            !strcmp(token, "long"))
            return tokentype = QUALIFIER;

        return tokentype = NAME;
    }
    else {
        token[0] = c;
        token[1] = '\0';
        return tokentype = c;
    }
}
