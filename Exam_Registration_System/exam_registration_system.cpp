/****************************************************************
 * Project Name:  Exam_Registration_System
 * File Name:     exam_registration_system.cpp
 * File Function: 考试报名系统的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/13
 ****************************************************************/

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <climits>
#ifdef _WIN32
#include <conio.h>
#elif __linux__
#include <ncurses.h>
#endif

/* Macro definitions */
#define MAX_SIZE 64
#define MEMORY_ALLOCATION_ERROR -1
#define TRAVELED 1
#define UNTRAVELED 2

/* Define StuInfo structure */
struct StuInfo {
    char no[MAX_SIZE] = { 0 };
    char name[MAX_SIZE] = { 0 };
    bool sex = true;
    int age = 0;
    char category[MAX_SIZE] = { 0 };
};

/*
 * Function Name:    operator<<
 * Function:         Overload operator <<
 * Input Parameters: std::ostream& out
 *                   const StuInfo& stuInfo
 * Return Value:     out
 */
std::ostream& operator<<(std::ostream& out, const StuInfo& stuInfo)
{
    out << std::setiosflags(std::ios::left)
        << "| " << std::setw(12) << stuInfo.no
        << " | " << std::setw(24) << stuInfo.name
        << " | " << (stuInfo.sex ? " 男 " : " 女 ")
        << " |  " << std::setw(3) << stuInfo.age
        << " | " << std::setw(32) << stuInfo.category
        << " |" << std::resetiosflags(std::ios::left);
    return out;
}

/* Define MyLinkNode structure */
template <typename Type>
struct MyLinkNode {
    Type data;
    MyLinkNode<Type>* link;
    MyLinkNode(MyLinkNode<Type>* ptr = NULL) { link = ptr; }
    MyLinkNode(const Type& item, MyLinkNode<Type>* ptr = NULL) { data = item; link = ptr; }
};

/* Define MyList class */
template <typename Type>
class MyList {
private:
    MyLinkNode<Type>* first;
    MyLinkNode<Type>* last;
public:
    MyList();
    MyList(const Type& item);
    MyList(MyList<Type>& L);
    ~MyList();
    void makeEmpty(void);
    int getLength(void) const;
    MyLinkNode<Type>* getHead(void) const;
    MyLinkNode<Type>* getTail(void) const;
    MyLinkNode<Type>* search(Type item) const;
    MyLinkNode<Type>* locate(int i) const;
    bool getData(int i, Type& item) const;
    bool setData(int i, Type& item);
    bool insert(int i, Type& item);
    bool remove(int i, Type& item);
    void pushFront(Type& item);
    void popFront(void);
    bool isEmpty(void) const;
    void output(void) const;
    void splice(MyLinkNode<Type>* pos, MyList<Type>& other);
    void merge(MyList<Type>& other);
    void reverse(void);
    MyList<Type>& operator=(MyList<Type> L);
};

