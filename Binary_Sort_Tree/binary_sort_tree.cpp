/****************************************************************
 * Project Name:  Binary_Sort_Tree
 * File Name:     binary_sort_tree.cpp
 * File Function: 二叉排序树的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/13
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <iostream>
#include <climits>
#ifdef _WIN32
#include <conio.h>
#elif __linux__
#include <ncurses.h>
#endif

/* Macro definition */
#define MEMORY_ALLOCATION_ERROR -1

/* Define MyLinkNode structure */
template <typename Type>
struct MyLinkNode {
    Type data;
    MyLinkNode<Type>* link;
    MyLinkNode(MyLinkNode<Type>* ptr = NULL) { link = ptr; }
    MyLinkNode(const Type& item, MyLinkNode<Type>* ptr = NULL) { data = item; link = ptr; }
};

/* Define MyQueue class */
template <typename Type>
class MyQueue {
private:
    MyLinkNode<Type>* front;
    MyLinkNode<Type>* rear;
public:
    MyQueue() : front(NULL), rear(NULL) {}
    ~MyQueue() { makeEmpty(); }
    bool isEmpty(void) const { return front == NULL; }
    void makeEmpty(void);
    void enQueue(const Type& item);
    bool deQueue(Type& item);
    bool getFront(Type& item) const;
    int getSize(void) const;
};

/*
 * Function Name:    makeEmpty
 * Function:         Clear the queue
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyQueue<Type>::makeEmpty(void)
{
    MyLinkNode<Type>* current;
    while (front != NULL) {
        current = front;
        front = front->link;
        delete current;
    }
}

/*
 * Function Name:    enQueue
 * Function:         Add item to the queue
 * Input Parameters: const Type& item
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyQueue<Type>::enQueue(const Type& item)
{
    if (front == NULL) {
        rear = new(std::nothrow) MyLinkNode<Type>(item);
        if (rear == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        front = rear;
    }
    else {
        rear->link = new(std::nothrow) MyLinkNode<Type>(item);
        if (rear->link == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        rear = rear->link;
    }
}

/*
 * Function Name:    deQueue
 * Function:         Remove the front element and return its value by reference
 * Input Parameters: Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyQueue<Type>::deQueue(Type& item)
{
    if (isEmpty())
        return false;
    else {
        MyLinkNode<Type>* current = front;
        item = front->data;
        front = front->link;
        delete current;
        return true;
    }
}

/*
 * Function Name:    getFront
 * Function:         Get the value of the front element
 * Input Parameters: Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyQueue<Type>::getFront(Type& item) const
{
    if (isEmpty())
        return false;
    else {
        item = front->data;
        return true;
    }
}

/*
 * Function Name:    getSize
 * Function:         Calculate the number of elements in the queue
 * Input Parameters: void
 * Return Value:     the number of elements in the queue
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
int MyQueue<Type>::getSize(void) const
{
    int count = 0;
    MyLinkNode<Type>* current = front;
    while (current != NULL) {
        current = current->link;
        count++;
    }
    return count;
}

/* Define MyBinTreeNode structure */
template <typename Type>
struct MyBinTreeNode {
    Type data;
    MyBinTreeNode<Type>* leftChild;
    MyBinTreeNode<Type>* rightChild;
    MyBinTreeNode() : leftChild(NULL), rightChild(NULL) {}
    MyBinTreeNode(Type item, MyBinTreeNode<Type>* l = NULL, MyBinTreeNode<Type>* r = NULL) : data(item), leftChild(l), rightChild(r) {}
};

