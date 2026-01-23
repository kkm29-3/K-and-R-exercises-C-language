#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXNODES 1000

/* tree node */
struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void tree_to_array(struct tnode *);
int getword(char *, int);

/* array for sorting */
struct tnode *node_array[MAXNODES];
int node_count = 0;

/* comparison function for qsort */
int compare(const void *a, const void *b)
{
    struct tnode *x = *(struct tnode **)a;
    struct tnode *y = *(struct tnode **)b;
    return y->count - x->count;   /* decreasing order */
}

int main(void)
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    tree_to_array(root);

    qsort(node_array, node_count, sizeof(struct tnode *), compare);

    for (int i = 0; i < node_count; i++)
        printf("%4d %s\n", node_array[i]->count, node_array[i]->word);

    return 0;
}

/* add a node or increment count */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

/* store tree nodes in array */
void tree_to_array(struct tnode *p)
{
    if (p != NULL) {
        tree_to_array(p->left);
        node_array[node_count++] = p;
        tree_to_array(p->right);
    }
}

/* getword: read next word or character */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getchar()))
        ;

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

//run code in cmd window:;
//user inputs:
//this is a test this is only a test

//then run clrl+z ENTER to end input and see output.
//expected output:
//   2 this
//   2 is
//   2 test
//   1 only
