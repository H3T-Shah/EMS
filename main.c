#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <windows.h>

int homeScreen()
{
    /*
    REGEX HACK
    /e provides an escape
    and e [1;1H] place your cursor in the upper right corner of the console screen
    and e [2J adds a space to the top of all existing screen characters
    */
    printf("\e[1;1H\e[2J");

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