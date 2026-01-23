#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES   5000
#define MAXLEN     1000
#define MAXFIELDS  10

/* Windows compatibility */
#ifdef _WIN32
#define strcasecmp _stricmp
#endif

char *lineptr[MAXLINES];

/* Per-field options */
typedef struct {
    int numeric;
    int fold;
    int directory;
} FieldOpt;

FieldOpt fieldopt[MAXFIELDS];
int nfields = 0;

/* Prototypes */
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort_(void *v[], int left, int right,
            int (*comp)(const void *, const void *));
int fieldcmp(const void *s1, const void *s2);

char *getfield(const char *line, int fieldno, char *buf);
int numcmp(const char *s1, const char *s2);
int dircmp(const char *s1, const char *s2, int fold);

/* ================= MAIN ================= */

int main(int argc, char *argv[])
{
    int nlines;

    /* initialize field options */
    for (int i = 0; i < MAXFIELDS; i++)
        fieldopt[i] = (FieldOpt){0, 0, 0};

    /* parse command line */
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-k", 2) == 0) {
            int f = argv[i][2] - '0';
            if (f < 0 || f >= MAXFIELDS) {
                fprintf(stderr, "Invalid field number\n");
                exit(1);
            }

            if (f + 1 > nfields)
                nfields = f + 1;

            for (char *p = argv[i] + 3; *p; p++) {
                if (*p == 'n') fieldopt[f].numeric = 1;
                else if (*p == 'f') fieldopt[f].fold = 1;
                else if (*p == 'd') fieldopt[f].directory = 1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_((void **)lineptr, 0, nlines - 1, fieldcmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        fprintf(stderr, "Input too big to sort\n");
        return 1;
    }
}

/* ================= SORT ================= */

void qsort_(void *v[], int left, int right,
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
    qsort_(v, left, last - 1, comp);
    qsort_(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* ================= FIELD COMPARISON ================= */

int fieldcmp(const void *s1, const void *s2)
{
    const char *l1 = *(const char **)s1;
    const char *l2 = *(const char **)s2;

    char a[MAXLEN], b[MAXLEN];

    for (int f = 0; f < nfields; f++) {
        getfield(l1, f, a);
        getfield(l2, f, b);

        int r;
        if (fieldopt[f].numeric)
            r = numcmp(a, b);
        else if (fieldopt[f].directory)
            r = dircmp(a, b, fieldopt[f].fold);
        else
            r = fieldopt[f].fold ? strcasecmp(a, b)
                                  : strcmp(a, b);

        if (r != 0)
            return r;
    }
    return 0;
}

/* ================= HELPERS ================= */

char *getfield(const char *line, int fieldno, char *buf)
{
    while (*line && fieldno > 0) {
        while (*line && !isspace(*line)) line++;
        while (*line && isspace(*line)) line++;
        fieldno--;
    }

    int i = 0;
    while (*line && !isspace(*line))
        buf[i++] = *line++;

    buf[i] = '\0';
    return buf;
}

int numcmp(const char *s1, const char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);
    return (v1 < v2) ? -1 : (v1 > v2);
}

int dircmp(const char *s1, const char *s2, int fold)
{
    char a, b;
    do {
        while (*s1 && !isalnum(*s1) && *s1 != ' ') s1++;
        while (*s2 && !isalnum(*s2) && *s2 != ' ') s2++;

        a = fold ? tolower(*s1) : *s1;
        b = fold ? tolower(*s2) : *s2;

        if (a != b)
            return a - b;

        if (*s1) s1++;
        if (*s2) s2++;
    } while (a && b);

    return 0;
}

/* ================= INPUT / OUTPUT ================= */

int readlines(char *lineptr[], int maxlines)
{
    char line[MAXLEN];
    int nlines = 0;

    while (fgets(line, MAXLEN, stdin)) {
        if (nlines >= maxlines)
            return -1;

        line[strcspn(line, "\n")] = '\0';
        lineptr[nlines++] = strdup(line);
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}
