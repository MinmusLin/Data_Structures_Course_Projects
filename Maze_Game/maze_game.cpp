/****************************************************************
 * Project Name:  Maze_Game
 * File Name:     maze_game.cpp
 * File Function: 迷宫游戏的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/10/25
 ****************************************************************/

#include <iostream>
#include <ctime>
#include <Windows.h>
#include <limits>
#include <conio.h>
#include <cmath>
#include <iomanip>

/* Macro definitions */
#define MEMORY_ALLOCATION_ERROR -1
#define INVALID_INDEX_ERROR -2
#define MAZE_BLANK 0
#define MAZE_WALL 1
#define MAZE_PATH 2

/* Define constant variables */
const int mazeSizeLowerLimit = 7;
const int mazeSizeUpperLimit = 99;
const int mazeStartRow = 1;
const int mazeStartCol = 1;

/* Define Direction */
enum Direction { Up, Down, Left, Right };

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

/* Define MyPriorityQueue class */
template <typename Type>
class MyPriorityQueue {
private:
    Type* elements;
    int count;
    int maxSize;
    void adjust(void);
public:
    MyPriorityQueue(int _maxSize);
    ~MyPriorityQueue() { delete[] elements; }
    void makeEmpty(void) { count = 0; }
    bool isEmpty(void) const { return count == 0; }
    bool isFull(void) const { return count == maxSize; }
    int getSize(void) const { return count; }
    bool insert(const Type& item);
    bool remove(Type& item);
    bool getFront(Type& item) const;
};

/*
 * Function Name:    adjust
 * Function:         Adjust the queue
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
void MyPriorityQueue<Type>::adjust(void)
{
    Type temp = elements[count - 1];
    for (int i = count - 2; i >= 0; i--) {
        if (elements[i] <= temp)
            break;
        else
            elements[i + 1] = elements[i];
        elements[i] = temp;
    }
}

/*
 * Function Name:    MyPriorityQueue
 * Function:         Constructed function
 * Input Parameters: int _maxSize
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
MyPriorityQueue<Type>::MyPriorityQueue(int _maxSize)
{
    maxSize = _maxSize;
    count = 0;
    elements = new(std::nothrow) Type[maxSize];
    if (elements == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
}

/*
 * Function Name:    insert
 * Function:         Add item to the queue
 * Input Parameters: const Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyPriorityQueue<Type>::insert(const Type& item)
{
    if (isFull())
        return false;
    else {
        elements[count++] = item;
        adjust();
        return true;
    }
}

/*
 * Function Name:    remove
 * Function:         Remove the front element and return its value by reference
 * Input Parameters: Type& item
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
template <typename Type>
bool MyPriorityQueue<Type>::remove(Type& item)
{
    if (isEmpty())
        return false;
    else {
        item = elements[0];
        for (int i = 1; i < count; i++)
            elements[i - 1] = elements[i];
        count--;
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
bool MyPriorityQueue<Type>::getFront(Type& item) const
{
    if (isEmpty())
        return false;
    else {
        item = elements[0];
        return true;
    }
}

/* Define Coordinate structure */
typedef struct {
    int row;
    int col;
} Coordinate;

/* Define AStarNode structure */
typedef struct {
    int row;
    int col;
    int accumuCost;
    int totalCost;
} AStarNode;

/*
 * Function Name:    operator<=
 * Function:         Overload operator <=
 * Input Parameters: const AStarNode& left
 *                   const AStarNode& right
 * Return Value:     true / false
 */
bool operator<=(const AStarNode& left, const AStarNode& right)
{
    return left.totalCost <= right.totalCost;
}

/* Define Maze class */
class Maze {
private:
    int** mazeMap;
    int rows;
    int cols;
    int startRow;
    int startCol;
    int targetRow;
    int targetCol;
    int currRow;
    int currCol;
    int mazePointCount;
    struct MazePoint { int row; int col; Direction direction; };
    MazePoint* mazePointList;
    MyStack<Coordinate> path;
    void pushList(const struct MazePoint& mazePoint);
    void popList(int index);
    void findAdjacentWalls(void);
    void generateMaze(void);
    bool isValid(int row, int col);
    bool recursivePathfinding(int row, int col, bool** visited);
public:
    Maze(int _rows, int _cols, int _startRow, int _startCol, int _targetRow, int _targetCol);
    ~Maze();
    void output(void);
    bool recursiveBacktracking(void);
    bool DFS(void);
    bool BFS(void);
    bool AStar(void);
    MyStack<Coordinate>& getPath(void) { return path; }
};

