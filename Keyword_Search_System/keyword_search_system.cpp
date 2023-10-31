/****************************************************************
 * Project Name:  Keyword_Search_System
 * File Name:     keyword_search_system.cpp
 * File Function: 关键词检索系统的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/10/31
 ****************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <limits>

/* Macro definitions */
#define MAX_LENGTH 64
#define MEMORY_ALLOCATION_ERROR -1
#define FILE_OPEN_ERROR -2
#define FILE_EXIST_ERROR -3
#define FILE_CREATE_ERROR -4
#define INVALID_INDEX_ERROR -5

/*
 * Function Name:    hasSpace
 * Function:         Check if a string has spaces
 * Input Parameters: const char* str
 * Return Value:     true / false
 */
bool hasSpace(const char* str)
{
    while (*str) {
        if (*str == ' ')
            return true;
        str++;
    }
    return false;
}

/*
 * Function Name:    inputString
 * Function:         Input a string without spaces
 * Input Parameters: char* str
 *                   const char* strName
 * Return Value:     void
 */
void inputString(char* str, const char* strName)
{
    while (true) {
        std::cout << std::endl << "请输入" << strName << "（不含空格的不超过 " << MAX_LENGTH << " 个英文字符或 " << MAX_LENGTH / 2 << " 个汉字字符组成的字符串，超出部分将被截断）: ";
        std::cin.get(str, MAX_LENGTH + 1, '\n');
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        str[MAX_LENGTH] = '\0';
        if (*str == '\0')
            std::cout << std::endl << ">>> " << strName << "为空，请重新输入！" << std::endl;
        else if (hasSpace(str))
            std::cout << std::endl << ">>> " << strName << "含有空格，请重新输入！" << std::endl;
        else
            break;
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
    std::cout << std::endl << ">>> 字符串模式匹配算法: [1]BF(Brute-Force)算法 [2]KMP(Knuth-Morris-Pratt)算法" << std::endl;
    std::cout << std::endl << "请选择字符串模式匹配算法: ";
    char optn;
    while (true) {
        optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if (optn >= '1' && optn <= '2') {
            std::cout << "[" << optn << "]" << std::endl << std::endl;
            return optn - '0';
        }
    }
}

/* Define KeywordSearch class */
class KeywordSearch {
private:
    long long fileLen;
    int keywordLen;
    char filename[MAX_LENGTH + 1];
    char keyword[MAX_LENGTH + 1];
    char getCharFromFile(std::fstream& file, int index);
    void getNext(int next[]);
public:
    KeywordSearch(const char* _filename) :fileLen(0), keywordLen(0), filename{ '\0' }, keyword{ '\0' } { strcpy_s(filename, _filename); }
    void initializeFile(void);
    void inputTextAndKeyword(std::fstream& file);
    void outputText(std::fstream& file);
    int BF_Search(std::fstream& file);
    int KMP_Search(std::fstream& file);
    void search(std::fstream& file, int optn);
};

/*
 * Function Name:    getCharFromFile
 * Function:         Read a specified character from a file
 * Input Parameters: std::fstream& file
 *                   int index
 * Return Value:     a specified character
 * Notes:            Class external implementation of member functions
 */
char KeywordSearch::getCharFromFile(std::fstream& file, int index)
{
    file.seekg(index, std::ios::beg);
    char ch;
    if (file.get(ch).good())
        return ch;
    else {
        std::cerr << "Error: Index out of range." << std::endl;
        exit(INVALID_INDEX_ERROR);
    }
}

/*
 * Function Name:    getNext
 * Function:         Obtain the next[] array in the KMP algorithm
 * Input Parameters: int next[]
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void KeywordSearch::getNext(int next[])
{
    int k = -1;
    next[0] = -1;
    for (int i = 1; i < keywordLen; i++) {
        while (k >= 0 && keyword[i] != keyword[k + 1])
            k = next[k];
        if (keyword[i] == keyword[k + 1])
            k++;
        next[i] = k;
    }
}

/*
 * Function Name:    inputTextAndKeyword
 * Function:         Input text and keyword
 * Input Parameters: std::fstream& file
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void KeywordSearch::inputTextAndKeyword(std::fstream& file)
{
    char ch;
    std::cout << std::endl << "请输入文本内容（按回车键结束输入）:" << std::endl << std::endl;
    while ((ch = std::cin.get()) != '\n')
        file.put(ch);
    std::cout << std::endl << ">>> 文本文件 " << filename << " 保存成功" << std::endl;
    file.clear();
    file.seekg(0, std::ios::end);
    fileLen = file.tellg();
    file.seekg(0, std::ios::beg);
    inputString(keyword, "关键词");
    keywordLen = static_cast<int>(strlen(keyword));
}

/*
 * Function Name:    outputText
 * Function:         Output the content of the file
 * Input Parameters: std::fstream& file
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void KeywordSearch::outputText(std::fstream& file)
{
    char ch;
    std::cout << std::endl << ">>> 文本文件 " << filename << " 内容" << std::endl << std::endl;
    while (file.get(ch))
        std::cout.put(ch);
    std::cout << std::endl;
    file.clear();
    file.seekg(0, std::ios::beg);
}

/*
 * Function Name:    BF_Search
 * Function:         BF (Brute-Force) algorithm
 * Input Parameters: std::fstream& file
 * Return Value:     the keyword count
 * Notes:            Class external implementation of member functions
 */
int KeywordSearch::BF_Search(std::fstream& file)
{
    int count = 0;
    for (int i = 0; i < fileLen - keywordLen + 1; i++) {
        int j = 0;
        for (; j < keywordLen; j++)
            if (getCharFromFile(file, i + j) != keyword[j])
                break;
        if (j == keywordLen)
            count++;
    }
    return count;
}

/*
 * Function Name:    KMP_Search
 * Function:         KMP (Knuth-Morris-Pratt) algorithm
 * Input Parameters: std::fstream& file
 * Return Value:     the keyword count
 * Notes:            Class external implementation of member functions
 */
int KeywordSearch::KMP_Search(std::fstream& file)
{
    int count = 0, k = -1;
    int* next = new(std::nothrow) int[keywordLen];
    if (next == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    getNext(next);
    for (int i = 0; i < fileLen; i++) {
        while (k >= 0 && getCharFromFile(file, i) != keyword[k + 1])
            k = next[k];
        if (getCharFromFile(file, i) == keyword[k + 1])
            k++;
        if (k == keywordLen - 1) {
            count++;
            k = next[k];
        }
    }
    delete[] next;
    return count;
}

/*
 * Function Name:    search
 * Function:         Keyword Search
 * Input Parameters: std::fstream& file
 *                   int optn
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void KeywordSearch::search(std::fstream& file, int optn)
{
    int count = 0;
    LARGE_INTEGER tick, begin, end;
    QueryPerformanceFrequency(&tick);
    QueryPerformanceCounter(&begin);
    if (optn == 1)
        count = BF_Search(file);
    else if (optn == 2)
        count = KMP_Search(file);
    QueryPerformanceCounter(&end);
    std::cout << ">> 检索结束（检索时长: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒" << "）" << std::endl << std::endl;
    std::cout << "关键词 \"" << keyword << "\" 在文本文件 " << filename << " 中出现 " << count << " 次" << std::endl << std::endl;
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* System entry prompt */
    std::cout << "+-------------------------+" << std::endl;
    std::cout << "|     关键词检索系统      |" << std::endl;
    std::cout << "|  Keyword Search System  |" << std::endl;
    std::cout << "+-------------------------+" << std::endl << std::endl;

    /* Initialize file operations */
    char filename[MAX_LENGTH + 1] = { '\0' };
    std::cout << ">>> 请创建文本文件" << std::endl;
    inputString(filename, "文件名");
    std::ifstream fileCheck(filename);
    if (fileCheck) {
        fileCheck.close();
        std::cerr << "Error: File " << filename << " already exists." << std::endl;
        exit(FILE_EXIST_ERROR);
    }
    std::ofstream emptyFile(filename);
    if (!emptyFile.is_open()) {
        std::cerr << "Error: File " << filename << " creation failed." << std::endl;
        exit(FILE_CREATE_ERROR);
    }
    std::cout << std::endl << ">>> 文本文件 " << filename << " 创建成功" << std::endl;
    emptyFile.close();
    std::fstream textFile(filename);
    if (!textFile.is_open()) {
        std::cerr << "Error: File " << filename << " open failed." << std::endl;
        exit(FILE_OPEN_ERROR);
    }

    /* Keyword search system */
    KeywordSearch keywordSearch(filename);
    keywordSearch.inputTextAndKeyword(textFile);
    keywordSearch.outputText(textFile);
    keywordSearch.search(textFile, selectOptn());
    textFile.close();

    /* Wait for enter to quit */
    std::cout << "Press Enter to Quit" << std::endl;
    while (_getch() != '\r')
        continue;

    /* Program ends */
    return 0;
}