#ifndef UI_H
#define UI_H

#include "employee.h"

/* ---------- Settings you can tweak ---------- */
#define ASCII_ART_PATH "ascii/future.txt" // Same art file you were already using
#define UI_WIDTH 82                       // Inner width of the boxes: 82 + 2 border characters = 84, the width of the art

/* ---------- Limits used when checking what the user types ---------- */
#define MAX_ID 99999999         // 8 digits, so it always fits the table's ID column
#define MAX_SALARY 50000000.0f
#define MAX_ADD 50              // Most employees that can be added in one go

/* ---------- Colours (ANSI escape codes) ---------- */
#define C_RESET "\x1b[0m"
#define C_BOLD "\x1b[1m"
#define C_DIM "\x1b[2m"
#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"
#define C_YELLOW "\x1b[33m"
#define C_CYAN "\x1b[36m"

/*
 * Box-drawing characters.
 * They are written as UTF-8 byte escapes so they print correctly no matter
 * which encoding your editor saves the .c file in.
 */
#define BOX_H "\xE2\x94\x80"  /* horizontal line */
#define BOX_V "\xE2\x94\x82"  /* vertical line   */
#define BOX_TL "\xE2\x94\x8C" /* top-left corner */
#define BOX_TR "\xE2\x94\x90" /* top-right       */
#define BOX_BL "\xE2\x94\x94" /* bottom-left     */
#define BOX_BR "\xE2\x94\x98" /* bottom-right    */
#define BOX_LT "\xE2\x94\x9C" /* left T-junction  */
#define BOX_RT "\xE2\x94\xA4" /* right T-junction */
#define BOX_TT "\xE2\x94\xAC" /* top T-junction   */
#define BOX_BT "\xE2\x94\xB4" /* bottom T-junction */
#define BOX_X "\xE2\x94\xBC"  /* cross            */

/* ---------- Setup and screen control ---------- */
void initUI(void);      // Turn on colours + UTF-8 (needed on Windows)
void clearScreen(void);
void pauseScreen(void); // "Press Enter to return to the menu..."

/* ---------- Things drawn on screen ---------- */
void printBanner(void);     // ASCII art (or a plain title if the file is missing)
void printStatusBar(void);  // "N records on file | Last saved: ..."
void printMenu(void);
void printHeading(const char *title);
void printSuccess(const char *msg);
void printError(const char *msg);
void printInfo(const char *msg);
void printEmployeeTable(const Employee emp[], int count);

/* ---------- Safe keyboard input (they keep asking until the input is valid) ---------- */
void readLine(const char *prompt, char *buf, int size);
int readInt(const char *prompt, int min, int max);
float readFloat(const char *prompt, float min, float max);

#endif