/*
 * Function Name:    MyList
 * Function:         Constructed function
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyList<Type>::MyList()
{
    first = new(std::nothrow) MyLinkNode<Type>;
    if (first == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    last = first;
}

/*
 * Function Name:    MyList
 * Function:         Constructed function
 * Input Parameters: const Type& item
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyList<Type>::MyList(const Type& item)
{
    first = new(std::nothrow) MyLinkNode<Type>(item);
    if (first == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    last = first;
}

/*
 * Function Name:    MyList
 * Function:         Constructed function
 * Input Parameters: MyList<Type>& L
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyList<Type>::MyList(MyList<Type>& L)
{
    first = new(std::nothrow) MyLinkNode<Type>;
    if (first == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    last = first;
    MyLinkNode<Type>* srcptr = L.first->link;
    MyLinkNode<Type>* dstptr = first;
    while (srcptr != NULL) {
        dstptr->link = new(std::nothrow) MyLinkNode<Type>(srcptr->data);
        if (dstptr->link == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        srcptr = srcptr->link;
        dstptr = dstptr->link;
    }
    last = dstptr;
    last->link = NULL;
}

/*
 * Function Name:    ~MyList
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyList<Type>::~MyList()
{
    makeEmpty();
}

/*
 * Function Name:    makeEmpty
 * Function:         Set the linked list to an empty list
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyList<Type>::makeEmpty(void)
{
    MyLinkNode<Type>* current;
    while (first->link != NULL) {
        current = first->link;
        first->link = current->link;
        delete current;
    }
}

/*
 * Function Name:    getLength
 * Function:         Calculate the length of a singly linked list with an appended head node
 * Input Parameters: void
 * Return Value:     the length of a singly linked list with an appended head node
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
int MyList<Type>::getLength(void) const
{
    int count = 0;
    MyLinkNode<Type>* current = first->link;
    while (current != NULL) {
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
MyLinkNode<Type>* MyList<Type>::getHead(void) const
{
    return first;
}

/*
 * Function Name:    getTail
 * Function:         Return the address of the tail node of a singly linked list with an appended head node
 * Input Parameters: void
 * Return Value:     the address of the tail node
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyLinkNode<Type>* MyList<Type>::getTail(void) const
{
    return last;
}

/*
 * Function Name:    search
 * Function:         Search for a node containing data x in the linked list, if the search is successful,
 *                   the function returns the address of that node, otherwise, it returns a NULL value
 * Input Parameters: Type item
 * Return Value:     the address of the node / NULL
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyLinkNode<Type>* MyList<Type>::search(Type item) const
{
    MyLinkNode<Type>* current = first->link;
    while (current != NULL) {
        if (current->data == item)
            break;
        else
            current = current->link;
    }
    return current;
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
MyLinkNode<Type>* MyList<Type>::locate(int i) const
{
    if (i < 0)
        return NULL;
    MyLinkNode<Type>* current = first;
    int k = 0;
    while (current != NULL && k < i) {
        current = current->link;
        k++;
    }
    return current;
}

/*
 * Function Name:    getData
 * Function:         Return the value of the ith element in the linked list
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyList<Type>::getData(int i, Type& item) const
{
    if (i <= 0)
        return false;
    MyLinkNode<Type>* current = locate(i);
    if (current == NULL)
        return false;
    else {
        item = current->data;
        return true;
    }
}

/*
 * Function Name:    setData
 * Function:         Assign a value to the ith element in the linked list
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyList<Type>::setData(int i, Type& item)
{
    if (i <= 0)
        return false;
    MyLinkNode<Type>* current = locate(i);
    if (current == NULL)
        return false;
    else {
        current->data = item;
        return true;
    }
}

/*
 * Function Name:    insert
 * Function:         Insert the new element after the ith node in the linked list
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyList<Type>::insert(int i, Type& item)
{
    MyLinkNode<Type>* current = locate(i);
    if (current == NULL)
        return false;
    MyLinkNode<Type>* newNode = new(std::nothrow) MyLinkNode<Type>(item);
    if (newNode == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    newNode->link = current->link;
    current->link = newNode;
    return true;
}

/*
 * Function Name:    remove
 * Function:         Remove the ith element from the linked list and return its value through a reference parameter
 * Input Parameters: int i
 *                   Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyList<Type>::remove(int i, Type& item)
{
    MyLinkNode<Type>* current = locate(i - 1);
    if (current == NULL || current->link == NULL)
        return false;
    MyLinkNode<Type>* del = current->link;
    current->link = del->link;
    item = del->data;
    delete del;
    return true;
}

/*
 * Function Name:    pushFront
 * Function:         Insert a new element with value item at the beginning of the list
 * Input Parameters: Type& item
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyList<Type>::pushFront(Type& item)
{
    MyLinkNode<Type>* newNode = new(std::nothrow) MyLinkNode<Type>(item);
    if (newNode == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    newNode->link = first->link;
    first->link = newNode;
    if (last == first)
        last = newNode;
}

/*
 * Function Name:    popFront
 * Function:         Remove the first element in the list
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyList<Type>::popFront(void)
{
    if (first->link != NULL) {
        MyLinkNode<Type>* temp = first->link;
        first->link = temp->link;
        delete temp;
        if (first->link == NULL)
            last = first;
    }
}

/*
 * Function Name:    isEmpty
 * Function:         Check if the linked list is empty
 * Input Parameters: void
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyList<Type>::isEmpty(void) const
{
    return first->link == NULL;
}

/*
 * Function Name:    output
 * Function:         Output all data in the singly linked list in logical order
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyList<Type>::output(void) const
{
    MyLinkNode<Type>* current = first->link;
    while (current != NULL) {
        std::cout << current->data << std::endl;
        current = current->link;
    }
}

/*
 * Function Name:    splice
 * Function:         Move elements from another list other into this list at position pos
 * Input Parameters: MyLinkNode<Type>* pos
 *                   MyList<Type>& other
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyList<Type>::splice(MyLinkNode<Type>* pos, MyList<Type>& other)
{
    if (other.isEmpty() || pos == NULL)
        return;
    MyLinkNode<Type>* otherFirst = other.first->link;
    MyLinkNode<Type>* otherLast = other.last;
    other.first->link = pos->link;
    pos->link = otherFirst;
    if (otherFirst == NULL)
        last = otherLast;
    other.makeEmpty();
}

/*
 * Function Name:    merge
 * Function:         Merge the elements from another sorted list other into this sorted list, maintaining the sorted order
 * Input Parameters: MyList<Type>& other
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyList<Type>::merge(MyList<Type>& other)
{
    if (this == &other)
        return;
    MyLinkNode<Type>* thisCurrent = first->link;
    MyLinkNode<Type>* otherCurrent = other.first->link;
    MyLinkNode<Type>* mergedList = new(std::nothrow) MyLinkNode<Type>;
    if (mergedList == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    MyLinkNode<Type>* mergedLast = mergedList;
    while (thisCurrent != NULL && otherCurrent != NULL) {
        if (thisCurrent->data < otherCurrent->data) {
            mergedLast->link = thisCurrent;
            mergedLast = thisCurrent;
            thisCurrent = thisCurrent->link;
        }
        else {
            mergedLast->link = otherCurrent;
            mergedLast = otherCurrent;
            otherCurrent = otherCurrent->link;
        }
    }
    while (thisCurrent != NULL) {
        mergedLast->link = thisCurrent;
        mergedLast = thisCurrent;
        thisCurrent = thisCurrent->link;
    }
    while (otherCurrent != NULL) {
        mergedLast->link = otherCurrent;
        mergedLast = otherCurrent;
        otherCurrent = otherCurrent->link;
    }
    mergedLast->link = NULL;
    first->link = mergedList->link;
    last = mergedLast;
    other.makeEmpty();
}

/*
 * Function Name:    reverse
 * Function:         Reverse the order of elements in the list
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyList<Type>::reverse(void)
{
    MyLinkNode<Type>* prev = NULL;
    MyLinkNode<Type>* current = first->link;
    MyLinkNode<Type>* next;
    last = current;
    while (current != NULL) {
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }
    first->link = prev;
}

/*
 * Function Name:    operator=
 * Function:         Overload operator =
 * Input Parameters: MyList<Type> L
 * Return Value:     *this
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyList<Type>& MyList<Type>::operator=(MyList<Type> L)
{
    if (this == &L)
        return *this;
    makeEmpty();
    MyLinkNode<Type>* currentL = L.first->link;
    MyLinkNode<Type>* currentThis = first;
    while (currentL != NULL) {
        MyLinkNode<Type>* newNode = new MyLinkNode<Type>(currentL->data);
        if (newNode == nullptr) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        currentThis->link = newNode;
        currentThis = newNode;
        currentL = currentL->link;
    }
    last = currentThis;
    return *this;
}

/*
 * Function Name:    printStuInfo
 * Function:         Print the information of a specific student
 * Input Parameters: const StuInfo& stuInfo
 * Return Value:     void
 */
