#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <time.h>

#define FILENAME "employees.dat"
#define MAX_NAME_LEN 128 // Maximum amount of characters for name
#define MAX_DEPT_LEN 64  // Maximum amount of characters for department

// Data structure to store details about the Employee
typedef struct{
    int id;
    char name[MAX_NAME_LEN];
    char department[MAX_DEPT_LEN];
    float salary;
} Employee;

// file_ops.c
Employee *loadDataFromFile(int count);
int saveToFile(Employee emp[], int count);
time_t loadTimeStampFromFile();
int loadCountFromFile();
int updateEmployeeData(Employee data, int index);

// employee_ops.c
int addEmployee(int count);
void displayAllRecord();
int searchById(int id);
int updateEmployee(int id);

#endif