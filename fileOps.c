#include <stdio.h>
#include <stdlib.h>
#include "employee.h"

/*
 * Reads all records from FILENAME into emp[].
 * Returns the number of records read (0 if the file doesn't exist yet,
 * e.g. on the very first run).
 */
int loadFromFile(Employee emp[])
{
    int count = 0;

    // TODO:
    // 1. Open FILENAME in binary read mode ("rb")
    // 2. If fopen fails, the file just doesn't exist yet -- return 0
    // 3. Loop: fread one Employee at a time into emp[count],
    //    incrementing count each time, until fread returns 0 (EOF)
    // 4. fclose the file
    // 5. return count

    return count;
}

/*
 * Writes all `count` records from emp[] back to FILENAME,
 * overwriting whatever was there before.
 */
void saveToFile(Employee emp[], int count)
{

    FILE *file;
    file = fopen(FILENAME, "a+b");

    if (file == NULL)
    {
        printf("fopen encountered NULL File");
        return -1;
    }
    // TODO:
    // 1. Open FILENAME in binary write mode ("wb") -- this truncates the file
    // 2. Write the whole array in one call:
    //    fwrite(emp, sizeof(Employee), count, fp)
    // 3. fclose the file
    // One thing to absolutely keep in mind is, I need to write data in append mode.
}

void nuke()
{
}