void printStuInfo(const StuInfo& stuInfo)
{
    std::cout << std::endl << ">>> 考生信息" << std::endl;
    std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
    std::cout << "| 考号         | 姓名                     | 性别 | 年龄 | 报考类别                         |" << std::endl;
    std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
    std::cout << stuInfo << std::endl;
    std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
}

/*
 * Function Name:    printStuInfo
 * Function:         Print the information of all students
 * Input Parameters: MyList<StuInfo>& stuInfo
 * Return Value:     void
 */
void printStuInfo(MyList<StuInfo>& stuInfo)
{
    std::cout << std::endl << ">>> 全体考生信息 (考生人数: " << stuInfo.getLength() << ")" << std::endl;
    std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
    std::cout << "| 考号         | 姓名                     | 性别 | 年龄 | 报考类别                         |" << std::endl;
    std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
    if (stuInfo.isEmpty())
        std::cout << "| 无考生信息   |                          |      |      |                                  |" << std::endl;
    else
        stuInfo.output();
    std::cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
}

/*
 * Function Name:    selectOptn
 * Function:         Select operation
 * Input Parameters: void
 * Return Value:     operation
 */
int selectOptn(void)
{
    std::cout << std::endl << ">>> 菜单: [1]插入功能 [2]删除功能 [3]查询功能 [4]修改功能 [5]统计功能 [0]退出系统" << std::endl;
    std::cout << std::endl << "请选择操作类型: ";
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
        else if (optn >= '0' && optn <= '5') {
            std::cout << "[" << optn << "]" << std::endl << std::endl;
            return optn - '0';
        }
    }
}

