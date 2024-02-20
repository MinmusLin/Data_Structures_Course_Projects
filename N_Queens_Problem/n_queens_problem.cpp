/****************************************************************
 * Project Name:  N_Queens_Problem
 * File Name:     n_queens_problem.cpp
 * File Function: N皇后问题的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/13
 ****************************************************************/

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#ifdef _WIN32
#include <conio.h>
#elif __linux__
#include <ncurses.h>
#endif

/* Macro definition */
#define MEMORY_ALLOCATION_ERROR -1

/* Define N_Queens class */
class N_Queens {
private:
    int size;
    int count;
    int* array;
public:
    N_Queens(int n);
    ~N_Queens();
    bool isSafeToPlace(int n);
    void findRecursively(int n);
    void printChessboard(void);
    void solve(void);
};

/*
 * Function Name:    N_Queens
 * Function:         Constructed function
 * Input Parameters: int n
 * Notes:            Class external implementation of member functions
 */
N_Queens::N_Queens(int n)
{
    size = n;
    count = 0;
    array = new(std::nothrow) int[size];
    if (array == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < size; i++)
        array[i] = -1;
}

/*
 * Function Name:    ~N_Queens
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
N_Queens::~N_Queens()
{
    delete[] array;
}

/*
 * Function Name:    isSafeToPlace
 * Function:         Check if it is safe to place a queen
 * Input Parameters: int n
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool N_Queens::isSafeToPlace(int n)
{
    for (int i = 0; i < n; i++)
        if (array[n] == array[i] || std::abs(n - i) == std::abs(array[n] - array[i]))
            return false;
    return true;
}

/*
 * Function Name:    findRecursively
 * Function:         Recursively find solutions to the N-Queens problem
 * Input Parameters: int n
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void N_Queens::findRecursively(int n)
{
    if (n == size) {
        printChessboard();
        count++;
    }
    else {
        for (int i = 0; i < size; i++) {
            array[n] = i;
            if (isSafeToPlace(n))
                findRecursively(n + 1);
        }
    }
}

/*
 * Function Name:    printChessboard
 * Function:         Print the chessboard state for one solution
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void N_Queens::printChessboard(void)
{
    std::cout << std::endl << ">>> 解法 " << count + 1 << std::endl << std::endl << "   ";
    for (int i = 0; i < size; i++)
        std::cout << std::setw(2) << i + 1;
    std::cout << std::endl << "  +" << std::setfill('-') << std::setw(2 * size) << "-" << std::setfill(' ') << "+" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(2) << i + 1 << "|";
        for (int j = 0; j < size; j++)
            std::cout << (j == array[i] ? "●" : "  ");
        std::cout << "|" << std::endl;
    }
    std::cout << "  +" << std::setfill('-') << std::setw(2 * size) << "-" << std::setfill(' ') << "+" << std::endl;
}

/*
 * Function Name:    solve
 * Function:         Solve N-Queens problem
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void N_Queens::solve(void)
{
    findRecursively(0);
    std::cout << std::endl << ">>> " << size << " 皇后问题有 " << count << " 种解法" << std::endl << std::endl;
}

/*
 * Function Name:    inputInteger
 * Function:         Input an integer
 * Input Parameters: int lowerLimit
 *                   int upperLimit
 *                   const char* prompt
 * Return Value:     an integer
 */
int inputInteger(int lowerLimit, int upperLimit, const char* prompt)
{
    while (true) {
        std::cout << "请输入" << prompt << " [整数范围: " << lowerLimit << "~" << upperLimit << "]: ";
        double tempInput;
        std::cin >> tempInput;
        if (std::cin.good() && tempInput == static_cast<int>(tempInput) && tempInput >= lowerLimit && tempInput <= upperLimit) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            return static_cast<int>(tempInput);
        }
        else {
            std::cerr << std::endl << ">>> " << prompt << " 输入不合法，请重新输入" << prompt << " ！" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* System entry prompt */
    std::cout << "+--------------------+" << std::endl;
    std::cout << "|     N皇后问题      |" << std::endl;
    std::cout << "|  N Queens Problem  |" << std::endl;
    std::cout << "+--------------------+" << std::endl << std::endl;

    /* Problem description */
    std::cout << ">>> 问题描述" << std::endl << std::endl;
    std::cout << "    在一个 N × N 的棋盘上，放置 N 个皇后，使其互不攻" << std::endl;
    std::cout << "击，即没有任意两个皇后在同一行、同一列或同一对角线上。" << std::endl << std::endl;

    /* Input N and initialize n_queens object */
    N_Queens n_queens(inputInteger(1, 99, "皇后个数 N"));

    /* Solve N-Queens Problem */
    n_queens.solve();

    /* Wait for enter to quit */
    std::cout << "Press Enter to Quit" << std::endl;
#ifdef _WIN32
    while (_getch() != '\r')
        continue;
#elif __linux__
    char ch;
    do {
        initscr();
        noecho();
        cbreak();
        ch = getch();
        endwin();
    } while (ch != '\n');
#endif

    /* Program ends */
    return 0;
}