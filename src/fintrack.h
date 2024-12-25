/**
 * @file Fintrack.h
 * @author Vivek Singh
 * @brief
 * The FinTrack - "Expense and Budget Analyzer" is a command-line interface (CLI)application developed in C that helps users track, analyze, and manage their personal finances. It allows users to input and categorize their daily expenses, set budget limits, and receive personalized feedback on their spending habits. The application generates detailed reports on how well users are adhering to their budget and offers
suggestions for better financial management

 * @version 0.1
 * @date 2024-11-02
 * @copyright Copyright (c) 2024
 */

#include <string.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include "beautifulConsole.h"
#include <time.h>
#include <unistd.h>

#define MAX_NAME_LEN 50
#define MAX_CATEGORY_LEN 20
#define MAX_STACK_SIZE 200
#define USER_DATA_FILE "user_data.txt"
#define MAX_CATEGORIES 5

// User structure
typedef struct
{
    char username[MAX_NAME_LEN];
    char fullName[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
} User;

// Expense structure
typedef struct
{
    char category[MAX_CATEGORY_LEN];
    float amount;
    char date[20];
} Expense;

// Function Prototypes
int registerUser(const char *username, const char *fullName, const char *password);
int loginUser(const char *username, const char *password);
void addExpense(const char *username);
void setBudget(const char *username);
void generateExpenditureReport(const char *username);
void giveRecommendations(const char *username);

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

// Register a new user
int registerUser(const char *username, const char *fullName, const char *password)
{
    FILE *file = fopen(USER_DATA_FILE, "a+"); // Open file in append and read mode
    if (!file)
    {
        printLightRed("Error opening user data file.\n");
        return 0;
    }

    // Check if username already exists
    rewind(file); // Move to the beginning of the file
    User user;
    int userExists = 0;
    char line[200]; // Buffer to read lines

    while (fgets(line, sizeof(line), file))
    {
        // Debug: Print the line being read
        //printf("DEBUG: Reading line: %s", line);

        // Parse the line into the User structure
        if (sscanf(line, "%s %[^\t\n] %s", user.username, user.fullName, user.password) == 3)
        {
            if (strcmp(user.username, username) == 0)
            {
                userExists = 1;
                break;
            }
        }
    }

    if (userExists)
    {
        printLightYellow("\nUsername already exists.\n");
        fclose(file);
        return 0;
    }

    // Add new user to the file
    fprintf(file, "%s\t%s\t%s\n", username, fullName, password);
    fclose(file);

    // Create a file for storing user-specific data (e.g., expenses)
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", fullName);
    FILE *userFile = fopen(userFilePath, "a"); // Create if it doesn't exist
    if (userFile)
        fclose(userFile);

    return 1;
}

int loginUser(const char *username, const char *password)
{
    FILE *file = fopen(USER_DATA_FILE, "r");
    if (!file)
    {
        printf("\033[1;31mError opening user data file.\033[0m\n"); // Red text for error
        return 0;
    }

    User user;
    char line[200]; // Buffer to read each line

    while (fgets(line, sizeof(line), file))
    {
        // Parse the line into the User structure
        if (sscanf(line, "%s %[^\t\n] %s", user.username, user.fullName, user.password) == 3)
        {
            if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0)
            {
                fclose(file);
                printf("\n");
                printf("\033[1;32mLogin successful! Welcome, %s.\033[0m\n", user.fullName); // Green text for success
                return 1;
            }
        }
    }

    fclose(file);
    printf("\033[1;33mInvalid username or password.\033[0m\n"); // Yellow text for warning
    return 0;
}