/*
 * Function Name:    isNumericString
 * Function:         Check if a string is a numeric string
 * Input Parameters: const char* str
 * Return Value:     true / false
 */
bool isNumericString(const char* str)
{
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9')
            str++;
        else
            return false;
    }
    return true;
}

/*
 * Function Name:    truncateString
 * Function:         Truncate string
 * Input Parameters: char* str
 *                   int len
 * Return Value:     void
 */
void truncateString(char* str, int len)
{
    if (static_cast<int>(strlen(str)) > len)
        str[len] = '\0';
}

/*
 * Function Name:    inputPrompt
 * Function:         print input prompt
 * Input Parameters: const char* prompt
 * Return Value:     void
 */
void inputPrompt(const char* prompt)
{
    std::cout << std::endl << ">>> " << prompt << std::endl;
    std::cout << "    [输入格式] 考号 姓名 性别 年龄 报考类别 (用空格分隔数据)" << std::endl;
    std::cout << "    [考    号] 不超过 12 个数字字符组成的字符串，超出部分将被截断" << std::endl;
    std::cout << "    [姓    名] 不超过 24 个英文字符或 12 个汉字字符组成的字符串，超出部分将被截断" << std::endl;
    std::cout << "    [性    别] 男 / 女" << std::endl;
    std::cout << "    [年    龄] 在 1 至 99 范围内的整型数据" << std::endl;
    std::cout << "    [报考类别] 不超过 32 个英文字符或 16 个汉字字符组成的字符串，超出部分将被截断" << std::endl << std::endl;
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
            std::cerr << std::endl << ">>> " << prompt << "输入不合法，请重新输入" << prompt << "！" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
}

/*
 * Function Name:    findPosByStuNo
 * Function:         Find position by student number
 * Input Parameters: MyList<StuInfo>& stuInfo
 *                   const char* stuNo
 * Return Value:     position / 0 (Search failed)
 */
int findPosByStuNo(MyList<StuInfo>& stuInfo, const char* stuNo)
{
    MyLinkNode<StuInfo>* current = stuInfo.getHead()->link;
    int position = 1;
    while (current != NULL) {
        if (!strcmp(current->data.no, stuNo))
            return position;
        current = current->link;
        position++;
    }
    return 0;
}

/*
 * Function Name:    inputStuInfo
 * Function:         Input student information
 * Input Parameters: MyList<StuInfo>& stuInfo
 * Return Value:     inputted student information
 */
