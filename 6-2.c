#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXLIST 100

/* tree node */
struct tnode {
    char *word;                 /* representative word */
    char *list[MAXLIST];        /* words with same prefix */
    int count;                  /* number of words */
    struct tnode *left;
    struct tnode *right;
};

int prefix = 6;

/* prototypes */
int getword(char *, int);
int iskeyword(char *);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);

/* C keywords */
const char *keywords[] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof",
    "static","struct","switch","typedef","union","unsigned","void",
    "volatile","while"
};

#define NKEYS (sizeof keywords / sizeof keywords[0])

/* main */
int main(int argc, char *argv[]) {
    struct tnode *root = NULL;
    char word[MAXWORD];

    if (argc > 1)
        prefix = atoi(argv[1]);

    while (getword(word, MAXWORD) != EOF) {
        if ((isalpha(word[0]) || word[0] == '_') && !iskeyword(word))
            root = addtree(root, word);
    }

    treeprint(root);
    return 0;
}

/* add word to tree */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->list[0] = p->word;
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strncmp(w, p->word, prefix)) == 0) {
        if (strcmp(w, p->word) != 0)
            p->list[p->count++] = strdup(w);
    }
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

/* print tree in order */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);

        if (p->count > 1) {
            printf("\nGroup (%.*s...):\n", prefix, p->word);
            for (int i = 0; i < p->count; i++)
                printf("  %s\n", p->list[i]);
        }

        treeprint(p->right);
    }
}

/* keyword check */
int iskeyword(char *word) {
    for (int i = 0; i < NKEYS; i++)
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    return 0;
}

/* get next word, skip comments & strings */
int getword(char *word, int lim) {
    int c, d;
    char *w = word;

    while (isspace(c = getchar()))
        ;

    if (c == '/') {
        if ((d = getchar()) == '/') {        /* single-line comment */
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            return getword(word, lim);
        }
        else if (d == '*') {                 /* multi-line comment */
            while ((c = getchar()) != EOF)
                if (c == '*' && getchar() == '/')
                    break;
            return getword(word, lim);
        }
        else
            ungetc(d, stdin); // put back d, stdin will read it again
    }

    if (c == '"' || c == '\'') {             /* string or char */
        int quote = c;
        while ((c = getchar()) != quote && c != EOF)
            if (c == '\\')
                getchar();
        return getword(word, lim);
    }

    if (c == EOF)
        return EOF;

    *w++ = c;

    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        c = getchar();
        if (!isalnum(c) && c != '_') {
            ungetc(c, stdin);
            break;
        }
        *w = c;
    }
    *w = '\0';
    return word[0];
}


//input maually in cmd window:
// int computeSum;
// int computeAvg;
// int computeTotal;
// int compare;
// int complexValue;
// int computer;

//then run clrl+z ENTER to end input and see output.
//In Windows CMD,
// (👉 Ctrl + Z then Enter means: “I’m done giving input”
//CMD has NO automatic EOF
// Unlike Linux/macOS, Windows does not have a file-end signal from keyboard.)
// Expected output:
// Group (comp...):     
//   computeSum
//   computeAvg
//   computeTotal
//   compare
//   complexValue
//   computer
