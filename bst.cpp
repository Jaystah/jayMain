#include <iostream>
#include <vector>
#include <stack>
class BSTNode
{
private:
    int value;
    BSTNode *left = nullptr;
    BSTNode *right = nullptr;

public:
    BSTNode(int val);
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

BSTNode::BSTNode(int val)
{
    value = val;
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
    std::vector<int> inOrder();
    int getHeight()
    {
        return height;
    }

private:
    std::vector<int> allNumbers;
    BSTNode *head = nullptr;
    int height = 0;
    int level = 0;
};

BST::BST()
{
}
BST::~BST()
{
}
void BST::insertKey(int newKey)
{
    BSTNode *curr = nullptr;
    if (head != nullptr)
    {
        curr = head;
        for (int i = 0; i < height; i++)
        {

            if (newKey > curr->getVal())
            {
                if (curr->hasRight())
                {
                    curr = curr->getRight();
                    if (level > height)
                    {

                        level++;
                    }
                }
                else
                {
                    curr->setRight(newKey);
                    if (!curr->hasLeft())
                    {
                        level++;
                    }
                    break;
                }
            }
            else if (newKey < curr->getVal())
            {
                if (curr->hasLeft())
                {
                    curr = curr->getLeft();
                    if (level > height)
                    {

                        level++;
                    }
                }
                else
                {
                    curr->setLeft(newKey);
                    if (!curr->hasRight())
                    {
                        level++;
                    }
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
        head = new BSTNode(newKey);
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
    if(this->getHeight() == 0){
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
int main()
{
    BST bst;
    int num;
    char numChar;
    int srch;
    std::cout << "Enter the numbers to be stored (end with a letter): ";
    std::cin >> numChar;
    std::cout << numChar - '0' << std::endl;

      if(num){
            bst.insertKey(num);
        }
    while (num)
    {
        std::cin >> num;
        if(num){
            bst.insertKey(num);
        }
        
    }
    std::cout << std::endl;
    std::cout << "Which number do you want to look up? ";
    std::cin.clear();
    std::cin.ignore();
    std::cin >> srch;
    if (bst.hasKey(srch))
    {
        std::cout << srch << " is in the tree: yes" << std::endl;
    }
    else
    {
        std::cout << srch << " is in the tree: no" << std::endl;
    }
    std::cout << "The numbers in sorted order: ";
    std::vector<int> test = bst.inOrder();
    if(!test.empty()){
            for (int i = 0; i < test.size(); i++)
    {
        std::cout << test.at(i) << ' ';
    }
    }

    std::cout << std::endl;
    std::cout << "Height of the tree: " << bst.getHeight() << std::endl;

    return 0;
}