StuInfo inputStuInfo(MyList<StuInfo>& stuInfo)
{
    while (true) {
        /* Create a temporary StuInfo object to store student information */
        StuInfo tempStu;

        /* Input student number and validate its format */
        std::cin >> tempStu.no;
        truncateString(tempStu.no, 12);
        if (!isNumericString(tempStu.no)) {
            std::cerr << std::endl << ">>> 考号输入不合法，请重新输入当前考生信息！" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            continue;
        }
        else if (findPosByStuNo(stuInfo, tempStu.no)) {
            std::cerr << std::endl << ">>> 已存在考号相同的考生，请重新输入当前考生信息！" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            continue;
        }

        /* Input student name and validate its format */
        std::cin >> tempStu.name;
        truncateString(tempStu.name, 24);

        /* Input student sex and validate its format */
        char sex[MAX_SIZE] = { 0 };
        std::cin >> sex;
        if (!strcmp(sex, "男"))
            tempStu.sex = true;
        else if (!strcmp(sex, "女"))
            tempStu.sex = false;
        else {
            std::cerr << std::endl << ">>> 性别输入不合法，请重新输入当前考生信息！" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            continue;
        }

        /* Input student age and validate its format */
        double tempInput;
        std::cin >> tempInput;
        if (std::cin.good() && tempInput == static_cast<int>(tempInput) && tempInput > 0 && tempInput < 100)
            tempStu.age = static_cast<int>(tempInput);
        else {
            std::cerr << std::endl << ">>> 年龄输入不合法，请重新输入当前考生信息！" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            continue;
        }

        /* Input exam Category and validate its format */
        std::cin >> tempStu.category;
        truncateString(tempStu.category, 32);

        /* Return inputted student information */
        return tempStu;
    }
}

/*
 * Function Name:    buildStuInfoList
 * Function:         Build a student information system through standard input
 * Input Parameters: MyList<StuInfo>& stuInfo
 *                   int stuNum
 * Return Value:     void
 */
void buildStuInfoList(MyList<StuInfo>& stuInfo, int stuNum)
{
    inputPrompt("请依次录入考生信息:");
    for (int count = 0; count < stuNum; count++) {
        StuInfo tempStu = inputStuInfo(stuInfo);
        stuInfo.insert(count, tempStu);
    }
    std::cout << std::endl << ">>> 考生信息系统建立完成 (考生人数: " << stuNum << ")" << std::endl;
    printStuInfo(stuInfo);
}

/*
 * Function Name:    getStuNoAndPos
 * Function:         Get valid student number and find position by it
 * Input Parameters: MyList<StuInfo>& stuInfo
 *                   const char* prompt
 * Return Value:     position / 0 (Search failed)
 */
int getStuNoAndPos(MyList<StuInfo>& stuInfo, const char* prompt)
{
    /* Get valid student number */
    char stuNo[MAX_SIZE] = { 0 };
    while (true) {
        std::cout << "请输入" << prompt << " [不超过 12 个数字字符组成的字符串，超出部分将被截断]: ";
        std::cin >> stuNo;
        truncateString(stuNo, 12);
        if (!isNumericString(stuNo)) {
            std::cerr << std::endl << ">>> " << prompt << "输入不合法，请重新输入" << prompt << "！" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            continue;
        }
        else
            break;
    }

    /* Find position by student number */
    return findPosByStuNo(stuInfo, stuNo);
}

/*
 * Function Name:    insertFunction
 * Function:         Insert function
 * Input Parameters: MyList<StuInfo>& stuInfo
 * Return Value:     void
 */
void insertFunction(MyList<StuInfo>& stuInfo)
{
    int position = inputInteger(1, stuInfo.getLength() + 1, "待插入考生的位置");
    inputPrompt("请录入待插入考生信息:");
    StuInfo tempStu = inputStuInfo(stuInfo);
    stuInfo.insert(position - 1, tempStu);
    printStuInfo(tempStu);
    printStuInfo(stuInfo);
}

