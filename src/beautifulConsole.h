#ifndef CONSOLE_COLORS_H
#define CONSOLE_COLORS_H

#include <stdio.h>

/**

    // Regular (light) colors
    printf("\033[0;30mThis is light black (gray).\033[0m\n");
    printf("\033[0;31mThis is light red.\033[0m\n");
    printf("\033[0;32mThis is light green.\033[0m\n");
    printf("\033[0;33mThis is light yellow.\033[0m\n");
    printf("\033[0;34mThis is light blue.\033[0m\n");
    printf("\033[0;35mThis is light magenta.\033[0m\n");
    printf("\033[0;36mThis is light cyan.\033[0m\n");
    printf("\033[0;37mThis is light white.\033[0m\n");

    // Bold colors
    printf("\033[1;30mThis is bold black (gray).\033[0m\n");
    printf("\033[1;31mThis is bold red.\033[0m\n");
    printf("\033[1;32mThis is bold green.\033[0m\n");
    printf("\033[1;33mThis is bold yellow.\033[0m\n");
    printf("\033[1;34mThis is bold blue.\033[0m\n");
    printf("\033[1;35mThis is bold magenta.\033[0m\n");
    printf("\033[1;36mThis is bold cyan.\033[0m\n");
    printf("\033[1;37mThis is bold white.\033[0m\n");

 *
 */


// Light colors
void printLightBlack(const char *text) { printf("\033[0;30m%s\033[0m\n", text); }
void printLightRed(const char *text) { printf("\033[0;31m%s\033[0m\n", text); }
void printLightGreen(const char *text) { printf("\033[0;32m%s\033[0m\n", text); }
void printLightYellow(const char *text) { printf("\033[0;33m%s\033[0m\n", text); }
void printLightBlue(const char *text) { printf("\033[0;34m%s\033[0m\n", text); }
void printLightMagenta(const char *text) { printf("\033[0;35m%s\033[0m\n", text); }
int printLightCyan(const char *text) { printf("\033[0;36m%s\033[0m\n", text); return 1; }
void printLightWhite(const char *text) { printf("\033[0;37m%s\033[0m\n", text); }

// Bold colors
void printBoldBlack(const char *text) { printf("\033[1;30m%s\033[0m\n", text); }
void printBoldRed(const char *text) { printf("\033[1;31m%s\033[0m\n", text); }
void printBoldGreen(const char *text) { printf("\033[1;32m%s\033[0m\n", text); }
void printBoldYellow(const char *text) { printf("\033[1;33m%s\033[0m\n", text); }
void printBoldBlue(const char *text) { printf("\033[1;34m%s\033[0m\n", text); }
void printBoldMagenta(const char *text) { printf("\033[1;35m%s\033[0m\n", text); }
void printBoldCyan(const char *text) { printf("\033[1;36m%s\033[0m\n", text); }
void printBoldWhite(const char *text) { printf("\033[1;37m%s\033[0m\n", text); }

#endif // CONSOLE_COLORS_H
