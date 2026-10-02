#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Using time() function as a seed for rand()
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
int addEmployee(int count) {

    Employee data[count];

    //Prompt for name, department, salary; store into emp[count]
    for (int i = 0; i < count; i++)
    {
        printf("Employee %d:\n", i + 1);
        printf("Name: ");
        fgets(data[i].name, MAX_NAME_LEN, stdin);

        printf("Department: ");
        fgets(data[i].department, MAX_DEPT_LEN, stdin);

        printf("Salary: ");
        scanf("%f", data[i].salary);

        data[i].id = genrateId();
    }
    // 3. Return count + 1

    /* DROPING THIS IDEA; IT MAKES THINGS VERY COMPLEX
    TODO: Need to implement an index array which keeps track
    of id generated and count/index associated with the id.

    eg. index[count][2] = {{0, 8936},
                    {1, 3276},
                    {2, 2873}};

    The reason why I'm doing this is to implement
    a binary search algorithim, which requires a
    sorted list.
    This way I can read the file at the exact length and
    no need to read the whole file.
    Don't forget, you need to write the first few bytes the length
    of array, so you can keep track of number of employees.
    */
    return count;
}

/*
 * Prints every record in emp[] in a readable table format.
 */
void displayAll(Employee emp[], int count) {

    // TODO:
    // 1. If count == 0, print "No records found" and return
    // 2. Print a header row (ID | Name | Department | Salary)
    // 3. Loop through emp[0..count-1] and print each record

}

/*
 * Linear search by id.
 * Returns the index in emp[] if found, -1 otherwise.
 */
int searchById(Employee emp[], int count, int id) {

    // TODO:
    // Loop i = 0 to count-1, compare emp[i].id == id
    // Return i as soon as you find a match
    // Return -1 if the loop finishes with no match

    return -1;
}

/*
 * Prompts for an id, finds it via searchById, then asks for and applies
 * new values. Returns 1 on success, 0 if the id wasn't found.
 */
int updateEmployee(Employee emp[], int count) {

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
int deleteEmployee(Employee emp[], int *count) {

    // TODO:
    // 1. Prompt for the id to delete
    // 2. int idx = searchById(emp, *count, id)
    // 3. If idx == -1, print "not found" and return 0
    // 4. Otherwise, for i = idx to *count-2: emp[i] = emp[i+1]
    //    (this shifts everything after idx one slot left)
    // 5. Decrement *count and return 1

    return 0;
}