#include <stdio.h>
#include <stdlib.h> // malloc() & free()
#include <string.h> // Using strlen()
#include <time.h>   // Using time() function as a seed for rand()
#include "employee.h"

/*
 * Adds a new employee to record
 * Returns the value of saveToFile()
 */
int addEmployee(int count)
{
    Employee data[count];

    // Prompt for name, department, salary; store into emp[count]
    for (int i = 0; i < count; i++)
    {
        printf("Employee %d:\n", i + 1);

        printf("  ID Number: ");
        scanf("%d", &data[i].id);

        // Consume the newline left by the ID Number scanf
        getchar();

        // using fget() to obtain string with spaces included

        printf("  Name: ");
        fgets(data[i].name, MAX_NAME_LEN, stdin);

        printf("  Department: ");
        fgets(data[i].department, MAX_DEPT_LEN, stdin);

        // removing trailing new line character
        data[i].name[strlen(data[i].name) - 1] = '\0';
        data[i].department[strlen(data[i].department) - 1] = '\0';

        printf("  Salary: ");
        scanf("%f", &data[i].salary);

        // Consume the newline left by the salary scanf so the NEXT
        // loop iteration's fgets() for the name works correctly.
        getchar();
    }

    /*
    printf("\n__________________________DEBUG__________________________\n");
    for (int i = 0; i < count; i++)
    {
        printf("\nName: %s\nDepartment: %s\nSalary: %f\nId: %d",
               data[i].name,
               data[i].department,
               data[i].salary,
               data[i].id);
    }
    */

    return saveToFile(data, count);
}

/*
 * Prints every record in record in a readable table format.
 */
void displayAllRecord()
{

    int count = loadCountFromFile();

    Employee *data = loadDataFromFile(count);

    for (int i = 0; i < count; i++)
    {
        printf("Employee %d:\n  Id:%d\n  Name:%s\n  Department:%s\n  Salary:%.2f\n",
               i + 1, data[i].id, data[i].name, data[i].department, data[i].salary);
    }

    free(data);
}

/*
 * Linear search by id.
 * Returns the index in emp[] if found, -1 otherwise.
 */
int searchById(int id)
{

    int count = loadCountFromFile();
    Employee *data = loadDataFromFile(count);

    for (int i = 0; i < count; i++)
        if (data[i].id == id)
        {
            printf("Employee %d:\n\tId:%d\n\tName:%s\n\tDepartment:%s\n\tSalary:%.2f\n",
                   i, data[i].id, data[i].name, data[i].department, data[i].salary);
            return i;
        }

    return -1;
}

/*
 * Takes id as an input, finds it via searchById, then asks for and applies
 * new values. Returns 1 on success, 0 if the id wasn't found.
 */
int updateEmployee(int id)
{
    int count = loadCountFromFile();

    int indexOfEmployee = searchById(id);
    if(indexOfEmployee == -1)
    {
        printf("\nDidn't find an employee with ID Number: %d", id);
        return 0;
    }
    printf("Existing data of employee you want to update:\n");
    Employee data;
    printf("#########################################\nUpdate the data:\n");
    printf("  ID Number: ");
    scanf("%d", &data.id);
    // Consume new line left by ID Number scanf
    getchar();

    printf("  Name: ");
    fgets(data.name, MAX_NAME_LEN, stdin);

    // using fget() to obtain string with spaces included

    printf("  Department: ");
    fgets(data.department, MAX_DEPT_LEN, stdin);

    // removing trailing new line character
    data.name[strlen(data.name) - 1] = '\0';
    data.department[strlen(data.department) - 1] = '\0';

    printf("  Salary: ");
    scanf("%f", &data.salary);

    // Consume the newline left by the salary scanf
    getchar();
    if(updateEmployeeData(data, indexOfEmployee) == 1)
        return 1;

    return 2;
}