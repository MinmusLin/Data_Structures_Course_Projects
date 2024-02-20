/****************************************************************
 * Project Name:  Josephus_Problem
 * File Name:     josephus_problem.cpp
 * File Function: 约瑟夫游戏的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/13
 ****************************************************************/

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <climits>
#ifdef _WIN32
#include <conio.h>
#elif __linux__
#include <ncurses.h>
#endif

/* Macro definition */
#define MEMORY_ALLOCATION_ERROR -1

/* Define MyCircLinkNode structure */
template <typename Type>
struct MyCircLinkNode {
    Type data;
    MyCircLinkNode<Type>* link;
    MyCircLinkNode(MyCircLinkNode<Type>* ptr = NULL) { data = 0, link = ptr; }
    MyCircLinkNode(const Type& item, MyCircLinkNode<Type>* ptr = NULL) { data = item; link = ptr; }
};

/* Define MyCircList class */
template <typename Type>
class MyCircList {
private:
    MyCircLinkNode<Type>* first;
    MyCircLinkNode<Type>* last;
public:
    MyCircList();
    MyCircList(const Type& item);
    MyCircList(MyCircList<Type>& L);
    ~MyCircList();
    void makeEmpty(void);
    int getLength(void) const;
    MyCircLinkNode<Type>* getHead(void) const;
    MyCircLinkNode<Type>* getTail(void) const;
    MyCircLinkNode<Type>* search(Type item) const;
    MyCircLinkNode<Type>* locate(int i) const;
    bool getData(int i, Type& item) const;
    bool setData(int i, Type& item);
    bool insert(int i, Type& item);
    bool remove(int i, Type& item);
    bool isEmpty(void) const;
    void output(void) const;
    MyCircList<Type>& operator=(MyCircList<Type> L);
};

