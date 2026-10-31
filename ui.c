#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "ui.h"

#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

// Column widths of the employee table (in characters, not counting the padding).
// With these numbers the whole table is 84 characters wide, the same as the ASCII art.
#define COL_NO 3
#define COL_ID 8
#define COL_NAME 29
#define COL_DEPT 16
#define COL_SAL 12

/* ====================================================================
 *  Small private helpers (static = only visible inside this file)
 * ==================================================================== */

// Prints the string s, n times in a row
static void repeat(const char *s, int n)
{
    for (int i = 0; i < n; i++)
        fputs(s, stdout);
}

// Prints one horizontal edge of a box, e.g. ┌──────┐
static void boxLine(const char *left, const char *mid, const char *right, int width)
{
    printf("  %s", left);
    repeat(mid, width);
    printf("%s\n", right);
}

// Prints one box row with the text centred inside it
static void boxCentered(const char *text, int width)
{
    int len = (int)strlen(text);
    int left = (width - len) / 2;
    int right = width - len - left;

    if (left < 0)
        left = 0;
    if (right < 0)
        right = 0;

    // "%*s" with "" prints 'left' spaces: the colour codes take no space on screen,
    // so the padding is worked out from the plain text only.
    printf("  " BOX_V "%*s" C_BOLD "%s" C_RESET "%*s" BOX_V "\n", left, "", text, right, "");
}

// Prints one numbered line of the menu box
static void menuRow(int number, const char *label)
{
    printf("  " BOX_V "  " C_CYAN C_BOLD "%d" C_RESET "   %-*s" BOX_V "\n",
           number, UI_WIDTH - 6, label);
}

// Prints one horizontal edge of the employee table
static void tableLine(const char *left, const char *mid, const char *right)
{
    printf("  %s", left);
    repeat(BOX_H, COL_NO + 2);
    printf("%s", mid);
    repeat(BOX_H, COL_ID + 2);
    printf("%s", mid);
    repeat(BOX_H, COL_NAME + 2);
    printf("%s", mid);
    repeat(BOX_H, COL_DEPT + 2);
    printf("%s", mid);
    repeat(BOX_H, COL_SAL + 2);
    printf("%s\n", right);
}

// Prints a coloured tag followed by the message, e.g.  [ERROR] Something broke
static void message(const char *color, const char *label, const char *msg)
{
    printf("  %s" C_BOLD "%s" C_RESET " %s\n", color, label, msg);
}

/*
 * Reads one whole line from the keyboard into buf (without the trailing '\n').
 * Whatever doesn't fit in buf is thrown away, so leftovers can never leak into
 * the next prompt. This replaces scanf() + getchar() tricks.
 */
static void getLine(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL)
    {
        // Keyboard input was closed (Ctrl+Z / Ctrl+D): nothing sensible left to do
        printf("\n");
        exit(0);
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
        buf[len - 1] = '\0';
    else
    {
        // The line was longer than buf: discard the rest of it
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }
}

