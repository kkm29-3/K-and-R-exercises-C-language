#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES   5000
#define MAXLEN     1000
#define MAXFIELDS  10

char *lineptr[MAXLINES];

struct fieldopt {
    int numeric;
    int fold;
    int dir;
} fieldopts[MAXFIELDS];

int nfields = 0;

/* prototypes */
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void myqsort(void *v[], int left, int right,
             int (*comp)(const void *, const void *));
int fieldcmp(const void *p1, const void *p2);
int numcmp(const char *s1, const char *s2);
int strfieldcmp(const char *s1, const char *s2, struct fieldopt opt);
void extractfield(const char *line, int fieldno, char *out);

/* ---------------- main ---------------- */
int main(int argc, char *argv[])
{
    int nlines;
    int i;

    for (i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-k", 2) == 0) {
            nfields = atoi(argv[i] + 2);
            fieldopts[nfields - 1].numeric = 0;
            fieldopts[nfields - 1].fold = 0;
            fieldopts[nfields - 1].dir = 0;
        } else if (argv[i][0] == '-') {
            if (argv[i][1] == 'n')
                fieldopts[nfields - 1].numeric = 1;
            else if (argv[i][1] == 'f')
                fieldopts[nfields - 1].fold = 1;
            else if (argv[i][1] == 'd')
                fieldopts[nfields - 1].dir = 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        myqsort((void **)lineptr, 0, nlines - 1, fieldcmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too large\n");
        return 1;
    }
}

/* ---------------- sorting ---------------- */
void myqsort(void *v[], int left, int right,
             int (*comp)(const void *, const void *))
{
    int i, last;
    void swap(void *v[], int i, int j);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    myqsort(v, left, last - 1, comp);
    myqsort(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* ---------------- comparison ---------------- */
int fieldcmp(const void *p1, const void *p2)
{
    const char *l1 = *(const char **)p1;
    const char *l2 = *(const char **)p2;
    char f1[MAXLEN], f2[MAXLEN];
    int i, cmp;

    for (i = 0; i < nfields; i++) {
        extractfield(l1, i, f1);
        extractfield(l2, i, f2);

        if (fieldopts[i].numeric)
            cmp = numcmp(f1, f2);
        else
            cmp = strfieldcmp(f1, f2, fieldopts[i]);

        if (cmp != 0)
            return cmp;
    }
    return 0;
}

int numcmp(const char *s1, const char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

/* correct directory + fold comparison */
int strfieldcmp(const char *s1, const char *s2, struct fieldopt opt)
{
    char c1, c2;

    for (;;) {
        if (opt.dir) {
            while (*s1 && !isalnum(*s1) && *s1 != ' ')
                s1++;
            while (*s2 && !isalnum(*s2) && *s2 != ' ')
                s2++;
        }

        c1 = *s1;
        c2 = *s2;

        if (opt.fold) {
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

/* ---------------- field extraction ---------------- */
void extractfield(const char *line, int fieldno, char *out)
{
    int i = 0;

    while (*line && fieldno > 0) {
        while (*line && !isspace(*line))
            line++;
        while (isspace(*line))
            line++;
        fieldno--;
    }

    while (*line && !isspace(*line))
        out[i++] = *line++;

    out[i] = '\0';
}

/* ---------------- input/output ---------------- */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while (fgets(line, MAXLEN, stdin) != NULL) {
        len = strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';

        p = malloc(len + 1);
        if (p == NULL)
            return -1;

        strcpy(p, line);
        lineptr[nlines++] = p;

        if (nlines >= maxlines)
            return -1;
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}
