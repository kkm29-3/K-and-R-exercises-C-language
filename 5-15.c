#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000     /* max #lines to be sorted */
#define MAXLEN   1000     /* max length of any input line */

char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort_(void *v[], int left, int right,
            int (*comp)(void *, void *));
int numcmp(const char *, const char *);
int foldcmp(const char *, const char *);
char *alloc(int);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;           /* number of input lines read */
    int numeric = 0;      /* 1 if numeric sort */
    int fold = 0;         /* 1 if fold case */

    /* process command-line options */
    while (--argc > 0 && (*++argv)[0] == '-') {
        while (*++argv[0]) {
            switch (*argv[0]) {
            case 'n':
                numeric = 1;
                break;
            case 'f':
                fold = 1;
                break;
            default:
                printf("sort: illegal option %c\n", *argv[0]);
                return 1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (numeric)
            qsort_((void **)lineptr, 0, nlines - 1,
                   (int (*)(void *, void *))numcmp);
        else if (fold)
            qsort_((void **)lineptr, 0, nlines - 1,
                   (int (*)(void *, void *))foldcmp);
        else
            qsort_((void **)lineptr, 0, nlines - 1,
                   (int (*)(void *, void *))strcmp);

        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while (fgets(line, MAXLEN, stdin) != NULL) {
        len = strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        if ((p = alloc(len + 1)) == NULL)
            return -1;
        strcpy(p, line);
        lineptr[nlines++] = p;
        if (nlines >= maxlines)
            return -1;
    }
    return nlines;
}

/* write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] */
void qsort_(void *v[], int left, int right,
            int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    qsort_(v, left, last - 1, comp);
    qsort_(v, last + 1, right, comp);
}

/* swap v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* foldcmp: compare strings ignoring case */
int foldcmp(const char *s1, const char *s2)
{
    for ( ; tolower(*s1) == tolower(*s2); s1++, s2++)
        if (*s1 == '\0')
            return 0;

    return tolower(*s1) - tolower(*s2);
}

/* simple allocator */
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return NULL;
}