// Returns 1 if the string is empty or contains only spaces/tabs
static int isBlank(const char *s)
{
    while (*s != '\0')
    {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}

/* ====================================================================
 *  Setup and screen control
 * ==================================================================== */

void initUI(void)
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // So the box characters and ASCII art show correctly

    // Windows needs to be told to understand colour / cursor escape codes
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (out != INVALID_HANDLE_VALUE && GetConsoleMode(out, &mode))
        SetConsoleMode(out, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

void clearScreen(void)
{
    // Clear the whole screen, then move the cursor to row 1, column 1
    printf("\x1b[2J\x1b[1;1H");
}

void pauseScreen(void)
{
    char line[8];

    printf("\n  " C_DIM "Press Enter to return to the menu..." C_RESET);
    getLine(line, sizeof line);
}

/* ====================================================================
 *  Things drawn on screen
 * ==================================================================== */

void printBanner(void)
{
    FILE *art = fopen(ASCII_ART_PATH, "r");

    if (art == NULL)
    {
        // Art file not found (e.g. program started from another folder):
        // show a plain title instead of failing.
        printf("\n");
        boxLine(BOX_TL, BOX_H, BOX_TR, UI_WIDTH);
        boxCentered("EMPLOYEE RECORD MANAGEMENT", UI_WIDTH);
        boxLine(BOX_BL, BOX_H, BOX_BR, UI_WIDTH);
        printf("\n");
        return;
    }

    printf(C_CYAN);

    // Print the art with the same 2-space left margin as the boxes below it
    int ch;
    int atLineStart = 1;
    while ((ch = fgetc(art)) != EOF)
    {
        if (ch == '\r') // Ignore the extra '\r' of Windows-style line endings
            continue;

        if (atLineStart && ch != '\n')
            printf("  ");

        putchar(ch);
        atLineStart = (ch == '\n');
    }

    printf(C_RESET "\n");
    fclose(art);
}

void printStatusBar(void)
{
    int count = loadCountFromFile();
    time_t last = loadTimeStampFromFile();

    printf("  " C_DIM);
    repeat(BOX_H, UI_WIDTH + 2);
    printf(C_RESET "\n");

    if (last == -1)
        printf("  " C_YELLOW "No data file yet" C_RESET " - choose 1 to add your first employee\n");
    else if (last < 0 || count < 0)
        printf("  " C_RED "Data file found, but it could not be read" C_RESET "\n");
    else
    {
        char when[40] = "unknown";
        struct tm *t = localtime(&last);
        if (t != NULL)
            strftime(when, sizeof when, "%d %b %Y, %I:%M %p", t);

        printf("  " C_GREEN C_BOLD "%d" C_RESET " record%s on file   " BOX_V "   Last saved: " C_BOLD "%s" C_RESET "\n",
               count, count == 1 ? "" : "s", when);
    }

    printf("  " C_DIM);
    repeat(BOX_H, UI_WIDTH + 2);
    printf(C_RESET "\n");
}

void printMenu(void)
{
    printf("\n");
    boxLine(BOX_TL, BOX_H, BOX_TR, UI_WIDTH);
    boxCentered("MAIN MENU", UI_WIDTH);
    boxLine(BOX_LT, BOX_H, BOX_RT, UI_WIDTH);
    menuRow(1, "Add Employee");
    menuRow(2, "Update Employee");
    menuRow(3, "Search Employees");
    menuRow(4, "Display Employees Record");
    menuRow(5, "Exit");
    boxLine(BOX_BL, BOX_H, BOX_BR, UI_WIDTH);
    printf("\n");
}

void printHeading(const char *title)
{
    printf("\n");
    boxLine(BOX_TL, BOX_H, BOX_TR, UI_WIDTH);
    boxCentered(title, UI_WIDTH);
    boxLine(BOX_BL, BOX_H, BOX_BR, UI_WIDTH);
    printf("\n");
}

void printSuccess(const char *msg)
{
    printf("\n");
    message(C_GREEN, "[ OK ]", msg);
}

void printError(const char *msg)
{
    printf("\n");
    message(C_RED, "[ERROR]", msg);
}

void printInfo(const char *msg)
{
    printf("\n");
    message(C_YELLOW, "[INFO]", msg);
}

// Draws emp[0..count-1] as a table. Long names/departments are cut to fit their column.
void printEmployeeTable(const Employee emp[], int count)
{
    tableLine(BOX_TL, BOX_TT, BOX_TR);

    printf("  " BOX_V " " C_BOLD C_CYAN "%-*s" C_RESET " " BOX_V
           " " C_BOLD C_CYAN "%-*s" C_RESET " " BOX_V
           " " C_BOLD C_CYAN "%-*s" C_RESET " " BOX_V
           " " C_BOLD C_CYAN "%-*s" C_RESET " " BOX_V
           " " C_BOLD C_CYAN "%*s" C_RESET " " BOX_V "\n",
           COL_NO, "#",
           COL_ID, "ID",
           COL_NAME, "Name",
           COL_DEPT, "Department",
           COL_SAL, "Salary");

    tableLine(BOX_LT, BOX_X, BOX_RT);

    for (int i = 0; i < count; i++)
    {
        // %-*.*s  =  left-aligned, padded to the column width AND cut at the column width
        printf("  " BOX_V " %*d " BOX_V " %*d " BOX_V " %-*.*s " BOX_V " %-*.*s " BOX_V " %*.2f " BOX_V "\n",
               COL_NO, i + 1,
               COL_ID, emp[i].id,
               COL_NAME, COL_NAME, emp[i].name,
               COL_DEPT, COL_DEPT, emp[i].department,
               COL_SAL, emp[i].salary);
    }

    tableLine(BOX_BL, BOX_BT, BOX_BR);
}

/* ====================================================================
 *  Safe keyboard input
 * ==================================================================== */

// Asks until the user types something that isn't empty
void readLine(const char *prompt, char *buf, int size)
{
    for (;;)
    {
        printf("  %s: ", prompt);
        getLine(buf, size);

        if (!isBlank(buf))
            return;

        message(C_RED, "[ERROR]", "This field cannot be empty.");
    }
}

// Asks until the user types a whole number between min and max (inclusive)
int readInt(const char *prompt, int min, int max)
{
    char line[64];

    for (;;)
    {
        printf("  %s: ", prompt);
        getLine(line, sizeof line);

        char *end;
        long value = strtol(line, &end, 10);
        int parsed = (end != line); // Did at least one digit get read?

        while (isspace((unsigned char)*end))
            end++;

        if (parsed && *end == '\0' && value >= min && value <= max)
            return (int)value;

        char msg[80];
        snprintf(msg, sizeof msg, "Please enter a whole number from %d to %d.", min, max);
        message(C_RED, "[ERROR]", msg);
    }
}

// Asks until the user types a number between min and max (inclusive)
float readFloat(const char *prompt, float min, float max)
{
    char line[64];

    for (;;)
    {
        printf("  %s: ", prompt);
        getLine(line, sizeof line);

        char *end;
        double value = strtod(line, &end);
        int parsed = (end != line);

        while (isspace((unsigned char)*end))
            end++;

        if (parsed && *end == '\0' && value >= min && value <= max)
            return (float)value;

        char msg[80];
        snprintf(msg, sizeof msg, "Please enter a number from %.0f to %.0f.", min, max);
        message(C_RED, "[ERROR]", msg);
    }
}