// Add a new expense for the user
void addExpense(const char *username)
{
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", username);
    FILE *file = fopen(userFilePath, "a+"); // Open in append+read mode

    if (!file)
    {
        printf("Error opening user file.\n");
        return;
    }

    // Predefined categories
    const char *categories[] = {"Food", "Rent", "Entertainment", "Utilities", "Misc"};
    int numCategories = sizeof(categories) / sizeof(categories[0]);

    // Display categories
    printf("\nAvailable categories:\n");
    for (int i = 0; i < numCategories; i++)
    {
        printf("%d. %s\n", i + 1, categories[i]);
    }

    Expense expense;
    int categoryChoice;

    // Choose category
    do
    {
        printf("Enter the category number: ");
        scanf("%d", &categoryChoice);
        if (categoryChoice < 1 || categoryChoice > numCategories)
        {
            printf("Invalid choice. Please choose a valid category.\n");
        }
    } while (categoryChoice < 1 || categoryChoice > numCategories);

    strncpy(expense.category, categories[categoryChoice - 1], MAX_CATEGORY_LEN);

    // Input amount
    do
    {
        printf("Enter amount (positive value): ");
        scanf("%f", &expense.amount);
        if (expense.amount <= 0)
        {
            printf("Amount must be positive. Try again.\n");
        }
    } while (expense.amount <= 0);

    // Input date
    printf("Enter date (dd-mm-yyyy): ");
    scanf("%s", expense.date);

    // Save the expense
    fprintf(file, "Category: %s | Amount: %.2f | Date: %s\n", expense.category, expense.amount, expense.date);
    fclose(file);

    printf("\nExpense added successfully.\n");

    // Budget Check
    file = fopen(userFilePath, "r");
    if (!file)
    {
        printf("Error reopening user file for budget check.\n");
        return;
    }

    // Analyze budget
    float totalSpending = 0;
    int budget = 0;
    char line[200];

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "Category: %*s | Amount: %f", &expense.amount) == 1)
        {
            totalSpending += expense.amount;
        }
        else if (sscanf(line, "Budget: %d", &budget) == 1)
        {
            continue;
        }
    }
    fclose(file);

    // Notify user if over budget
    if (budget > 0)
    {
        printf("\nBudget Analysis:\n");
        printf("Total Spending: %.2f | Budget: %d\n", totalSpending, budget);
        if (totalSpending > budget)
        {
            printf("Warning: You have exceeded your budget by %.2f.\n", totalSpending - budget);
        }
        else
        {
            printf("You are within your budget. Remaining: %.2f.\n", budget - totalSpending);
        }
    }
}

// Set a budget for the user
void setBudget(const char *username)
{
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", username);
    FILE *file = fopen(userFilePath, "r+"); // Open in read+write mode

    if (!file)
    {
        printf("Error opening user file.\n");
        return;
    }

    // Check if a budget already exists
    int currentBudget = 0;
    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "Budget: %d", &currentBudget) == 1)
        {
            break; // Budget found
        }
    }

    // Notify the user if a budget is already set
    if (currentBudget > 0)
    {
        printf("\nCurrent Budget: %d\n", currentBudget);
        printf("Do you want to update it? (1 for Yes, 0 for No): ");
        int updateChoice;
        scanf("%d", &updateChoice);

        if (updateChoice == 0)
        {
            printf("No changes made to the budget.\n");
            fclose(file);
            return;
        }
    }

    // Input new budget
    int newBudget;
    do
    {
        printf("Enter new budget amount (positive value): ");
        scanf("%d", &newBudget);
        if (newBudget <= 0)
        {
            printf("Invalid budget. Please enter a positive value.\n");
        }
    } while (newBudget <= 0);

    // Confirm budget with the user
    printf("You entered a budget of %d. Confirm? (1 for Yes, 0 for No): ", newBudget);
    int confirmChoice;
    scanf("%d", &confirmChoice);
    if (confirmChoice == 0)
    {
        printf("Budget setting canceled.\n");
        fclose(file);
        return;
    }

    // Rewrite file without previous budget if it exists
    rewind(file);
    FILE *tempFile = fopen("temp_data.txt", "w");
    if (!tempFile)
    {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    int budgetWritten = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "Budget:") == NULL)
        {
            fputs(line, tempFile);
        }
        else if (!budgetWritten)
        {
            fprintf(tempFile, "Budget: %d\n", newBudget);
            budgetWritten = 1;
        }
    }

    if (!budgetWritten)
    {
        fprintf(tempFile, "Budget: %d\n", newBudget); // Write new budget if none existed
    }

    fclose(file);
    fclose(tempFile);
    remove(userFilePath);                  // Remove old file
    rename("temp_data.txt", userFilePath); // Rename temp file to original

    printf("\nBudget set successfully!\n");
}

// Generate a report of expenses
 // Required for date and day conversion

// Helper function to determine the day of the week
const char *getDayOfWeek(const char *date)
{
    struct tm timeStruct = {0};
    static const char *daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    // Parse the date string (dd-mm-yyyy) into a struct tm
    if (sscanf(date, "%2d-%2d-%4d", &timeStruct.tm_mday, &timeStruct.tm_mon, &timeStruct.tm_year) == 3)
    {
        timeStruct.tm_mon -= 1;                // Adjust month range from [1-12] to [0-11]
        timeStruct.tm_year -= 1900;            // Adjust year to years since 1900
        mktime(&timeStruct);                   // Normalize timeStruct and compute day of the week
        return daysOfWeek[timeStruct.tm_wday]; // Return the day of the week
    }

    return "Invalid Date"; // Fallback for invalid date
}