/* Define MyBinaryTree class */
template <typename Type>
class MyBinaryTree {
protected:
    MyBinTreeNode<Type>* root;
private:
    typedef void (MyBinaryTree::* VisitFunction)(MyBinTreeNode<Type>*);
    MyBinTreeNode<Type>* copy(const MyBinTreeNode<Type>* subTree);
    void outputNode(MyBinTreeNode<Type>* node) { if (node != NULL) std::cout << node->data << " -> "; }
public:
    MyBinaryTree() : root(NULL) {}
    MyBinaryTree(Type& item);
    MyBinaryTree(MyBinaryTree<Type>& other) { root = copy(other.root); }
    ~MyBinaryTree() { destroy(root); }
    void destroy(MyBinTreeNode<Type>*& subTree);
    bool isEmpty(void) { return root == NULL; }
    int getHeight(MyBinTreeNode<Type>* subTree) { return (subTree == NULL) ? 0 : (std::max(getHeight(subTree->leftChild), getHeight(subTree->rightChild)) + 1); }
    int getSize(MyBinTreeNode<Type>* subTree) { return (subTree == NULL) ? 0 : (getSize(subTree->leftChild) + getSize(subTree->rightChild) + 1); }
    MyBinTreeNode<Type>* getRoot(void) { return root; }
    MyBinTreeNode<Type>* getParent(MyBinTreeNode<Type>* current, MyBinTreeNode<Type>* subTree);
    MyBinTreeNode<Type>* getLeftChild(MyBinTreeNode<Type>* current) { return current == NULL ? NULL : current->leftChild; }
    MyBinTreeNode<Type>* getRightChild(MyBinTreeNode<Type>* current) { return current == NULL ? NULL : current->rightChild; }
    MyBinTreeNode<Type>* findNode(const Type& item, MyBinTreeNode<Type>* subTree);
    void preOrder(VisitFunction visit, MyBinTreeNode<Type>* subTree);
    void inOrder(VisitFunction visit, MyBinTreeNode<Type>* subTree);
    void postOrder(VisitFunction visit, MyBinTreeNode<Type>* subTree);
    void levelOrder(VisitFunction visit, MyBinTreeNode<Type>* subTree);
    void preOrderOutput(MyBinTreeNode<Type>* subTree) { preOrder(&MyBinaryTree<Type>::outputNode, subTree); }
    void inOrderOutput(MyBinTreeNode<Type>* subTree) { inOrder(&MyBinaryTree<Type>::outputNode, subTree); }
    void postOrderOutput(MyBinTreeNode<Type>* subTree) { postOrder(&MyBinaryTree<Type>::outputNode, subTree); }
    void levelOrderOutput(MyBinTreeNode<Type>* subTree) { levelOrder(&MyBinaryTree<Type>::outputNode, subTree); }
    bool leftInsertNode(MyBinTreeNode<Type>* current, const Type& item);
    bool rightInsertNode(MyBinTreeNode<Type>* current, const Type& item);
    bool modifyNode(const Type& oldItem, const Type& newItem, MyBinTreeNode<Type>* subTree);
    MyBinaryTree<Type>& operator=(const MyBinaryTree<Type>& other);
};

/*
 * Function Name:    copy
 * Function:         Copy a subtree
 * Input Parameters: const MyBinTreeNode<Type>* subTree
 * Return Value:     a new subtree / NULL
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyBinTreeNode<Type>* MyBinaryTree<Type>::copy(const MyBinTreeNode<Type>* subTree)
{
    if (subTree == NULL)
        return NULL;
    MyBinTreeNode<Type>* newNode = new(std::nothrow) MyBinTreeNode<Type>(subTree->data);
    if (newNode == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    newNode->leftChild = copy(subTree->leftChild);
    newNode->rightChild = copy(subTree->rightChild);
    return newNode;
}

/*
 * Function Name:    MyBinaryTree
 * Function:         Constructed function
 * Input Parameters: Type& item
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyBinaryTree<Type>::MyBinaryTree(Type& item)
{
    root = new(std::nothrow) MyBinTreeNode<Type>(item);
    if (root == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
}

/*
 * Function Name:    destroy
 * Function:         Destroy a subtree
 * Input Parameters: MyBinTreeNode<Type>*& subTree
 * Notes:            Class external implementation of member functions
 * Return Value:     void
 */
template <typename Type>
void MyBinaryTree<Type>::destroy(MyBinTreeNode<Type>*& subTree)
{
    if (subTree) {
        destroy(subTree->leftChild);
        destroy(subTree->rightChild);
        delete subTree;
        subTree = NULL;
    }
}

