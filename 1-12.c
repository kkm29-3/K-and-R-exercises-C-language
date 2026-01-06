#include <stdio.h>

int main(void) {
    int character;
    int previous_character = EOF;

    while ((character = getchar()) != EOF) // reads characters one by one until the end of input is reached.
     {
        if (character == ' ' || character == '\t' || character == '\n') {
            if (previous_character != ' ' && previous_character != '\t' && previous_character != '\n') {
                putchar('\n');
            }
        }
         else 
        {
            putchar(character);
        }

        previous_character = character;
    }

    return 0;
}