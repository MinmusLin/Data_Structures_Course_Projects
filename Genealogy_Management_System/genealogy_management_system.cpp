/****************************************************************
 * Project Name:  Genealogy_Management_System
 * File Name:     genealogy_management_system.cpp
 * File Function: 家谱管理系统的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/27
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <conio.h>
#include <limits>

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
private:
    MyBinTreeNode<Type>* root;
    typedef void (MyBinaryTree::* VisitFunction)(MyBinTreeNode<Type>*);
    MyBinTreeNode<Type>* copy(const MyBinTreeNode<Type>* subTree);
    void outputNode(MyBinTreeNode<Type>* node) { if (node != NULL) std::cout << node->data << " "; }
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

/* Define Person structure */
struct Person {
    enum { DescendantsMaxNumber = 16, NameMaxLength = 32 };
    char name[NameMaxLength + 1];
    Person() { strcpy(name, ""); }
    Person& operator=(const Person& other) { if (this != &other) strcpy(name, other.name); return *this; }
    bool operator==(const Person& other) { return strcmp(name, other.name) == 0; }
    friend std::ostream& operator<<(std::ostream& out, const Person& person);
    friend std::istream& operator>>(std::istream& in, Person& person);
};

/*
 * Function Name:    operator<<
 * Function:         Overload operator <<
 * Input Parameters: std::ostream& out
 *                   const Person& person
 * Return Value:     out
 */
std::ostream& operator<<(std::ostream& out, const Person& person)
{
    return (out << person.name);
}

/*
 * Function Name:    operator>>
 * Function:         Overload operator >>
 * Input Parameters: std::ostream& in
 *                   Person& person
 * Return Value:     in
 */
std::istream& operator>>(std::istream& in, Person& person)
{
    std::cin >> person.name;
    person.name[Person::NameMaxLength] = '\0';
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    return in;
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
    std::cout << std::endl << ">>> 菜单: [1] [2]添加家庭成员 [3]解散家庭成员 [4]更改家庭成员姓名 [5]统计家庭成员 [0]退出系统" << std::endl;
    std::cout << std::endl << "请选择操作类型: ";
    char optn;
    while (true) {
        optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if (optn >= '0' && optn <= '5') {
            std::cout << "[" << optn << "]" << std::endl << std::endl;
            return optn - '0';
        }
    }
}

/*
 * Function Name:    completeFamilyMembers
 * Function:         Complete family members
 * Input Parameters: MyBinaryTree<Person>& genealogy
 * Return Value:     void
 */
void completeFamilyMembers(MyBinaryTree<Person>& genealogy)
{
    Person person;
    std::cout << "请输入要建立家庭的人的姓名: ";
    std::cin >> person;
    char tmp[Person::NameMaxLength * 2];
    std::cout << std::endl;
    MyBinTreeNode<Person>* p = genealogy.findNode(person, genealogy.getRoot());
    if (p == NULL) {
        std::cout << ">>> 未在家谱中找到" << person << std::endl;
        return;
    }
    else if (p->leftChild != NULL) {
        std::cout << ">>> " << person << "已建立家庭" << std::endl;
        return;
    }
    strcat(strcpy(tmp, person.name), "的儿女人数");
    int num = inputInteger(1, Person::DescendantsMaxNumber, tmp);
    std::cout << std::endl << ">>> 请依次输入" << person << "的儿女的姓名" << std::endl << std::endl;
    Person* descendants = new(std::nothrow) Person[num];
    if (descendants == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < num; i++) {
        std::cout << "请输入" << person << "的第" << i + 1 << "个儿女的姓名: ";
        std::cin >> descendants[i];
        if (genealogy.findNode(descendants[i], genealogy.getRoot())) {
            std::cout << std::endl << ">>> " << descendants[i--] << "在家谱中已存在" << std::endl << std::endl;
            continue;
        }
        if (i == 0)
            genealogy.leftInsertNode(genealogy.findNode(person, genealogy.getRoot()), descendants[i]);
        else
            genealogy.rightInsertNode(genealogy.findNode(descendants[i - 1], genealogy.getRoot()), descendants[i]);
    }
    std::cout << std::endl << ">>> " << person << "的下一代子孙是: ";
    for (int i = 0; i < num; i++)
        std::cout << (i == 0 ? "" : " ") << descendants[i];
    std::cout << std::endl;
}

/*
 * Function Name:    addFamilyMembers
 * Function:         Add family members
 * Input Parameters: MyBinaryTree<Person>& genealogy
 * Return Value:     void
 */
void addFamilyMembers(MyBinaryTree<Person>& genealogy)
{
    Person person, descendant;
    std::cout << "请输入要添加家庭成员的人的姓名: ";
    std::cin >> person;
    if (!genealogy.findNode(person, genealogy.getRoot())) {
        std::cout << std::endl << ">>> 未在家谱中找到" << person << std::endl;
        return;
    }
    while (true) {
        std::cout << std::endl << "请输入" << person << "新添加的儿女的姓名: ";
        std::cin >> descendant;
        if (genealogy.findNode(descendant, genealogy.getRoot())) {
            std::cout << std::endl << ">>> " << descendant << "在家谱中已存在" << std::endl;
            continue;
        }
        break;
    }
    MyBinTreeNode<Person>* p = genealogy.findNode(person, genealogy.getRoot());
    std::cout << std::endl << ">>> " << person << "的下一代子孙是: ";
    if (p->leftChild == NULL)
        genealogy.leftInsertNode(p, descendant);
    else {
        MyBinTreeNode<Person>* current = p->leftChild;
        std::cout << current->data << " ";
        while (current->rightChild != NULL) {
            current = current->rightChild;
            std::cout << current->data << " ";
        }
        genealogy.rightInsertNode(current, descendant);
    }
    std::cout << descendant << std::endl;
}