/*
 * Function Name:    getParent
 * Function:         Find the parent of a given node
 * Input Parameters: MyBinTreeNode<Type>* current
 *                   MyBinTreeNode<Type>* subTree
 * Return Value:     the parent of a given node / NULL
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyBinTreeNode<Type>* MyBinaryTree<Type>::getParent(MyBinTreeNode<Type>* current, MyBinTreeNode<Type>* subTree)
{
    if (subTree == NULL || current == NULL)
        return NULL;
    if (subTree->leftChild == current || subTree->rightChild == current)
        return subTree;
    MyBinTreeNode<Type>* foundParent = getParent(current, subTree->leftChild);
    if (foundParent == NULL)
        foundParent = getParent(current, subTree->rightChild);
    return foundParent;
}

/*
 * Function Name:    findNode
 * Function:         Find a node with a given value
 * Input Parameters: const Type& item
 *                   MyBinTreeNode<Type>* subTree
 * Return Value:     the node / NULL
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyBinTreeNode<Type>* MyBinaryTree<Type>::findNode(const Type& item, MyBinTreeNode<Type>* subTree)
{
    if (subTree == NULL)
        return NULL;
    if (subTree->data == item)
        return subTree;
    MyBinTreeNode<Type>* found = findNode(item, subTree->leftChild);
    if (found != NULL)
        return found;
    return findNode(item, subTree->rightChild);
}

/*
 * Function Name:    preOrder
 * Function:         Traverse a subtree in pre-order
 * Input Parameters: VisitFunction visit
 *                   MyBinTreeNode<Type>* subTree
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyBinaryTree<Type>::preOrder(VisitFunction visit, MyBinTreeNode<Type>* subTree)
{
    if (subTree) {
        (this->*visit)(subTree);
        preOrder(visit, subTree->leftChild);
        preOrder(visit, subTree->rightChild);
    }
}

/*
 * Function Name:    inOrder
 * Function:         Traverse a subtree in in-order
 * Input Parameters: VisitFunction visit
 *                   MyBinTreeNode<Type>* subTree
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyBinaryTree<Type>::inOrder(VisitFunction visit, MyBinTreeNode<Type>* subTree)
{
    if (subTree) {
        inOrder(visit, subTree->leftChild);
        (this->*visit)(subTree);
        inOrder(visit, subTree->rightChild);
    }
}

/*
 * Function Name:    postOrder
 * Function:         Traverse a subtree in post-order
 * Input Parameters: VisitFunction visit
 *                   MyBinTreeNode<Type>* subTree
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyBinaryTree<Type>::postOrder(VisitFunction visit, MyBinTreeNode<Type>* subTree)
{
    if (subTree) {
        postOrder(visit, subTree->leftChild);
        postOrder(visit, subTree->rightChild);
        (this->*visit)(subTree);
    }
}

/*
 * Function Name:    levelOrder
 * Function:         Traverse a subtree in level-order
 * Input Parameters: VisitFunction visit
 *                   MyBinTreeNode<Type>* subTree
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyBinaryTree<Type>::levelOrder(VisitFunction visit, MyBinTreeNode<Type>* subTree)
{
    if (subTree == NULL)
        return;
    MyQueue<MyBinTreeNode<Type>*> q;
    q.enQueue(subTree);
    while (!q.isEmpty()) {
        MyBinTreeNode<Type>* current;
        if (!q.deQueue(current))
            break;
        (this->*visit)(current);
        if (current->leftChild != NULL)
            q.enQueue(current->leftChild);
        if (current->rightChild != NULL)
            q.enQueue(current->rightChild);
    }
}

/*
 * Function Name:    leftInsertNode
 * Function:         Insert a new node as the left child of a given node
 * Input Parameters: MyBinTreeNode<Type>* current
 *                   const Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyBinaryTree<Type>::leftInsertNode(MyBinTreeNode<Type>* current, const Type& item)
{
    if (current == NULL || current->leftChild != NULL)
        return false;
    current->leftChild = new(std::nothrow) MyBinTreeNode<Type>(item);
    if (current->leftChild == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    return true;
}

/*
 * Function Name:    rightInsertNode
 * Function:         Insert a new node as the right child of a given node
 * Input Parameters: MyBinTreeNode<Type>* current
 *                   const Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyBinaryTree<Type>::rightInsertNode(MyBinTreeNode<Type>* current, const Type& item)
{
    if (current == NULL || current->rightChild != NULL)
        return false;
    current->rightChild = new(std::nothrow) MyBinTreeNode<Type>(item);
    if (current->rightChild == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    return true;
}

/*
 * Function Name:    modifyNode
 * Function:         Modifiy the data of a given node
 * Input Parameters: const Type& oldItem
 *                   const Type& newItem
 *                   MyBinTreeNode<Type>* subTree
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyBinaryTree<Type>::modifyNode(const Type& oldItem, const Type& newItem, MyBinTreeNode<Type>* subTree)
{
    MyBinTreeNode<Type>* node = findNode(oldItem, subTree);
    if (node == NULL)
        return false;
    else {
        node->data = newItem;
        return true;
    }
}

/*
 * Function Name:    operator=
 * Function:         Overload operator =
 * Input Parameters: const MyBinaryTree<Type>& other
 * Return Value:     *this
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyBinaryTree<Type>& MyBinaryTree<Type>::operator=(const MyBinaryTree<Type>& other)
{
    if (this != &other) {
        destroy(root);
        root = copy(other.root);
    }
    return *this;
}

/* Define BinarySortTree class */
template <typename Type>
class BinarySortTree : public MyBinaryTree<Type> {
private:
    void insertPrivate(const Type& item, MyBinTreeNode<Type>*& subTree);
public:
    void insert(const Type& item) { insertPrivate(item, this->root); }
    bool search(const Type& item);
    void outputBST(void);
};

