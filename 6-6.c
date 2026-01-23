#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define HASHSIZE 101
#define BUFSIZE 100

/* ---------- hash table ---------- */
struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

/* ---------- getch / ungetch ---------- */
static char buf[BUFSIZE];
static int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

/* ---------- utility ---------- */
unsigned hash(char *s) {
    unsigned hashval = 0;
    while (*s)
        hashval = *s++ + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

char *strdup_(char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p)
        strcpy(p, s);
    return p;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = malloc(sizeof(*np));
        if (!np || !(np->name = strdup_(name)))
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->defn);
    }
    if (!(np->defn = strdup_(defn)))
        return NULL;
    return np;
}

/* ---------- getword ---------- */
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

/* ---------- main ---------- */
int main(void) {
    char word[MAXWORD];
    char name[MAXWORD];
    char defn[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (strcmp(word, "#define") == 0) {
            getword(name, MAXWORD);   // macro name
            getword(defn, MAXWORD);   // macro definition
            install(name, defn);
        } else {
            struct nlist *np = lookup(word);
            if (np)
                printf("%s", np->defn);
            else
                printf("%s", word);
        }
    }
    return 0;
}

//example input:
//innput.c
// #define MAX 100
// #define PI 3.14

// int a = MAX;
// float b = PI;

//example output:
// int a = 100;
// float b = 3.14;

