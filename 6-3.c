// Ignore noise words like:
// the, and, is, of, to, a, in, that, it, for

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXLINES 100
#define NOISECOUNT 10

/* -------- Data Structures -------- */

struct linelist {
    int lines[MAXLINES];
    int count;
};

struct tnode {
    char *word;
    struct linelist ll;
    struct tnode *left;
    struct tnode *right;
};

/* -------- Noise Words -------- */

char *noise[NOISECOUNT] = {
    "the", "and", "is", "of", "to",
    "a", "in", "that", "it", "for"
};

/* -------- Function Prototypes -------- */

int getword(char *, int);
int isnoise(char *);
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *strdup_(char *);

/* -------- Globals -------- */

int lineno = 1;

/* -------- Main -------- */

int main(void)
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && !isnoise(word))
            root = addtree(root, word, lineno);

    treeprint(root);
    return 0;
}

/* -------- Tree Functions -------- */

struct tnode *addtree(struct tnode *p, char *w, int line)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup_(w); //p->word denotes pointer to word
        p->ll.lines[0] = line;
        p->ll.count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        if (p->ll.lines[p->ll.count - 1] != line)
            p->ll.lines[p->ll.count++] = line;
    } else if (cond < 0)
        p->left = addtree(p->left, w, line);
    else
        p->right = addtree(p->right, w, line);

    return p;
}

void treeprint(struct tnode *p)
{
    int i;

    if (p != NULL) {
        treeprint(p->left);
        printf("%-15s:", p->word);
        for (i = 0; i < p->ll.count; i++)
            printf(" %d", p->ll.lines[i]);
        printf("\n");
        treeprint(p->right);
    }
}

/* -------- Helpers -------- */

int isnoise(char *w)
{
    for (int i = 0; i < NOISECOUNT; i++)
        if (strcmp(w, noise[i]) == 0)
            return 1;
    return 0;
}

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup_(char *s)
{
    char *p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* -------- getword -------- */

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == '\n')
        lineno++;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = getchar())) {
            ungetc(*w, stdin);
            break;
        }

    *w = '\0';
    return word[0];
}

//run with input file
// 6-3 < test.c
// expected input (example):
// This is a test.
// This test is simple.
// The test is useful.

// expected output:
// simple         : 2
// test           : 1 2 3
// this           : 1 2
// useful         : 3