/*
 * Function Name:    removeFamilyMembers
 * Function:         Remove family members
 * Input Parameters: MyBinaryTree<Person>& genealogy
 * Return Value:     void
 */
void removeFamilyMembers(MyBinaryTree<Person>& genealogy)
{
    Person person;
    std::cout << "请输入要解散家庭成员的人的姓名: ";
    std::cin >> person;
    MyBinTreeNode<Person>* p = genealogy.findNode(person, genealogy.getRoot());
    if (p == NULL) {
        std::cout << std::endl << ">>> 未在家谱中找到" << person << std::endl;
        return;
    }
    else if (p->leftChild == NULL) {
        std::cout << std::endl << ">>> " << person << "无家庭成员" << std::endl;
        return;
    }
    std::cout << std::endl << ">>> " << person << "的家庭成员是: ";
    genealogy.inOrderOutput(p->leftChild);
    genealogy.destroy(p->leftChild);
    std::cout << std::endl << std::endl << ">>> " << person << "的家庭成员已解散" << std::endl;
}

/*
 * Function Name:    changeFamilyMembers
 * Function:         Change family members
 * Input Parameters: MyBinaryTree<Person>& genealogy
 * Return Value:     void
 */
void changeFamilyMembers(MyBinaryTree<Person>& genealogy)
{
    Person personBeforeChange, personAfterChange;
    std::cout << "请输入要更改家庭成员姓名的人的更改前姓名: ";
    std::cin >> personBeforeChange;
    if (!genealogy.findNode(personBeforeChange, genealogy.getRoot())) {
        std::cout << std::endl << ">>> 未在家谱中找到" << personBeforeChange << std::endl;
        return;
    }
    while (true) {
        std::cout << std::endl << "请输入要更改家庭成员姓名的人的更改后姓名: ";
        std::cin >> personAfterChange;
        if (genealogy.findNode(personAfterChange, genealogy.getRoot())) {
            std::cout << std::endl << ">>> " << personAfterChange << "在家谱中已存在" << std::endl;
            continue;
        }
        break;
    }
    genealogy.modifyNode(personBeforeChange, personAfterChange, genealogy.getRoot());
    std::cout << std::endl << ">>> " << personBeforeChange << "已更名为" << personAfterChange << std::endl;
}

/*
 * Function Name:    countFamilyMembers
 * Function:         Count family members
 * Input Parameters: MyBinaryTree<Person>& genealogy
 * Return Value:     void
 */
void countFamilyMembers(MyBinaryTree<Person>& genealogy)
{
    Person person;
    std::cout << "请输入要统计的家庭成员的人的姓名: ";
    std::cin >> person;
    MyBinTreeNode<Person>* p = genealogy.findNode(person, genealogy.getRoot());
    if (p == NULL) {
        std::cout << std::endl << ">>> 未在家谱中找到" << person << std::endl;
        return;
    }
    int num = genealogy.getSize(p->leftChild);
    std::cout << std::endl << ">>> " << person << "共有" << num << "个儿女";
    if (num != 0) {
        std::cout << "，分别是: ";
        genealogy.inOrderOutput(p->leftChild);
    }
    std::cout << std::endl;
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* System entry prompt */
    std::cout << "+-------------------------------+" << std::endl;
    std::cout << "|         家谱管理系统          |" << std::endl;
    std::cout << "|  Genealogy Management System  |" << std::endl;
    std::cout << "+-------------------------------+" << std::endl << std::endl;

    /* Establish a genealogy management system */
    std::cout << ">>> 请建立家谱管理系统" << std::endl;
    std::cout << std::endl << ">>> [姓名输入要求] 不超过 " << Person::NameMaxLength << " 个英文字符或 " << Person::NameMaxLength / 2 << " 个汉字字符组成的字符串，超出部分将被截断" << std::endl;
    std::cout << std::endl << "请输入祖先姓名: ";
    Person ancestor;
    std::cin >> ancestor;
    MyBinaryTree<Person> genealogy(ancestor);
    std::cout << std::endl << ">>> 家谱建立成功（祖先: " << genealogy.getRoot()->data << "）" << std::endl;

    /* Perform operations on genealogy management system */
    while (true) {
        switch (selectOptn()) {
            case 1:
                completeFamilyMembers(genealogy);
                break;
            case 2:
                addFamilyMembers(genealogy);
                break;
            case 3:
                removeFamilyMembers(genealogy);
                break;
            case 4:
                changeFamilyMembers(genealogy);
                break;
            case 5:
                countFamilyMembers(genealogy);
                break;
            default:
                std::cout << ">>> 家谱管理系统已退出" << std::endl;
                return 0;
        }
    }
}