/*
 * Function Name:    MyCircList
 * Function:         Constructed function
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyCircList<Type>::MyCircList()
{
    first = new(std::nothrow) MyCircLinkNode<Type>;
    if (first == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    first->link = first;
    last = first;
}

/*
 * Function Name:    MyCircList
 * Function:         Constructed function
 * Input Parameters: const Type& item
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyCircList<Type>::MyCircList(const Type& item)
{
    first = new(std::nothrow) MyCircLinkNode<Type>(item);
    if (first == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    first->link = first;
    last = first;
}

/*
 * Function Name:    MyCircList
 * Function:         Constructed function
 * Input Parameters: MyCircList<Type>& L
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyCircList<Type>::MyCircList(MyCircList<Type>& L)
{
    first = new(std::nothrow) MyCircLinkNode<Type>;
    if (first == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    first->link = first;
    last = first;
    MyCircLinkNode<Type>* srcptr = L.first->link;
    MyCircLinkNode<Type>* dstptr = first;
    while (srcptr != NULL) {
        dstptr->link = new(std::nothrow) MyCircLinkNode<Type>(srcptr->data);
        if (dstptr->link == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        srcptr = srcptr->link;
        dstptr = dstptr->link;
    }
    last = dstptr;
    last->link = first;
}

/*
 * Function Name:    ~MyCircList
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyCircList<Type>::~MyCircList()
{
    makeEmpty();
}

/*
 * Function Name:    makeEmpty
 * Function:         Set the circular linked list to an empty circular list
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyCircList<Type>::makeEmpty(void)
{
    MyCircLinkNode<Type>* current = first->link;
    while (current != first) {
        MyCircLinkNode<Type>* temp = current;
        current = current->link;
        delete temp;
    }
    first->link = first;
    last = first;
}

/*
 * Function Name:    getLength
 * Function:         Calculate the length of a circular singly linked list with an appended head node
 * Input Parameters: void
 * Return Value:     the length of a circular singly linked list with an appended head node
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
int MyCircList<Type>::getLength(void) const
{
    int count = 0;
    MyCircLinkNode<Type>* current = first->link;
    while (current != first) {
        current = current->link;
        count++;
    }
    return count;
}

/*
 * Function Name:    getHead
 * Function:         Return the address of the appended head node
 * Input Parameters: void
 * Return Value:     the address of the appended head node
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyCircLinkNode<Type>* MyCircList<Type>::getHead(void) const
{
    return first;
}

/*
 * Function Name:    getTail
 * Function:         Return the address of the tail node of a circular singly linked list with an appended head node
 * Input Parameters: void
 * Return Value:     the address of the tail node
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyCircLinkNode<Type>* MyCircList<Type>::getTail(void) const
{
    return last;
}

/*
 * Function Name:    search
 * Function:         Search for a node containing data x in the circular linked list, if the search is successful,
 *                   the function returns the address of that node, otherwise, it returns a NULL value
 * Input Parameters: Type item
 * Return Value:     the address of the node / NULL
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyCircLinkNode<Type>* MyCircList<Type>::search(Type item) const
{
    MyCircLinkNode<Type>* current = first->link;
    while (current != first) {
        if (current->data == item)
            return current;
        current = current->link;
    }
    return NULL;
}

/*
 * Function Name:    locate
 * Function:         Return the address of the ith element in the list, if i < 0
 *                   or exceeds the number of nodes in the list, return NULL
 * Input Parameters: int i
 * Return Value:     the address of the ith element / NULL
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyCircLinkNode<Type>* MyCircList<Type>::locate(int i) const
{
    if (i < 0)
        return NULL;
    else if (i == 0)
        return first;
    else if (i > 0 && i <= getLength()) {
        MyCircLinkNode<Type>* current = first->link;
        int k = 1;
        while (current != first && k < i) {
            current = current->link;
            k++;
        }
        return current;
    }
    else
        return NULL;
}

/*
 * Function Name:    getData
 * Function:         Return the value of the ith element in the circular linked list
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyCircList<Type>::getData(int i, Type& item) const
{
    if (i <= 0)
        return false;
    MyCircLinkNode<Type>* current = locate(i);
    if (current == NULL)
        return false;
    else {
        item = current->data;
        return true;
    }
}

/*
 * Function Name:    setData
 * Function:         Assign a value to the ith element in the circular linked list
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyCircList<Type>::setData(int i, Type& item)
{
    if (i <= 0)
        return false;
    MyCircLinkNode<Type>* current = locate(i);
    if (current == NULL)
        return false;
    else {
        current->data = item;
        return true;
    }
}

/*
 * Function Name:    insert
 * Function:         Insert the new element after the ith node in the circular linked list
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyCircList<Type>::insert(int i, Type& item)
{
    MyCircLinkNode<Type>* current = locate(i);
    if (current == NULL)
        return false;
    MyCircLinkNode<Type>* newNode = new(std::nothrow) MyCircLinkNode<Type>(item);
    if (newNode == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    newNode->link = current->link;
    current->link = newNode;
    if (current == last)
        last = newNode;
    return true;
}

/*
 * Function Name:    remove
 * Function:         Remove the ith element from the circular linked list and return its value through a reference parameter
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyCircList<Type>::remove(int i, Type& item)
{
    MyCircLinkNode<Type>* current = locate(i - 1);
    if (current == NULL || current->link == NULL)
        return false;
    MyCircLinkNode<Type>* del = current->link;
    current->link = del->link;
    item = del->data;
    if (del == last)
        last = current;
    delete del;
    return true;
}

/*
 * Function Name:    isEmpty
 * Function:         Check if the circular linked list is empty
 * Input Parameters: void
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyCircList<Type>::isEmpty(void) const
{
    return first == last;
}

/*
 * Function Name:    output
 * Function:         Output all data in the circular singly linked list in logical order
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyCircList<Type>::output(void) const
{
    MyCircLinkNode<Type>* current = first->link;
    std::cout << current->data;
    current = current->link;
    while (current != first) {
        std::cout << " " << current->data;
        current = current->link;
    }
}

/*
 * Function Name:    operator=
 * Function:         Overload operator =
 * Input Parameters: MyCircList<Type> L
 * Return Value:     *this
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyCircList<Type>& MyCircList<Type>::operator=(MyCircList<Type> L)
{
    if (this == &L)
        return *this;
    makeEmpty();
    MyCircLinkNode<Type>* currentL = L.first->link;
    MyCircLinkNode<Type>* currentThis = first;
    while (currentL != L.first) {
        MyCircLinkNode<Type>* newNode = new(std::nothrow) MyCircLinkNode<Type>(currentL->data);
        if (newNode == nullptr) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        currentThis->link = newNode;
        currentThis = newNode;
        currentL = currentL->link;
    }
    last = currentThis;
    currentThis->link = first;
    return *this;
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
        std::cout << "请输入" << prompt << "[整数范围: " << lowerLimit << "~" << upperLimit << "]: ";
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
 * Function Name:    printPrompt
 * Function:         print information prompt
 * Input Parameters: void
 * Return Value:     void
 */
