# FinTrack: Expense and Budget Analyzer

![image](https://github.com/user-attachments/assets/037d6193-0280-4394-89ce-b84ff6bbfd13)


---

## 🌟 **Overview**

**FinTrack** is a robust and user-friendly **Expense and Budget Analyzer** designed to help individuals effectively manage their finances. With a clean and intuitive interface, FinTrack allows you to:
- **Track daily expenses.**
- **Analyze spending patterns.**
- **Set and manage budgets.**
- **Gain financial insights to achieve better savings goals.**

Whether you are saving for your next big purchase or simply keeping an eye on your monthly expenses, **FinTrack** is your go-to solution!

---

## 🛠️ **Key Features**

✨ **Expense Tracking**: Log and categorize your daily expenses effortlessly.  
✨ **Budget Management**: Set budgets for various categories and track your spending against them.  
✨ **Data Visualization**: View insightful charts and graphs to analyze your spending habits.  
✨ **Customizable Categories**: Tailor expense categories to fit your unique needs.  
✨ **Secure Data Storage**: Ensures your financial data remains private and secure.

---

## 📸 **Screenshots**

- **Dashboard**:  
![image](https://github.com/user-attachments/assets/096e1b1a-77a8-4bf4-84a1-c101215bf7d4)
![image](https://github.com/user-attachments/assets/07a3c9e5-d9c7-4d79-b8d1-897881b8a4d1)
![image](https://github.com/user-attachments/assets/8d0576a1-ff64-4386-910f-447b7cbf9760)

- **Expense Input Form**:  
![image](https://github.com/user-attachments/assets/6f2b39da-6ff4-44bc-878b-7ce7b25ea768)


- **Budget Analysis (Other User)**:  
![image](https://github.com/user-attachments/assets/24772eed-36a6-4b31-b9cd-b1983fffc7b8)
![image](https://github.com/user-attachments/assets/274c5d1d-6d28-4451-bdab-7e81768d2fc4)



---

## 🚀 **Getting Started**

Follow these steps to set up and run **FinTrack** on your local machine:

### Prerequisites

Ensure you have the following installed:
- A **C Compiler** (e.g., GCC, Clang, MinGW). 

### Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/vivek081202/FinTrack-Expense_and_Budget_Analyzer.git
   ```
2. Navigate to the project directory:
   ```bash
   cd FinTrack-Expense_and_Budget_Analyzer
   ```
3. Install the dependencies:
   To make your terminal correctly interpret ANSI escape codes without needing registry edits or complex setup, you can 
   use Windows Terminal or Git Bash, which support ANSI escape sequences by default. If you still want to stick to the 
   Windows Command Prompt and improve the experience, here’s another way:

    Using chcp Command
    Run the following command before executing your C program:
    ```bash
    chcp 65001
    ```

### Running the Application

1. Run the application (FinTrack\src\output):
   ```bash
   g++ main.exe
   ```
2. Access the application in your CLI-based interface.

---

## 🔧 Tech Stack

- **Programming Language**: C  
- **Header Files**:
  - `fintrack.h`: Contains function prototypes, constants, and structures for managing expenses and budgets.
  - `beautifulConsole.h`: Provides color-coded console output for better user experience.
  - Standard C libraries:  
    - `<stdio.h>`: For input/output operations.  
    - `<stdlib.h>`: For dynamic memory allocation.  
    - `<string.h>`: For string handling.  
    - `<time.h>`: For date and time processing.  
    - `<unistd.h>`: For sleep functionality in animations (Linux/macOS support).  
    - `<direct.h>`: For directory operations (Windows-specific).  

---

## 📚 Core Data Structures and Algorithms

The **FinTrack** program leverages several fundamental data structures and algorithms to efficiently manage and analyze expenses:

### 1. **Merge Sort**
- **Purpose**: Sort expenses by their amounts in ascending order.  
- **Implementation**:  
  - The `mergeSort` function recursively splits the list of expenses into smaller subarrays, sorts them, and merges them back into a single sorted list.  
- **Key Files**:  
  - `fintrack.h`: Contains the `mergeSort` and `merge` functions.  
  - Usage in program: Sorting expenses for display and binary search.

---

### 2. **Binary Search**
- **Purpose**: Efficiently search for a specific expense amount within a sorted list of expenses.  
- **Implementation**:  
  - After sorting expenses using merge sort, the `binarySearchByAmount` function performs a logarithmic search to quickly locate the target amount.  
- **Key Files**:  
  - `fintrack.h`: Implements the binary search logic.  
  - Usage in program: Search expenses by amount.

---

### 3. **Stack (Simulated)**
- **Purpose**: Manage fixed-size arrays for temporary storage during operations like merging and sorting.  
- **Implementation**:  
  - The program uses arrays (like in the `mergeSort` function) as a stack-like structure to temporarily hold intermediate data during sorting.  
- **Key Details**:
  - Maximum size for arrays is defined as `MAX_STACK_SIZE`.  
  - Core usage: Memory management for sorting operations.

---

### 4. **File-Based Persistent Storage**
- **Purpose**: Store and retrieve user-specific expenses and budgets.  
- **Implementation**:  
  - The program reads and writes data to text files (`user_data.txt` and `<username>_data.txt`), allowing persistent tracking across sessions.
  - Temporary files (like `temp_data.txt`) are used for updates (e.g., clearing budgets or expenses).
- **Key Operations**:  
  - Budget and expense data manipulation.  
  - Report generation by parsing stored data.  

---

## 🌈 **Future Enhancements**

Here’s what’s next on the roadmap:
- Integration with bank APIs for automatic expense tracking.
- Advanced AI-powered insights and predictions.
- Multi-language support.
- Mobile-friendly version.
---

## 📜 **License**

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

## 📬 **Contact**

For any inquiries or feedback, feel free to reach out:
- **Developer**: Vivek Kumar Singh
- **Email**: [vihixi50@gmail.com](mailto:vihixi50@gmail.com)
- **GitHub**: [@vivek081202](https://github.com/vivek081202)


