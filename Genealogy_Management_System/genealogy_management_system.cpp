/****************************************************************
 * Project Name:  Genealogy_Management_System
 * File Name:     genealogy_management_system.cpp
 * File Function: 家谱管理系统的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/25
 ****************************************************************/

#include <iostream>

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
    MyBinTreeNode() :leftChild(NULL), rightChild(NULL) {}
    MyBinTreeNode(Type item, MyBinTreeNode<Type>* l = NULL, MyBinTreeNode<Type>* r = NULL) :data(item), leftChild(l), rightChild(r) {}
};

/* Define MyBinaryTree class */
template <typename Type>
class MyBinaryTree {
private:
    /* Define private data member */
    MyBinTreeNode<Type>* root;

    /*
     * Function Name:    copy
     * Function:         Copy a subtree
     * Input Parameters: const MyBinTreeNode<Type>* subTree
     * Return Value:     a new subtree / NULL
     */
    MyBinTreeNode<Type>* copy(const MyBinTreeNode<Type>* subTree)
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
     * Function Name:    destroy
     * Function:         Destroy a subtree
     * Input Parameters: MyBinTreeNode<Type>* subTree
     * Return Value:     void
     */
    void destroy(MyBinTreeNode<Type>* subTree)
    {
        if (subTree) {
            destroy(subTree->leftChild);
            destroy(subTree->rightChild);
            delete subTree;
        }
    }

    /*
     * Function Name:    getHeight
     * Function:         Get the height of a subtree
     * Input Parameters: MyBinTreeNode<Type>* subTree
     * Return Value:     the height of a subtree
     */
    int getHeight(MyBinTreeNode<Type>* subTree)
    {
        return (subTree == NULL) ? 0 : (std::max(getHeight(subTree->leftChild), getHeight(subTree->rightChild)) + 1);
    }

    /*
     * Function Name:    getSize
     * Function:         Get the size (number of nodes) of a subtree
     * Input Parameters: MyBinTreeNode<Type>* subTree
     * Return Value:     the size (number of nodes) of a subtree
     */
    int getSize(MyBinTreeNode<Type>* subTree)
    {
        return (subTree == NULL) ? 0 : (getSize(subTree->leftChild) + getSize(subTree->rightChild) + 1);
    }

    /*
     * Function Name:    getParent
     * Function:         Find the parent of a given node
     * Input Parameters: MyBinTreeNode<Type>* subTree
     *                   MyBinTreeNode<Type>* current
     * Return Value:     the parent of a given node / NULL
     */
    MyBinTreeNode<Type>* getParent(MyBinTreeNode<Type>* subTree, MyBinTreeNode<Type>* current)
    {
        if (subTree == NULL)
            return NULL;
        if (subTree->leftChild == current || subTree->rightChild == current)
            return subTree;
        MyBinTreeNode<Type>* parent = getParent(subTree->leftChild, current);
        if (parent != NULL)
            return parent;
        return getParent(subTree->rightChild, current);
    }

    /*
     * Function Name:    findNode
     * Function:         Find a node with a given value
     * Input Parameters: MyBinTreeNode<Type>* subTree
     *                   const Type& item
     * Return Value:     the node / NULL
     */
    MyBinTreeNode<Type>* findNode(MyBinTreeNode<Type>* subTree, const Type& item)
    {
        if (subTree == NULL)
            return NULL;
        if (subTree->data == item)
            return subTree;
        MyBinTreeNode<Type>* found = findNode(subTree->leftChild, item);
        if (found != NULL)
            return found;
        return findNode(subTree->rightChild, item);
    }

    /*
     * Function Name:    preOrder
     * Function:         Traverse a subtree in pre-order
     * Input Parameters: MyBinTreeNode<Type>* subTree
     *                   void(*visit)(MyBinTreeNode<Type>*)
     * Return Value:     void
     */
    void preOrder(MyBinTreeNode<Type>* subTree, void(*visit)(MyBinTreeNode<Type>*))
    {
        if (subTree) {
            visit(subTree);
            preOrder(subTree->leftChild, visit);
            preOrder(subTree->rightChild, visit);
        }
    }

    /*
     * Function Name:    inOrder
     * Function:         Traverse a subtree in in-order
     * Input Parameters: MyBinTreeNode<Type>* subTree
     *                   void(*visit)(MyBinTreeNode<Type>*)
     * Return Value:     void
     */
    void inOrder(MyBinTreeNode<Type>* subTree, void(*visit)(MyBinTreeNode<Type>*))
    {
        if (subTree) {
            inOrder(subTree->leftChild, visit);
            visit(subTree);
            inOrder(subTree->rightChild, visit);
        }
    }

    /*
     * Function Name:    postOrder
     * Function:         Traverse a subtree in post-order 
     * Input Parameters: MyBinTreeNode<Type>* subTree
     *                   void(*visit)(MyBinTreeNode<Type>*)
     * Return Value:     void
     */
    void postOrder(MyBinTreeNode<Type>* subTree, void(*visit)(MyBinTreeNode<Type>*))
    {
        if (subTree) {
            postOrder(subTree->leftChild, visit);
            postOrder(subTree->rightChild, visit);
            visit(subTree);
        }
    }

