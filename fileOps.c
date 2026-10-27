#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "employee.h"

// TODO: Make different return code for different errors

Employee *loadDataFromFile(int count)
{
    FILE *file;
    file = fopen(FILENAME, "rb");

    if (file == NULL)
    {
        //  Could not open file
        exit(-1);
    }

    Employee *data = malloc(sizeof(Employee) * count);

    fseek(file, sizeof(int) + sizeof(time_t), 0);

    if (fread(data, sizeof(Employee), count, file) != count)
    {
        // Could not read record into data identifier
        exit(-2);
    }
    fclose(file);

    return data;
}

int saveToFile(Employee emp[], int count)
{
    /*
    Structure of file:
    First few bytes (precisely sizeof(time_t)) is the timestamp of last file write.
    Followed by count of employees.
    And finally the data of employees.
    */

    FILE *fileCheck = fopen(FILENAME, "rb");
    // Checking whether file already exists or not
    // If it doesn't, fopen in rb mode will return NULL

    if (fileCheck == NULL)
    {
        /*
         * This if block excutes if file DOES NOT already exists.
         * Because it returns NULL, NO FILE WAS OPENED.
         *
         * Which may be the case if you running the program for the first time.
         * Further implying no saved data from previous session.
         */

        FILE *file = fopen(FILENAME, "wb");

        if (file == NULL)
        {
            // fprintf(stderr, "fopen encountered NULL File while CREATING it\n");
            return -1;
        }

        // Timestamp at the start of file
        time_t timeStamp = time(NULL);

        if (fwrite(&timeStamp, sizeof(timeStamp), 1, file) != 1)
        {
            // fprintf(stderr, "fwrite was NOT able to WRITE timestamp successfully\n");
            fclose(file); // Prevent leak
            return -2;
        }

        // writing count next to the timestamp
        // fwrite returns how many elements was it able to write
        // successfully
        if (fwrite(&count, sizeof(int), 1, file) != 1)
        {
            // fprintf(stderr, "fwrite was NOT able to WRITE count to file\n");
            fclose(file); // Prevent leak
            return -3;
        }

        if (fwrite(emp, sizeof(Employee), count, file) != count)
        {
            // fprintf(stderr, "fwrite was NOT able to WRITE all or some data successfully\n");
            fclose(file); // Prevent leak
            return -4;
        }

        if (fclose(file) == EOF)
        {
            fprintf(stderr,
                    "fclose was NOT able to CLOSE file correctly\n");
            return -5;
        }
    } // End of if statement
    else
    {
        /*
         * This block executes if the file DOES exist.
         * Because fileCheck is not NULL, the file is currently OPEN.
         * You must close it before moving on to update the file.
         */
        fclose(fileCheck);

        FILE *file = fopen(FILENAME, "r+b");

        if (file == NULL)
        {
            // fprintf(stderr, "fopen encountered NULL File while OPENING for update\n");
            return -11;
        }

        // Reading the timeStamp
        time_t oldTimeStamp;
        if (fread(&oldTimeStamp, sizeof(time_t), 1, file) != 1)
        {
            // fprintf(stderr, "Could NOT READ timestamp!");
            fclose(file);
            return -12;
        }
        // After reading the timeStamp, file pointer has moved past it
        // Can implement more descriptive error handling using feof & ferror

        // Will need this to update count after the appending the data as well as
        // it will make the pointer move to the data
        int oldCount;
        if (fread(&oldCount, sizeof(int), 1, file) != 1)
        {
            // fprintf(stderr, "Could NOT READ number of employees (count)!");
            fclose(file);
            return -13;
        }

        // Jumped to the end of file
        fseek(file, 0, SEEK_END);

        // Appending new data
        if (fwrite(emp, sizeof(Employee), count, file) != count)
        {
            // fprintf(stderr, "fwrite was NOT able to APPEND all or some data successfully\n");
            fclose(file); // Prevent leak
            return -14;
        }

        // Jumping to the beginning of file
        // To update timestamp & count

        fseek(file, 0, SEEK_SET);

        time_t newTimeStamp = time(NULL);

        if (fwrite(&newTimeStamp, sizeof(time_t), 1, file) != 1)
        {
            // fprintf(stderr, "fwrite was NOT able to UPDATE timestamp successfully\n");
            fclose(file); // Prevent leak
            return -15;
        }

        int totalCount = oldCount + count;
        if (fwrite(&totalCount, sizeof(int), 1, file) != 1)
        {
            // fprintf(stderr, "fwrite was NOT able to UPDATE count successfully\n");
            fclose(file); // Prevent leak
            return -16;
        }

        // Closing file
        if (fclose(file) == EOF)
        {
            // fprintf(stderr, "fclose was NOT able to CLOSE file correctly\n");
            return -17;
        }
    }
}

time_t loadTimeStampFromFile()
{
    FILE *file;
    file = fopen(FILENAME, "rb");
    if (file == NULL)
    {
        // fprintf(stderr, "Could NOT OPEN FILENAME");
        return -1; // Return if file missing
    }

    time_t timeStamp;
    if (fread(&timeStamp, sizeof(time_t), 1, file) != 1)
    {
        // fprintf(stderr, "Could NOT READ timeStamp");
        return -2;
    }
    fclose(file);
    return timeStamp;
}

int loadCountFromFile()
{
    FILE *file;
    file = fopen(FILENAME, "rb");
    if (file == NULL)
    {
        // fprintf(stderr, "Could NOT OPEN FILENAME");
        return -1; // Return if file missing
    }

    int count;
    fseek(file, sizeof(time_t), SEEK_SET);
    if (fread(&count, sizeof(int), 1, file) != 1)
    {
        // fprintf(stderr, "Could NOT READ count");
        return -2;
    }
    fclose(file);
    return count;
}

int updateEmployeeData(Employee data, int index)
{
    FILE *file = fopen(FILENAME, "r+b");

    if(file == NULL)
    {
        fprintf(stderr, "fopen encountered NULL File while trying to update employee record at index: %d", index);
        return -1;
    }

    // Moving pointer to the employee who's data has to be updated
    fseek(file, sizeof(time_t) + sizeof(int) + sizeof(Employee) * index, SEEK_SET);

    if (fwrite(&data, sizeof(Employee), 1, file) != 1)
    {
        fprintf(stderr, "Could NOT write updated data of employee");
        return -2;
    }

    time_t currTimeStamp = time(NULL);

    // Moving to the start of file
    fseek(file, 0, SEEK_SET);
    if (fwrite(&currTimeStamp, sizeof(time_t), 1, file) != 1)
    {
        // fwrite could not update time stamp
        return -3;
    }

    return 1;
}