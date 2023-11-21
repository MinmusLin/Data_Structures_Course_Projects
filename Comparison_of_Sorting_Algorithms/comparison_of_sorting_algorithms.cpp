/****************************************************************
 * Project Name:  Comparison_of_Sorting_Algorithms
 * File Name:     comparison_of_sorting_algorithms.cpp
 * File Function: 排序算法比较的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/17
 ****************************************************************/

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <limits>
#include <conio.h>

/* Macro definition */
#define MEMORY_ALLOCATION_ERROR -1

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
            std::cerr << std::endl << ">>> " << prompt << "输入不合法，请重新输入" << prompt << "！" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
}

/*
 * Function Name:    selectOptn
 * Function:         Select operation
 * Input Parameters: void
 * Return Value:     operation
 */
int selectOptn(void)
{
    std::cout << std::endl << "请选择排序算法: ";
    char optn;
    while (true) {
        optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if (optn >= '0' && optn <= '8') {
            std::cout << "[" << optn << "]" << std::endl << std::endl;
            return optn - '0';
        }
    }
}

/*
 * Function Name:    mySwap
 * Function:         Swap function
 * Input Parameters: Type& a
 *                   Type& b
 * Return Value:     void
 */
template <typename Type>
void mySwap(Type& a, Type& b) {
    Type temp = a;
    a = b;
    b = temp;
}

/*
 * Function Name:    bubbleSort
 * Function:         Bubble sort
 * Input Parameters: Type arr[]
 *                   int n
 * Return Value:     void
 */
template <typename Type>
void bubbleSort(Type arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                mySwap(arr[j], arr[j + 1]);
}

/*
 * Function Name:    selectionSort
 * Function:         Selection sort
 * Input Parameters: Type arr[]
 *                   int n
 * Return Value:     void
 */
template <typename Type>
void selectionSort(Type arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        mySwap(arr[min_idx], arr[i]);
    }
}

/*
 * Function Name:    insertionSort
 * Function:         Insertion sort
 * Input Parameters: Type arr[]
 *                   int n
 * Return Value:     void
 */
template <typename Type>
void insertionSort(Type arr[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/*
 * Function Name:    booleanSort
 * Function:         Boolean sort
 * Input Parameters: Type arr[]
 *                   int n
 * Return Value:     void
 */
template <typename Type>
void booleanSort(Type arr[], int n)
{
    if (n <= 1)
        return;
    Type minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal)
            minVal = arr[i];
        else if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    int index = 0, range = maxVal - minVal + 1;
    bool* booleanArray = new(std::nothrow) int[range] {false};
    if (booleanArray == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < n; i++) {
        int index = arr[i] - minVal;
        booleanArray[index] = true;
    }
    for (int i = 0; i < range; i++) {
        while (booleanArray[i]) {
            arr[index++] = i + minVal;
            booleanArray[i] = false;
        }
    }
}

/*
 * Function Name:    partition
 * Function:         Partition the array for quicksort
 * Input Parameters: Type arr[]
 *                   int low
 *                   int high
 * Return Value:     the index of the pivot element after partition
 */
template <typename Type>
int partition(Type arr[], int low, int high)
{
    Type pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            mySwap(arr[i], arr[j]);
        }
    }
    mySwap(arr[i + 1], arr[high]);
    return i + 1;
}

/*
 * Function Name:    quickSort
 * Function:         Quick sort
 * Input Parameters: Type arr[]
 *                   int low
 *                   int high
 * Return Value:     void
 */
template <typename Type>
void quickSort(Type arr[], int low, int high)
{
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/*
 * Function Name:    quickSort
 * Function:         Quick sort
 * Input Parameters: Type arr[]
 *                   int n
 * Return Value:     void
 */
template <typename Type>
void quickSort(Type arr[], int n)
{
    quickSort(arr, 0, n - 1);
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* Generate random number seed */
    srand((unsigned int)(time(0)));

    /* System entry prompt */
    std::cout << "+------------------------------------+" << std::endl;
    std::cout << "|            排序算法比较            |" << std::endl;
    std::cout << "|  Comparison of Sorting Algorithms  |" << std::endl;
    std::cout << "+------------------------------------+" << std::endl << std::endl;
    std::cout << ">>> 排序算法:" << std::endl;
    std::cout << "    [1] 冒泡排序 Bubble Sort" << std::endl;
    std::cout << "    [2] 选择排序 Selection Sort" << std::endl;
    std::cout << "    [3] 插入排序 Insertion Sort" << std::endl;
    std::cout << "    [4] 布尔排序 Boolean Sort" << std::endl;
    std::cout << "    [5] 快速排序 Quick Sort" << std::endl;
    std::cout << "    [6] 堆 排 序 Heap Sort" << std::endl;
    std::cout << "    [7] 归并排序 Merge Sort" << std::endl;
    std::cout << "    [8] 基数排序 Radix Sort" << std::endl;
    std::cout << "    [0] 退出程序 Quit Program" << std::endl << std::endl;
    
    /* Generate random numbers */
    int num = inputInteger(1, INT_MAX, "要生成随机数的个数");
    int* arr = new(std::nothrow) int[num];
    if (arr == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < num; i++)
        arr[i] = rand();
    std::cout << std::endl << ">>> 随机数生成成功（随机数数量: " << num << "）" << std::endl;

    /* Sorting algorithm */
    while (true) {
        int* sortArr = new(std::nothrow) int[num];
        if (sortArr == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        for (int i = 0; i < num; i++)
            sortArr[i] = arr[i];
        switch (selectOptn()) {
            case 1:
                std::cout << ">>> [1] 冒泡排序 Bubble Sort" << std::endl;
                break;
            case 2:
                std::cout << ">>> [2] 选择排序 Selection Sort" << std::endl;
                break;
            case 3:
                std::cout << ">>> [3] 插入排序 Insertion Sort" << std::endl;
                break;
            case 4:
                std::cout << ">>> [4] 布尔排序 Boolean Sort" << std::endl;
                break;
            case 5:
                std::cout << ">>> [5] 快速排序 Quick Sort" << std::endl;
                break;
            case 6:
                std::cout << ">>> [6] 堆排序 Heap Sort" << std::endl;
                break;
            case 7:
                std::cout << ">>> [7] 归并排序 Merge Sort" << std::endl;
                break;
            case 8:
                std::cout << ">>> [8] 基数排序 Radix Sort" << std::endl;
                break;
            default:
                return 0;
        }
    }
}