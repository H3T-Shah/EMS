#include <stdio.h>
#include "employee.h"
#include "ui.h"

int main()
{
    int choice, count, id, position, result;

    initUI(); // Colours + UTF-8 (see ui.c)

    do
    {
        // Home screen: art, status line, then the menu
        clearScreen();
        printBanner();
        printStatusBar();
        printMenu();

        // readInt() keeps asking until the answer is a number from 1 to 5
        choice = readInt("Choose an option (1-5)", 1, 5);

        // Every action gets its own clean screen
        clearScreen();

        switch (choice)
        {
        case 1:
            printHeading("ADD EMPLOYEES");
            count = readInt("How many employees do you want to add", 1, MAX_ADD);

            // saveToFile() returns a negative number when something goes wrong
            if (addEmployee(count) < 0)
                printError("Something went wrong while writing data to the record.");
            else
                printSuccess("Record saved successfully.");

            pauseScreen();
            break;

        case 2:
            printHeading("UPDATE EMPLOYEE");
            id = readInt("ID of the employee you want to update", 1, MAX_ID);

            // updateEmployee() already reports "not found" itself (returns 0)
            result = updateEmployee(id);
            if (result == 1)
                printSuccess("Employee updated successfully.");
            else if (result == 2)
                printError("Employee found, but the record could not be updated.");

            pauseScreen();
            break;

        case 3:
            printHeading("SEARCH EMPLOYEES");
            id = readInt("ID of the employee you want to search", 1, MAX_ID);

            // searchById() prints the record itself when it finds it
            position = searchById(id);
            if (position == -1)
                printError("No such employee found!");

            pauseScreen();
            break;

        case 4:
            printHeading("EMPLOYEES RECORD");
            displayAllRecord();
            pauseScreen();
            break;

        case 5:
            printInfo("Goodbye!");
            printf("\n");
            break;
        }
    } while (choice != 5);

    return 0;
}