/*
 * Function Name:    insertPrivate
 * Function:         Insert a new node to binary sort tree
 * Input Parameters: const Type& item
 *                   MyBinTreeNode<Type>*& subTree
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void BinarySortTree<Type>::insertPrivate(const Type& item, MyBinTreeNode<Type>*& subTree)
{
    if (subTree == NULL) {
        subTree = new(std::nothrow) MyBinTreeNode<Type>(item);
        if (subTree == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
    }
    else if (item < subTree->data)
        insertPrivate(item, subTree->leftChild);
    else if (item > subTree->data)
        insertPrivate(item, subTree->rightChild);
    // If item is equal to subTree->data, then it is not inserted,
    // because binary sort tree (BST) does not allow duplicate values.
}

/*
 * Function Name:    search
 * Function:         Search a node in binary sort tree
 * Input Parameters: const Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool BinarySortTree<Type>::search(const Type& item)
{
    MyBinTreeNode<Type>* current = this->root;
    while (current != NULL) {
        if (item == current->data)
            return true;
        else if (item < current->data)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    return false;
}

/*
 * Function Name:    outputBST
 * Function:         Output binary sort tree
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void BinarySortTree<Type>::outputBST(void)
{
    std::cout << std::endl << ">>> 二叉排序树（元素个数: " << this->getSize(this->root) << "）: ";
    this->inOrderOutput(this->root);
    std::cout << "[END]" << std::endl;
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
 * Function Name:    selectOptn
 * Function:         Select operation
 * Input Parameters: void
 * Return Value:     operation
 */
int selectOptn(void)
{
    std::cout << std::endl << ">>> 菜单: [1]插入元素 [2]查询元素 [0]退出程序" << std::endl;
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
        else if (optn >= '0' && optn <= '2') {
            std::cout << "[" << optn << "]" << std::endl;
            return optn - '0';
        }
    }
}

/*
 * Function Name:    insertElement
 * Function:         Insert element function
 * Input Parameters: BinarySortTree<int>& binarySortTree
 * Return Value:     void
 */
void insertElement(BinarySortTree<int>& binarySortTree)
{
    std::cout << std::endl;
    int val = inputInteger(SHRT_MIN, SHRT_MAX, "插入元素的值");
    if (binarySortTree.search(val))
        std::cout << std::endl << ">>> 输入元素的值 " << val << " 在二叉排序树中已存在！" << std::endl;
    else {
        binarySortTree.insert(val);
        binarySortTree.outputBST();
    }
}

/*
 * Function Name:    searchElement
 * Function:         Search element function
 * Input Parameters: BinarySortTree<int>& binarySortTree
 * Return Value:     void
 */
void searchElement(BinarySortTree<int>& binarySortTree)
{
    std::cout << std::endl;
    int val = inputInteger(SHRT_MIN, SHRT_MAX, "查询元素的值");
    std::cout << std::endl << ">>> 查询元素的值 " << val << " 在二叉排序树中" << (binarySortTree.search(val) ? "" : "不") << "存在！" << std::endl;
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
    std::cout << "|     二叉排序树     |" << std::endl;
    std::cout << "|  Binary Sort Tree  |" << std::endl;
    std::cout << "+--------------------+" << std::endl;

    /* Establish binary sort tree */
    BinarySortTree<int> binarySortTree;
    std::cout << std::endl << ">>> 请建立二叉排序树" << std::endl << std::endl;
    int num = inputInteger(SHRT_MIN, SHRT_MAX, "二叉排序树元素个数");
    std::cout << std::endl << ">>> 请依次输入元素的值（使用空格分隔）" << std::endl << std::endl;
    for (int i = 0; i < num; i++) {
        char tmp[64] = { 0 };
        sprintf(tmp, "第 %d 个元素的值", i + 1);
        int val = inputInteger(SHRT_MIN, SHRT_MAX, tmp);
        if (binarySortTree.search(val)) {
            std::cout << std::endl << ">>> 输入元素的值 " << val << " 在二叉排序树中已存在，请重新输入！" << std::endl << std::endl;
            i--;
        }
        else
            binarySortTree.insert(val);
    }
    std::cout << std::endl << ">>> 二叉排序树建立完成" << std::endl;
    binarySortTree.outputBST();

    /* Perform operations */
    while (true) {
        int optn = selectOptn();
        if (optn == 1)
            insertElement(binarySortTree);
        else if (optn == 2)
            searchElement(binarySortTree);
        else
            return 0;
    }
}