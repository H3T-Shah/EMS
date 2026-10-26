#include "employee.h"

#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <time.h>
#include <windows.h>

int homeScreen()
{
    /*
    ANSI escape sequences
    move cursor to row 1, column 1 (ESC[1;1H), then clear the entire screen (ESC[2J)
    ESC = \e = \x1b
    */
    printf("\x1b[1;1H\x1b[2J");

    SetConsoleOutputCP(65001); // Setting console to UTF-8 formatting

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
}

void printOptions()
{
    printf("\n1. Add Employee\n");
    printf("2. Update Employee\n");
    printf("3. Search Employees\n");
    printf("4. Display Employees Record\n");
    printf("5. Exit\n");
}

int main()
{
    unsigned short choice;
    time_t lastWrite;

    homeScreen();

    lastWrite = loadTimeStampFromFile();
    if (lastWrite > 0)
        printf("\nExisting Data Found.\nLast write on %s\n", ctime(&lastWrite));
    else if (lastWrite == -1)
        printf("\nNo Existing data found!\nIntiating a new record.\n");
    else if (lastWrite == -2)
        fprintf(stderr, "\nExisting Data Found but CAN'T READ the last write\n");

    do
    {
        printOptions();
        printf("\nWhat you wanna do?\n: ");
        scanf("%hu", &choice);

        switch (choice)
        {
        case 1:
            int count;
            printf("How many employee you want to add?\n: ");
            scanf("%d", &count);
            getchar(); // To catch the \n from the above scanf
            if (addEmployee(count) == -1)
                fprintf(stderr, "Something went wrong while writing data to record.");
            break;

        case 2:
            int id;
            printf("ID of the employee you want to update: ");
            scanf("%d", &id);
            updateEmployee(id);
            break;

        case 3:
            printf("ID of the employee you want to search: ");
            scanf("%d", &id);
            int index = searchById(id);
            if (index == -1)
                printf("No such employee found!\n");

            break;

        case 4:
            displayAllRecord();
            break;

        // If we don't make this case, default case gets executed
        case 5:
            break;

        default:
            printf("Invalid choice!!\n");
            break;
        }
    } while (choice != 5);
}