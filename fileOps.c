#include <stdio.h>
#include <time.h>
#include "employee.h"

// TODO: Make different return code for different errors

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
int saveToFile(Employee emp[], int count)
{

    /*
    Before writing the data I need to check whether it already
    exists or not. If, it has data and I need to update count
    at the start of file.

    What I have in my mind rn:
    try to fopen in read mode and read count & timestamp
    if able to, first update count then append the exsiting
    data.
    */

    /*
    Structure of file:
    First few bytes (precisely sizeof(int)) is the count of data i.e.
    how many records of employee are present.
    Followed by the actual data of employee.
    And at the end is the timestamp at which file was written.
    */

    FILE *file;
    file = fopen(FILENAME, "wb");

    if (file == NULL)
    {
        fprintf(stderr, "fopen encountered NULL File");
        return -1;
    }

    // writing count at the start of the file
    // fwrite returns how many elements was it able to write
    // successfully
    if (fwrite(&count, sizeof(int), 1, file) != 1)
    {
        fprintf(stderr,
                "fwrite was NOT able to write count to file");
        fclose(file); // Prevent leak
        return -1;
    }

    if (fwrite(emp, sizeof(Employee), count, file) != count)
    {
        fprintf(stderr,
                "fwrite was NOT able to write all or some data successfully");
        fclose(file); // Prevent leak
        return -1;
    }

    time_t timeStamp = time(0);

    if (fwrite(&timeStamp, sizeof(timeStamp), 1, file) != 1)
    {
        fprintf(stderr,
                "fwrite was NOT able to write timestamp successfully");
        fclose(file); //Prevent leak
        return -1;
    }

    if(fclose(file) == EOF)
    {
        fprintf(stderr,
                "fclose was NOT able to close file correctly");
        return -1;
    }
}

void nuke()
{
}