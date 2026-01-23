#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000     /* max #lines to be sorted */
#define MAXLEN   1000     /* max length of any input line */
#define ALLOCSIZE 10000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void qsort_(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmp_(char *, char *);

int getline_(char *, int);
char *alloc(int);

int numeric = 0;   /* 1 if numeric sort */
int reverse = 0;   /* 1 if reverse order */

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;
    int c;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                printf("sort: illegal option %c\n", c);
                return 1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_((void **) lineptr, 0, nlines - 1,
               (int (*)(void *, void *))
               (numeric ? numcmp : strcmp_));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* qsort_: sort v[left]...v[right] */
void qsort_(void *v[], int left, int right,
            int (*comp)(void *, void *))
{
    int i, last;
    void *tmp;

    if (left >= right)
        return;

    tmp = v[left];
    v[left] = v[(left + right) / 2];
    v[(left + right) / 2] = tmp;

    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0) {
            ++last;
            tmp = v[last];
            v[last] = v[i];
            v[i] = tmp;
        }

    tmp = v[left];
    v[left] = v[last];
    v[last] = tmp;

    qsort_(v, left, last - 1, comp);
    qsort_(v, last + 1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return reverse ? 1 : -1;
    else if (v1 > v2)
        return reverse ? -1 : 1;
    else
        return 0;
}

/* strcmp_ : compare s and t lexicographically */
int strcmp_(char *s, char *t)
{
    int r = strcmp(s, t);
    return reverse ? -r : r;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = getline_(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == 0)
            return -1;
        line[len - 1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* getline_: get line into s, return length */
int getline_(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 &&
         (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* alloc: return pointer to n characters */
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return 0;
}
