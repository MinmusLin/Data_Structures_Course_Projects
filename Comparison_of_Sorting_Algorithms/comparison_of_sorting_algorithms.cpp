/****************************************************************
 * Project Name:  Comparison_of_Sorting_Algorithms
 * File Name:     comparison_of_sorting_algorithms.cpp
 * File Function: 排序算法比较的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/13
 ****************************************************************/

#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <climits>
#include <iomanip>
#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#elif __linux__
#include <ncurses.h>
#endif

/* Macro definition */
#define MEMORY_ALLOCATION_ERROR -1

/* Define SortFunction type */
typedef void (*SortFunction)(int*, int);

/* Define SortOption structure */
struct SortOption {
    SortFunction func;
    const char* description;
};

/* Define static global variable */
static unsigned int compareCount = 0;

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
#ifdef _WIN32
        optn = _getch();
#elif __linux__
        initscr();
        noecho();
        cbreak();
        optn = getch();
        endwin();
#endif
        if (optn == 0 || optn == -32) {
#ifdef _WIN32
            optn = _getch();
#elif __linux__
            initscr();
            noecho();
            cbreak();
            optn = getch();
            endwin();
#endif
        }
        else if (optn >= '0' && optn <= '8') {
            std::cout << "[" << optn << "]" << std::endl;
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
void mySwap(Type& a, Type& b)
{
    Type tmp = a;
    a = b;
    b = tmp;
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
        for (int j = 0; j < n - i - 1; j++) {
            compareCount++;
            if (arr[j] > arr[j + 1])
                mySwap(arr[j], arr[j + 1]);
        }
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
        int k = i;
        for (int j = i + 1; j < n; j++) {
            compareCount++;
            if (arr[j] < arr[k])
                k = j;
        }
        mySwap(arr[k], arr[i]);
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
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            compareCount++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/*
 * Function Name:    shellSort
 * Function:         Shell sort
 * Input Parameters: Type arr[]
 *                   int n
 * Return Value:     void
 */
template <typename Type>
void shellSort(Type arr[], int n)
{
    int gap, i, j;
    for (gap = n >> 1; gap > 0; gap >>= 1)
        for (i = gap; i < n; i++) {
            Type tmp = arr[i];
            for (j = i - gap; j >= 0 && arr[j] > tmp; j -= gap) {
                compareCount++;
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = tmp;
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
        compareCount++;
        if (arr[j] < pivot)
            mySwap(arr[++i], arr[j]);
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
 * Function Name:    heapify
 * Function:         Adjust the subtree rooted at index in the array to form a max heap
 * Input Parameters: Type arr[]
 *                   int n
 *                   int i
 * Return Value:     void
 */
template <typename Type>
void heapify(Type arr[], int n, int i)
{
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    compareCount++;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    compareCount++;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    compareCount++;
    if (largest != i) {
        mySwap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

/*
 * Function Name:    heapSort
 * Function:         Heap sort
 * Input Parameters: Type arr[]
 *                   int n
 * Return Value:     void
 */
template <typename Type>
void heapSort(Type arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        mySwap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

/*
 * Function Name:    merge
 * Function:         Merge function
 * Input Parameters: Type arr[]
 *                   int left
 *                   int mid
 *                   int right
 * Return Value:     void
 */
template <typename Type>
void merge(Type arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1, n2 = right - mid, i = 0, j = 0, k = left;
    Type* leftArr = new(std::nothrow) Type[n1];
    if (leftArr == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    Type* rightArr = new(std::nothrow) Type[n2];
    if (rightArr == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];
    while (i < n1 && j < n2) {
        compareCount++;
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }
    while (i < n1) {
        compareCount++;
        arr[k++] = leftArr[i++];
    }
    while (j < n2) {
        compareCount++;
        arr[k++] = rightArr[j++];
    }
    delete[] leftArr;
    delete[] rightArr;
}

/*
 * Function Name:    mergeSort
 * Function:         Merge sort
 * Input Parameters: Type arr[]
 *                   int left
 *                   int right
 * Return Value:     void
 */
template <typename Type>
void mergeSort(Type arr[], int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/*
 * Function Name:    mergeSort
 * Function:         Merge sort
 * Input Parameters: Type arr[]
 *                   int n
 * Return Value:     void
 */
template <typename Type>
void mergeSort(Type arr[], int n)
{
    mergeSort(arr, 0, n - 1);
}

/*
 * Function Name:    getMaxVal
 * Function:         Get the maximum value
 * Input Parameters: Type arr[]
 *                   int n
 * Return Value:     the maximum value
 * Notes:            Assume that all elements in the array are positive integers
 */
template <typename Type>
Type getMaxVal(Type arr[], int n)
{
    Type maxVal = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];
    return maxVal;
}

/*
 * Function Name:    countSort
 * Function:         Perform counting sort for each digit
 * Input Parameters: Type arr[]
 *                   int n
 *                   int exp
 * Return Value:     void
 * Notes:            Assume that all elements in the array are positive integers
 */
template <typename Type>
void countSort(Type arr[], int n, int exp)
{
    Type* output = new(std::nothrow) Type[n];
    if (output == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    int i, count[10] = { 0 };
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
    delete[] output;
}

/*
 * Function Name:    radixSort
 * Function:         Radix sort
 * Input Parameters: Type arr[]
 *                   int n
 * Return Value:     void
 */
template <typename Type>
void radixSort(Type arr[], int n)
{
    Type maxVal = getMaxVal(arr, n);
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

/* Define sortOptions array */
SortOption sortOptions[] = {
    { bubbleSort, "冒泡排序 Bubble Sort" },
    { selectionSort, "选择排序 Selection Sort" },
    { insertionSort, "插入排序 Insertion Sort" },
    { shellSort, "希尔排序 Shell Sort" },
    { quickSort, "快速排序 Quick Sort" },
    { heapSort, "堆 排 序 Heap Sort" },
    { mergeSort, "归并排序 Merge Sort" },
    { radixSort, "基数排序 Radix Sort" }
};

/*
 * Function Name:    performSort
 * Function:         Sort function
 * Input Parameters: SortFunction sortFunc
 *                   Type arr[]
 *                   int n
 *                   const char* prompt
 * Return Value:     void
 */
template <typename Type>
void performSort(SortFunction sortFunc, Type arr[], int n, const char* prompt)
{
    compareCount = 0;
    std::cout << std::endl << ">>> 排序算法: " << prompt << std::endl;
    int* sortArr = new(std::nothrow) int[n];
    if (sortArr == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    std::copy(arr, arr + n, sortArr);
#ifdef _WIN32
    LARGE_INTEGER tick, begin, end;
    QueryPerformanceFrequency(&tick);
    QueryPerformanceCounter(&begin);
#endif
    sortFunc(sortArr, n);
#ifdef _WIN32
    QueryPerformanceCounter(&end);
    std::cout << ">>> 排序时间: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << static_cast<double>(end.QuadPart - begin.QuadPart) / tick.QuadPart << "s" << std::endl;
#endif
    std::cout << ">>> 比较次数: " << compareCount << std::endl;
    //std::cout << ">>> 排序数组: ";
    //for (int i = 0; i < n; i++)
    //    std::cout << sortArr[i] << " ";
    //std::cout << std::endl;
    delete[] sortArr;
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
    for (int i = 1; i <= 8; i++)
        std::cout << "    [" << i << "] " << sortOptions[i - 1].description << std::endl;
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
        int optn = selectOptn();
        if (optn == 0)
            return 0;
        else
            performSort(sortOptions[optn - 1].func, arr, num, sortOptions[optn - 1].description);
    }
}