void printPrompt(void)
{
    /* System entry prompt */
    std::cout << "+--------------------+" << std::endl;
    std::cout << "|     约瑟夫游戏     |" << std::endl;
    std::cout << "|  Josephus Problem  |" << std::endl;
    std::cout << "+--------------------+" << std::endl;

    /* Problem description */
    std::cout << std::endl << ">>> 问题描述" << std::endl << std::endl;
    std::cout << "    N 个人按顺序排成一个环形，依次顺序编号为 1 到 N ，从" << std::endl;
    std::cout << "第 S 号开始，沿环顺序计数，每数到第 M 个人就将其淘汰，且" << std::endl;
    std::cout << "从下一个人开始重新计数，重复这个过程，直到剩下 K 个人为止。" << std::endl << std::endl;
}

/*
 * Function Name:    josephusProblem
 * Function:         Josephus problem
 * Input Parameters: void
 * Return Value:     void
 */
void josephusProblem(void)
{
    /* Input */
    printPrompt();
    std::cout << ">>> 请输入总人数、起始位置、间隔人数、剩余人数" << std::endl << std::endl;
    int N = inputInteger(1, INT_MAX, "总人数 N ");
    std::cout << std::endl;
    int S = inputInteger(1, N, "起始位置 S ");
    std::cout << std::endl;
    int M = inputInteger(1, INT_MAX, "间隔人数 M ");
    std::cout << std::endl;
    int K = inputInteger(0, N - 1, "剩余人数 K ");

    /* Save the order number of each person */
    int* order = new(std::nothrow) int[N];
    if (order == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int count = 0; count < N; count++)
        order[count] = count + 1;

    /* Calculate the number of eliminated people's digits for formatting output */
    int numDigits = 0, num = N - K;
    while (num != 0) {
        num /= 10;
        numDigits++;
    }

    /* Initialize a circular linked list */
    MyCircList<int> circList;
    for (int count = 0; count < N; count++)
        circList.insert(count, order[count]);

    /* Perform Josephus problem */
    int remaining = N, currentPos = S, eliminated;
    MyCircLinkNode<int>* currentNode = circList.locate(currentPos);
    std::cout << std::endl << ">>> 游戏开始" << std::endl << std::endl;
    while (remaining > K) {
        for (int count = 1; count < M; count++) {
            currentNode = currentNode->link;
            if (currentNode == circList.getHead())
                count--;
        }
        currentPos = (currentPos + M - 1) % remaining;
        if (currentPos == 0)
            currentPos = remaining;
        currentNode = currentNode->link;
        if (currentNode == circList.getHead())
            currentNode = currentNode->link;
        circList.remove(currentPos, eliminated);
        std::cout << "第 " << std::setw(numDigits) << N - (--remaining) << " 个淘汰的人的位置: " << eliminated << std::endl;
    }
    std::cout << std::endl << ">>> 游戏结束（剩余人数: " << remaining << "）" << std::endl << std::endl;
    if (remaining > 0) {
        std::cout << "剩余人的位置为: ";
        circList.output();
        std::cout << std::endl << std::endl;
    }

    /* Free dynamic memory */
    delete[] order;
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* Josephus problem */
    josephusProblem();

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