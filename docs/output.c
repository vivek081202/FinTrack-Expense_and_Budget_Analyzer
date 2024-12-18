/**
 * @file output.c
 * @author Vivek Kumar Singh
 * @brief 
 * Block Designs and animations for stuructured console Outputs.
 * 
 * @version 0.1
 * @date 2024-10-26
 * @copyright Copyright (c) 2024
 * 
 */

#include <unistd.h>
#include <stdio.h>

void showLoadingAnimation() {
    printf("Loading");
    fflush(stdout); // Ensure "Loading" is printed immediately

    // Print dots with a delay
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        sleep(1); // Wait for 1 second
    }

    // Overwrite the loading text with spaces
    printf("\r                \r"); // Move cursor back and clear the line
    fflush(stdout);
}

void progressBar(int duration) {
    printf("[");
    for (int i = 0; i < duration; i++) {
        printf("#");
        usleep(200000); // sleep for 0.1 second
    }
    printf("]\n");
}

 // For usleep function

void bouncingDot()
{
    int width = 20;
    int direction = 1;
    int pos = 0;

    for (int i = 0; i < 40; i++)
    {
        printf("\r");
        for (int j = 0; j < width; j++)
        {
            if (j == pos)
                printf("*");
            else
                printf(" ");
        }
        fflush(stdout);
        usleep(100000); // Delay for 100 milliseconds

        pos += direction;
        if (pos == width - 1 || pos == 0)
            direction = -direction; // Reverse direction
    }
    printf("\n");
}

void loadingDots() {
    printf("Loading");
    for (int i = 0; i < 5; i++) {
        fflush(stdout);
        sleep(1); // Wait for 1 second
        printf(".");
    }
    printf("\n");
}


void smoothLoadingBar()
{
    int barWidth = 50;
    printf("Loading:\n");
    printf("[");
    for (int i = 0; i <= barWidth; i++)
    {
        printf("#");
        fflush(stdout);
        usleep(80000); // Delay for 80 milliseconds
        printf("\r[%-*s] %3d%%", barWidth, "##################################################", (i * 100) / barWidth);
    }
    printf(" 100%%\n");
}

int main(){

printf("\033[1;32mThis is green text.\033[0m\n");  // Bold green
printf("\033[1;34mThis is blue text.\033[0m\n");   // Bold blue

/**
Command to activate color encodings

*/

printf("\n\n");

printf("+-------------------------+\n");
printf("|      Welcome to CLI     |\n");
printf("+-------------------------+\n");

printf("\n\n");

printf("=============================\n");
printf("       MENU OPTIONS          \n");
printf("=============================\n");

printf("\n\n");

loadingAnimation();

printf("\n\n");

printf("Item\t\tPrice\n");
printf("---------------------\n");
printf("Apple\t\t$1.00\n");
printf("Banana\t\t$0.50\n");

progressBar(50);

bouncingDot();

smoothLoadingBar();

loadingDots();

return 0;
}
