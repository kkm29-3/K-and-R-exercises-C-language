#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN   1000
#define MAXFIELDS 10

char *lineptr[MAXLINES];

/* field options */
typedef struct {
    int numeric;
    int fold;
    int directory;
} FieldOpt;

FieldOpt fieldopt[MAXFIELDS];
int nfields = 0;

/* function prototypes */
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort_(void *v[], int left, int right,
            int (*comp)(void *, void *));
int fieldcmp(const char *s1, const char *s2);

/* main */
int main(int argc, char *argv[])
{
    int nlines;

    /* parse command-line options */
    while (--argc > 0 && (*++argv)[0] == '-') {
        FieldOpt opt = {0, 0, 0};
        char *p = argv[0] + 1;

        while (*p) {
            if (*p == 'n') opt.numeric = 1;
            else if (*p == 'f') opt.fold = 1;
            else if (*p == 'd') opt.directory = 1;
            p++;
        }
        fieldopt[nfields++] = opt;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_((void **) lineptr, 0, nlines - 1,
               (int (*)(void *, void *)) fieldcmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int fieldcmp(const char *s1, const char *s2)
{
    char f1[MAXLEN], f2[MAXLEN];
    int field = 0;

    while (field < nfields) {
        /* extract field */
        sscanf(s1, "%s", f1);
        sscanf(s2, "%s", f2);

        int result;
        if (fieldopt[field].numeric)
            result = atof(f1) - atof(f2);
        else {
            char *p1 = f1, *p2 = f2;
            while (*p1 && *p2) {
                char c1 = *p1, c2 = *p2;

                if (fieldopt[field].directory) {
                    if (!isalnum(c1) && c1 != ' ') { p1++; continue; }
                    if (!isalnum(c2) && c2 != ' ') { p2++; continue; }
                }
                if (fieldopt[field].fold) {
                    c1 = tolower(c1);
                    c2 = tolower(c2);
                }
                if (c1 != c2)
                    return c1 - c2;
                p1++; p2++;
            }
            result = *p1 - *p2;
        }

        if (result != 0)
            return result;

        /* move to next field */
        s1 = strchr(s1, ' ');
        s2 = strchr(s2, ' ');
        if (!s1 || !s2) break;
        s1++; s2++;
        field++;
    }
    return 0;
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while (fgets(line, MAXLEN, stdin) != NULL) {
        len = strlen(line);
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s", *lineptr++);
}

void qsort_(void *v[], int left, int right,int (*comp)(void *, void *))
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

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

//expected input:
// printf 12
// printf 3
// scanf 25
// scanf 7


//expected output (sorted by first field):
// printf 3
// printf 12
// scanf 7
// scanf 25