/*
 * Function Name:    deleteFunction
 * Function:         Delete function
 * Input Parameters: MyList<StuInfo>& stuInfo
 * Return Value:     void
 */
void deleteFunction(MyList<StuInfo>& stuInfo)
{
    int position = getStuNoAndPos(stuInfo, "待删除考生的考号");
    StuInfo delStu;
    if (stuInfo.remove(position, delStu)) {
        printStuInfo(delStu);
        printStuInfo(stuInfo);
    }
    else
        std::cout << std::endl << ">>> 未查询到该考生" << std::endl;
}

/*
 * Function Name:    searchFunction
 * Function:         Search function
 * Input Parameters: MyList<StuInfo>& stuInfo
 * Return Value:     void
 */
void searchFunction(MyList<StuInfo>& stuInfo)
{
    int position = getStuNoAndPos(stuInfo, "待查询考生的考号");
    StuInfo tempStu;
    if (stuInfo.getData(position, tempStu))
        printStuInfo(tempStu);
    else
        std::cout << std::endl << ">>> 未查询到该考生" << std::endl;
}

/*
 * Function Name:    modifyFunction
 * Function:         Modify function
 * Input Parameters: MyList<StuInfo>& stuInfo
 * Return Value:     void
 */
void modifyFunction(MyList<StuInfo>& stuInfo)
{
    /* Delete the information of the student before modification */
    int position = getStuNoAndPos(stuInfo, "待修改考生的考号");
    StuInfo modifyStu;
    if (stuInfo.remove(position, modifyStu))
        printStuInfo(modifyStu);
    else {
        std::cout << std::endl << ">>> 未查询到该考生" << std::endl;
        return;
    }

    /* Add the information of the student after modification */
    inputPrompt("请录入待修改考生信息:");
    modifyStu = inputStuInfo(stuInfo);
    stuInfo.insert(position - 1, modifyStu);
    printStuInfo(modifyStu);
    printStuInfo(stuInfo);
}

/*
 * Function Name:    printCategoryChartHeader
 * Function:         Print category statistics chart header
 * Input Parameters: void
 * Return Value:     void
 */
void printCategoryChartHeader(void)
{
    std::cout  << ">>> 考生报考类别统计" << std::endl;
    std::cout << "+----------------------------------+------------+------------+" << std::endl;
    std::cout << "| 报考类别                         | 人数       | 比例(%)    |" << std::endl;
    std::cout << "+----------------------------------+------------+------------+" << std::endl;
}

/*
 * Function Name:    statisticsGender
 * Function:         Gender statistics function
 * Input Parameters: int stuNum
 *                   int maleCount
 * Return Value:     void
 */
void statisticsGender(int stuNum, int maleCount)
{
    std::cout << std::setiosflags(std::ios::left) << std::endl << ">>> 考生性别统计" << std::endl;
    std::cout << "+------+------------+------------+" << std::endl;
    std::cout << "| 性别 | 人数       | 比例(%)    |" << std::endl;
    std::cout << "+------+------------+------------+" << std::endl;
    std::cout << "|  男  | " << std::setw(10) << maleCount << " | " << std::setw(10) << (maleCount * 100.0 / stuNum) << " |" << std::endl;
    std::cout << "|  女  | " << std::setw(10) << (stuNum - maleCount) << " | " << std::setw(10) << ((stuNum - maleCount) * 100.0 / stuNum) << " |" << std::endl;
    std::cout << "+------+------------+------------+" << std::endl << std::resetiosflags(std::ios::left);
}

/*
 * Function Name:    statisticsAge
 * Function:         Age statistics function
 * Input Parameters: int stuNum
 *                   int ageCount[]
 * Return Value:     void
 */