void generateExpenditureReport(const char *username)
{
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", username);
    FILE *file = fopen(userFilePath, "r");

    if (!file)
    {
        printf("\033[1;31mError opening user file.\033[0m\n");
        return;
    }

    printf("\033[1;36m\n\n==== Expenditure Report for %s ====\033[0m\n", username);

    // Initialize variables for analysis
    float categoryTotals[5] = {0};
    char categories[5][MAX_CATEGORY_LEN] = {"Food", "Rent", "Entertainment", "Utilities", "Misc"};
    float totalSpending = 0;
    int budget = 0;
    Expense expense;
    int daysTracked = 0;                             // For calculating daily average spending
    char earliestDate[20] = "", latestDate[20] = ""; // For tracking date range

    // Read user data
    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        // Parse expenses
        if (sscanf(line, "Category: %s | Amount: %f | Date: %s", expense.category, &expense.amount, expense.date) == 3)
        {
            totalSpending += expense.amount;

            for (int i = 0; i < 5; i++)
            {
                if (strcmp(expense.category, categories[i]) == 0)
                {
                    categoryTotals[i] += expense.amount;
                    break;
                }
            }

            // Update earliest and latest dates
            if (daysTracked == 0 || strcmp(expense.date, earliestDate) < 0)
                strcpy(earliestDate, expense.date);
            if (daysTracked == 0 || strcmp(expense.date, latestDate) > 0)
                strcpy(latestDate, expense.date);

            // Print expense with day and date
            printf("Category: %s | Amount: %.2f | Date: %s (%s)\n",
                   expense.category, expense.amount, expense.date, getDayOfWeek(expense.date));

            daysTracked++;
        }
        // Parse budget
        else if (sscanf(line, "Budget: %d", &budget) == 1)
        {
            continue;
        }
    }
    fclose(file);

    // Interactive Breakdown
    printf("\033[1;34m\nCategory-Wise Spending:\033[0m\n");
    for (int i = 0; i < 5; i++)
    {
        if (categoryTotals[i] > 0)
        {
            float percentageOfTotal = (totalSpending > 0) ? (categoryTotals[i] / totalSpending) * 100 : 0;

            // Display bar visualization
            printf("- %s: %.2f (%.2f%%) ", categories[i], categoryTotals[i], percentageOfTotal);
            int barLength = (int)(percentageOfTotal / 5); // Scale bar to fit
            printf("[");
            for (int j = 0; j < barLength; j++)
            {
                printf("=");
            }
            printf("]\n");
        }
    }

    // Total Spending
    printf("\033[1;33m\nTotal Spending: %.2f\033[0m\n", totalSpending);

    // Budget Information
    if (budget > 0)
    {
        printf("\033[1;33mBudget: %d\033[0m\n", budget);
        if (totalSpending > budget)
        {
            printf("\033[1;31mWARNING: You have exceeded your budget by %.2f.\033[0m\n", totalSpending - budget);
        }
        else
        {
            printf("\033[1;32mGreat job! You are within your budget. Remaining: %.2f.\033[0m\n", budget - totalSpending);
        }
    }
    else
    {
        printf("\033[1;33mNo budget set. Consider setting one to track your expenses better.\033[0m\n");
    }

    // Month-to-Date Analysis
    if (daysTracked > 0)
    {
        printf("\033[1;33m\nSpending Period: %s to %s (%d days)\033[0m\n", earliestDate, latestDate, daysTracked);
        printf("\033[1;33mAverage Daily Spending: %.2f\033[0m\n", totalSpending / daysTracked);
    }

    printf("\033[1;36m\n==== End of Report ====\033[0m\n");
    printf("\n");
}

