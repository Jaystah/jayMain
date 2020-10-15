#include <iostream>
#include "BST.h"

int countSymbols(int num)
{
    int count = 0;
    if (num < 0)
    {
        num *= -1;
        count++;
    }
    while (num > 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

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
    calcInOrder(head);
    std::vector<int> temp = sortedVec;
    sortedVec.clear();
    return temp;
}
void BST::calcInOrder(BSTNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    calcInOrder(node->getLeft());
    sortedVec.push_back(node->getVal());
    calcInOrder(node->getRight());
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
                int spaces = (countSymbols(valsFromLevel.at(j)->getVal()) - 4) * -1;
                if (i == getTotalNodes()) //last element
                {
                    std::cout << "|";

                    for (int i = 0; i < spaces; i++)
                    {
                        std::cout << ' ';
                    }

                    std::cout << valsFromLevel.at(j)->getVal() << '|';
                    isInLevel = true;
                    break;
                }
                else
                {
                    std::cout << "|";

                    for (int i = 0; i < spaces; i++)
                    {
                        std::cout << ' ';
                    }

                    std::cout << valsFromLevel.at(j)->getVal();
                    isInLevel = true;
                    break;
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
