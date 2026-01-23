#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;

    return NULL;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;

        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->defn);
    }

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}

/* undef: remove name from hashtab */
void undef(char *name)
{
    struct nlist *np, *prev = NULL;
    unsigned hashval = hash(name);

    for (np = hashtab[hashval]; np != NULL; prev = np, np = np->next) {
        if (strcmp(name, np->name) == 0) {
            if (prev == NULL)
                hashtab[hashval] = np->next;
            else
                prev->next = np->next;

            free(np->name);
            free(np->defn);
            free(np);
            return;
        }
    }
}

/* test program */
int main(void)
{
    install("MAX", "100");
    install("MIN", "1");

    printf("Before undef:\n");
    printf("MAX = %s\n", lookup("MAX")->defn);

    undef("MAX");

    printf("\nAfter undef:\n");
    if (lookup("MAX") == NULL)
        printf("MAX is undefined\n");

    return 0;
}