// Provide financial recommendations based on spending habits
void dynamicRecommendations(const char *username)
{
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", username);
    FILE *file = fopen(userFilePath, "r");

    if (!file)
    {
        printf("\033[1;31mError opening user file.\033[0m\n");
        return;
    }

    Expense expense;
    float totalSpending = 0, categorySpending[5] = {0};
    char categories[5][MAX_CATEGORY_LEN] = {"Food", "Rent", "Entertainment", "Utilities", "Misc"};
    int budget = 0;

    // Read user data
    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "Category: %s | Amount: %f", expense.category, &expense.amount) == 2)
        {
            for (int i = 0; i < 5; i++)
            {
                if (strcmp(expense.category, categories[i]) == 0)
                {
                    categorySpending[i] += expense.amount;
                }
            }
            totalSpending += expense.amount;
        }
        else if (sscanf(line, "Budget: %d", &budget) == 1)
        {
            continue;
        }
    }
    fclose(file);

    // Generate recommendations
    printf("\033[1;36m\n\n==== Personalized Recommendations for %s ====\033[0m\n", username);
    if (budget > 0)
    {
        printf("\033[1;33m- Budget: %d | Total Spending: %.2f (%.2f%% of budget)\033[0m\n",
               budget, totalSpending, (totalSpending / budget) * 100);

        if (totalSpending > budget)
        {
            printf("\033[1;31m- ALERT: You have exceeded your budget by %.2f.\033[0m\n", totalSpending - budget);
        }
        else
        {
            printf("\033[1;32m- Great job! You are within your budget. Remaining: %.2f.\033[0m\n", budget - totalSpending);
        }
    }
    else
    {
        printf("\033[1;33m- No budget set. Consider setting one to track your expenses better.\033[0m\n");
    }

    printf("\n\033[1;34mCategory-Wise Spending Analysis:\033[0m\n");
    for (int i = 0; i < 5; i++)
    {
        if (categorySpending[i] > 0)
        {
            float percentageOfBudget = (budget > 0) ? (categorySpending[i] / budget) * 100 : 0;
            printf("- %s: %.2f (%.2f%% of budget)\n", categories[i], categorySpending[i], percentageOfBudget);

            if (budget > 0 && categorySpending[i] > (budget / 5))
            {
                printf("\033[1;31m  * You have overspent in '%s' by %.2f.\033[0m\n",
                       categories[i], categorySpending[i] - (budget / 5));
            }
        }
    }

    printf("\n\033[1;35mActionable Suggestions:\033[0m\n");
    if (budget > 0 && totalSpending > budget)
    {
        printf("- Review categories where spending exceeds the allocated share of the budget.\n");
    }
    for (int i = 0; i < 5; i++)
    {
        if (categorySpending[i] > (budget / 5))
        {
            printf("- Reduce spending on '%s' to save more.\n", categories[i]);
        }
    }

    if (totalSpending < budget)
    {
        printf("- Keep up the good work! You're within your budget.\n");
    }
    else
    {
        printf("- Consider reallocating funds or reducing expenses to avoid overspending.\n");
    }

    printf("\033[1;36m\n==== End of Recommendations ====\033[0m\n");
    printf("\n");
}

void merge(Expense *arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Expense *L = (Expense *)malloc(n1 * sizeof(Expense));
    Expense *R = (Expense *)malloc(n2 * sizeof(Expense));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].amount <= R[j].amount)
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(Expense *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void sortExpensesByAmount(const char *username)
{
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", username);

    FILE *file = fopen(userFilePath, "r");
    if (!file)
    {
        printf("Error opening user data file.\n");
        return;
    }

    Expense expenses[MAX_STACK_SIZE];
    int count = 0;
    char line[200];

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "Category: %s | Amount: %f | Date: %s",
                   expenses[count].category, &expenses[count].amount, expenses[count].date) == 3)
        {
            count++;
        }
    }
    fclose(file);

    // Sort using Merge Sort
    mergeSort(expenses, 0, count - 1);

    // Display sorted expenses
    printf("\nExpenses sorted by amount:\n");
    for (int i = 0; i < count; i++)
    {
        printf("Category: %s | Amount: %.2f | Date: %s\n",
               expenses[i].category, expenses[i].amount, expenses[i].date);
    }
}

int binarySearchByAmount(Expense *expenses, int left, int right, float amount)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (expenses[mid].amount == amount)
            return mid;
        if (expenses[mid].amount < amount)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // Not found
}

void searchExpenseByAmount(const char *username, float amount)
{
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", username);

    FILE *file = fopen(userFilePath, "r");
    if (!file)
    {
        printf("Error opening user data file.\n");
        return;
    }

    Expense expenses[MAX_STACK_SIZE];
    int count = 0;
    char line[200];

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "Category: %s | Amount: %f | Date: %s",
                   expenses[count].category, &expenses[count].amount, expenses[count].date) == 3)
        {
            count++;
        }
    }
    fclose(file);

    // Sort expenses by amount for Binary Search
    mergeSort(expenses, 0, count - 1);

    // Perform Binary Search
    int index = binarySearchByAmount(expenses, 0, count - 1, amount);

    if (index != -1)
    {
        printf("Expense found: Category: %s | Amount: %.2f | Date: %s\n",
               expenses[index].category, expenses[index].amount, expenses[index].date);
    }
    else
    {
        printf("No expense found with amount %.2f.\n", amount);
    }
}


