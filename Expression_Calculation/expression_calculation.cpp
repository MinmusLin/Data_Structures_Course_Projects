/****************************************************************
 * Project Name:  Expression_Calculation
 * File Name:     expression_calculation.cpp
 * File Function: 表达式计算的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/28
 ****************************************************************/

#include <iostream>
#include <conio.h>

/* Macro definitions */
#define MEMORY_ALLOCATION_ERROR -1
#define MAX_LENGTH 256

/* Define MyLinkNode structure */
template <typename Type>
struct MyLinkNode {
    Type data;
    MyLinkNode<Type>* link;
    MyLinkNode(MyLinkNode<Type>* ptr = NULL) { link = ptr; }
    MyLinkNode(const Type& item, MyLinkNode<Type>* ptr = NULL) { data = item; link = ptr; }
};

/* Define MyStack class */
template <typename Type>
class MyStack {
private:
    MyLinkNode<Type>* top;
public:
    MyStack() : top(NULL) {}
    ~MyStack() { makeEmpty(); }
    bool isEmpty(void) const { return top == NULL; }
    void makeEmpty(void);
    void push(const Type& item);
    bool pop(Type& item);
    bool getTop(Type& item);
    int getSize(void) const;
};

/*
 * Function Name:    makeEmpty
 * Function:         Clear the stack
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyStack<Type>::makeEmpty(void)
{
    MyLinkNode<Type>* current;
    while (top != NULL) {
        current = top;
        top = top->link;
        delete current;
    }
}

/*
 * Function Name:    push
 * Function:         Push onto the stack
 * Input Parameters: const Type& item
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyStack<Type>::push(const Type& item)
{
    top = new(std::nothrow) MyLinkNode<Type>(item, top);
    if (top == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
}

/*
 * Function Name:    pop
 * Function:         Pop from the stack
 * Input Parameters: Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyStack<Type>::pop(Type& item)
{
    if (isEmpty())
        return false;
    else {
        MyLinkNode<Type>* current = top;
        top = top->link;
        item = current->data;
        delete current;
        return true;
    }
}

/*
 * Function Name:    getTop
 * Function:         Get the top element of the stack
 * Input Parameters: Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyStack<Type>::getTop(Type& item)
{
    if (isEmpty())
        return false;
    else {
        item = top->data;
        return true;
    }
}

/*
 * Function Name:    getSize
 * Function:         Calculate the number of elements in the stack
 * Input Parameters: void
 * Return Value:     the number of elements in the stack
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
int MyStack<Type>::getSize(void) const
{
    int count = 0;
    MyLinkNode<Type>* current = top;
    while (current != NULL) {
        current = current->link;
        count++;
    }
    return count;
}

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
    void outputNode(MyBinTreeNode<Type>* node) { if (node != NULL) std::cout << node->data; }
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

/* Define ExpressionTree class */
class ExpressionTree : public MyBinaryTree<char> {
private:
    MyStack<char> charStack;
    MyStack<MyBinTreeNode<char>*> treeStack;
    bool isOperand(char ch) { return ch >= '0' && ch <= '9'; }
    int precedence(char op);
public:
    void createExpressionTree(const char expression[]);
};

/*
 * Function Name:    precedence
 * Function:         Get operator precedence
 * Input Parameters: char op
 * Return Value:     precedence
 * Notes:            Class external implementation of member functions
 */
int ExpressionTree::precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

/*
 * Function Name:    createExpressionTree
 * Function:         Create expression tree
 * Input Parameters: const char expression[]
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void ExpressionTree::createExpressionTree(const char expression[])
{
    char postfix[MAX_LENGTH + 1]; // Array to store postfix expression
    int postfixIndex = 0; // Index for the postfix array
    for (int i = 0; expression[i] != '\0'; i++) {
        char token = expression[i];
        if (isOperand(token))
            postfix[postfixIndex++] = token; // Directly add operand to postfix
        else if (token == '(')
            charStack.push(token); // Push '(' onto stack
        else if (token == ')') {
            char topToken;
            charStack.getTop(topToken);
            while (!charStack.isEmpty() && topToken != '(') {
                charStack.pop(postfix[postfixIndex++]);
                if (!charStack.isEmpty())
                    charStack.getTop(topToken);
            }
            charStack.pop(topToken); // Pop the '(' from the stack
        }
        else {
            char topToken;
            charStack.getTop(topToken);
            while (!charStack.isEmpty() && precedence(token) <= precedence(topToken))
                charStack.pop(postfix[postfixIndex++]);
            charStack.push(token); // Push current operator onto stack
        }
    }
    while (!charStack.isEmpty())
        charStack.pop(postfix[postfixIndex++]); // Pop remaining operators from the stack
    postfix[postfixIndex] = '\0';
    for (int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];
        MyBinTreeNode<char>* node;
        if (isOperand(token)) {
            node = new(std::nothrow) MyBinTreeNode<char>(token);
            if (node == NULL) {
                std::cerr << "Error: Memory allocation failed." << std::endl;
                exit(MEMORY_ALLOCATION_ERROR);
            }
            treeStack.push(node); // Push node onto tree stack
        }
        else {
            MyBinTreeNode<char>* right, * left;
            treeStack.pop(right);
            treeStack.pop(left);
            node = new(std::nothrow) MyBinTreeNode<char>(token, left, right);
            if (node == NULL) {
                std::cerr << "Error: Memory allocation failed." << std::endl;
                exit(MEMORY_ALLOCATION_ERROR);
            }
            treeStack.push(node); // Push the new node onto the tree stack
        }
    }
    treeStack.getTop(this->root); // Set the root of the tree
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* System entry prompt */
    std::cout << "+--------------------------+" << std::endl;
    std::cout << "|        表达式计算        |" << std::endl;
    std::cout << "|  Expression Calculation  |" << std::endl;
    std::cout << "+--------------------------+" << std::endl << std::endl;

    /* Enter the expression */
    char expression[MAX_LENGTH + 1] = { 0 };
    std::cout << "请输入表达式: ";
    std::cin >> expression;

    // TODO: Invalid input

    /* Build the expression tree */
    ExpressionTree expressionTree;
    expressionTree.createExpressionTree(expression);

    /* Output three types of the expression */
    std::cout << std::endl << ">>> 前缀表达式（波兰表达式）  : ";
    expressionTree.preOrderOutput(expressionTree.getRoot());
    std::cout << std::endl << std::endl << ">>> 中缀表达式                : " << expression << std::endl;
    std::cout << std::endl << ">>> 后缀表达式（逆波兰表达式）: ";
    expressionTree.postOrderOutput(expressionTree.getRoot());
    std::cout << std::endl << std::endl;

    /* Wait for enter to quit */
    std::cout << "Press Enter to Quit" << std::endl;
    while (_getch() != '\r')
        continue;

    /* Program ends */
    return 0;
}