/*
 * Function Name:    pushList
 * Function:         Insert a maze point at the end of the maze point list
 * Input Parameters: const struct MazePoint& mazePoint
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Maze::pushList(const struct MazePoint& mazePoint)
{
    mazePointList[mazePointCount++] = mazePoint;
}

/*
 * Function Name:    popList
 * Function:         Remove an element from the list and rearrange the remaining elements
 * Input Parameters: int index
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Maze::popList(int index)
{
    if (index < 0 || index >= mazePointCount) {
        std::cerr << "Error: Invalid index for erase operation." << std::endl;
        exit(INVALID_INDEX_ERROR);
    }
    for (int i = index; i < mazePointCount - 1; i++)
        mazePointList[i] = mazePointList[i + 1];
    mazePointCount--;
}

/*
 * Function Name:    findAdjacentWalls
 * Function:         Find adjacent walls
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Maze::findAdjacentWalls(void)
{
    if (currRow < rows && mazeMap[currRow + 1][currCol] == MAZE_WALL)
        pushList({ currRow + 1, currCol, Down });
    if (currCol < cols && mazeMap[currRow][currCol + 1] == MAZE_WALL)
        pushList({ currRow, currCol + 1, Right });
    if (currRow > 1 && mazeMap[currRow - 1][currCol] == MAZE_WALL)
        pushList({ currRow - 1, currCol, Up });
    if (currCol > 1 && mazeMap[currRow][currCol - 1] == MAZE_WALL)
        pushList({ currRow, currCol - 1, Left });
}

/*
 * Function Name:    generateMaze
 * Function:         Generate maze
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Maze::generateMaze(void)
{
    findAdjacentWalls();
    while (mazePointCount) {
        int index = rand() % mazePointCount;
        MazePoint currPoint = mazePointList[index];
        currRow = currPoint.row;
        currCol = currPoint.col;
        if (currPoint.direction == Up)
            currRow--;
        else if (currPoint.direction == Down)
            currRow++;
        else if (currPoint.direction == Left)
            currCol--;
        else if (currPoint.direction == Right)
            currCol++;
        if (isValid(currRow, currCol) && mazeMap[currRow][currCol] == MAZE_WALL) {
            mazeMap[currPoint.row][currPoint.col] = mazeMap[currRow][currCol] = MAZE_BLANK;
            findAdjacentWalls();
        }
        popList(index);
    }
}

/*
 * Function Name:    isValid
 * Function:         Check if a point is inside the map
 * Input Parameters: int row
 *                   int col
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
bool Maze::isValid(int row, int col)
{
    return (row >= 0 && row < rows && col >= 0 && col < cols);
}

/*
 * Function Name:    recursivePathfinding
 * Function:         Recursive pathfinding
 * Input Parameters: int row
 *                   int col
 *                   bool** visited
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Maze::recursivePathfinding(int row, int col, bool** visited)
{
    /* Check if we have reached the target destination */
    if (row == targetRow && col == targetCol)
        return true;

    /* Mark the current position as visited */
    visited[row][col] = true;

    /* Define four possible movement directions */
    const int dr[] = { -1, 1, 0, 0 }, dc[] = { 0, 0, -1, 1 };

    /* Check if the new position is within the maze and has not been visited */
    for (int i = 0; i < 4; i++) {
        int newRow = row + dr[i], newCol = col + dc[i];
        if (isValid(newRow, newCol) && !visited[newRow][newCol] && mazeMap[newRow][newCol] == MAZE_BLANK && recursivePathfinding(newRow, newCol, visited)) {
            mazeMap[newRow][newCol] = MAZE_PATH;
            path.push({ newRow,newCol });
            return true;
        }
    }
    return false;
}

/*
 * Function Name:    Maze
 * Function:         Constructed function
 * Notes:            Class external implementation of member functions
 */
