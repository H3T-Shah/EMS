#include <stdio.h>
#include <stdlib.h> // free()
#include "employee.h"
#include "ui.h"

/*
 * Adds new employees to the record
 * Returns the value of saveToFile() (negative means something went wrong)
 */
int addEmployee(int count)
{
    Employee data[count];

    for (int i = 0; i < count; i++)
    {
        printf("\n  " C_BOLD "Employee %d of %d" C_RESET "\n\n", i + 1, count);

        // The read...() helpers (see ui.c) keep asking until the input is valid.
        // readLine() uses fgets() inside, so names with spaces work too.
        data[i].id = readInt("ID Number", 1, MAX_ID);
        readLine("Name", data[i].name, MAX_NAME_LEN);
        readLine("Department", data[i].department, MAX_DEPT_LEN);
        data[i].salary = readFloat("Salary", 0, MAX_SALARY);
    }

    return saveToFile(data, count);
}

/*
 * Prints every record in a readable table format.
 */
void displayAllRecord()
{
    int count = loadCountFromFile();

    // No file yet (-1) or nothing in it: loadDataFromFile() would exit the program
    if (count <= 0)
    {
        printInfo("No records yet. Add an employee first.");
        return;
    }

    Employee *data = loadDataFromFile(count);

    printEmployeeTable(data, count);
    printf("\n  " C_DIM "%d record%s" C_RESET "\n", count, count == 1 ? "" : "s");

    free(data);
}

/*
 * Linear search by id. Prints the record as a table when found.
 * Returns the index in the record if found, -1 otherwise.
 */
int searchById(int id)
{
    int count = loadCountFromFile();

    if (count <= 0)
        return -1;

    Employee *data = loadDataFromFile(count);

    for (int i = 0; i < count; i++)
        if (data[i].id == id)
        {
            printf("\n  " C_GREEN "Record found:" C_RESET "\n");
            printEmployeeTable(&data[i], 1);

            free(data);
            return i;
        }

    free(data);
    return -1;
}

/*
 * Takes id as an input, finds it via searchById, then asks for and applies
 * new values. Returns 1 on success, 0 if the id wasn't found,
 * 2 if the employee was found but the file could not be updated.
 */
int updateEmployee(int id)
{
    int indexOfEmployee = searchById(id);

    if (indexOfEmployee == -1)
    {
        printError("No employee found with that ID Number.");
        return 0;
    }

    Employee data;

    printf("\n  " C_BOLD "Enter the new details" C_RESET " (every field is required)\n\n");

    data.id = readInt("ID Number", 1, MAX_ID);
    readLine("Name", data.name, MAX_NAME_LEN);
    readLine("Department", data.department, MAX_DEPT_LEN);
    data.salary = readFloat("Salary", 0, MAX_SALARY);

    if (updateEmployeeData(data, indexOfEmployee) == 1)
        return 1;

    return 2;
}
