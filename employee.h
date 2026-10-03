#ifndef EMPLOYEE_H
#define EMPLOYEE_H

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
int loadFromFile(Employee emp[]);
void saveToFile(Employee emp[], int count);
void nuke();

// employee_ops.c
int addEmployee();
void displayAll(Employee emp[], int count);
int searchById(Employee emp[], int count, int id);
int updateEmployee(Employee emp[], int count);
int deleteEmployee(Employee emp[], int *count);

#endif