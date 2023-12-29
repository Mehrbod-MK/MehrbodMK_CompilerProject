// MehrbodMK_CompilerProject.cpp
// Developer:  Mehrbod Molla Kazemi
// Professor: Dr. Nasim Vatani
// Date: 08 Dey 1402 (29 December 2023)

// This project is a 'syntax-analyzer', one of the phases from the frontend of a compiler.

// The grammer is this:
/* 
*  EXPR -> ID = EXPR2
*  EXPR2 -> id | EXPR2 + | EXPR2 - | EXPR2 * | EXPR2 / | EXPR2 %
*  NUMBER -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
*  ID -> a | b | c | ... | y | z
*/

#include <iostream>
#include <stdio.h>

using namespace std;

char lookahead = 0;

// Function prototypes.
void MATCH(char);
void EXPR();
void ID();
void EXPR2();
void NUMBER();
char IS_ID(char);
char IS_NUMBER(char);

void MATCH(char symbol)
{
    while (lookahead == ' ' || lookahead == '\t')
        lookahead = getchar();

    // Ignore blank CR / LF.
    /*if (lookahead == 10 || lookahead == 13)
        lookahead = getchar();*/

    if (lookahead == symbol)
        lookahead = getchar();
    else
    {
        cout << "ERROR!" << endl << endl;
        exit(-1);
    }
}

void EXPR()
{
    while (lookahead == ' ' || lookahead == '\t')
        lookahead = getchar();

    ID();
    MATCH('=');
    EXPR2();
}

void ID()
{
    while (lookahead == ' ' || lookahead == '\t')
        lookahead = getchar();

    char mtch = IS_ID(lookahead);

    if(mtch)
        MATCH(mtch);
}

char IS_ID(char a)
{
    while (lookahead == ' ' || lookahead == '\t')
        lookahead = getchar();

    for (int c = 'a'; c <= 'z'; c++)
        if (lookahead == c)
            return c;

    return 0;
}

char IS_NUMBER(char a)
{
    while (lookahead == ' ' || lookahead == '\t')
        lookahead = getchar();

    for (int c = '0'; c <= '9'; c++)
        if (lookahead == c)
            return c;

    return 0;
}

void EXPR2()
{
    while (lookahead == ' ' || lookahead == '\t')
        lookahead = getchar();

    // Check if ID.
    char match = IS_ID(lookahead);
    if (match)
    {
        ID();
        return;
    }

    // Check if NUMBER.
    match = IS_NUMBER(lookahead);
    if (match)
    {
        NUMBER();
        return;
    }

    // Otherwise, one of the EXPR2 terms.
    EXPR2();
    
    // Match trailing symbols.
    switch (lookahead)
    {
    case '+':
            MATCH('+');
            break;

    case '-':
        MATCH('-');
        break;

    case '*':
        MATCH('*');
        break;

    case '/':
        MATCH('/');
        break;

    case '%':
        MATCH('%');
        break;
    }
}

void NUMBER()
{
    char mtch = IS_NUMBER(lookahead);

    if (mtch)
        MATCH(mtch);
}

int main()
{
    cout << "** MehrbodMK_CompilerProject.cpp **\n** Developer:  Mehrbod Molla Kazemi **\n** Professor: Dr. Nasim Vatani **\n** Date: 08 Dey 1402 (29 December 2023) **\n\n";
    cout << "GRAMMAR:\n1- EXPR -> ID = EXPR2\n2- EXPR2 -> ID | NUMBER | EXPR2 + | EXPR2 - | EXPR2 * | EXPR2 / | EXPR2 %\n3- NUMBER -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9\n4- ID -> a | b | c | ... | y | z\n\n";

    cout << "Lotfan ebarat morede nazar ra vared karde ta nahv barresi shavad.):\n\n";

    lookahead = getchar();

    EXPR();
    cout << "Accepted." << endl << endl;

    return 0;
}