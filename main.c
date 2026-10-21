#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <windows.h>

int homeScreen()
{
    /*
    ANSI escape sequences
    move cursor to row 1, column 1 (ESC[1;1H), then clear the entire screen (ESC[2J)
    ESC = \e = \x1b
    */
    printf("\x1b[1;1H\x1b[2J");

    // printing ascii art

    FILE *ascii;
    ascii = fopen("ascii/future.txt", "r");
    if (ascii == NULL)
    {
        fprintf(stderr, "CAN'T OPEN ASCII ART");
        fclose(ascii);
        return -1;
    }

    int ch;
    while ((ch = fgetc(ascii)) != EOF)
        putchar(ch);

    fclose(ascii);

    // ascii art printed

    printf("\n1. Add Employee\n");
    printf("2. Update Employee\n");
    printf("3. Search Employees\n");
    printf("4. Display Employees Record\n");
    printf("5. Exit\n");
}

void main()
{
    SetConsoleOutputCP(65001); // Setting console to UTF-8 formatting
    unsigned short choice;
    homeScreen();
}