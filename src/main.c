#include <stdio.h>
#include "fintrack.h"
#include "beautifulConsole.h"

// Main function to run the application
int main()
{
    showLoadingAnimation();
    int choice;
    char username[MAX_NAME_LEN], fullName [MAX_NAME_LEN], password[MAX_NAME_LEN];
    char searchCategory[MAX_CATEGORY_LEN];

    while (1)
    {
        printf("WELCOME! to FinTrack - Expense and Budget Analyzer\n\n");
        printf("+--------------------------+\n");
        printf("|  Register or Login Here  |\n");
        printf("+--------------------------+\n");
        printf("|    1. Register User      |\n");
        printf("|    2. Login User         |\n");
        printf("|    3. Exit               |\n");
        printf("+--------------------------+\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter username: ");
            scanf("%s", username);

            // Clear the input buffer after scanf
            while (getchar() != '\n');

            printf("Enter Full Name: ");
            fgets(fullName, MAX_NAME_LEN, stdin);
            // Remove trailing newline from fgets
            fullName[strcspn(fullName, "\n")] = '\0';

            printf("Enter password: ");
            scanf("%s", password);

            // Clear the input buffer after scanf
            while (getchar() != '\n');
            
            if (registerUser(username, fullName, password))
                printLightGreen("\nUser registered successfully!\n");
        }
        else if (choice == 2)
        {
            printf("\n");
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");
            scanf("%s", password);
            if (loginUser(username, password))
            {
                int userChoice;
                do
                {          
                    printf("+----------------------------------------+\n");
                    printf("|          FinTrack Main Menu            |\n");
                    printf("+----------------------------------------+\n");
                    printf("|   1. Add Expense                       |\n");
                    printf("|   2. Set Budget                        |\n");
                    printf("|   3. Generate Report                   |\n");
                    printf("|   4. Get Dynamic Recommendations       |\n");
                    printf("|   5. Sort Expenses by Amount           |\n");
                    printf("|   6. Search Expense by Amount          |\n");
                    printf("|   7. Search Expense by Category        |\n");
                    printf("|   8. Generate Category Graph           |\n");
                    printf("|   9. Clear All Expenses                |\n");
                    printf("|  10. Clear Budget                      |\n");
                    printf("|  11. Logout                            |\n");
                    printf("+----------------------------------------+\n");
                    printf("Choose an option: ");
                    scanf("%d", &userChoice);
                    printf("\n");
                    switch (userChoice)
                    {
                    case 1:
                        addExpense(username);
                        break;
                    case 2:
                        setBudget(username);
                        break;
                    case 3:
                        generateExpenditureReport(username);
                        break;
                    case 4:
                        dynamicRecommendations(username);
                        break;
                    case 5:
                        sortExpensesByAmount(username);
                        printf("\n");
                        break;
                    case 6:
                        printf("\nEnter amount to search: ");
                        float searchAmount;
                        scanf("%f", &searchAmount);
                        searchExpenseByAmount(username, searchAmount);
                        printf("\n");
                        break;
                    case 7:
                        printf("Enter category to search: ");
                        scanf("%s", searchCategory);
                        // Call the search function with the category
                        searchExpenseByCategory(username, searchCategory);
                        printf("\n");
                        break;
                    case 8:
                        generateCategoryGraph(username);
                        printf("\n");
                        break;
                    case 9:
                        clearExpenses(username);
                        break;
                    case 10:
                        clearBudget(username);
                        break;
                    case 11:
                        printf("Logging out...\n");
                        break;
                    default:
                        printf("Invalid option.\n");
                    }
                } while (userChoice != 11);
            }
        }
        else if (choice == 3)
        {
            printf("Exiting FinTrack. Goodbye!\n");
            break;
        }
        else
        {
            printLightRed("Invalid option. Please try again.\n");
        }
    }
    return 0;
}