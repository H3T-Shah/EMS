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
 * Adds a new employee to emp[] (prompts the user for details).
 * Returns the new count (old count + 1), or the unchanged count if full.
 */
int addEmployee()
{

    int count;
    printf("How many employee you want to add?\n: ");
    scanf("%d", &count);
    getchar(); // To catch the \n from the above scanf

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

    // Implement logic of saving the above data in file.

    return count;
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
int searchById()
{

    int count = loadCountFromFile();
    Employee *data = loadDataFromFile(count);
    int id;

    printf("ID of the employee you want to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
        if(data[i].id == id)
        {
            printf("Employee %d:\n\tId:%d\n\tName:%s\n\tDepartment:%s\n\tSalary:%.2f\n",
               i, data[i].id, data[i].name, data[i].department, data[i].salary);
            return i;
        }

    return -1;
}

/*
 * Prompts for an id, finds it via searchById, then asks for and applies
 * new values. Returns 1 on success, 0 if the id wasn't found.
 */
int updateEmployee(Employee emp[], int count)
{

    // TODO:
    // 1. Prompt for the id to update
    // 2. int idx = searchById(emp, count, id)
    // 3. If idx == -1, print "not found" and return 0
    // 4. Otherwise prompt for new name/department/salary,
    //    overwrite emp[idx], and return 1

    return 0;
}

/*
 * Prompts for an id, finds it, and removes it by shifting later
 * records one position left. Updates *count.
 * Returns 1 on success, 0 if the id wasn't found.
 */
int deleteEmployee(Employee emp[], int *count)
{

    // TODO:
    // 1. Prompt for the id to delete
    // 2. int idx = searchById(emp, *count, id)
    // 3. If idx == -1, print "not found" and return 0
    // 4. Otherwise, for i = idx to *count-2: emp[i] = emp[i+1]
    //    (this shifts everything after idx one slot left)
    // 5. Decrement *count and return 1

    return 0;
}