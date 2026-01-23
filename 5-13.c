#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000   /* max number of lines */
#define MAXLEN   1000   /* max length of a line */
#define ALLOCSIZE 10000 /* storage size */

char *lineptr[MAXLINES];  /* pointers to lines */

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

/* function declarations */
int readlines(char *lineptr[], int maxlines);
void writetail(char *lineptr[], int nlines, int n);
char *alloc(int n);
int getline_(char *s, int lim);

/* ---------------- main ---------------- */
int main(int argc, char *argv[])
{
    int n = 10;   /* default number of lines */
    int nlines;

    /* parse optional -n argument */
    if (argc == 2 && argv[1][0] == '-') {
        n = atoi(argv[1] + 1);
        if (n < 0)
            n = 0;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        writetail(lineptr, nlines, n);
        return 0;
    } else {
        fprintf(stderr, "tail: input too large\n");
        return 1;
    }
}

/* ---------------- readlines ---------------- */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = getline_(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        line[len - 1] = '\0'; /* remove newline */
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

/* ---------------- writetail ---------------- */
void writetail(char *lineptr[], int nlines, int n)
{
    int start;

    if (n > nlines)
        start = 0;
    else
        start = nlines - n;

    for (int i = start; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* ---------------- alloc ---------------- */
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return NULL;
    }
}

/* ---------------- getline ---------------- */
int getline_(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}