    /*
     * Function Name:    levelOrder
     * Function:         Traverse a subtree in level-order
     * Input Parameters: MyBinTreeNode<Type>* subTree
     *                   void(*visit)(MyBinTreeNode<Type>*)
     * Return Value:     void
     */
    void levelOrder(MyBinTreeNode<Type>* subTree, void(*visit)(MyBinTreeNode<Type>*))
    {
        if (subTree == NULL)
            return;
        MyQueue<MyBinTreeNode<Type>*> q;
        q.enQueue(subTree);
        while (!q.isEmpty()) {
            MyBinTreeNode<Type>* current;
            if (!q.deQueue(current))
                break;
            visit(current);
            if (current->leftChild != NULL)
                q.enQueue(current->leftChild);
            if (current->rightChild != NULL)
                q.enQueue(current->rightChild);
        }
    }

    /*
     * Function Name:    outputNode
     * Function:         Output the data of a node
     * Input Parameters: MyBinTreeNode<Type>* node
     * Return Value:     void
     */
    void outputNode(MyBinTreeNode<Type>* node)
    {
        if (node != NULL)
            std::cout << node->data << " ";
    }

    /*
     * Function Name:    deleteNode
     * Function:         Delete a node and its subtree
     * Input Parameters: MyBinTreeNode<Type>* node
     * Return Value:     true / false
     */
    bool deleteNode(MyBinTreeNode<Type>* node)
    {
        if (node == NULL)
            return false;
        else {
            destroy(node);
            return true;
        }
    }

    /*
     * Function Name:    modifyNode
     * Function:         Modifiy the data of a given node
     * Input Parameters: MyBinTreeNode<Type>* subTree
     *                   const Type& newItem
     * Return Value:     true / false
     */
    bool modifyNode(MyBinTreeNode<Type>* subTree, const Type& newItem)
    {
        if (subTree == NULL)
            return false;
        subTree->data = newItem;
        return true;
    }

public:
    /*
     * Function Name:    MyBinaryTree
     * Function:         Constructed function
     */
    MyBinaryTree() :root(NULL) {}

    /*
     * Function Name:    MyBinaryTree
     * Function:         Constructed function
     * Input Parameters: MyBinaryTree<Type>& other
     */
    MyBinaryTree(MyBinaryTree<Type>& other)
    {
        root = copy(other.root);
    }

    /*
     * Function Name:    ~MyList
     * Function:         Destructor
     */
    ~MyBinaryTree()
    {
        destroy(root);
    }

    /*
     * Function Name:    isEmpty
     * Function:         Check if a tree is empty
     * Input Parameters: void
     * Return Value:     true / false
     */
    bool isEmpty(void)
    {
        return root == NULL;
    }

    /*
     * Function Name:    getHeight
     * Function:         Get the height of the tree
     * Input Parameters: void
     * Return Value:     the height of the tree
     */
    int getHeight(void)
    {
        return getHeight(root);
    }

    /*
     * Function Name:    getSize
     * Function:         Get the size (number of nodes) of the tree
     * Input Parameters: void
     * Return Value:     the size (number of nodes) of the tree
     */
    int getSize(void)
    {
        return getSize(root);
    }

    /*
     * Function Name:    getRoot
     * Function:         Get the root of the tree
     * Input Parameters: void
     * Return Value:     the root of the tree / NULL
     */
    MyBinTreeNode<Type>* getRoot(void)
    {
        return root;
    }

    /*
     * Function Name:    getParent
     * Function:         Get the parent of a given node
     * Input Parameters: MyBinTreeNode<Type>* current
     * Return Value:     the parent of a given node / NULL
     */
    MyBinTreeNode<Type>* getParent(MyBinTreeNode<Type>* current)
    {
        return (root == NULL || root == current) ? NULL : getParent(root, current);
    }

    /*
     * Function Name:    getLeftChild
     * Function:         Get the left child of a given node
     * Input Parameters: MyBinTreeNode<Type>* current
     * Return Value:     the left child of a given node / NULL
     */
    MyBinTreeNode<Type>* getLeftChild(MyBinTreeNode<Type>* current)
    {
        return current == NULL ? NULL : current->leftChild;
    }

    /*
     * Function Name:    getRightChild
     * Function:         Get the right child of a given node
     * Input Parameters: MyBinTreeNode<Type>* current
     * Return Value:     the right child of a given node / NULL
     */
    MyBinTreeNode<Type>* getRightChild(MyBinTreeNode<Type>* current)
    {
        return current == NULL ? NULL : current->rightChild;
    }

    /*
     * Function Name:    findNode
     * Function:         Find a node with a given value
     * Input Parameters: const Type& item
     * Return Value:     the node / NULL
     */
    MyBinTreeNode<Type>* findNode(const Type& item)
    {
        return findNode(root, item);
    }

