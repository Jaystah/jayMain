#include <iostream>
#include <vector>
#include <stack>
class BSTNode
{
private:
    int value;
    BSTNode *left;
    BSTNode *right;
    int level;
    int col;

public:
    BSTNode(int value);
    bool exists()
    {
        if (value)
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    int getLevel()
    {
        return level;
    }
    void setLevel(int value)
    {
        level = value;
    }
    int getCol()
    {
        return col;
    }
    void setCol(int value)
    {
        col = value;
    }
    void setLeft(int val);
    void setRight(int val);
    BSTNode *getRight()
    {
        return right;
    }
    BSTNode *getLeft()
    {
        return left;
    }
    bool hasLeft()
    {
        return left != nullptr;
    }
    bool hasRight()
    {
        return right != nullptr;
    }
    int getVal()
    {
        return value;
    }
};

BSTNode::BSTNode(int value)
{
    this->value = value;
    left = nullptr;
    right = nullptr;
    level = 0;
    col = 0;
}

void BSTNode::setLeft(int val)
{
    left = new BSTNode(val);
}
void BSTNode::setRight(int val)
{
    right = new BSTNode(val);
}

class BST
{
public:
    BST();
    ~BST();
    void insertKey(int newKey);
    bool hasKey(int searchKey);
    void deleteTree(BSTNode *node);
    std::vector<int> inOrder();
    int getHeight()
    {
        return height;
    }
    void prettyPrint();

private:
    BSTNode *head = nullptr;
    int height;
    int level;
    int totalNodes;
    std::vector<BSTNode *> allnodes;
    void printLine(int width);
    void printLevel(int level);
    std::vector<BSTNode *> getVectorFromLevel(int level);
    void setTotalNodes(int num)
    {
        totalNodes = num;
    }
    int getTotalNodes()
    {
        return totalNodes;
    }
};

BST::BST()
{
    height = 0;
    level = 0;
    totalNodes = 0;
}
BST::~BST()
{
    deleteTree(head);
}
void BST::deleteTree(BSTNode *node)
{
    if (!node)
    {
        return;
    }

    deleteTree(node->getLeft());
    deleteTree(node->getRight());
    delete node;
}
void BST::insertKey(int newKey)
{
    int nodelevel = 0;
    BSTNode *curr = nullptr;
    if (head != nullptr)
    {
        curr = head;
        level = 1;
        for (int i = 0; i < height; i++)
        {

            if (newKey > curr->getVal())
            {
                if (curr->hasRight())
                {
                    curr = curr->getRight();

                    level++;
                }
                else
                {
                    setTotalNodes(getTotalNodes() + 1);
                    curr->setRight(newKey);
                    nodelevel = level;
                    nodelevel++;
                    if (!curr->hasLeft())
                    {
                        level++;
                    }
                    curr->getRight()->setLevel(nodelevel);
                    allnodes.push_back(curr->getRight());
                    break;
                }
            }
            else if (newKey < curr->getVal())
            {
                if (curr->hasLeft())
                {
                    curr = curr->getLeft();

                    level++;
                }
                else
                {
                    setTotalNodes(getTotalNodes() + 1);
                    curr->setLeft(newKey);
                    nodelevel = level;
                    nodelevel++;
                    if (!curr->hasRight())
                    {
                        level++;
                    }
                    curr->getLeft()->setLevel(nodelevel);
                    allnodes.push_back(curr->getLeft());
                    break;
                }
            }
        }
        if (level > height)
        {
            height = level;
        }
    }
    else
    {
        setTotalNodes(getTotalNodes() + 1);
        head = new BSTNode(newKey);
        head->setLevel(1);
        allnodes.push_back(head);
        height++;
        level++;
    }
}

bool BST::hasKey(int searchKey)
{
    BSTNode *curr = nullptr;
    curr = head;
    for (int i = 0; i < height; i++)
    {
        if (curr == nullptr)
        {
            return false;
        }
        else if (curr->getVal() == searchKey)
        {
            return true;
        }
        else if (searchKey < curr->getVal())
        {
            curr = curr->getLeft();
        }
        else if (searchKey > curr->getVal())
        {
            curr = curr->getRight();
        }
    }
    return false;
}
std::vector<int> BST::inOrder()
{
    BSTNode *curr = nullptr;
    std::vector<int> sortedVec;
    std::stack<BSTNode *> sortStack;
    bool done = false;
    curr = head;
    if (this->getHeight() == 0)
    {
        sortedVec.resize(0);
        return sortedVec;
    }
    while (!done)
    {
        while (curr != nullptr)
        {
            sortStack.push(curr);
            curr = curr->getLeft();
        }

        if (curr == nullptr && !sortStack.empty())
        {
            BSTNode *temp = sortStack.top();
            sortStack.pop();
            sortedVec.push_back(temp->getVal());
            curr = temp->getRight();
        }
        if (curr == nullptr && sortStack.empty())
        {
            done = true;
        }
    }
    return sortedVec;
}
void BST::printLine(int width)
{
    int dashAmount = width * 5 + 1;
    for (int i = 0; i < dashAmount; i++)
    {
        std::cout << '-';
    }
    std::cout << std::endl;
}
void BST::printLevel(int level)
{
    std::vector<BSTNode *> valsFromLevel = getVectorFromLevel(level);
    bool isInLevel = false;
    for (int i = 1; i <= getTotalNodes(); i++)
    {
        for (int j = 0; j < valsFromLevel.size(); j++)
        {
            if (i == valsFromLevel.at(j)->getCol())
            {
                if (i == getTotalNodes()) //last element
                {
                    if (valsFromLevel.at(j)->getVal() < 0 || valsFromLevel.at(j)->getVal() >= 10)
                    {
                        std::cout << "|  " << valsFromLevel.at(j)->getVal() << '|';
                        isInLevel = true;
                        break;
                    }
                    else
                    {
                        std::cout << "|   " << valsFromLevel.at(j)->getVal() << '|';
                        isInLevel = true;
                        break;
                    }
                }
                else
                {
                    if (valsFromLevel.at(j)->getVal() < 0 || valsFromLevel.at(j)->getVal() >= 10)
                    {
                        std::cout << "|  " << valsFromLevel.at(j)->getVal();
                        isInLevel = true;
                        break;
                    }
                    else
                    {
                        std::cout << "|   " << valsFromLevel.at(j)->getVal();
                        isInLevel = true;
                    }
                }
            }
        }
            if (!isInLevel)
            {
                if (i == getTotalNodes())
                {
                    std::cout << "|    |";
                }
                else
                {
                    std::cout << "|    ";
                }
            }
            isInLevel = false;
        }
        std::cout << std::endl;
    }
    std::vector<BSTNode *> BST::getVectorFromLevel(int level)
    {

        std::vector<int> sortedNodes = inOrder();
        std::vector<BSTNode *> vecFromLevel;

        for (int i = 0; i < sortedNodes.size(); i++)
        {
            for (int j = 0; j < allnodes.size(); j++)
            {
                if (sortedNodes.at(i) == allnodes.at(j)->getVal())
                {
                    if (allnodes.at(j)->getLevel() == level)
                    {
                        vecFromLevel.push_back(allnodes.at(j));
                    }
                }
            }
        }

        return vecFromLevel;
    }
    void BST::prettyPrint()
    {
        int width = getTotalNodes();
        int height = getHeight();

        std::vector<int> sortedNodes = inOrder();

        for (int i = 0; i < allnodes.size(); i++)
        {
            for (int j = 0; j < sortedNodes.size(); j++)
            {
                if (sortedNodes.at(j) == allnodes.at(i)->getVal())
                {
                    allnodes.at(i)->setCol(j + 1);
                }
            }
        }

        for (int i = 1; i <= height; i++)
        {
            printLine(width);
            printLevel(i);
        }
        if (width >= 1)
        {
            printLine(width);
        }
    }

    int main()
    {
        BST bst;
        int num;
        int srch;
        std::cout << "Enter the numbers to be stored: ";
        std::cin >> num;

        if (!std::cin.fail())
        {
            bst.insertKey(num);
        }
        while (!std::cin.fail())
        {
            std::cin >> num;
            if (!std::cin.fail())
            {
                bst.insertKey(num);
            }
        }

        std::cout << "The numbers in sorted order: ";
        std::vector<int> test = bst.inOrder();
        if (!test.empty())
        {
            for (int i = 0; i < test.size(); i++)
            {
                std::cout << test.at(i) << ' ';
            }
        }
        std::cout << std::endl;

        bst.prettyPrint();

        return 0;
    }