void generateCategoryGraph(const char *username)
{
    // Categories we are tracking in the expenses
    const char *categories[] = {"Food", "Rent", "Entertainment", "Utilities", "Misc"};
    float categoryTotals[5] = {0}; // Array to store total spending per category
    int numCategories = 5;

    // File path for user-specific data
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", username);

    // Open the user's data file
    FILE *file = fopen(userFilePath, "r");
    if (!file)
    {
        printf("Error opening user data file.\n");
        return;
    }

    // Read the data and sum up the amounts for each category
    char line[200];
    Expense expense;

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "Category: %s | Amount: %f | Date: %s", expense.category, &expense.amount, expense.date) == 3)
        {
            // Match the category and sum up the amounts
            for (int i = 0; i < numCategories; i++)
            {
                if (strcmp(expense.category, categories[i]) == 0)
                {
                    categoryTotals[i] += expense.amount;
                    break;
                }
            }
        }
    }

    fclose(file);

    // Find the maximum amount for scaling the bars
    float maxAmount = 0;
    for (int i = 0; i < numCategories; i++)
    {
        if (categoryTotals[i] > maxAmount)
        {
            maxAmount = categoryTotals[i];
        }
    }

    // Generate the bar graph
    printf("\n--- Category Spending Graph ---\n");

    for (int i = 0; i < numCategories; i++)
    {
        int barLength = (int)(categoryTotals[i] / maxAmount * 50); // Scale bars to fit
        printf("%-15s | ", categories[i]);
        for (int j = 0; j < barLength; j++)
        {
            printf("=");
        }
        printf(" %.2f\n", categoryTotals[i]);
    }
}

void searchExpenseByCategory(const char *username, const char *category)
{
    // Define the categories array to compare against
    const char *categories[] = {"Food", "Rent", "Entertainment", "Utilities", "Misc"};
    int numCategories = 5;

    // Check if the entered category exists in the predefined categories
    int categoryFound = 0;
    for (int i = 0; i < numCategories; i++)
    {
        if (strcmp(categories[i], category) == 0)
        {
            categoryFound = 1;
            break; // Category found, no need to continue searching
        }
    }

    if (!categoryFound)
    {
        printf("Category '%s' not found.\n", category);
        return; // Exit if category is not found
    }

    // File path for user-specific data
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", username);

    // Open the user's data file
    FILE *file = fopen(userFilePath, "r");
    if (!file)
    {
        printf("Error opening user data file.\n");
        return;
    }

    printf("\nExpenses in category '%s':\n", category);
    char line[200];
    Expense expense;
    int found = 0;

    // Read through the file and search for expenses in the specified category
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "Category: %s | Amount: %f | Date: %s", expense.category, &expense.amount, expense.date) == 3)
        {
            // Compare the category in the file with the user-specified category
            if (strcmp(expense.category, category) == 0)
            {
                printf("Amount: %.2f | Date: %s\n", expense.amount, expense.date);
                found = 1;
            }
        }
    }
    fclose(file);

    // If no expenses were found in the category
    if (!found)
    {
        printf("No expenses found in this category.\n");
    }
}

/*Clear Expense Function*/
void clearExpenses(const char* username) {
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", username);

    FILE* file = fopen(userFilePath, "r");
    if (!file) {
        printf("\033[0;31mError: Unable to open file for clearing expenses.\033[0m\n");
        return;
    }

    // Temporary file to store non-expense data
    FILE* tempFile = fopen("temp_data.txt", "w");
    if (!tempFile) {
        fclose(file);
        printf("\033[0;31mError: Unable to create a temporary file.\033[0m\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        // Keep lines that do not start with "Category:"
        if (strstr(line, "Category:") == NULL) {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated file
    remove(userFilePath);
    rename("temp_data.txt", userFilePath);

    printf("\033[0;32mAll expenses cleared for user %s.\033[0m\n", username);
}


/*Clear Budget Function*/
void clearBudget(const char* username) {
    char userFilePath[100];
    snprintf(userFilePath, sizeof(userFilePath), "%s_data.txt", username);

    FILE* file = fopen(userFilePath, "r");
    if (!file) {
        printf("\033[0;31mError: Unable to open file for clearing budget.\033[0m\n");
        return;
    }

    // Temporary file to store filtered data
    FILE* tempFile = fopen("temp_data.txt", "w");
    if (!tempFile) {
        fclose(file);
        printf("\033[0;31mError: Unable to create a temporary file.\033[0m\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        // Skip the line containing "Budget:"
        if (strstr(line, "Budget:") == NULL) {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated file
    remove(userFilePath);
    rename("temp_data.txt", userFilePath);

    printf("\033[0;32mBudget cleared for user %s.\033[0m\n", username);
}
