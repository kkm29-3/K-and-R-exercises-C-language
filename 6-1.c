#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])
#define BUFSIZE 100

/* ---------- keyword table ---------- */

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
    "auto",     0,
    "break",    0,
    "case",     0,
    "char",     0,
    "const",    0,
    "continue", 0,
    "default",  0,
    "do",       0,
    "double",   0,
    "else",     0,
    "enum",     0,
    "extern",   0,
    "float",    0,
    "for",      0,
    "goto",     0,
    "if",       0,
    "int",      0,
    "long",     0,
    "register", 0,
    "return",   0,
    "short",    0,
    "signed",   0,
    "sizeof",   0,
    "static",   0,
    "struct",   0,
    "switch",   0,
    "typedef",  0,
    "union",    0,
    "unsigned", 0,
    "void",     0,
    "volatile", 0,
    "while",    0
};

/* ---------- function prototypes ---------- */

int getword(char *, int);
int binsearch(char *, struct key *, int);

int getch(void);
void ungetch(int);

/* ---------- main ---------- */

int main(void)
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) || word[0] == '_')
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;

    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}

/* ---------- binsearch ---------- */

int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* ---------- getch / ungetch ---------- */

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* ---------- improved getword ---------- */

int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    /* skip whitespace */
    while (isspace(c = getch()))
        ;

    if (c == EOF)
        return EOF;

    /* skip preprocessor lines */
    if (c == '#') {
        while ((c = getch()) != '\n' && c != EOF)
            ;
        return getword(word, lim);
    }

    /* skip string constants */
    if (c == '"') {
        while ((c = getch()) != '"' && c != EOF)
            if (c == '\\')
                getch();
        return getword(word, lim);
    }

    /* skip character constants */
    if (c == '\'') {
        while ((c = getch()) != '\'' && c != EOF)
            if (c == '\\')
                getch();
        return getword(word, lim);
    }

    /* skip comments */
    if (c == '/') {
        d = getch();
        if (d == '/') {
            while ((c = getch()) != '\n' && c != EOF)
                ;
            return getword(word, lim);
        } else if (d == '*') {
            while ((c = getch()) != EOF) {
                if (c == '*' && (d = getch()) == '/')
                    break;
                ungetch(d);
            }
            return getword(word, lim);
        } else
            ungetch(d);
    }

    /* not an identifier */
    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    /* collect identifier */
    *w++ = c;
    for (; --lim > 0; w++) {
        c = getch();
        if (!isalnum(c) && c != '_') {
            ungetch(c);
            break;
        }
        *w = c;
    }
    *w = '\0';

    return word[0];
}

//run this code with (powershell):
// 6-1 < test.c
// expected output:
//    1 if
//    1 int
//    1 return

// 🧪 Manual Input Test
// 6-1
//int main() { return 0; }
// Expected output:
//    1 int 
//    1 return
