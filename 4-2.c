/*
 * Simple program: read a line of input, print it, and print its numeric
 * conversion as a double. Implements a custom `get_line` and `atof`.
 */

#include <ctype.h>
#include <stdio.h>

#define MAXLEN 500

/* Read a line into `line`, return length. `max_line_len` limits buffer use. */
int get_line(char line[], unsigned int max_line_len);

/* Convert string to double. Handles optional sign, fractional part, and
 * optional exponent in form [e|E][+|-]digits. Returns the parsed double.
 */
double atof(char s[]);

int main(void) {
    char line[MAXLEN];

    /* Read one line from stdin into `line` (including trailing '\n' if any). */
    get_line(line, MAXLEN);

    /* Print the raw line as read. */
    printf("%s", line);

    /* Convert the line to a double and print it with %f format. */
    printf("%f", atof(line));

    return 0;
}

int get_line(char line[], unsigned int max_line_len) {
    /* Use unsigned to match the unsigned parameter and avoid signed/unsigned
     * comparison warnings when checking bounds. */
    unsigned int i = 0;
    int c;

    /* Read characters until buffer is full or newline encountered. Leave room
     * for the terminating null byte. */
    while (i < max_line_len - 1 && (c = getchar()) != '\n' && c != EOF) {
        line[i] = c;
        ++i;
    }

    /* If newline was found, include it in the stored line. */
    if (c == '\n') {
        line[i++] = c;
    }

    /* Null-terminate the C string and return its length. */
    line[i] = '\0';

    return i;
}

double atof(char s[]) {
    double val;       /* accumulates integer and fractional digits */
    double power;     /* scale factor for fractional digits */
    int i;            /* string index */
    int sign;         /* sign of the whole number (+1 or -1) */
    int exp_sign = 1; /* sign of exponent (+1 or -1) */
    int exp_pwr = 0;  /* exponent magnitude parsed from digits */

    /* Skip leading whitespace */
    for (i = 0; isspace((unsigned char)s[i]); ++i)
        ;

    /* Handle optional sign before the number */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        ++i;
    }

    /* Parse integer part: accumulate digits into `val`. */
    for (val = 0.0; isdigit((unsigned char)s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
    }

    /* If there is a fractional part, parse digits after the decimal point. */
    if (s[i] == '.') {
        ++i; /* skip the decimal point */
    }

    /* For each fractional digit, accumulate into `val` and increase `power` */
    for (power = 1.0; isdigit((unsigned char)s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    /* Handle optional exponent part: look for 'e' or 'E' */
    if (s[i] == 'e' || s[i] == 'E') {
        ++i; /* move past 'e' or 'E' */
        if (s[i] == '-') {
            exp_sign = -1;
            ++i;
        } else if (s[i] == '+') {
            ++i;
        }
    }

    /* Parse exponent digits into exp_pwr. */
    while (isdigit((unsigned char)s[i])) {
        exp_pwr = 10 * exp_pwr + (s[i] - '0');
        ++i;
    }

    /* Apply the exponent: adjust `power` by multiplying/dividing by 10
     * exp_pwr times depending on exponent sign. This effectively scales the
     * value by 10^(exp_sign * exp_pwr). */
    while (exp_pwr > 0) {
        if (exp_sign == -1) {
            /* negative exponent -> multiply power (makes final result smaller) */
            power *= 10.0;
        } else {
            /* positive exponent -> divide power (makes final result larger) */
            power /= 10.0;
        }

        --exp_pwr;
    }

    /* Combine sign, accumulated digits, and scale to produce final double. */
    return sign * val / power;
}