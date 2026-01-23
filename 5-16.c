#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000     /* max number of lines */
#define MAXLEN   1000     /* max length of any input line */

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void myqsort(void *v[], int left, int right,int (*comp)(const void *, const void *), int reverse);

int numcmp(const char *, const char *);
int foldcmp(const char *, const char *);
int dircmp(const char *, const char *, int fold);

/* option flags */
int numeric = 0;
int fold = 0;
int directory = 0;
int reverse = 0;

/* ---------- main ---------- */
int main(int argc, char *argv[])
{
    int nlines;

    /* parse options */
    while (--argc > 0 && (*++argv)[0] == '-') {
        char *p = *argv + 1;
        while (*p) {
            switch (*p++) {
            case 'n': numeric = 1; break;
            case 'f': fold = 1; break;
            case 'd': directory = 1; break;
            case 'r': reverse = 1; break;
            default:
                printf("illegal option\n");
                return 1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
        printf("input too big to sort\n");
        return 1;
    }

    /* select comparison function */
    int (*cmp)(const void *, const void *);

    if (numeric)
        cmp = (int (*)(const void *, const void *)) numcmp;
    else if (directory)
        cmp = (int (*)(const void *, const void *)) dircmp;
    else if (fold)
        cmp = (int (*)(const void *, const void *)) foldcmp;
    else
        cmp = (int (*)(const void *, const void *)) strcmp;

    myqsort((void **) lineptr, 0, nlines - 1, cmp, reverse);
    writelines(lineptr, nlines);

    return 0;
}

/* ---------- line input/output ---------- */

int getline_kr(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = getline_kr(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        line[len - 1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* ---------- sorting ---------- */

void myqsort(void *v[], int left, int right,
             int (*comp)(const void *, const void *), int reverse)
{
    int i, last;

    if (left >= right)
        return;

    void *temp = v[left];
    v[left] = v[(left + right) / 2];
    v[(left + right) / 2] = temp;

    last = left;
    for (i = left + 1; i <= right; i++) {
        int result = (*comp)(&v[i], &v[left]);
        if (reverse)
            result = -result;
        if (result < 0) {
            ++last;
            temp = v[last];
            v[last] = v[i];
            v[i] = temp;
        }
    }

    temp = v[left];
    v[left] = v[last];
    v[last] = temp;

    myqsort(v, left, last - 1, comp, reverse);
    myqsort(v, last + 1, right, comp, reverse);
}

/* ---------- comparison functions ---------- */

int numcmp(const char *s1, const char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

int foldcmp(const char *s1, const char *s2)
{
    char c1, c2;

    while (*s1 || *s2) {
        c1 = tolower(*s1);
        c2 = tolower(*s2);
        if (c1 != c2)
            return c1 - c2;
        if (*s1) s1++;
        if (*s2) s2++;
    }
    return 0;
}

#define isdir(c) (isalnum(c) || (c) == ' ' || (c) == '\t')

int dircmp(const char *s1, const char *s2, int dummy)
{
    char c1, c2;

    while (1) {
        while (*s1 && !isdir(*s1)) s1++;
        while (*s2 && !isdir(*s2)) s2++;

        c1 = *s1;
        c2 = *s2;

        if (fold) {
            c1 = tolower(c1);
            c2 = tolower(c2);
        }

        if (c1 != c2)
            return c1 - c2;

        if (c1 == '\0')
            return 0;

        s1++;
        s2++;
    }
}