Maze::Maze(int _rows, int _cols, int _startRow, int _startCol, int _targetRow, int _targetCol)
{
    rows = _rows;
    cols = _cols;
    startRow = _startRow;
    startCol = _startCol;
    targetRow = _targetRow;
    targetCol = _targetCol;
    currRow = startRow;
    currCol = startCol;
    mazeMap = new(std::nothrow) int* [rows];
    if (mazeMap == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < rows; i++) {
        mazeMap[i] = new(std::nothrow) int[cols];
        if (mazeMap[i] == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mazeMap[i][j] = MAZE_WALL;
    mazeMap[currRow][currCol] = MAZE_BLANK;
    mazePointCount = 0;
    mazePointList = new(std::nothrow) MazePoint[rows * cols];
    if (mazePointList == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    generateMaze();
}

/*
 * Function Name:    ~MyList
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
Maze::~Maze()
{
    for (int i = 0; i < rows; i++)
        delete[] mazeMap[i];
    delete[] mazeMap;
    delete[] mazePointList;
}

/*
 * Function Name:    output
 * Function:         Output maze
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Maze::output(void)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == startRow && j == startCol)
                std::cout << "始";
            else if (i == targetRow && j == targetCol)
                std::cout << "终";
            else  if (mazeMap[i][j] == MAZE_BLANK)
                std::cout << "  ";
            else if (mazeMap[i][j] == MAZE_WALL)
                std::cout << "■";
            else if (mazeMap[i][j] == MAZE_PATH)
                std::cout << "×";
        }
        std::cout << std::endl;
    }
}

/*
 * Function Name:    recursiveBacktracking
 * Function:         Recursive backtracking pathfinding
 * Input Parameters: void
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Maze::recursiveBacktracking(void)
{
    /* Create a two dimensional array to mark whether each position has been visited */
    bool** visited = new(std::nothrow) bool* [rows];
    if (visited == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = new(std::nothrow) bool[cols];
        if (visited[i] == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        for (int j = 0; j < cols; j++)
            visited[i][j] = false;
    }

    /* Call the recursive pathfinding function to search for a path */
    bool pathFound = recursivePathfinding(startRow, startCol, visited);
    if (pathFound) {
        mazeMap[startRow][startCol] = MAZE_PATH;
        path.push({ startRow, startCol });
    }

    /* Free up dynamic memory */
    for (int i = 0; i < rows; i++)
        delete[] visited[i];
    delete[] visited;

    /* Return whether a path has been found */
    return pathFound;
}

/*
 * Function Name:    DFS
 * Function:         Depth-First Search
 * Input Parameters: void
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Maze::DFS(void)
{
    /* Create a two dimensional array to mark whether each position has been visited */
    bool** visited = new(std::nothrow) bool* [rows];
    if (visited == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = new(std::nothrow) bool[cols];
        if (visited[i] == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        for (int j = 0; j < cols; j++)
            visited[i][j] = false;
    }

    /* Initialize the stack with the starting point */
    Coordinate start{ startRow ,startCol };
    MyStack<Coordinate> DFSPath;
    DFSPath.push(start);
    mazeMap[startRow][startCol] = MAZE_PATH;

    /* DFS algorithm */
    while (!DFSPath.isEmpty()) {
        /* Get current point */
        Coordinate current;
        DFSPath.getTop(current);
        currRow = current.row;
        currCol = current.col;

        /* Found the target, the path is complete */
        if (currRow == targetRow && currCol == targetCol) {
            while (!DFSPath.isEmpty()) {
                Coordinate tempCoord;
                DFSPath.pop(tempCoord);
                path.push(tempCoord);
            }
            for (int i = 0; i < rows; i++)
                delete[] visited[i];
            delete[] visited;
            return true;
        }

        /* Try moving in each of the four directions */
        bool found = false;
        for (int dir = Up; dir <= Right; dir++) {
            int newRow = currRow, newCol = currCol;
            if (dir == Up)
                newRow--;
            else if (dir == Down)
                newRow++;
            else if (dir == Left)
                newCol--;
            else if (dir == Right)
                newCol++;
            if (isValid(newRow, newCol) && mazeMap[newRow][newCol] == MAZE_BLANK && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                Coordinate next;
                next.row = newRow;
                next.col = newCol;
                DFSPath.push(next);
                mazeMap[newRow][newCol] = MAZE_PATH;
                found = true;
                break;
            }
        }

        /* If there are no valid neighbors to move, backtrack */
        if (!found) {
            DFSPath.pop(current);
            mazeMap[current.row][current.col] = MAZE_BLANK;
        }
    }

    /* No path found */
    for (int i = 0; i < rows; i++)
        delete[] visited[i];
    delete[] visited;
    return false;
}

/*
 * Function Name:    BFS
 * Function:         Breadth-First Search
 * Input Parameters: void
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Maze::BFS(void)
{
    /* Create a two dimensional array to mark whether each position has been visited */
    bool** visited = new(std::nothrow) bool* [rows];
    if (visited == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = new(std::nothrow) bool[cols];
        if (visited[i] == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        for (int j = 0; j < cols; j++)
            visited[i][j] = false;
    }

    /* Create a two dimensional array to keep track of parent cells */
    Coordinate** parent = new(std::nothrow) Coordinate * [rows];
    if (parent == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < rows; i++) {
        parent[i] = new(std::nothrow) Coordinate[cols];
        if (parent[i] == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        for (int j = 0; j < cols; j++)
            parent[i][j] = { -1,-1 };
    }

    /* Start from the initial cell and mark it as visited */
    MyQueue<Coordinate> queue;
    Coordinate start = { startRow, startCol };
    visited[startRow][startCol] = true;
    queue.enQueue(start);

    /* BFS algorithm */
    while (!queue.isEmpty()) {
        /* Dequeue a cell from the queue */
        Coordinate current;
        queue.deQueue(current);

        /* If we have reached the target, backtrack to find the path */
        if (current.row == targetRow && current.col == targetCol) {
            while (!(current.row == startRow && current.col == startCol)) {
                path.push(current);
                mazeMap[current.row][current.col] = MAZE_PATH;
                current = parent[current.row][current.col];
            }
            path.push({ startRow, startCol });
            mazeMap[startRow][startCol] = MAZE_PATH;
            for (int i = 0; i < rows; i++) {
                delete[] visited[i];
                delete[] parent[i];
            }
            delete[] visited;
            delete[] parent;
            return true;
        }

        /* Explore neighbors */
        const int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dx[i], newCol = current.col + dy[i];
            if (isValid(newRow, newCol) && mazeMap[newRow][newCol] == MAZE_BLANK && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = current;
                queue.enQueue({ newRow, newCol });
            }
        }
    }

    /* No path found */
    for (int i = 0; i < rows; i++) {
        delete[] visited[i];
        delete[] parent[i];
    }
    delete[] visited;
    delete[] parent;
    return false;
}

/*
 * Function Name:    AStar
 * Function:         A* Search
 * Input Parameters: void
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Maze::AStar(void)
{
    /* Create a two dimensional array to mark whether each position has been visited */
    bool** visited = new(std::nothrow) bool* [rows];
    if (visited == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = new(std::nothrow) bool[cols];
        if (visited[i] == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        for (int j = 0; j < cols; j++)
            visited[i][j] = false;
    }

    /* Create a two dimensional array to keep track of parent cells */
    Coordinate** parent = new(std::nothrow) Coordinate * [rows];
    if (parent == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < rows; i++) {
        parent[i] = new(std::nothrow) Coordinate[cols];
        if (parent[i] == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
        for (int j = 0; j < cols; j++)
            parent[i][j] = { -1,-1 };
    }

    /* Define a lambda function for comparing the estimated total cost of two states */
    auto compareF = [](const AStarNode& a, const AStarNode& b) { return a.totalCost > b.totalCost; };

    /* Initialize the start node and the target node */
    AStarNode startNode = { startRow, startCol, 0, 0 };
    AStarNode targetNode = { targetRow, targetCol, 0, 0 };

    /* Use a priority queue to store the search states */
    MyPriorityQueue<AStarNode> openSet(rows * cols);

    /* Add the start node to the openSet */
    startNode.totalCost = abs(targetNode.row - startNode.row) + abs(targetNode.col - startNode.col);
    openSet.insert(startNode);

    /* A-Star algorithm */
    while (!openSet.isEmpty()) {
        /* If the current node is the target node, it means the path has been found */
        AStarNode currentNode;
        openSet.remove(currentNode);
        if (currentNode.row == targetNode.row && currentNode.col == targetNode.col) {
            Coordinate currentCoord = { currentNode.row, currentNode.col };
            while (!(currentCoord.row == startRow && currentCoord.col == startCol)) {
                path.push(currentCoord);
                mazeMap[currentCoord.row][currentCoord.col] = MAZE_PATH;
                currentCoord = parent[currentCoord.row][currentCoord.col];
            }
            path.push({ startRow, startCol });
            mazeMap[startRow][startCol] = MAZE_PATH;
            for (int i = 0; i < rows; i++) {
                delete[] visited[i];
                delete[] parent[i];
            }
            delete[] visited;
            delete[] parent;
            return true;
        }
        visited[currentNode.row][currentNode.col] = true;

        /* Represent offsets for the four directions */
        const int dr[] = { -1, 1, 0, 0 }, dc[] = { 0, 0, -1, 1 };
        for (int i = 0; i < 4; i++) {
            int newRow = currentNode.row + dr[i], newCol = currentNode.col + dc[i];
            if (isValid(newRow, newCol) && mazeMap[newRow][newCol] == MAZE_BLANK && !visited[newRow][newCol]) {
                AStarNode neighborNode = { newRow, newCol, currentNode.accumuCost + 1, 0 };
                neighborNode.totalCost = neighborNode.accumuCost + abs(targetNode.row - newRow) + abs(targetNode.col - newCol);
                if (!openSet.insert(neighborNode)) {
                    openSet.remove(neighborNode);
                    if (neighborNode.totalCost < currentNode.totalCost)
                        openSet.insert(neighborNode);
                }
                parent[newRow][newCol] = { currentNode.row, currentNode.col };
            }
        }
    }

    /* No path found */
    for (int i = 0; i < rows; i++) {
        delete[] visited[i];
        delete[] parent[i];
    }
    delete[] visited;
    delete[] parent;
    return false;
}

/*
 * Function Name:    inputOddInteger
 * Function:         Input an odd integer
 * Input Parameters: int lowerLimit
 *                   int upperLimit
 *                   const char* prompt
 * Return Value:     an odd integer
 */
int inputOddInteger(int lowerLimit, int upperLimit, const char* prompt)
{
    while (true) {
        std::cout << "请输入" << prompt << " (奇数) [整数范围: " << lowerLimit << "~" << upperLimit << "]: ";
        double tempInput;
        std::cin >> tempInput;
        if (std::cin.good() && tempInput == static_cast<int>(tempInput) && tempInput >= lowerLimit && tempInput <= upperLimit && static_cast<int>(tempInput) % 2) {
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
    std::cout << std::endl << ">>> 迷宫寻路算法: [1]递归回溯搜索算法 [2]深度优先搜索(DFS)算法 [3]广度优先搜索(BFS)算法 [4]A*搜索算法" << std::endl;
    std::cout << std::endl << "请选择迷宫寻路算法: ";
    char optn;
    while (true) {
        optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if (optn >= '1' && optn <= '4') {
            std::cout << "[" << optn << "]" << std::endl << std::endl;
            return optn - '0';
        }
    }
}

/*
 * Function Name:    mazeGame
 * Function:         Initialize the maze and find a path
 * Input Parameters: void
 * Return Value:     void
 */
void mazeGame(void)
{
    /* System entry prompt */
    std::cout << "+-------------+" << std::endl;
    std::cout << "|  迷宫游戏   |" << std::endl;
    std::cout << "|  Maze Game  |" << std::endl;
    std::cout << "+-------------+" << std::endl << std::endl;
    std::cout << ">>> 本程序基于随机Prim生成算法生成迷宫地图" << std::endl << std::endl;

    /* Input the size of the maze map */
    int mazeRows = inputOddInteger(mazeSizeLowerLimit, mazeSizeUpperLimit, "迷宫地图行数");
    std::cout << std::endl;
    int mazeCols = inputOddInteger(mazeSizeLowerLimit, mazeSizeUpperLimit, "迷宫地图列数");
    std::cout << std::endl;

    /* Initialize the maze */
    Maze maze(mazeRows, mazeCols, mazeStartRow, mazeStartCol, mazeRows - 2, mazeCols - 2);

    /* Output the original maze map */
    std::cout << ">>> 迷宫地图" << std::endl << std::endl;
    maze.output();

    /* Select a pathfinding algorithm */
    LARGE_INTEGER tick, begin, end;
    QueryPerformanceFrequency(&tick);
    int optn = selectOptn();
    QueryPerformanceCounter(&begin);
    if(optn == 1)
        maze.recursiveBacktracking();
    else if(optn == 2)
        maze.DFS();
    else if(optn == 3)
        maze.BFS();
    else if (optn == 4)
        maze.AStar();
    QueryPerformanceCounter(&end);

    /* Output the maze path map */
    maze.output();

    /* Output the maze path */
    if (maze.getPath().isEmpty()) {
        std::cout << std::endl << ">>> 未找到迷宫路径" << std::endl << std::endl;
        return;
    }
    std::cout << std::endl << ">>> 迷宫路径（寻路时长: " << std::setiosflags(std::ios::fixed) << std::setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒" << "）" << std::endl << std::endl;
    while (!maze.getPath().isEmpty()) {
        Coordinate coord;
        maze.getPath().pop(coord);
        std::cout << "(" << coord.row << "," << coord.col << ")";
        if (maze.getPath().getSize() > 0)
            std::cout << " --> ";
    }
    std::cout << std::endl << std::endl;
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

    /* Initialize the maze and find a path */
    mazeGame();

    /* Wait for enter to quit */
    std::cout << "Press Enter to Quit" << std::endl;
    while (_getch() != '\r')
        continue;

    /* Program ends */
    return 0;
}