void statisticsAge(int stuNum, int ageCount[])
{
    std::cout << std::setiosflags(std::ios::left) << std::endl << ">>> 考生年龄统计" << std::endl;
    std::cout << "+------+------------+------------+" << std::endl;
    std::cout << "| 年龄 | 人数       | 比例(%)    |" << std::endl;
    std::cout << "+------+------------+------------+" << std::endl;
    for (int count = 0; count < 100; count++)
        if (ageCount[count])
            std::cout << "|  " << std::setw(3) << count << " | " << std::setw(10) << ageCount[count] << " | " << std::setw(10) << (ageCount[count] * 100.0 / stuNum) << " |" << std::endl;
    std::cout << "+------+------------+------------+" << std::endl << std::resetiosflags(std::ios::left);
}

/*
 * Function Name:    statisticsFunction
 * Function:         Statistics function
 * Input Parameters: MyList<StuInfo>& stuInfo
 * Return Value:     void
 */
void statisticsFunction(MyList<StuInfo>& stuInfo)
{
    /* Initialize the number of students and counter for student gender and age*/
    int stuNum = stuInfo.getLength(), maleCount = 0, ageCount[100] = { 0 };

    /* Array to keep track of visited nodes */
    int* traversedFlag = new(std::nothrow) int[stuNum + 2];
    if (traversedFlag == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int count = 0; count < stuNum + 2; count++)
        traversedFlag[count] = UNTRAVELED;

    /* Traverse the student info */
    printCategoryChartHeader();
    MyLinkNode<StuInfo>* exterCurr = stuInfo.getHead()->link;
    int exterPos = 1;
    while (exterCurr != NULL) {
        if (exterCurr->data.sex)
            maleCount++;
        ageCount[exterCurr->data.age]++;
        if (traversedFlag[exterPos - 1] == UNTRAVELED) {
            traversedFlag[exterPos - 1] = TRAVELED;
            std::cout << std::setiosflags(std::ios::left) << "| " << std::setw(32) << exterCurr->data.category << " | ";
            int cateCount = 1, interPos = exterPos + 1;
            MyLinkNode<StuInfo>* interCurr = exterCurr->link;
            while (interCurr != NULL) {
                if (!strcmp(exterCurr->data.category, interCurr->data.category)) {
                    cateCount++;
                    traversedFlag[interPos - 1] = TRAVELED;
                }
                interCurr = interCurr->link;
                interPos++;
            }
            std::cout << std::setw(10) << cateCount << " | " << std::setw(10) << (cateCount * 100.0 / stuNum) << " |" << std::endl << std::resetiosflags(std::ios::left);
        }
        exterCurr = exterCurr->link;
        exterPos++;
    }
    std::cout << "+----------------------------------+------------+------------+" << std::endl;

    /* Free dynamically allocated memory */
    delete[] traversedFlag;

    /* Count student gender and age */
    statisticsGender(stuNum, maleCount);
    statisticsAge(stuNum, ageCount);
}

/*
 * Function Name:    examRegistrationSystem
 * Function:         Exam registration system
 * Input Parameters: void
 * Return Value:     void
 */
void examRegistrationSystem(void)
{
    /* System entry prompt */
    std::cout << "+----------------------------+" << std::endl;
    std::cout << "|        考试报名系统        |" << std::endl;
    std::cout << "|  Exam Registration System  |" << std::endl;
    std::cout << "+----------------------------+" << std::endl;

    /* Build a student information system */
    std::cout << std::endl << ">>> 请建立考生信息系统" << std::endl << std::endl;
    MyList<StuInfo> stuInfo;
    int stuNum = inputInteger(1, INT_MAX, "考生人数");
    buildStuInfoList(stuInfo, stuNum);

    /* Perform operations on the exam registration system */
    while (true) {
        switch (selectOptn()) {
            case 1:
                insertFunction(stuInfo);
                break;
            case 2:
                deleteFunction(stuInfo);
                break;
            case 3:
                searchFunction(stuInfo);
                break;
            case 4:
                modifyFunction(stuInfo);
                break;
            case 5:
                statisticsFunction(stuInfo);
                break;
            default:
                std::cout << ">>> 考试报名系统已退出" << std::endl;
                return;
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
    /* Exam registration system */
    examRegistrationSystem();

    /* Program ends */
    return 0;
}