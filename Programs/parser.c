#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define EXPRESSION_ERROR (-1)

/* return the next character from stdin without consuming it */
int peekchar(void) {
    int c;

    c = getchar();
    if(c != EOF) ungetc(c, stdin);      /* puts it back */

    return c;
}

/* read an integer written in decimal notation from stdin until the first
/* non-digit and return it.  Returns 0 if there are no digits. */
int readNumber(void) {
    int accumulator;        /* the number so far */
    int c;                  /* next character */

    accumulator = 0;

    while((c = peekchar()) != EOF && isdigit(c)) {
        c = getchar();                      /* consume it */
        accumulator *= 10;                  /* shift previous digits over */
        accumulator += (c - '0');           /* add decimal value of new digit */
    }

    return accumulator;
}

/* read an expression from stdin and return its value */
/* returns EXPRESSION_ERROR on error */
int  readExpression(void) {
    int e1;                 /* value of the first sub-expression */
    int e2;                 /* value of the second sub-expression */
    int c;
    int op;                 /* operation: '+' or '*' */

    c = peekchar();

    if(c == '(') {
        c = getchar();

        e1 = readExpression();
        op = getchar();
        e2 = readExpression();

        c = getchar();

        if(c != ')') return EXPRESSION_ERROR;

        switch (op) {
            case '*':
                return e1 * e2;
                break;
            case '+':
                return e1 + e2;
                break;
            default:
                return EXPRESSION_ERROR;
                break;
        }
    } else if(isdigit(c)) {
        return readNumber();
    } else {
        return EXPRESSION_ERROR;
    }
}

int main(void) {
    printf("%d", readExpression());

    return EXIT_SUCCESS;
}