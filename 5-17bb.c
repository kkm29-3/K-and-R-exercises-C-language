#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN   1000
#define MAXFIELDS 10

char *lineptr[MAXLINES];

/* ---------- field option structure ---------- */
typedef struct {
    int field;
    int numeric;
    int fold;
    int directory;
} FieldOpt;

FieldOpt fields[MAXFIELDS];
int nfields = 0;

/* ---------- function prototypes ---------- */
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort_(void *v[], int left, int right, int (*comp)(const void *, const void *));
int fieldcmp(const char *s1, const char *s2);
char *getfield(const char *line, int field);

/* ---------- main ---------- */
int main(int argc, char *argv[])
{
    int nlines;

    /* parse arguments */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-k") == 0 && i + 1 < argc) {
            fields[nfields].field = atoi(argv[++i]);
            fields[nfields].numeric = 0;
            fields[nfields].fold = 0;
            fields[nfields].directory = 0;

            /* read options following -k */
            while (i + 1 < argc && argv[i + 1][0] == '-') {
                i++;
                if (strchr(argv[i], 'n')) fields[nfields].numeric = 1;
                if (strchr(argv[i], 'f')) fields[nfields].fold = 1;
                if (strchr(argv[i], 'd')) fields[nfields].directory = 1;
            }
            nfields++;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_((void **) lineptr, 0, nlines - 1,
               (int (*)(const void *, const void *))fieldcmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big\n");
        return 1;
    }
}

/* ---------- field comparison ---------- */
int fieldcmp(const char *s1, const char *s2)
{
    for (int i = 0; i < nfields; i++) {
        char *f1 = getfield(s1, fields[i].field);
        char *f2 = getfield(s2, fields[i].field);

        int result;

        if (fields[i].numeric) {
            double v1 = atof(f1);
            double v2 = atof(f2);
            result = (v1 < v2) ? -1 : (v1 > v2);
        } else {
            while (*f1 || *f2) {
                char c1 = *f1;
                char c2 = *f2;

                if (fields[i].directory) {
                    while (c1 && !isalnum(c1) && !isspace(c1)) c1 = *++f1;
                    while (c2 && !isalnum(c2) && !isspace(c2)) c2 = *++f2;
                }

                if (fields[i].fold) {
                    c1 = tolower(c1);
                    c2 = tolower(c2);
                }

                if (c1 != c2)
                    return c1 - c2;

                if (*f1) f1++;
                if (*f2) f2++;
            }
            result = 0;
        }

        if (result != 0)
            return result;
    }
    return 0;
}

/* ---------- get Nth field ---------- */
char *getfield(const char *line, int field)
{
    static char buf[MAXLEN];
    int count = 1;

    while (*line && count < field) {
        if (*line == ' ' || *line == '\t')
            count++;
        line++;
    }

    int i = 0;
    while (*line && *line != ' ' && *line != '\t')
        buf[i++] = *line++;
    buf[i] = '\0';

    return buf;
}

/* ---------- quicksort ---------- */
void qsort_(void *v[], int left, int right, int (*comp)(const void *, const void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right)/2);
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

/* ---------- input/output ---------- */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char line[MAXLEN];
    char *p;

    while (fgets(line, MAXLEN, stdin) != NULL) {
        len = strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        p = malloc(len);
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