    /*
     * Function Name:    preOrder
     * Function:         Traverse the tree in pre-order
     * Input Parameters: void(*visit)(MyBinTreeNode<Type>*)
     * Return Value:     void
     */
    void preOrder(void(*visit)(MyBinTreeNode<Type>*))
    {
        preOrder(root, visit);
    }

    /*
     * Function Name:    inOrder
     * Function:         Traverse the tree in in-order
     * Input Parameters: void(*visit)(MyBinTreeNode<Type>*)
     * Return Value:     void
     */
    void inOrder(void(*visit)(MyBinTreeNode<Type>*))
    {
        inOrder(root, visit);
    }

    /*
     * Function Name:    postOrder
     * Function:         Traverse the tree in post-order
     * Input Parameters: void(*visit)(MyBinTreeNode<Type>*)
     * Return Value:     void
     */
    void postOrder(void(*visit)(MyBinTreeNode<Type>*))
    {
        postOrder(root, visit);
    }

    /*
     * Function Name:    levelOrder
     * Function:         Traverse the tree in level-order
     * Input Parameters: void(*visit)(MyBinTreeNode<Type>*)
     * Return Value:     void
     */
    void levelOrder(void(*visit)(MyBinTreeNode<Type>*))
    {
        levelOrder(root, visit);
    }

    /*
     * Function Name:    preOrderOutput
     * Function:         Output the tree data in pre-order
     * Input Parameters: void
     * Return Value:     void
     */
    void preOrderOutput(void)
    {
        preOrder(root, outputNode);
    }

    /*
     * Function Name:    inOrderOutput
     * Function:         Output the tree data in in-order
     * Input Parameters: void
     * Return Value:     void
     */
    void inOrderOutput(void)
    {
        inOrder(root, outputNode);
    }

    /*
     * Function Name:    postOrderOutput
     * Function:         Output the tree data in post-order
     * Input Parameters: void
     * Return Value:     void
     */
    void postOrderOutput(void)
    {
        postOrder(root, outputNode);
    }

    /*
     * Function Name:    levelOrderOutput
     * Function:         Output the tree data in level-order
     * Input Parameters: void
     * Return Value:     void
     */
    void levelOrderOutput(void)
    {
        levelOrder(root, outputNode);
    }

    /*
     * Function Name:    leftInsertNode
     * Function:         Insert a new node as the left child of a given node
     * Input Parameters: MyBinTreeNode<Type>* current
     *                   const Type& item
     * Return Value:     true / false
     */
    bool leftInsertNode(MyBinTreeNode<Type>* current, const Type& item)
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
     */
    bool rightInsertNode(MyBinTreeNode<Type>* current, const Type& item)
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
     * Function Name:    deleteNode
     * Function:         Delete a node with a given value
     * Input Parameters: const Type& item
     * Return Value:     true / false
     */
    bool deleteNode(const Type& item)
    {
        return deleteNode(find(item));
    }

    /*
     * Function Name:    modifyNode
     * Function:         Modifiy the data of a node with a given old value to a new value
     * Input Parameters: const Type& oldItem
     *                   const Type& newItem
     * Return Value:     true / false
     */
    bool modifyNode(const Type& oldItem, const Type& newItem)
    {
        modifyNode(findNode(root, oldItem), newItem);
    }

    /*
     * Function Name:    inOrderPredecessor
     * Function:         Find the in-order predecessor of a given node
     * Input Parameters: MyBinTreeNode<Type>* node
     * Return Value:     true / false
     */
    MyBinTreeNode<Type>* inOrderPredecessor(MyBinTreeNode<Type>* node)
    {
        if (node == NULL)
            return NULL;
        if (node->leftChild != NULL) {
            MyBinTreeNode<Type>* pred = node->leftChild;
            while (pred->rightChild != NULL)
                pred = pred->rightChild;
            return pred;
        }
        MyBinTreeNode<Type>* parent = getParent(node);
        while (parent != NULL && node == parent->leftChild) {
            node = parent;
            parent = getParent(parent);
        }
        return parent;
    }

    /*
     * Function Name:    inOrderSuccessor
     * Function:         Find the in-order successor of a given node
     * Input Parameters: MyBinTreeNode<Type>* node
     * Return Value:     true / false
     */
    MyBinTreeNode<Type>* inOrderSuccessor(MyBinTreeNode<Type>* node)
    {
        if (node == NULL)
            return NULL;
        if (node->rightChild != NULL) {
            MyBinTreeNode<Type>* succ = node->rightChild;
            while (succ->leftChild != NULL)
                succ = succ->leftChild;
            return succ;
        }
        MyBinTreeNode<Type>* parent = getParent(node);
        while (parent != NULL && node == parent->rightChild) {
            node = parent;
            parent = getParent(parent);
        }
        return parent;
    }

    /*
     * Function Name:    operator=
     * Function:         Overload operator =
     * Input Parameters: const MyBinaryTree<Type>& other
     * Return Value:     *this
     */
    MyBinaryTree<Type>& operator=(const MyBinaryTree<Type>& other)
    {
        if (this != &other) {
            destroy(root);
            root = copy(other.root);
        }
        return *this;
    }
};

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    return 0;
}