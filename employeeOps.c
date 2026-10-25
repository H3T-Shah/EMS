#include <stdio.h>
#include <stdlib.h> // Using srand() & rand(); malloc() & free()
#include <string.h> // Using strlen()
#include <time.h>   // Using time() function as a seed for rand()
#include "employee.h"

int genrateId()
{
    /*
    Setting up seed for rand.
    Seed is current time in number of seconds since Epoch.
    */
    srand(time(0));
    return rand() % (10000 + 1000 + 1) + 1000;
}

/*
 * Adds a new employee to record
 * Returns the new count (old count + 1), or the unchanged count if full.
 */
int addEmployee(int count)
{
    Employee data[count];

    // Prompt for name, department, salary; store into emp[count]
    for (int i = 0; i < count; i++)
    {
        printf("Employee %d:\n", i + 1);
        printf("Name: ");
        fgets(data[i].name, MAX_NAME_LEN, stdin);

        // using fget() to obtain string with spaces included

        printf("Department: ");
        fgets(data[i].department, MAX_DEPT_LEN, stdin);

        // removing trailing new line character
        data[i].name[strlen(data[i].name) - 1] = '\0';
        data[i].department[strlen(data[i].department) - 1] = '\0';

        printf("Salary: ");
        scanf("%f", &data[i].salary);

        // Consume the newline left by the salary scanf so the NEXT
        // loop iteration's fgets() for the name works correctly.
        getchar();

        data[i].id = genrateId();
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
        printf("Employee %d:\n\tId:%d\n\tName:%s\n\tDepartment:%s\n\tSalary:%.2f\n",
               i, data[i].id, data[i].name, data[i].department, data[i].salary);
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

    printf("Existing data of employee you want to update:\n");
    int indexOfEmployee = searchById(id);

    Employee data;
    data.id = id;

    printf("Name: ");
    fgets(data.name, MAX_NAME_LEN, stdin);

    // using fget() to obtain string with spaces included

    printf("Department: ");
    fgets(data.department, MAX_DEPT_LEN, stdin);

    // removing trailing new line character
    data.name[strlen(data.name) - 1] = '\0';
    data.department[strlen(data.department) - 1] = '\0';

    printf("Salary: ");
    scanf("%f", &data.salary);

    // Consume the newline left by the salary scanf
    getchar();
    if(updateEmployeeData(data, indexOfEmployee) == 1)
        return 1;
    return 0;
}